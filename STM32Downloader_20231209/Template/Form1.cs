using System;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Security.Cryptography;
using Windows.Devices.Bluetooth;


namespace Template
{
    public partial class Form1 : Form
    {
        private BleCore ble;
        private delegate void RenewInterfaceHandler();
        private const int SppFrame = 1024;
        private const int BleFrame = 128;
        private byte[] SppReadFrame;
        private byte[] SppSendBuff;
        private byte[] SppReceiveBuff;
        private byte[] BleReadFrame;
        private byte[] BleSendBuff;
        private byte[] BleReceiveBuff;
        private string FilePath;
        private long FileLength;
        private long Progress;
        private bool SentFlag;
        private int Overtime;
        private int TimeDelayer;
        private Thread SendThread;
        private Thread TimerThread;
        public Form1()
        {
            InitializeComponent();

            SppReadFrame = new byte[SppFrame + 2];
            SppSendBuff = new byte[SppFrame + 30];
            SppReceiveBuff = new byte[SppFrame + 30];

            string[] portList = SerialPort.GetPortNames();
            foreach (string s in portList)
            {
                comboBoxPortList.Items.Add(s);
            }

            BleReadFrame = new byte[BleFrame + 2];
            BleSendBuff = new byte[BleFrame + 30];
            BleReceiveBuff = new byte[BleFrame + 30];

            ble = new BleCore();
            ble.DeviceWatcherChanged += Ble_DeviceWatcherChanged;
            ble.DeviceReceiveData += Ble_DeviceReceiveData;
            ble.DeviceStatusChanged += Ble_DeviceStatusChanged;
        }

        private void Ble_DeviceStatusChanged(bool status)
        {
            BeginInvoke(new Action(() =>
            {
                if (status)
                {
                    buttonOperate.Text = "断开";
                    buttonResetSpp.Enabled = true;
                    buttonResetBle.Enabled = true;
                    buttonDownload.Enabled = true;
                    buttonSend.Enabled = true;
                    buttonLoadFile.Enabled = true;
                }
                else
                {
                    buttonOperate.Text = "连接";
                    buttonResetSpp.Enabled = false;
                    buttonResetBle.Enabled = false;
                    buttonDownload.Enabled = false;
                    buttonSend.Enabled = false;
                    buttonLoadFile.Enabled = false;
                }

            }));
        }


        private void Ble_DeviceWatcherChanged(BluetoothLEDevice bluetoothLEDevice)
        {
            BeginInvoke(new Action(() =>
            {
                comboBoxDeviceList.Items.Add(bluetoothLEDevice.Name);
            }));
        }

