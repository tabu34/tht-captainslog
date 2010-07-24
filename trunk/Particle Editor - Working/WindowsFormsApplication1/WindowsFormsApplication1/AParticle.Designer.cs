namespace WindowsFormsApplication1
{
    partial class AParticle
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
            this.groupBoxScale = new System.Windows.Forms.GroupBox();
            this.numericUpDownMaxHeight = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDownMaxWidth = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.checkBoxRandScale = new System.Windows.Forms.CheckBox();
            this.numericUpDownScaleMinHeight = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.numericUpDownScaleMinWidth = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonApply = new System.Windows.Forms.Button();
            this.buttonGoBack = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.groupBoxScale.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMaxHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMaxWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownScaleMinHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownScaleMinWidth)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxScale
            // 
            this.groupBoxScale.Controls.Add(this.numericUpDownMaxHeight);
            this.groupBoxScale.Controls.Add(this.label2);
            this.groupBoxScale.Controls.Add(this.numericUpDownMaxWidth);
            this.groupBoxScale.Controls.Add(this.label3);
            this.groupBoxScale.Controls.Add(this.checkBoxRandScale);
            this.groupBoxScale.Controls.Add(this.numericUpDownScaleMinHeight);
            this.groupBoxScale.Controls.Add(this.label1);
            this.groupBoxScale.Controls.Add(this.numericUpDownScaleMinWidth);
            this.groupBoxScale.Controls.Add(this.label4);
            this.groupBoxScale.Location = new System.Drawing.Point(8, 7);
            this.groupBoxScale.Name = "groupBoxScale";
            this.groupBoxScale.Size = new System.Drawing.Size(214, 180);
            this.groupBoxScale.TabIndex = 0;
            this.groupBoxScale.TabStop = false;
            this.groupBoxScale.Text = "Scale (%)";
            // 
            // numericUpDownMaxHeight
            // 
            this.numericUpDownMaxHeight.Location = new System.Drawing.Point(135, 137);
            this.numericUpDownMaxHeight.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.numericUpDownMaxHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMaxHeight.Name = "numericUpDownMaxHeight";
            this.numericUpDownMaxHeight.Size = new System.Drawing.Size(62, 20);
            this.numericUpDownMaxHeight.TabIndex = 13;
            this.numericUpDownMaxHeight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 137);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(88, 13);
            this.label2.TabIndex = 12;
            this.label2.Text = "Maximum Height:";
            // 
            // numericUpDownMaxWidth
            // 
            this.numericUpDownMaxWidth.Location = new System.Drawing.Point(135, 104);
            this.numericUpDownMaxWidth.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.numericUpDownMaxWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMaxWidth.Name = "numericUpDownMaxWidth";
            this.numericUpDownMaxWidth.Size = new System.Drawing.Size(62, 20);
            this.numericUpDownMaxWidth.TabIndex = 11;
            this.numericUpDownMaxWidth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 106);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(85, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Maximum Width:";
            // 
            // checkBoxRandScale
            // 
            this.checkBoxRandScale.AutoSize = true;
            this.checkBoxRandScale.Location = new System.Drawing.Point(40, 84);
            this.checkBoxRandScale.Name = "checkBoxRandScale";
            this.checkBoxRandScale.Size = new System.Drawing.Size(96, 17);
            this.checkBoxRandScale.TabIndex = 9;
            this.checkBoxRandScale.Text = "Random Scale";
            this.checkBoxRandScale.UseVisualStyleBackColor = true;
            // 
            // numericUpDownScaleMinHeight
            // 
            this.numericUpDownScaleMinHeight.Location = new System.Drawing.Point(132, 58);
            this.numericUpDownScaleMinHeight.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.numericUpDownScaleMinHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownScaleMinHeight.Name = "numericUpDownScaleMinHeight";
            this.numericUpDownScaleMinHeight.Size = new System.Drawing.Size(65, 20);
            this.numericUpDownScaleMinHeight.TabIndex = 8;
            this.numericUpDownScaleMinHeight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 60);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(85, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Minimum Height:";
            // 
            // numericUpDownScaleMinWidth
            // 
            this.numericUpDownScaleMinWidth.Location = new System.Drawing.Point(132, 25);
            this.numericUpDownScaleMinWidth.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.numericUpDownScaleMinWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownScaleMinWidth.Name = "numericUpDownScaleMinWidth";
            this.numericUpDownScaleMinWidth.Size = new System.Drawing.Size(65, 20);
            this.numericUpDownScaleMinWidth.TabIndex = 6;
            this.numericUpDownScaleMinWidth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 27);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(82, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "Minimum Width:";
            // 
            // buttonOK
            // 
            this.buttonOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonOK.Location = new System.Drawing.Point(20, 222);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(94, 23);
            this.buttonOK.TabIndex = 1;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // buttonApply
            // 
            this.buttonApply.Location = new System.Drawing.Point(120, 193);
            this.buttonApply.Name = "buttonApply";
            this.buttonApply.Size = new System.Drawing.Size(92, 23);
            this.buttonApply.TabIndex = 2;
            this.buttonApply.Text = "Apply";
            this.buttonApply.UseVisualStyleBackColor = true;
            this.buttonApply.Click += new System.EventHandler(this.buttonApply_Click);
            // 
            // buttonGoBack
            // 
            this.buttonGoBack.Location = new System.Drawing.Point(20, 193);
            this.buttonGoBack.Name = "buttonGoBack";
            this.buttonGoBack.Size = new System.Drawing.Size(94, 23);
            this.buttonGoBack.TabIndex = 3;
            this.buttonGoBack.Text = "Go Back";
            this.buttonGoBack.UseVisualStyleBackColor = true;
            this.buttonGoBack.Click += new System.EventHandler(this.buttonGoBack_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Location = new System.Drawing.Point(120, 222);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(92, 23);
            this.buttonCancel.TabIndex = 4;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // AParticle
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(236, 255);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonGoBack);
            this.Controls.Add(this.buttonApply);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.groupBoxScale);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "AParticle";
            this.Text = "AParticle";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AParticle_FormClosing);
            this.groupBoxScale.ResumeLayout(false);
            this.groupBoxScale.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMaxHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMaxWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownScaleMinHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownScaleMinWidth)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxScale;
        private System.Windows.Forms.NumericUpDown numericUpDownScaleMinWidth;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numericUpDownScaleMinHeight;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonApply;
        private System.Windows.Forms.Button buttonGoBack;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.CheckBox checkBoxRandScale;
        private System.Windows.Forms.NumericUpDown numericUpDownMaxHeight;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numericUpDownMaxWidth;
        private System.Windows.Forms.Label label3;
    }
}