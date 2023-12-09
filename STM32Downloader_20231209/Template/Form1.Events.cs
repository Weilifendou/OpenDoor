using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Template
{
    public partial class Form1 : Form
    {

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Array.Clear(SppReceiveBuff, 0, SppReceiveBuff.Length);
            int length = serialPort.BytesToRead;
            byte[] buffer = new byte[length];
            serialPort.Read(buffer, 0, length);
            serialPort.DiscardInBuffer();
            SppReceiveBuff = buffer;
            BeginInvoke(new Action(() =>
            {
                if (checkBoxReceive.Checked)
                {
                    if (radioButtonRecAbc.Checked)
                    {
                        textBoxReceive.AppendText(Encoding.Default.GetString(SppReceiveBuff));
                        if (checkBoxNewLine.Checked)
                        {
                            textBoxReceive.AppendText("\r\n");
                        }
                    }
                    else if (radioButtonRecHex.Checked)
                    {
                        foreach (byte b in SppReceiveBuff)
                        {
                            textBoxReceive.AppendText(b.ToString("X2") + " ");
                        }
                    }
                }
            }));
        }
        private void Ble_DeviceReceiveData(byte[] data)
        {
            Array.Clear(BleReceiveBuff, 0, BleReceiveBuff.Length);
            BleReceiveBuff = data;
            BeginInvoke(new Action(() =>
            {
                if (checkBoxReceive.Checked)
                {
                    if (radioButtonRecAbc.Checked)
                    {
                        textBoxReceive.AppendText(Encoding.Default.GetString(data));
                        if (checkBoxNewLine.Checked)
                        {
                            textBoxReceive.AppendText("\r\n");
                        }
                    }
                    else if (radioButtonRecHex.Checked)
                    {
                        foreach (byte b in data)
                        {
                            textBoxReceive.AppendText(b.ToString("X2") + " ");
                        }
                    }
                }
            }));
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            ble.StartBleDeviceWatcher();
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
            }

        }

        private void buttonOperate_Click(object sender, EventArgs e)
        {
            if (radioButtonSpp.Checked)
            {
                OperateSpp();
            }
            else if (radioButtonBle.Checked)
            {
                OperateBle();
            }
        }

        private void buttonDownload_Click(object sender, EventArgs e)
        {
            if (FilePath == null) return;
            buttonDownload.Enabled = false;
            buttonOperate.Enabled = false;
            buttonResetSpp.Enabled = false;
            buttonResetBle.Enabled = false;
            FileLength = 0;
            Progress = 0;
            if (radioButtonSpp.Checked)
            {
                SendFileFrame(SppReadFrame, SppFrame);
            }
            else if (radioButtonBle.Checked)
            {
                SendFileFrame(BleReadFrame, BleFrame);
            }

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
            if (radioButtonSendAbc.Checked)
            {
                buff = Encoding.Default.GetBytes(text);
            }
            else if (radioButtonSendHex.Checked)
            {
                buff = HexStringToByte(text);
            }
            if (radioButtonSpp.Checked)
            {
                serialPort.Write(buff, 0, buff.Length);
            }
            else if (radioButtonBle.Checked)
            {
                ble.Write(buff);
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

        private void radioButtonSpp_CheckedChanged(object sender, EventArgs e)
        {
            comboBoxPortList.Enabled = radioButtonSpp.Checked;
            comboBoxDeviceList.Enabled = radioButtonBle.Checked;
        }

        private void radioButtonBle_CheckedChanged(object sender, EventArgs e)
        {
            comboBoxPortList.Enabled = radioButtonSpp.Checked;
            comboBoxDeviceList.Enabled = radioButtonBle.Checked;
        }

        private void buttonResetSpp_Click(object sender, EventArgs e)
        {
            if (radioButtonSpp.Checked)
            {
                SendData(new byte[0], SppSendBuff, 0x55, true);
            }
            else if (radioButtonBle.Checked)
            {
                SendData(new byte[0], BleSendBuff, 0x55, true);
            }

        }

        private void buttonResetBle_Click(object sender, EventArgs e)
        {
            if (radioButtonSpp.Checked)
            {
                SendData(new byte[0], SppSendBuff, 0xaa, true);
            }
            else if (radioButtonBle.Checked)
            {
                SendData(new byte[0], BleSendBuff, 0xaa, true);
            }

        }

        private void radioButtonRecAbc_CheckedChanged(object sender, EventArgs e)
        {
            Transform(radioButtonRecAbc.Checked, radioButtonRecHex.Checked, textBoxReceive);

        }
        private void radioButtonRecHex_CheckedChanged(object sender, EventArgs e)
        {
            Transform(radioButtonRecAbc.Checked, radioButtonRecHex.Checked, textBoxReceive);

        }

        private void radioButtonSendAbc_CheckedChanged(object sender, EventArgs e)
        {
            Transform(radioButtonSendAbc.Checked, radioButtonSendHex.Checked, textBoxSend);
        }

        private void radioButtonSendHex_CheckedChanged(object sender, EventArgs e)
        {
            Transform(radioButtonSendAbc.Checked, radioButtonSendHex.Checked, textBoxSend);
        }
    }
}