        private void SendData(byte[] dat, byte[] sendBuff, int funCode, bool type)
        {
            int s = 0;
            int header = 7;
            int datLength = dat.Length + header;
            sendBuff[s++] = 0x55;
            sendBuff[s++] = 0xaa;
            sendBuff[s++] = 0x55;
            sendBuff[s++] = 0xaa;
            sendBuff[s++] = (byte)(datLength >> 8);
            sendBuff[s++] = (byte)datLength;
            sendBuff[s++] = (byte)funCode;
            for (int i = 0; i < dat.Length; i++)
                sendBuff[s++] = dat[i];
            if (type)
            {
                int crc = CRCCheckout(sendBuff, datLength);
                sendBuff[s++] = (byte)(crc >> 8);
                sendBuff[s++] = (byte)crc;
            }
            else
            {
                byte[] hash = new MD5CryptoServiceProvider().ComputeHash(sendBuff, 0, datLength);
                foreach (byte b in hash)
                {
                    sendBuff[s++] = b;
                }
            }
            if (radioButtonSpp.Checked)
            {
                serialPort.Write(sendBuff, 0, sendBuff.Length);
            }
            else if(radioButtonBle.Checked)
            {
                ble.Write(sendBuff);
            }

        }
        private int CRCCheckout(byte[] dat, int length)
        {
            int crc = 0xffff;
            for (int i = 0; i < length; i++)
            {
                int temp = dat[i] & 0x00ff;
                crc ^= temp;
                for (int j = 0; j < 8; j++)
                {
                    if ((crc & 0x0001) == 1)
                    {
                        crc >>= 1;
                        crc ^= 0xa001;
                    }
                    else
                    {
                        crc >>= 1;
                    }
                }
            }
            return crc;
        }
        private void RenewInterface()
        {
            if (Overtime < 2)
            {
                var percent = Progress * 100.0 / FileLength;
                if (Progress >= FileLength)
                {
                    Progress = FileLength;
                    labelState.Text = "写入完成，进度为 " + percent.ToString("00.00") + "%";
                    myProgressBar.Progress = (int)percent;
                    labelState.Text = "写入完成";
                    buttonDownload.Text = "写入固件";
                    buttonDownload.Enabled = true;
                    buttonOperate.Enabled = true;
                    buttonResetSpp.Enabled = true;
                    buttonResetBle.Enabled = true;
                }
                else
                {
                    buttonDownload.Text = "正在写入";
                    labelState.Text = "正在写入，进度为 " + percent.ToString("00.00") + "%";
                    myProgressBar.Progress = (int)percent;
                }
            }
            else if (Overtime < 6)
            {
                labelState.Text = "无响应，正在尝试第" + Overtime.ToString() + "次写入";
            }
            else
            {
                labelState.Text = "写入超时";
                buttonDownload.Text = "写入固件";
                buttonDownload.Enabled = true;
                buttonOperate.Enabled = true;
                buttonResetSpp.Enabled = true;
                buttonResetBle.Enabled = true;
            }

        }
        private void OperateSpp()
        {
            try
            {
                if (!serialPort.IsOpen)
                {
                    serialPort.PortName = comboBoxPortList.Text;
                    serialPort.Open();
                    buttonOperate.Text = "关闭";
                    comboBoxPortList.Enabled = false;
                    buttonDownload.Enabled = true;
                    buttonResetSpp.Enabled = true;
                    buttonResetBle.Enabled = true;
                    buttonSend.Enabled = true;
                }
                else
                {
                    serialPort.DiscardInBuffer();
                    serialPort.Close();
                    buttonOperate.Text = "连接";
                    comboBoxPortList.Enabled = true;
                    buttonDownload.Enabled = false;
                    buttonResetSpp.Enabled = false;
                    buttonResetBle.Enabled = false;
                    buttonSend.Enabled = false;
                }
            }
            catch (Exception)
            {
                MessageBox.Show("接口操作失败");
            }

        }
        private void OperateBle()
        {
            if (!ble.status)
            {
                string deviceName = comboBoxDeviceList.Text;
                comboBoxDeviceList.Enabled = false;
                var device = ble.deviceList.Where(u => u.Name == deviceName).FirstOrDefault();
                ble.StopBleDeviceWathcer();
                ble.FindService(device);
                comboBoxDeviceList.Enabled = false;
            }
            else
            {
                ble.DeviceDispose();
                comboBoxDeviceList.Enabled = true;
            }
        }
        private void SendFileFrame(byte[] readFrame, int frameSize)
        {
            SendThread = new Thread(new ThreadStart(() =>
            {
                using (FileStream fs = new FileStream(FilePath, FileMode.Open, FileAccess.Read))
                {
                    FileLength = fs.Length;
                    byte[] buffer = new byte[2];
                    buffer[0] = (byte)(FileLength >> 8);
                    buffer[1] = (byte)FileLength;
                    if (radioButtonSpp.Checked)
                    {
                        SendData(buffer, SppSendBuff, 1, false);
                    }
                    else if (radioButtonBle.Checked)
                    {
                        SendData(buffer, BleSendBuff, 1, false);
                    }
                    TimerThread = new Thread(new ThreadStart(() =>
                    {
                        while (true)
                        {
                            if (TimeDelayer >= 800)
                            {
                                TimeDelayer = 0;
                                SentFlag = false;
                                Overtime++;
                                BeginInvoke(new RenewInterfaceHandler(RenewInterface));
                                if (Overtime > 5)
                                {
                                    SendThread.Abort();
                                    TimerThread.Abort();
                                }
                            }
                            Thread.Sleep(1);
                            TimeDelayer++;
                        }
                    }));
                    TimerThread.Start();
                    while (fs.Read(readFrame, 0, frameSize) > 0)
                    {
                        readFrame[frameSize] = (byte)(Progress >> 8);
                        readFrame[frameSize + 1] = (byte)Progress;
                        Overtime = 0;
                        SentFlag = false;

                        if (radioButtonSpp.Checked)
                        {
                            do
                            {
                                if (!SentFlag)
                                {
                                    SendData(readFrame, SppSendBuff, 2, false);
                                    SppReceiveBuff[0] = 0;
                                    TimeDelayer = 0;
                                    SentFlag = true;
                                }
                                else
                                {
                                    if (SppReceiveBuff[0] == 0xaa)
                                    {
                                        SppReceiveBuff[0] = 0;
                                        SentFlag = false;
                                    }
                                }
                            } while (SppReceiveBuff[0] != 0x55);
                        }
                        else if (radioButtonBle.Checked)
                        {
                            do
                            {
                                if (!SentFlag)
                                {
                                    SendData(readFrame, BleSendBuff, 2, false);
                                    BleReceiveBuff[0] = 0;
                                    TimeDelayer = 0;
                                    SentFlag = true;
                                }
                                else
                                {
                                    if (BleReceiveBuff[0] == 0xaa)
                                    {
                                        BleReceiveBuff[0] = 0;
                                        SentFlag = false;
                                    }
                                }
                            } while (BleReceiveBuff[0] != 0x55);
                        }
                        Progress += frameSize;
                        for (int i = 0; i < readFrame.Length; i++) readFrame[i] = 0xff;
                        BeginInvoke(new RenewInterfaceHandler(RenewInterface));
                    }
                    if (radioButtonSpp.Checked)
                    {
                        SendData(new byte[0], SppSendBuff, 3, false);
                    }
                    else if (radioButtonBle.Checked)
                    {
                        SendData(new byte[0], BleSendBuff, 3, false);
                    }
                    TimerThread.Abort();
                }
            }));
            SendThread.Start();

        }
        private byte[] HexStringToByte(string hex)
        {
            try
            {
                string[] chars = hex.Split(new char[] { ' ' },
                    StringSplitOptions.RemoveEmptyEntries);
                byte[] b = new byte[chars.Length];
                for (int i = 0; i < chars.Length; i++)
                {
                    b[i] = Convert.ToByte(chars[i], 16);
                }
                return b;
            }
            catch (Exception)
            {
                MessageBox.Show("注意输入正确十六进制字符，谢谢合作");
                return new byte[1];
            }
        }
        private string AbcStringToByteString(string abc)
        {
            byte[] data = Encoding.Default.GetBytes(abc);
            string s = null;
            foreach (byte b in data)
            {
                s += b.ToString("X2") + " ";
            }
            return s;

        }
        private void Transform(bool check1, bool check2, TextBox textbox)
        {
            if (check1)
            {
                string hex = textbox.Text;
                textbox.Text = "";
                byte[] b = HexStringToByte(hex);
                textbox.Text = Encoding.Default.GetString(b);
            }
            else if (check2)
            {
                string abc = textbox.Text;
                textbox.Text = AbcStringToByteString(abc);
            }

        }
    }
}
