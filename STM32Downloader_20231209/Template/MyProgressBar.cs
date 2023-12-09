using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing.Drawing2D;
using System.Drawing.Text;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Windows.UI.Xaml.Automation;

namespace Template
{
    public partial class MyProgressBar : Control
    {
        private Graphics graphic;
        private Bitmap bmp;
        private int progress;

        public int Progress
        {
            get { return progress; }
            set
            {
                progress = value;
                Invalidate();
            }
        }
        public enum EnumBarType
        {
            Straight,
            Bent
        }
        public EnumBarType barType;
        public EnumBarType BarType
        {
            get { return barType; }
            set
            {
                barType = value;
            }
        }
        public MyProgressBar()
        {
            InitializeComponent();
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            drawProgress(e.Graphics, BarType);
            base.OnPaint(e);

        }
        private void drawProgress(Graphics g, EnumBarType barType)
        {
            bmp = new Bitmap(Width, Height);
            int w = bmp.Width;
            int h = bmp.Height;
            int oX = w / 2;
            int oY = h / 2;
            graphic = Graphics.FromImage(bmp);
            graphic.SmoothingMode = SmoothingMode.HighQuality;
            graphic.InterpolationMode = InterpolationMode.HighQualityBicubic;
            graphic.CompositingQuality = CompositingQuality.HighQuality;
            graphic.TextRenderingHint = TextRenderingHint.AntiAlias;
            graphic.FillRectangle(Brushes.Transparent, 0, 0, w, h);
            graphic.DrawLine(Pens.Black, 0, 0, w - 1, 0);
            graphic.DrawLine(Pens.Black, w - 1, 0, w - 1, h - 1);
            graphic.DrawLine(Pens.Black, w - 1, h - 1, 0, h - 1);
            graphic.DrawLine(Pens.Black, 0, h - 1, 0, 0);
            if (barType == EnumBarType.Straight)
            {
                Pen pen = new Pen(Color.Green, h);
                int progressFill = (int)(progress / 100.0 * w);
                graphic.DrawLine(pen, 0, oY, progressFill, oY);
            }
            else if (barType == EnumBarType.Bent)
            {
                int min = (w > h ? h : w) / 2;
                int r = min - 4;
                graphic.FillEllipse(Brushes.LightGray, oX - r, oY - r, 2 * r, 2 * r);
                int R = (int)(r * 0.618);
                graphic.FillEllipse(Brushes.White, oX - R, oY - R, 2 * R, 2 * R);
                int f = r - R;
                int hf = f / 2;
                graphic.FillEllipse(Brushes.DeepSkyBlue, oX - hf, oY - r, f, f);
                int fr = R + hf;
                graphic.DrawArc(new Pen(Color.DeepSkyBlue, f), oX - fr, oY - fr, 2 * fr, 2 * fr, -90, progress * 360 / 100);
                double angle = (-90 + progress * 360 / 100) * Math.PI / 180;
                float rX = (float)(oX + fr * Math.Cos(angle) - hf);
                float rY = (float)(oY + fr * Math.Sin(angle) - hf);
                graphic.FillEllipse(Brushes.DeepSkyBlue, rX, rY, f, f);
                float fs = R * 0.618f;
                string text = progress.ToString();
                graphic.DrawString(text.ToString(), new Font("微软雅黑", fs), Brushes.DeepSkyBlue, oX - fs * text.Length / 2, oY - fs);
            }
            g.DrawImage(bmp, 0, 0);
        }

    }
}
