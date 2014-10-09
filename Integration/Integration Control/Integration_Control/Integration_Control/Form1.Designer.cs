namespace Integration_Control
{
    partial class Form1
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
            this.Robot_Controllers = new System.Windows.Forms.ListView();
            this.System_Name = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.IP_Address = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Version = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Robot_Data = new System.Windows.Forms.ListView();
            this.Data = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Start = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Robot_Controllers
            // 
            this.Robot_Controllers.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.System_Name,
            this.IP_Address,
            this.Version});
            this.Robot_Controllers.Location = new System.Drawing.Point(-1, 12);
            this.Robot_Controllers.Name = "Robot_Controllers";
            this.Robot_Controllers.Size = new System.Drawing.Size(527, 128);
            this.Robot_Controllers.TabIndex = 0;
            this.Robot_Controllers.UseCompatibleStateImageBehavior = false;
            this.Robot_Controllers.View = System.Windows.Forms.View.Details;
            this.Robot_Controllers.DoubleClick += new System.EventHandler(this.Robot_Controllers_DoubleClick);
            // 
            // System_Name
            // 
            this.System_Name.Text = "System Name";
            this.System_Name.Width = 130;
            // 
            // IP_Address
            // 
            this.IP_Address.Text = "IP Address";
            this.IP_Address.Width = 143;
            // 
            // Version
            // 
            this.Version.Text = "Version";
            this.Version.Width = 146;
            // 
            // Robot_Data
            // 
            this.Robot_Data.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Data});
            this.Robot_Data.Location = new System.Drawing.Point(-1, 146);
            this.Robot_Data.Name = "Robot_Data";
            this.Robot_Data.Size = new System.Drawing.Size(527, 104);
            this.Robot_Data.TabIndex = 1;
            this.Robot_Data.UseCompatibleStateImageBehavior = false;
            this.Robot_Data.View = System.Windows.Forms.View.Details;
            // 
            // Data
            // 
            this.Data.Text = "Robot Data";
            this.Data.Width = 515;
            // 
            // Start
            // 
            this.Start.Location = new System.Drawing.Point(12, 256);
            this.Start.Name = "Start";
            this.Start.Size = new System.Drawing.Size(100, 48);
            this.Start.TabIndex = 2;
            this.Start.Text = "Start Selected Robot";
            this.Start.UseVisualStyleBackColor = true;
            this.Start.Click += new System.EventHandler(this.Start_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(227, 269);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(526, 306);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Start);
            this.Controls.Add(this.Robot_Data);
            this.Controls.Add(this.Robot_Controllers);
            this.Name = "Form1";
            this.Text = "Integration Control V1.0";
            this.Load += new System.EventHandler(this.Initialise_Controller);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView Robot_Controllers;
        private System.Windows.Forms.ListView Robot_Data;
        private System.Windows.Forms.ColumnHeader System_Name;
        private System.Windows.Forms.ColumnHeader IP_Address;
        private System.Windows.Forms.ColumnHeader Version;
        private System.Windows.Forms.ColumnHeader Data;
        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.Button button1;
    }
}

