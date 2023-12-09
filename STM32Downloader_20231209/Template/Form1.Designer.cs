namespace Template
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.checkBoxReceive = new System.Windows.Forms.CheckBox();
            this.buttonOperate = new System.Windows.Forms.Button();
            this.labelState = new System.Windows.Forms.Label();
            this.buttonResetSpp = new System.Windows.Forms.Button();
            this.buttonDownload = new System.Windows.Forms.Button();
            this.checkBoxTopMost = new System.Windows.Forms.CheckBox();
            this.textBoxFilePath = new System.Windows.Forms.TextBox();
            this.buttonLoadFile = new System.Windows.Forms.Button();
            this.textBoxReceive = new System.Windows.Forms.TextBox();
            this.comboBoxDeviceList = new System.Windows.Forms.ComboBox();
            this.textBoxSend = new System.Windows.Forms.TextBox();
            this.buttonSend = new System.Windows.Forms.Button();
            this.radioButtonSendAbc = new System.Windows.Forms.RadioButton();
            this.radioButtonSendHex = new System.Windows.Forms.RadioButton();
            this.buttonSearch = new System.Windows.Forms.Button();
            this.buttonClearReceive = new System.Windows.Forms.Button();
            this.buttonClearSend = new System.Windows.Forms.Button();
            this.groupBoxSend = new System.Windows.Forms.GroupBox();
            this.groupBoxRecevie = new System.Windows.Forms.GroupBox();
            this.radioButtonRecAbc = new System.Windows.Forms.RadioButton();
            this.radioButtonRecHex = new System.Windows.Forms.RadioButton();
            this.groupBoxDownloadMode = new System.Windows.Forms.GroupBox();
            this.radioButtonSpp = new System.Windows.Forms.RadioButton();
            this.buttonResetBle = new System.Windows.Forms.Button();
            this.radioButtonBle = new System.Windows.Forms.RadioButton();
            this.comboBoxPortList = new System.Windows.Forms.ComboBox();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.checkBoxNewLine = new System.Windows.Forms.CheckBox();
            this.myProgressBar = new Template.MyProgressBar();
            this.groupBoxSend.SuspendLayout();
            this.groupBoxRecevie.SuspendLayout();
            this.groupBoxDownloadMode.SuspendLayout();
            this.SuspendLayout();
            // 
            // checkBoxReceive
            // 
            this.checkBoxReceive.AutoSize = true;
            this.checkBoxReceive.Location = new System.Drawing.Point(612, 49);
            this.checkBoxReceive.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxReceive.Name = "checkBoxReceive";
            this.checkBoxReceive.Size = new System.Drawing.Size(106, 22);
            this.checkBoxReceive.TabIndex = 3;
            this.checkBoxReceive.Text = "打开接收";
            this.checkBoxReceive.UseVisualStyleBackColor = true;
            // 
            // buttonOperate
            // 
            this.buttonOperate.Location = new System.Drawing.Point(364, 55);
            this.buttonOperate.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonOperate.Name = "buttonOperate";
            this.buttonOperate.Size = new System.Drawing.Size(90, 36);
            this.buttonOperate.TabIndex = 8;
            this.buttonOperate.Text = "连接";
            this.buttonOperate.UseVisualStyleBackColor = true;
            this.buttonOperate.Click += new System.EventHandler(this.buttonOperate_Click);
            // 
            // labelState
            // 
            this.labelState.Location = new System.Drawing.Point(6, 95);
            this.labelState.Name = "labelState";
            this.labelState.Size = new System.Drawing.Size(748, 25);
            this.labelState.TabIndex = 12;
            this.labelState.Text = "100%";
            this.labelState.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // buttonResetSpp
            // 
            this.buttonResetSpp.Enabled = false;
            this.buttonResetSpp.Location = new System.Drawing.Point(464, 55);
            this.buttonResetSpp.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonResetSpp.Name = "buttonResetSpp";
            this.buttonResetSpp.Size = new System.Drawing.Size(90, 36);
            this.buttonResetSpp.TabIndex = 9;
            this.buttonResetSpp.Text = "SPP复位";
            this.buttonResetSpp.UseVisualStyleBackColor = true;
            this.buttonResetSpp.Click += new System.EventHandler(this.buttonResetSpp_Click);
            // 
            // buttonDownload
            // 
            this.buttonDownload.Enabled = false;
            this.buttonDownload.Location = new System.Drawing.Point(664, 55);
            this.buttonDownload.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonDownload.Name = "buttonDownload";
            this.buttonDownload.Size = new System.Drawing.Size(90, 36);
            this.buttonDownload.TabIndex = 11;
            this.buttonDownload.Text = "写入固件";
            this.buttonDownload.UseVisualStyleBackColor = true;
            this.buttonDownload.Click += new System.EventHandler(this.buttonDownload_Click);
            // 
            // checkBoxTopMost
            // 
            this.checkBoxTopMost.AutoSize = true;
            this.checkBoxTopMost.Location = new System.Drawing.Point(648, 17);
            this.checkBoxTopMost.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxTopMost.Name = "checkBoxTopMost";
            this.checkBoxTopMost.Size = new System.Drawing.Size(106, 22);
            this.checkBoxTopMost.TabIndex = 5;
            this.checkBoxTopMost.Text = "窗口置顶";
            this.checkBoxTopMost.UseVisualStyleBackColor = true;
            this.checkBoxTopMost.CheckedChanged += new System.EventHandler(this.checkBoxTopMost_CheckedChanged);
            // 
            // textBoxFilePath
            // 
            this.textBoxFilePath.Location = new System.Drawing.Point(138, 16);
            this.textBoxFilePath.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBoxFilePath.Name = "textBoxFilePath";
            this.textBoxFilePath.ReadOnly = true;
            this.textBoxFilePath.Size = new System.Drawing.Size(220, 28);
            this.textBoxFilePath.TabIndex = 2;
            this.textBoxFilePath.Text = "文件位置";
            // 
            // buttonLoadFile
            // 
            this.buttonLoadFile.Location = new System.Drawing.Point(364, 9);
            this.buttonLoadFile.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonLoadFile.Name = "buttonLoadFile";
            this.buttonLoadFile.Size = new System.Drawing.Size(100, 36);
            this.buttonLoadFile.TabIndex = 3;
            this.buttonLoadFile.Text = "加载文件";
            this.buttonLoadFile.UseVisualStyleBackColor = true;
            this.buttonLoadFile.Click += new System.EventHandler(this.buttonLoadFile_Click);
            // 
            // textBoxReceive
            // 
            this.textBoxReceive.Location = new System.Drawing.Point(6, 21);
            this.textBoxReceive.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBoxReceive.Multiline = true;
            this.textBoxReceive.Name = "textBoxReceive";
            this.textBoxReceive.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxReceive.Size = new System.Drawing.Size(600, 180);
            this.textBoxReceive.TabIndex = 0;
            // 
            // comboBoxDeviceList
            // 
            this.comboBoxDeviceList.Enabled = false;
            this.comboBoxDeviceList.FormattingEnabled = true;
            this.comboBoxDeviceList.Location = new System.Drawing.Point(138, 61);
            this.comboBoxDeviceList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.comboBoxDeviceList.Name = "comboBoxDeviceList";
            this.comboBoxDeviceList.Size = new System.Drawing.Size(220, 26);
            this.comboBoxDeviceList.TabIndex = 7;
            this.comboBoxDeviceList.Text = "ble devices";
            // 
            // textBoxSend
            // 
            this.textBoxSend.Location = new System.Drawing.Point(6, 13);
            this.textBoxSend.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBoxSend.Multiline = true;
            this.textBoxSend.Name = "textBoxSend";
            this.textBoxSend.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxSend.Size = new System.Drawing.Size(600, 106);
            this.textBoxSend.TabIndex = 0;
            // 
            // buttonSend
            // 
            this.buttonSend.Enabled = false;
            this.buttonSend.Location = new System.Drawing.Point(612, 82);
            this.buttonSend.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(120, 36);
            this.buttonSend.TabIndex = 4;
            this.buttonSend.Text = "发送数据";
            this.buttonSend.UseVisualStyleBackColor = true;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // radioButtonSendAbc
            // 
            this.radioButtonSendAbc.AutoSize = true;
            this.radioButtonSendAbc.Checked = true;
            this.radioButtonSendAbc.Location = new System.Drawing.Point(612, 14);
            this.radioButtonSendAbc.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButtonSendAbc.Name = "radioButtonSendAbc";
            this.radioButtonSendAbc.Size = new System.Drawing.Size(60, 22);
            this.radioButtonSendAbc.TabIndex = 1;
            this.radioButtonSendAbc.TabStop = true;
            this.radioButtonSendAbc.Text = "Abc";
            this.radioButtonSendAbc.UseVisualStyleBackColor = true;
            this.radioButtonSendAbc.CheckedChanged += new System.EventHandler(this.radioButtonSendAbc_CheckedChanged);
            // 
            // radioButtonSendHex
            // 
            this.radioButtonSendHex.AutoSize = true;
            this.radioButtonSendHex.Location = new System.Drawing.Point(678, 14);
            this.radioButtonSendHex.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButtonSendHex.Name = "radioButtonSendHex";
            this.radioButtonSendHex.Size = new System.Drawing.Size(60, 22);
            this.radioButtonSendHex.TabIndex = 2;
            this.radioButtonSendHex.Text = "Hex";
            this.radioButtonSendHex.UseVisualStyleBackColor = true;
            this.radioButtonSendHex.CheckedChanged += new System.EventHandler(this.radioButtonSendHex_CheckedChanged);
            // 
            // buttonSearch
            // 
            this.buttonSearch.Location = new System.Drawing.Point(470, 8);
            this.buttonSearch.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonSearch.Name = "buttonSearch";
            this.buttonSearch.Size = new System.Drawing.Size(172, 36);
            this.buttonSearch.TabIndex = 4;
            this.buttonSearch.Text = "搜索";
            this.buttonSearch.UseVisualStyleBackColor = true;
            this.buttonSearch.Click += new System.EventHandler(this.buttonSearch_Click);
            // 
            // buttonClearReceive
            // 
            this.buttonClearReceive.Location = new System.Drawing.Point(612, 165);
            this.buttonClearReceive.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonClearReceive.Name = "buttonClearReceive";
            this.buttonClearReceive.Size = new System.Drawing.Size(120, 36);
            this.buttonClearReceive.TabIndex = 5;
            this.buttonClearReceive.Text = "清空接收";
            this.buttonClearReceive.UseVisualStyleBackColor = true;
            this.buttonClearReceive.Click += new System.EventHandler(this.buttonClearReceive_Click);
            // 
            // buttonClearSend
            // 
            this.buttonClearSend.Location = new System.Drawing.Point(612, 42);
            this.buttonClearSend.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonClearSend.Name = "buttonClearSend";
            this.buttonClearSend.Size = new System.Drawing.Size(120, 36);
            this.buttonClearSend.TabIndex = 3;
            this.buttonClearSend.Text = "清空发送";
            this.buttonClearSend.UseVisualStyleBackColor = true;
            this.buttonClearSend.Click += new System.EventHandler(this.buttonClearSend_Click);
            // 
            // groupBoxSend
            // 
            this.groupBoxSend.Controls.Add(this.radioButtonSendAbc);
            this.groupBoxSend.Controls.Add(this.radioButtonSendHex);
            this.groupBoxSend.Controls.Add(this.textBoxSend);
            this.groupBoxSend.Controls.Add(this.buttonClearSend);
            this.groupBoxSend.Controls.Add(this.buttonSend);
            this.groupBoxSend.Location = new System.Drawing.Point(6, 384);
            this.groupBoxSend.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBoxSend.Name = "groupBoxSend";
            this.groupBoxSend.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBoxSend.Size = new System.Drawing.Size(760, 128);
            this.groupBoxSend.TabIndex = 2;
            this.groupBoxSend.TabStop = false;
            // 
            // groupBoxRecevie
            // 
            this.groupBoxRecevie.Controls.Add(this.checkBoxNewLine);
            this.groupBoxRecevie.Controls.Add(this.radioButtonRecAbc);
            this.groupBoxRecevie.Controls.Add(this.radioButtonRecHex);
            this.groupBoxRecevie.Controls.Add(this.textBoxReceive);
            this.groupBoxRecevie.Controls.Add(this.checkBoxReceive);
            this.groupBoxRecevie.Controls.Add(this.buttonClearReceive);
            this.groupBoxRecevie.Location = new System.Drawing.Point(12, 177);
            this.groupBoxRecevie.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBoxRecevie.Name = "groupBoxRecevie";
            this.groupBoxRecevie.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBoxRecevie.Size = new System.Drawing.Size(760, 213);
            this.groupBoxRecevie.TabIndex = 1;
            this.groupBoxRecevie.TabStop = false;
            // 
            // radioButtonRecAbc
            // 
            this.radioButtonRecAbc.AutoSize = true;
            this.radioButtonRecAbc.Checked = true;
            this.radioButtonRecAbc.Location = new System.Drawing.Point(612, 21);
            this.radioButtonRecAbc.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButtonRecAbc.Name = "radioButtonRecAbc";
            this.radioButtonRecAbc.Size = new System.Drawing.Size(60, 22);
            this.radioButtonRecAbc.TabIndex = 1;
            this.radioButtonRecAbc.TabStop = true;
            this.radioButtonRecAbc.Text = "Abc";
            this.radioButtonRecAbc.UseVisualStyleBackColor = true;
            this.radioButtonRecAbc.CheckedChanged += new System.EventHandler(this.radioButtonRecAbc_CheckedChanged);
            // 
            // radioButtonRecHex
            // 
            this.radioButtonRecHex.AutoSize = true;
            this.radioButtonRecHex.Location = new System.Drawing.Point(678, 21);
            this.radioButtonRecHex.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButtonRecHex.Name = "radioButtonRecHex";
            this.radioButtonRecHex.Size = new System.Drawing.Size(60, 22);
            this.radioButtonRecHex.TabIndex = 2;
            this.radioButtonRecHex.Text = "Hex";
            this.radioButtonRecHex.UseVisualStyleBackColor = true;
            this.radioButtonRecHex.CheckedChanged += new System.EventHandler(this.radioButtonRecHex_CheckedChanged);
            // 
            // groupBoxDownloadMode
            // 
            this.groupBoxDownloadMode.Controls.Add(this.myProgressBar);
            this.groupBoxDownloadMode.Controls.Add(this.radioButtonSpp);
            this.groupBoxDownloadMode.Controls.Add(this.buttonResetBle);
            this.groupBoxDownloadMode.Controls.Add(this.radioButtonBle);
            this.groupBoxDownloadMode.Controls.Add(this.comboBoxPortList);
            this.groupBoxDownloadMode.Controls.Add(this.labelState);
            this.groupBoxDownloadMode.Controls.Add(this.textBoxFilePath);
            this.groupBoxDownloadMode.Controls.Add(this.comboBoxDeviceList);
            this.groupBoxDownloadMode.Controls.Add(this.buttonLoadFile);
            this.groupBoxDownloadMode.Controls.Add(this.checkBoxTopMost);
            this.groupBoxDownloadMode.Controls.Add(this.buttonSearch);
            this.groupBoxDownloadMode.Controls.Add(this.buttonDownload);
            this.groupBoxDownloadMode.Controls.Add(this.buttonOperate);
            this.groupBoxDownloadMode.Controls.Add(this.buttonResetSpp);
            this.groupBoxDownloadMode.Location = new System.Drawing.Point(12, 13);
            this.groupBoxDownloadMode.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBoxDownloadMode.Name = "groupBoxDownloadMode";
            this.groupBoxDownloadMode.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBoxDownloadMode.Size = new System.Drawing.Size(760, 156);
            this.groupBoxDownloadMode.TabIndex = 0;
            this.groupBoxDownloadMode.TabStop = false;
            // 
            // radioButtonSpp
            // 
            this.radioButtonSpp.AutoSize = true;
            this.radioButtonSpp.Checked = true;
            this.radioButtonSpp.Location = new System.Drawing.Point(6, 17);
            this.radioButtonSpp.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButtonSpp.Name = "radioButtonSpp";
            this.radioButtonSpp.Size = new System.Drawing.Size(60, 22);
            this.radioButtonSpp.TabIndex = 0;
            this.radioButtonSpp.TabStop = true;
            this.radioButtonSpp.Text = "SPP";
            this.radioButtonSpp.UseVisualStyleBackColor = true;
            this.radioButtonSpp.CheckedChanged += new System.EventHandler(this.radioButtonSpp_CheckedChanged);
            // 
            // buttonResetBle
            // 
            this.buttonResetBle.Enabled = false;
            this.buttonResetBle.Location = new System.Drawing.Point(564, 55);
            this.buttonResetBle.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonResetBle.Name = "buttonResetBle";
            this.buttonResetBle.Size = new System.Drawing.Size(90, 36);
            this.buttonResetBle.TabIndex = 10;
            this.buttonResetBle.Text = "BLE复位";
            this.buttonResetBle.UseVisualStyleBackColor = true;
            this.buttonResetBle.Click += new System.EventHandler(this.buttonResetBle_Click);
            // 
            // radioButtonBle
            // 
            this.radioButtonBle.AutoSize = true;
            this.radioButtonBle.Location = new System.Drawing.Point(72, 17);
            this.radioButtonBle.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButtonBle.Name = "radioButtonBle";
            this.radioButtonBle.Size = new System.Drawing.Size(60, 22);
            this.radioButtonBle.TabIndex = 1;
            this.radioButtonBle.Text = "BLE";
            this.radioButtonBle.UseVisualStyleBackColor = true;
            this.radioButtonBle.CheckedChanged += new System.EventHandler(this.radioButtonBle_CheckedChanged);
            // 
            // comboBoxPortList
            // 
            this.comboBoxPortList.Font = new System.Drawing.Font("宋体", 9F);
            this.comboBoxPortList.FormattingEnabled = true;
            this.comboBoxPortList.Location = new System.Drawing.Point(6, 61);
            this.comboBoxPortList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.comboBoxPortList.Name = "comboBoxPortList";
            this.comboBoxPortList.Size = new System.Drawing.Size(126, 26);
            this.comboBoxPortList.TabIndex = 6;
            this.comboBoxPortList.Text = "COM1";
            // 
            // serialPort
            // 
            this.serialPort.BaudRate = 115200;
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // checkBoxNewLine
            // 
            this.checkBoxNewLine.AutoSize = true;
            this.checkBoxNewLine.Location = new System.Drawing.Point(612, 75);
            this.checkBoxNewLine.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxNewLine.Name = "checkBoxNewLine";
            this.checkBoxNewLine.Size = new System.Drawing.Size(106, 22);
            this.checkBoxNewLine.TabIndex = 4;
            this.checkBoxNewLine.Text = "添加新行";
            this.checkBoxNewLine.UseVisualStyleBackColor = true;
            // 
            // myProgressBar
            // 
            this.myProgressBar.BarType = Template.MyProgressBar.EnumBarType.Straight;
            this.myProgressBar.Location = new System.Drawing.Point(6, 129);
            this.myProgressBar.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.myProgressBar.Name = "myProgressBar";
            this.myProgressBar.Progress = 0;
            this.myProgressBar.Size = new System.Drawing.Size(748, 23);
            this.myProgressBar.TabIndex = 13;
            this.myProgressBar.Text = "myProgressBar1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(783, 509);
            this.Controls.Add(this.groupBoxDownloadMode);
            this.Controls.Add(this.groupBoxRecevie);
            this.Controls.Add(this.groupBoxSend);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "STM32DOWNLOADER";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBoxSend.ResumeLayout(false);
            this.groupBoxSend.PerformLayout();
            this.groupBoxRecevie.ResumeLayout(false);
            this.groupBoxRecevie.PerformLayout();
            this.groupBoxDownloadMode.ResumeLayout(false);
            this.groupBoxDownloadMode.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.CheckBox checkBoxReceive;
        private System.Windows.Forms.Button buttonOperate;
        private System.Windows.Forms.Label labelState;
        private System.Windows.Forms.Button buttonResetSpp;
        private System.Windows.Forms.Button buttonDownload;
        private System.Windows.Forms.CheckBox checkBoxTopMost;
        private System.Windows.Forms.TextBox textBoxFilePath;
        private System.Windows.Forms.Button buttonLoadFile;
        private System.Windows.Forms.TextBox textBoxReceive;
        private System.Windows.Forms.ComboBox comboBoxDeviceList;
        private System.Windows.Forms.TextBox textBoxSend;
        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.RadioButton radioButtonSendAbc;
        private System.Windows.Forms.RadioButton radioButtonSendHex;
        private System.Windows.Forms.Button buttonSearch;
        private System.Windows.Forms.Button buttonClearReceive;
        private System.Windows.Forms.Button buttonClearSend;
        private System.Windows.Forms.GroupBox groupBoxSend;
        private System.Windows.Forms.GroupBox groupBoxRecevie;
        private System.Windows.Forms.RadioButton radioButtonRecAbc;
        private System.Windows.Forms.RadioButton radioButtonRecHex;
        private System.Windows.Forms.GroupBox groupBoxDownloadMode;
        private System.Windows.Forms.RadioButton radioButtonSpp;
        private System.Windows.Forms.RadioButton radioButtonBle;
        private System.Windows.Forms.ComboBox comboBoxPortList;
        private System.Windows.Forms.Button buttonResetBle;
        private System.IO.Ports.SerialPort serialPort;
        private MyProgressBar myProgressBar;
        private System.Windows.Forms.CheckBox checkBoxNewLine;
    }
}

