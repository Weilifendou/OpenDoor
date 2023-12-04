using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.IO;
using System.Security.Cryptography;
using Windows.Devices.Bluetooth;


namespace Template
{
    public partial class Form1 : Form
    {

        private BleCore ble;
        private delegate void RenewInterfaceHandler();
        private const int FrameSize = 128;
        private const int BuffSize = 200;
        private byte[] ReadFrame;
        private byte[] SendBuff;
        private byte[] ReceiveBuff;
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
            ble = new BleCore();
            ble.DeviceWatcherChanged += Ble_DeviceWatcherChanged;
            ble.DeviceReceiveData += Ble_DeviceReceiveData;
            ble.DeviceStatusChanged += Ble_DeviceStatusChanged;
            ReadFrame = new byte[FrameSize + 2];
            SendBuff = new byte[BuffSize];
            ReceiveBuff = new byte[BuffSize];
        }

        private void Ble_DeviceStatusChanged(bool status)
        {
            BeginInvoke(new Action(() =>
            {
                if (status)
                {
                    buttonOperate.Text = "断开";
                    comboBoxDeviceList.Enabled = false;
                    buttonReset.Enabled = true;
                    buttonDownload.Enabled = true;
                    buttonSend.Enabled = true;
                    buttonLoadFile.Enabled = true;
                }
                else
                {
                    buttonOperate.Text = "连接";
                    comboBoxDeviceList.Enabled = true;
                    buttonReset.Enabled = false;
                    buttonDownload.Enabled = false;
                    buttonSend.Enabled = false;
                    buttonLoadFile.Enabled = false;
                }

            }));
        }

