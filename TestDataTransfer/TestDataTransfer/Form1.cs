using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace TestDataTransfer
{
    public partial class Form1 : Form
    {
        private const int SppFrame = 128;
        private byte[] SppReadFrame;
        private byte[] SppSendBuff;
        private byte[] SppReceiveBuff;
        public Form1()
        {
            InitializeComponent();
            SppReadFrame = new byte[SppFrame + 2];
            SppSendBuff = new byte[SppFrame + 30];
            SppReceiveBuff = new byte[SppFrame + 30];
            var ports = SerialPort.GetPortNames();
            foreach(var s in ports)
            {
                comboBox1.Items.Add(s.ToString());
            }

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                if (!serialPort1.IsOpen)
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = 115200;
                    serialPort1.Open();
                }
                else
                {
                    serialPort1.Close();
                }
            }
            catch (Exception) { }
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

        private void SendData(byte[] dat, byte[] sendBuff, int funCode)
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
            {
                sendBuff[s++] = dat[i];
            }
            int crc = CRCCheckout(sendBuff, datLength);
            sendBuff[s++] = (byte)(crc >> 8);
            sendBuff[s++] = (byte)crc;
            serialPort1.Write(sendBuff, 0, sendBuff.Length);

        }
        private void button1_Click(object sender, EventArgs e)
        {
            Random random = new Random();
            int tem = random.Next(0, 1000); // 生成 -400 到 600 之间的随机数
            int hum = random.Next(0, 1000); // 生成 -400 到 600 之间的随机数
            byte[] buffer = new byte[4];
            buffer[0] = (byte)(tem >> 8);
            buffer[1] = (byte)tem;
            buffer[2] = (byte)(hum >> 8);
            buffer[3] = (byte)hum;
            SendData(buffer, SppSendBuff, 1);
        }
    }
}
