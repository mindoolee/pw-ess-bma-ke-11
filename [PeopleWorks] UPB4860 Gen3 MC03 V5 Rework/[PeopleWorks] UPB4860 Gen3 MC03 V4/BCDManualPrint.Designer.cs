namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    partial class BCDManualPrint
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
            this.richTextBox3 = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.label131 = new System.Windows.Forms.Label();
            this.simpleButton17 = new DevExpress.XtraEditors.SimpleButton();
            this.SuspendLayout();
            // 
            // richTextBox3
            // 
            this.richTextBox3.Font = new System.Drawing.Font("돋움체", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.richTextBox3.Location = new System.Drawing.Point(98, 49);
            this.richTextBox3.Multiline = false;
            this.richTextBox3.Name = "richTextBox3";
            this.richTextBox3.Size = new System.Drawing.Size(164, 30);
            this.richTextBox3.TabIndex = 1124;
            this.richTextBox3.Text = "";
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label1.Font = new System.Drawing.Font("돋움체", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label1.ForeColor = System.Drawing.Color.LightGreen;
            this.label1.Location = new System.Drawing.Point(12, 49);
            this.label1.Margin = new System.Windows.Forms.Padding(3, 5, 3, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 30);
            this.label1.TabIndex = 1123;
            this.label1.Text = "NO.";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Font = new System.Drawing.Font("돋움체", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.richTextBox1.Location = new System.Drawing.Point(98, 14);
            this.richTextBox1.Multiline = false;
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(164, 30);
            this.richTextBox1.TabIndex = 1122;
            this.richTextBox1.Text = "TEST";
            // 
            // label131
            // 
            this.label131.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label131.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label131.Font = new System.Drawing.Font("돋움체", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label131.ForeColor = System.Drawing.Color.LightGreen;
            this.label131.Location = new System.Drawing.Point(12, 14);
            this.label131.Margin = new System.Windows.Forms.Padding(3, 5, 3, 0);
            this.label131.Name = "label131";
            this.label131.Size = new System.Drawing.Size(84, 30);
            this.label131.TabIndex = 1121;
            this.label131.Text = "MODEL NAME";
            this.label131.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // simpleButton17
            // 
            this.simpleButton17.AllowFocus = false;
            this.simpleButton17.Appearance.BackColor = System.Drawing.SystemColors.Control;
            this.simpleButton17.Appearance.BackColor2 = System.Drawing.Color.LightGray;
            this.simpleButton17.Appearance.Font = new System.Drawing.Font("돋움체", 9F);
            this.simpleButton17.Appearance.GradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
            this.simpleButton17.Appearance.Options.UseBackColor = true;
            this.simpleButton17.Appearance.Options.UseFont = true;
            this.simpleButton17.ButtonStyle = DevExpress.XtraEditors.Controls.BorderStyles.Style3D;
            this.simpleButton17.Image = global::_PeopleWorks__UPB4860_Gen3_MC03_V4.Properties.Resources.printmgr;
            this.simpleButton17.Location = new System.Drawing.Point(268, 12);
            this.simpleButton17.Name = "simpleButton17";
            this.simpleButton17.Size = new System.Drawing.Size(148, 67);
            this.simpleButton17.TabIndex = 1346;
            this.simpleButton17.Text = "바코드 재출력";
            this.simpleButton17.Click += new System.EventHandler(this.simpleButton17_Click);
            // 
            // BCDManualPrint
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(428, 90);
            this.Controls.Add(this.simpleButton17);
            this.Controls.Add(this.richTextBox3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.label131);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "BCDManualPrint";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "바코드 재출력";
            this.Load += new System.EventHandler(this.BCDManualPrint_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBox3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Label label131;
        private DevExpress.XtraEditors.SimpleButton simpleButton17;
    }
}