namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    partial class RobotStartView
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.simpleButton2 = new DevExpress.XtraEditors.SimpleButton();
            this.label87 = new System.Windows.Forms.Label();
            this.simpleButton4 = new DevExpress.XtraEditors.SimpleButton();
            this.SuspendLayout();
            // 
            // simpleButton2
            // 
            this.simpleButton2.AllowFocus = false;
            this.simpleButton2.Appearance.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(250)))), ((int)(((byte)(220)))), ((int)(((byte)(220)))));
            this.simpleButton2.Appearance.BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(210)))), ((int)(((byte)(190)))), ((int)(((byte)(190)))));
            this.simpleButton2.Appearance.Font = new System.Drawing.Font("돋움체", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.simpleButton2.Appearance.Options.UseBackColor = true;
            this.simpleButton2.Appearance.Options.UseFont = true;
            this.simpleButton2.ButtonStyle = DevExpress.XtraEditors.Controls.BorderStyles.Style3D;
            this.simpleButton2.ImageIndex = 7;
            this.simpleButton2.Location = new System.Drawing.Point(154, 377);
            this.simpleButton2.Name = "simpleButton2";
            this.simpleButton2.Size = new System.Drawing.Size(768, 95);
            this.simpleButton2.TabIndex = 1140;
            this.simpleButton2.Text = "确    认";
            this.simpleButton2.Click += new System.EventHandler(this.simpleButton2_Click);
            // 
            // label87
            // 
            this.label87.BackColor = System.Drawing.Color.LightPink;
            this.label87.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label87.Font = new System.Drawing.Font("돋움체", 72F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label87.ForeColor = System.Drawing.Color.Black;
            this.label87.Location = new System.Drawing.Point(12, 14);
            this.label87.Margin = new System.Windows.Forms.Padding(3, 5, 3, 0);
            this.label87.Name = "label87";
            this.label87.Size = new System.Drawing.Size(910, 360);
            this.label87.TabIndex = 1252;
            this.label87.Text = "STATION #3 不良";
            this.label87.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // simpleButton4
            // 
            this.simpleButton4.AllowFocus = false;
            this.simpleButton4.Appearance.BackColor = System.Drawing.Color.LightYellow;
            this.simpleButton4.Appearance.BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(220)))), ((int)(((byte)(220)))), ((int)(((byte)(200)))));
            this.simpleButton4.Appearance.Font = new System.Drawing.Font("돋움체", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.simpleButton4.Appearance.GradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
            this.simpleButton4.Appearance.Options.UseBackColor = true;
            this.simpleButton4.Appearance.Options.UseFont = true;
            this.simpleButton4.ButtonStyle = DevExpress.XtraEditors.Controls.BorderStyles.Style3D;
            this.simpleButton4.Image = global::_PeopleWorks__UPB4860_Gen3_MC03_V4.Properties.Resources.kmixdocked_error;
            this.simpleButton4.ImageToTextAlignment = DevExpress.XtraEditors.ImageAlignToText.TopCenter;
            this.simpleButton4.Location = new System.Drawing.Point(12, 377);
            this.simpleButton4.Name = "simpleButton4";
            this.simpleButton4.Size = new System.Drawing.Size(136, 95);
            this.simpleButton4.TabIndex = 1253;
            this.simpleButton4.Text = "\r\n경고음 해제\r\n( 关掉蜂音器 )";
            this.simpleButton4.Click += new System.EventHandler(this.simpleButton4_Click);
            // 
            // RobotStartView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(934, 484);
            this.Controls.Add(this.simpleButton4);
            this.Controls.Add(this.label87);
            this.Controls.Add(this.simpleButton2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "RobotStartView";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "STATION #3 NG";
            this.Load += new System.EventHandler(this.RobotStartView_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.SimpleButton simpleButton2;
        private System.Windows.Forms.Label label87;
        private DevExpress.XtraEditors.SimpleButton simpleButton4;
    }
}