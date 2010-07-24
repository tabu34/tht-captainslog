namespace WindowsFormsApplication1
{
    partial class PEffect
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
            this.buttonOK = new System.Windows.Forms.Button();
            this.checkBoxGCrosshair = new System.Windows.Forms.CheckBox();
            this.checkBoxRSpread = new System.Windows.Forms.CheckBox();
            this.numericUpDownGravity = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.numericUpDownSpread = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownGravity)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpread)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonOK
            // 
            this.buttonOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonOK.Location = new System.Drawing.Point(86, 119);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(65, 23);
            this.buttonOK.TabIndex = 5;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // checkBoxGCrosshair
            // 
            this.checkBoxGCrosshair.AutoSize = true;
            this.checkBoxGCrosshair.Location = new System.Drawing.Point(13, 13);
            this.checkBoxGCrosshair.Name = "checkBoxGCrosshair";
            this.checkBoxGCrosshair.Size = new System.Drawing.Size(105, 17);
            this.checkBoxGCrosshair.TabIndex = 9;
            this.checkBoxGCrosshair.Text = "Gravity Crosshair";
            this.checkBoxGCrosshair.UseVisualStyleBackColor = true;
            this.checkBoxGCrosshair.CheckedChanged += new System.EventHandler(this.checkBoxGCrosshair_CheckedChanged);
            // 
            // checkBoxRSpread
            // 
            this.checkBoxRSpread.AutoSize = true;
            this.checkBoxRSpread.Location = new System.Drawing.Point(12, 50);
            this.checkBoxRSpread.Name = "checkBoxRSpread";
            this.checkBoxRSpread.Size = new System.Drawing.Size(103, 17);
            this.checkBoxRSpread.TabIndex = 10;
            this.checkBoxRSpread.Text = "Random Spread";
            this.checkBoxRSpread.UseVisualStyleBackColor = true;
            this.checkBoxRSpread.CheckedChanged += new System.EventHandler(this.checkBoxRSpread_CheckedChanged);
            // 
            // numericUpDownGravity
            // 
            this.numericUpDownGravity.Location = new System.Drawing.Point(173, 13);
            this.numericUpDownGravity.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDownGravity.Name = "numericUpDownGravity";
            this.numericUpDownGravity.Size = new System.Drawing.Size(69, 20);
            this.numericUpDownGravity.TabIndex = 13;
            this.numericUpDownGravity.ValueChanged += new System.EventHandler(this.numericUpDownGravity_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(124, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "Gravity:";
            // 
            // numericUpDownSpread
            // 
            this.numericUpDownSpread.Location = new System.Drawing.Point(172, 50);
            this.numericUpDownSpread.Maximum = new decimal(new int[] {
            9001,
            0,
            0,
            0});
            this.numericUpDownSpread.Name = "numericUpDownSpread";
            this.numericUpDownSpread.Size = new System.Drawing.Size(70, 20);
            this.numericUpDownSpread.TabIndex = 15;
            this.numericUpDownSpread.ValueChanged += new System.EventHandler(this.numericUpDownSpread_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(124, 52);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 13);
            this.label2.TabIndex = 16;
            this.label2.Text = "Spread:";
            // 
            // PEffect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(256, 155);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.numericUpDownSpread);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numericUpDownGravity);
            this.Controls.Add(this.checkBoxRSpread);
            this.Controls.Add(this.checkBoxGCrosshair);
            this.Controls.Add(this.buttonOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "PEffect";
            this.Text = "PEffect";
            this.TopMost = true;
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownGravity)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSpread)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.CheckBox checkBoxGCrosshair;
        private System.Windows.Forms.CheckBox checkBoxRSpread;
        private System.Windows.Forms.NumericUpDown numericUpDownGravity;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDownSpread;
        private System.Windows.Forms.Label label2;
    }
}