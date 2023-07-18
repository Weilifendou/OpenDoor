using System;
using System.IO;
using System.IO.Ports;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Template
{
    public partial class Form1 : Form
    {
        private const int FrameSize = 1024;
        private const int BuffSize = 1050;
        private delegate void RenewInterfaceHandler();
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
            ReadFrame = new byte[FrameSize+2];
            SendBuff = new byte[BuffSize];
            ReceiveBuff = new byte[BuffSize];
            string[] portList = SerialPort.GetPortNames();
            foreach (string s in portList)
            {
                comboBoxPortList.Items.Add(s);
            }
        }

        private void SendData(byte[] dat, int funCode)
        {
            int s = 0;
            int header = 7;
            int datLength = dat.Length + header;
            SendBuff[s++] =  0x55;
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
            serialPort.Write(SendBuff, 0, SendBuff.Length);

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
            //for (int i = 0; i < bbb.Length; i++)
            //{
            //    if (temp % 16 == 0) s += "\r\n";
            //    s += ReadFrame[i].ToString("X2");
            //    temp++;
            //}
            //textBox1.AppendText(s);
            if (Overtime < 2)
            {
                if (Progress > FileLength)
                {
                    Progress = FileLength;
                    buttonDownload.Text = "写入固件";
                    buttonDownload.Enabled = true;
                    buttonOperate.Enabled = true;
                }
                var temp = Progress * 100.0 / FileLength;
                labelState.Text = "正在写入，进度为 " + temp.ToString("00.00") + "%";
                progressBar.Value = (int)temp;
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
            }
            
        }
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int length = serialPort.BytesToRead;
            serialPort.Read(ReceiveBuff, 0, length);
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            SendData(new byte[0], 3);
        }

        private void buttonDownload_Click(object sender, EventArgs e)
        {
            buttonDownload.Enabled = false;
            buttonOperate.Enabled = false;
            buttonDownload.Text = "正在写入";
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
                    SendData(buffer, 1);
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
                                SendData(ReadFrame, 2);
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
                    SendData(new byte[0], 3);
                    TimerThread.Abort();

                }
            }));
            SendThread.Start();

        }
        private void OperatePort()
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
                    buttonReset.Enabled = true;
                }
                else
                {
                    serialPort.DiscardInBuffer();
                    serialPort.Close();
                    buttonOperate.Text = "打开";
                    comboBoxPortList.Enabled = true;
                    buttonDownload.Enabled = false;
                    buttonReset.Enabled = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("接口操作失败");
            }

        }
        private void buttonOperate_Click(object sender, EventArgs e)
        {
            OperatePort();
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
            }

        }


        private void checkBoxTopMode_CheckedChanged(object sender, EventArgs e)
        {
            TopMost = !TopMost;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {

            if (SendThread != null) SendThread.Abort();
            if (TimerThread != null) TimerThread.Abort();
            Environment.Exit(0);
        }
    }
}
