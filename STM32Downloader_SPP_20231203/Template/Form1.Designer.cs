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
            this.comboBoxPortList = new System.Windows.Forms.ComboBox();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonDownload = new System.Windows.Forms.Button();
            this.buttonLoadFile = new System.Windows.Forms.Button();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.textBoxFilePath = new System.Windows.Forms.TextBox();
            this.labelState = new System.Windows.Forms.Label();
            this.checkBoxTopMost = new System.Windows.Forms.CheckBox();
            this.buttonReset = new System.Windows.Forms.Button();
            this.buttonOperate = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // comboBoxPortList
            // 
            this.comboBoxPortList.Font = new System.Drawing.Font("宋体", 12F);
            this.comboBoxPortList.FormattingEnabled = true;
            this.comboBoxPortList.Location = new System.Drawing.Point(21, 61);
            this.comboBoxPortList.Name = "comboBoxPortList";
            this.comboBoxPortList.Size = new System.Drawing.Size(98, 28);
            this.comboBoxPortList.TabIndex = 3;
            this.comboBoxPortList.Text = "COM1";
            // 
            // serialPort
            // 
            this.serialPort.BaudRate = 115200;
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(468, 24);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox1.Size = new System.Drawing.Size(101, 140);
            this.textBox1.TabIndex = 2;
            // 
            // buttonDownload
            // 
            this.buttonDownload.Enabled = false;
            this.buttonDownload.Location = new System.Drawing.Point(337, 61);
            this.buttonDownload.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonDownload.Name = "buttonDownload";
            this.buttonDownload.Size = new System.Drawing.Size(89, 30);
            this.buttonDownload.TabIndex = 5;
            this.buttonDownload.Text = "写入固件";
            this.buttonDownload.UseVisualStyleBackColor = true;
            this.buttonDownload.Click += new System.EventHandler(this.buttonDownload_Click);
            // 
            // buttonLoadFile
            // 
            this.buttonLoadFile.Location = new System.Drawing.Point(231, 14);
            this.buttonLoadFile.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonLoadFile.Name = "buttonLoadFile";
            this.buttonLoadFile.Size = new System.Drawing.Size(89, 30);
            this.buttonLoadFile.TabIndex = 1;
            this.buttonLoadFile.Text = "加载文件";
            this.buttonLoadFile.UseVisualStyleBackColor = true;
            this.buttonLoadFile.Click += new System.EventHandler(this.buttonLoadFile_Click);
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(21, 166);
            this.progressBar.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(406, 19);
            this.progressBar.TabIndex = 8;
            // 
            // textBoxFilePath
            // 
            this.textBoxFilePath.Enabled = false;
            this.textBoxFilePath.Location = new System.Drawing.Point(21, 19);
            this.textBoxFilePath.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBoxFilePath.Name = "textBoxFilePath";
            this.textBoxFilePath.Size = new System.Drawing.Size(192, 25);
            this.textBoxFilePath.TabIndex = 0;
            // 
            // labelState
            // 
            this.labelState.Location = new System.Drawing.Point(21, 148);
            this.labelState.Name = "labelState";
            this.labelState.Size = new System.Drawing.Size(405, 15);
            this.labelState.TabIndex = 7;
            this.labelState.Text = "100%";
            this.labelState.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // checkBoxTopMost
            // 
            this.checkBoxTopMost.AutoSize = true;
            this.checkBoxTopMost.Location = new System.Drawing.Point(340, 21);
            this.checkBoxTopMost.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxTopMost.Name = "checkBoxTopMost";
            this.checkBoxTopMost.Size = new System.Drawing.Size(89, 19);
            this.checkBoxTopMost.TabIndex = 2;
            this.checkBoxTopMost.Text = "窗口置顶";
            this.checkBoxTopMost.UseVisualStyleBackColor = true;
            this.checkBoxTopMost.CheckedChanged += new System.EventHandler(this.checkBoxTopMode_CheckedChanged);
            // 
            // buttonReset
            // 
            this.buttonReset.Enabled = false;
            this.buttonReset.Location = new System.Drawing.Point(231, 61);
            this.buttonReset.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(89, 30);
            this.buttonReset.TabIndex = 6;
            this.buttonReset.Text = "复位";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // buttonOperate
            // 
            this.buttonOperate.Enabled = false;
            this.buttonOperate.Location = new System.Drawing.Point(124, 61);
            this.buttonOperate.Name = "buttonOperate";
            this.buttonOperate.Size = new System.Drawing.Size(89, 30);
            this.buttonOperate.TabIndex = 4;
            this.buttonOperate.Text = "打开";
            this.buttonOperate.UseVisualStyleBackColor = true;
            this.buttonOperate.Click += new System.EventHandler(this.buttonOperate_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(448, 218);
            this.Controls.Add(this.checkBoxTopMost);
            this.Controls.Add(this.labelState);
            this.Controls.Add(this.buttonReset);
            this.Controls.Add(this.textBoxFilePath);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.buttonLoadFile);
            this.Controls.Add(this.buttonDownload);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.comboBoxPortList);
            this.Controls.Add(this.buttonOperate);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "STM32DOWNLOADER";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ComboBox comboBoxPortList;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button buttonDownload;
        private System.Windows.Forms.Button buttonLoadFile;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.TextBox textBoxFilePath;
        private System.Windows.Forms.Label labelState;
        private System.Windows.Forms.CheckBox checkBoxTopMost;
        private System.Windows.Forms.Button buttonReset;
        private System.Windows.Forms.Button buttonOperate;
    }
}

