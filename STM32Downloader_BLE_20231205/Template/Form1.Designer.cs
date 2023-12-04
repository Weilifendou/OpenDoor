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
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.checkBoxReceive = new System.Windows.Forms.CheckBox();
            this.buttonOperate = new System.Windows.Forms.Button();
            this.labelState = new System.Windows.Forms.Label();
            this.buttonReset = new System.Windows.Forms.Button();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.buttonDownload = new System.Windows.Forms.Button();
            this.checkBoxTopMost = new System.Windows.Forms.CheckBox();
            this.textBoxFilePath = new System.Windows.Forms.TextBox();
            this.buttonLoadFile = new System.Windows.Forms.Button();
            this.textBoxReceive = new System.Windows.Forms.TextBox();
            this.comboBoxDeviceList = new System.Windows.Forms.ComboBox();
            this.textBoxSend = new System.Windows.Forms.TextBox();
            this.buttonSend = new System.Windows.Forms.Button();
            this.radioButtonAbc = new System.Windows.Forms.RadioButton();
            this.radioButtonHex = new System.Windows.Forms.RadioButton();
            this.buttonSearch = new System.Windows.Forms.Button();
            this.buttonClearReceive = new System.Windows.Forms.Button();
            this.buttonClearSend = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // checkBoxReceive
            // 
            this.checkBoxReceive.AutoSize = true;
            this.checkBoxReceive.Location = new System.Drawing.Point(393, 169);
            this.checkBoxReceive.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxReceive.Name = "checkBoxReceive";
            this.checkBoxReceive.Size = new System.Drawing.Size(89, 19);
            this.checkBoxReceive.TabIndex = 12;
            this.checkBoxReceive.Text = "打开接收";
            this.checkBoxReceive.UseVisualStyleBackColor = true;
            // 
            // buttonOperate
            // 
            this.buttonOperate.Location = new System.Drawing.Point(234, 63);
            this.buttonOperate.Name = "buttonOperate";
            this.buttonOperate.Size = new System.Drawing.Size(89, 30);
            this.buttonOperate.TabIndex = 5;
            this.buttonOperate.Text = "连接";
            this.buttonOperate.UseVisualStyleBackColor = true;
            this.buttonOperate.Click += new System.EventHandler(this.buttonOperate_Click);
            // 
            // labelState
            // 
            this.labelState.Location = new System.Drawing.Point(10, 109);
            this.labelState.Name = "labelState";
            this.labelState.Size = new System.Drawing.Size(408, 15);
            this.labelState.TabIndex = 8;
            this.labelState.Text = "100%";
            this.labelState.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // buttonReset
            // 
            this.buttonReset.Enabled = false;
            this.buttonReset.Location = new System.Drawing.Point(329, 63);
            this.buttonReset.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(89, 30);
            this.buttonReset.TabIndex = 6;
            this.buttonReset.Text = "复位";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(13, 126);
            this.progressBar.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(405, 19);
            this.progressBar.TabIndex = 9;
            // 
            // buttonDownload
            // 
            this.buttonDownload.Enabled = false;
            this.buttonDownload.Location = new System.Drawing.Point(424, 63);
            this.buttonDownload.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonDownload.Name = "buttonDownload";
            this.buttonDownload.Size = new System.Drawing.Size(89, 30);
            this.buttonDownload.TabIndex = 7;
            this.buttonDownload.Text = "写入固件";
            this.buttonDownload.UseVisualStyleBackColor = true;
            this.buttonDownload.Click += new System.EventHandler(this.buttonDownload_Click);
            // 
            // checkBoxTopMost
            // 
            this.checkBoxTopMost.AutoSize = true;
            this.checkBoxTopMost.Location = new System.Drawing.Point(424, 18);
            this.checkBoxTopMost.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.checkBoxTopMost.Name = "checkBoxTopMost";
            this.checkBoxTopMost.Size = new System.Drawing.Size(89, 19);
            this.checkBoxTopMost.TabIndex = 3;
            this.checkBoxTopMost.Text = "窗口置顶";
            this.checkBoxTopMost.UseVisualStyleBackColor = true;
            this.checkBoxTopMost.CheckedChanged += new System.EventHandler(this.checkBoxTopMost_CheckedChanged);
            // 
            // textBoxFilePath
            // 
            this.textBoxFilePath.Enabled = false;
            this.textBoxFilePath.Location = new System.Drawing.Point(17, 18);
            this.textBoxFilePath.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBoxFilePath.Name = "textBoxFilePath";
            this.textBoxFilePath.Size = new System.Drawing.Size(211, 25);
            this.textBoxFilePath.TabIndex = 0;
            this.textBoxFilePath.Text = "文件位置";
            // 
            // buttonLoadFile
            // 
            this.buttonLoadFile.Location = new System.Drawing.Point(234, 13);
            this.buttonLoadFile.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonLoadFile.Name = "buttonLoadFile";
            this.buttonLoadFile.Size = new System.Drawing.Size(89, 30);
            this.buttonLoadFile.TabIndex = 1;
            this.buttonLoadFile.Text = "加载文件";
            this.buttonLoadFile.UseVisualStyleBackColor = true;
            this.buttonLoadFile.Click += new System.EventHandler(this.buttonLoadFile_Click);
            // 
            // textBoxReceive
            // 
            this.textBoxReceive.Location = new System.Drawing.Point(17, 158);
            this.textBoxReceive.Multiline = true;
            this.textBoxReceive.Name = "textBoxReceive";
            this.textBoxReceive.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxReceive.Size = new System.Drawing.Size(496, 187);
            this.textBoxReceive.TabIndex = 11;
            // 
            // comboBoxDeviceList
            // 
            this.comboBoxDeviceList.FormattingEnabled = true;
            this.comboBoxDeviceList.Location = new System.Drawing.Point(13, 68);
            this.comboBoxDeviceList.Name = "comboBoxDeviceList";
            this.comboBoxDeviceList.Size = new System.Drawing.Size(215, 23);
            this.comboBoxDeviceList.TabIndex = 4;
            // 
            // textBoxSend
            // 
            this.textBoxSend.Location = new System.Drawing.Point(12, 351);
            this.textBoxSend.Multiline = true;
            this.textBoxSend.Name = "textBoxSend";
            this.textBoxSend.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxSend.Size = new System.Drawing.Size(384, 90);
            this.textBoxSend.TabIndex = 13;
            // 
            // buttonSend
            // 
            this.buttonSend.Enabled = false;
            this.buttonSend.Location = new System.Drawing.Point(402, 410);
            this.buttonSend.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(111, 31);
            this.buttonSend.TabIndex = 17;
            this.buttonSend.Text = "发送数据";
            this.buttonSend.UseVisualStyleBackColor = true;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // radioButtonAbc
            // 
            this.radioButtonAbc.AutoSize = true;
            this.radioButtonAbc.Checked = true;
            this.radioButtonAbc.Location = new System.Drawing.Point(403, 352);
            this.radioButtonAbc.Name = "radioButtonAbc";
            this.radioButtonAbc.Size = new System.Drawing.Size(52, 19);
            this.radioButtonAbc.TabIndex = 14;
            this.radioButtonAbc.TabStop = true;
            this.radioButtonAbc.Text = "Abc";
            this.radioButtonAbc.UseVisualStyleBackColor = true;
            // 
            // radioButtonHex
            // 
            this.radioButtonHex.AutoSize = true;
            this.radioButtonHex.Location = new System.Drawing.Point(461, 352);
            this.radioButtonHex.Name = "radioButtonHex";
            this.radioButtonHex.Size = new System.Drawing.Size(52, 19);
            this.radioButtonHex.TabIndex = 15;
            this.radioButtonHex.Text = "Hex";
            this.radioButtonHex.UseVisualStyleBackColor = true;
            // 
            // buttonSearch
            // 
            this.buttonSearch.Location = new System.Drawing.Point(329, 13);
            this.buttonSearch.Name = "buttonSearch";
            this.buttonSearch.Size = new System.Drawing.Size(89, 30);
            this.buttonSearch.TabIndex = 2;
            this.buttonSearch.Text = "搜索";
            this.buttonSearch.UseVisualStyleBackColor = true;
            this.buttonSearch.Click += new System.EventHandler(this.buttonSearch_Click);
            // 
            // buttonClearReceive
            // 
            this.buttonClearReceive.Location = new System.Drawing.Point(424, 115);
            this.buttonClearReceive.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonClearReceive.Name = "buttonClearReceive";
            this.buttonClearReceive.Size = new System.Drawing.Size(89, 30);
            this.buttonClearReceive.TabIndex = 10;
            this.buttonClearReceive.Text = "清空接收";
            this.buttonClearReceive.UseVisualStyleBackColor = true;
            this.buttonClearReceive.Click += new System.EventHandler(this.buttonClearReceive_Click);
            // 
            // buttonClearSend
            // 
            this.buttonClearSend.Location = new System.Drawing.Point(402, 376);
            this.buttonClearSend.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonClearSend.Name = "buttonClearSend";
            this.buttonClearSend.Size = new System.Drawing.Size(110, 30);
            this.buttonClearSend.TabIndex = 16;
            this.buttonClearSend.Text = "清空发送";
            this.buttonClearSend.UseVisualStyleBackColor = true;
            this.buttonClearSend.Click += new System.EventHandler(this.buttonClearSend_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(522, 453);
            this.Controls.Add(this.buttonClearSend);
            this.Controls.Add(this.buttonClearReceive);
            this.Controls.Add(this.buttonSearch);
            this.Controls.Add(this.radioButtonHex);
            this.Controls.Add(this.radioButtonAbc);
            this.Controls.Add(this.buttonSend);
            this.Controls.Add(this.textBoxSend);
            this.Controls.Add(this.checkBoxReceive);
            this.Controls.Add(this.buttonOperate);
            this.Controls.Add(this.labelState);
            this.Controls.Add(this.buttonReset);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.buttonDownload);
            this.Controls.Add(this.checkBoxTopMost);
            this.Controls.Add(this.textBoxFilePath);
            this.Controls.Add(this.buttonLoadFile);
            this.Controls.Add(this.textBoxReceive);
            this.Controls.Add(this.comboBoxDeviceList);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "STM32DOWNLOADER";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.CheckBox checkBoxReceive;
        private System.Windows.Forms.Button buttonOperate;
        private System.Windows.Forms.Label labelState;
        private System.Windows.Forms.Button buttonReset;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Button buttonDownload;
        private System.Windows.Forms.CheckBox checkBoxTopMost;
        private System.Windows.Forms.TextBox textBoxFilePath;
        private System.Windows.Forms.Button buttonLoadFile;
        private System.Windows.Forms.TextBox textBoxReceive;
        private System.Windows.Forms.ComboBox comboBoxDeviceList;
        private System.Windows.Forms.TextBox textBoxSend;
        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.RadioButton radioButtonAbc;
        private System.Windows.Forms.RadioButton radioButtonHex;
        private System.Windows.Forms.Button buttonSearch;
        private System.Windows.Forms.Button buttonClearReceive;
        private System.Windows.Forms.Button buttonClearSend;
    }
}