        private void Ble_DeviceReceiveData(byte[] data)
        {
            ReceiveBuff = data;
            BeginInvoke(new Action(() =>
            {
                if (checkBoxReceive.Checked)
                {
                    textBoxReceive.AppendText(Encoding.Default.GetString(data));
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

        private void Form1_Load(object sender, EventArgs e)
        {
            ble.StartBleDeviceWatcher();
        }

        private void SendFile(byte[] dat, int funCode)
        {
            int s = 0;
            int header = 7;
            int datLength = dat.Length + header;
            SendBuff[s++] = 0x55;
            SendBuff[s++] = 0xaa;
            SendBuff[s++] = 0x55;
            SendBuff[s++] = 0xaa;
            SendBuff[s++] = (byte)(datLength >> 8);
            SendBuff[s++] = (byte)datLength;
            SendBuff[s++] = (byte)funCode;
            for (int i = 0; i < dat.Length; i++)
                SendBuff[s++] = dat[i];
            //int crc = CRCCheckout(SendBuff, datLength);
            //SendBuff[s++] = (byte)(crc >> 8);
            //SendBuff[s++] = (byte)crc;
            byte[] hash = new MD5CryptoServiceProvider().ComputeHash(SendBuff, 0, datLength);
            foreach (byte b in hash)
            {
                SendBuff[s++] = b;
            }
            ble.Write(SendBuff);

        }
        private void SendData(byte[] dat, int funCode)
        {
            int s = 0;
            int header = 7;
            int datLength = dat.Length + header;
            SendBuff[s++] = 0x55;
            SendBuff[s++] = 0xaa;
            SendBuff[s++] = 0x55;
            SendBuff[s++] = 0xaa;
            SendBuff[s++] = (byte)(datLength >> 8);
            SendBuff[s++] = (byte)datLength;
            SendBuff[s++] = (byte)funCode;
            for (int i = 0; i < dat.Length; i++)
                SendBuff[s++] = dat[i];
            int crc = CRCCheckout(SendBuff, datLength);
            SendBuff[s++] = (byte)(crc >> 8);
            SendBuff[s++] = (byte)crc;
            ble.Write(SendBuff);

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
                if (Progress > FileLength)
                {
                    Progress = FileLength;
                    labelState.Text = "写入完成";
                    buttonDownload.Text = "写入固件";
                    buttonDownload.Enabled = true;
                    buttonOperate.Enabled = true;
                    buttonReset.Enabled = true;
                }
                var percent = Progress * 100.0 / FileLength;
                labelState.Text = "正在写入，进度为 " + percent.ToString("00.00") + "%";
                progressBar.Value = (int)percent;
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
                buttonReset.Enabled = true;
            }

        }
        private void buttonLoadFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "BIN文件|*.bin";
            DialogResult result = dialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                FilePath = dialog.FileName;
                textBoxFilePath.Text = FilePath;
                buttonOperate.Enabled = true;
                comboBoxDeviceList.Enabled = true;
            }

        }

        private void buttonOperate_Click(object sender, EventArgs e)
        {
            if (!ble.status)
            {
                string deviceName = comboBoxDeviceList.Text;
                var device = ble.deviceList.Where(u => u.Name == deviceName).FirstOrDefault();
                ble.StopBleDeviceWathcer();
                ble.FindService(device);
            }
            else
            {
                ble.DeviceDispose();
            }
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            SendData(new byte[0], 0xff);
        }

        private void buttonDownload_Click(object sender, EventArgs e)
        {
            if(FilePath == null) return;
            buttonDownload.Enabled = false;
            buttonOperate.Enabled = false;
            buttonReset.Enabled = false;
            buttonDownload.Text = "正在写入...";
            FileLength = 0;
            Progress = 0;
            SendThread = new Thread(new ThreadStart(() =>
            {
                using (FileStream fs = new FileStream(FilePath, FileMode.Open, FileAccess.Read))
                {
                    FileLength = fs.Length;
                    byte[] buffer = new byte[2];
                    buffer[0] = (byte)(FileLength >> 8);
                    buffer[1] = (byte)FileLength;
                    SendFile(buffer, 1);
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
                    while (fs.Read(ReadFrame, 0, FrameSize) > 0)
                    {
                        ReadFrame[FrameSize] = (byte)(Progress >> 8);
                        ReadFrame[FrameSize + 1] = (byte)Progress;
                        Overtime = 0;
                        SentFlag = false;
                        do
                        {
                            if (!SentFlag)
                            {
                                SendFile(ReadFrame, 2);
                                ReceiveBuff[0] = 0;
                                TimeDelayer = 0;
                                SentFlag = true;
                            }
                            else
                            {
                                if (ReceiveBuff[0] == 0xaa)
                                {
                                    ReceiveBuff[0] = 0;
                                    SentFlag = false;
                                }
                            }
                        } while (ReceiveBuff[0] != 0x55);
                        Progress += FrameSize;
                        for (int i = 0; i < ReadFrame.Length; i++) ReadFrame[i] = 0xff;
                        BeginInvoke(new RenewInterfaceHandler(RenewInterface));
                    }
                    SendFile(new byte[0], 3);
                    TimerThread.Abort();

                }
            }));
            SendThread.Start();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            ble.DeviceDispose();
            SendThread?.Abort();
            TimerThread?.Abort();
            Environment.Exit(0);
        }

        private void checkBoxTopMost_CheckedChanged(object sender, EventArgs e)
        {
            TopMost = !TopMost;
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            byte[] buff = null;
            string text = textBoxSend.Text;
            if (radioButtonAbc.Checked)
            {
                buff = Encoding.Default.GetBytes(text);
            }
            else if (radioButtonHex.Checked)
            {
                buff = ToBytesFromHexString(text);
            }
            ble.Write(buff);
        }
        private byte[] ToBytesFromHexString(string hexString)
        {
            try
            {
                //以 ' ' 分割字符串，并去掉空字符
                string[] chars = hexString.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                byte[] returnBytes = new byte[chars.Length];
                //逐个字符变为16进制字节数据
                for (int i = 0; i < chars.Length; i++)
                {
                    returnBytes[i] = Convert.ToByte(chars[i], 16);
                }
                return returnBytes;
            }
            catch (Exception)
            {
                MessageBox.Show("注意输入正确十六进制字符，谢谢合作");
                return new byte[1];
            }
        }

        private void buttonSearch_Click(object sender, EventArgs e)
        {
            ble.StartBleDeviceWatcher();
        }

        private void buttonClearReceive_Click(object sender, EventArgs e)
        {
            textBoxReceive.Text = "";
        }

        private void buttonClearSend_Click(object sender, EventArgs e)
        {
            textBoxSend.Text = "";
        }
    }
}
