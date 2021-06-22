namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    partial class HipotDSSWAlarm
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
            this.label33 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label33
            // 
            this.label33.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label33.Font = new System.Drawing.Font("돋움", 72F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label33.ForeColor = System.Drawing.Color.LightPink;
            this.label33.Location = new System.Drawing.Point(12, 14);
            this.label33.Margin = new System.Windows.Forms.Padding(3, 5, 3, 0);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(1206, 362);
            this.label33.TabIndex = 34;
            this.label33.Text = "DS 스위치 ON";
            this.label33.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // HipotDSSWAlarm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(1232, 391);
            this.Controls.Add(this.label33);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "HipotDSSWAlarm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "DS 스위치 알람";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label33;
    }
}