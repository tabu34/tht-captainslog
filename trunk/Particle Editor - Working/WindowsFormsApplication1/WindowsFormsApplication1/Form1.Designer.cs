namespace WindowsFormsApplication1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadParticleImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadBackgroundImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.advancedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.particleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.effectsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.comboBoxSource = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.buttonReset = new System.Windows.Forms.Button();
            this.groupBoxEffects = new System.Windows.Forms.GroupBox();
            this.groupBoxGrav = new System.Windows.Forms.GroupBox();
            this.checkBoxGravity = new System.Windows.Forms.CheckBox();
            this.numericUpDownGravityUpDown = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.numericUpDownGravityLeftRight = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.numericUpDownAlpha = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.EmitterBox = new System.Windows.Forms.GroupBox();
            this.numericUpDownEmitHeight = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownEmitWidth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownNParticles = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Particle1 = new System.Windows.Forms.GroupBox();
            this.numericUpDownMinLife = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownMaxLife = new System.Windows.Forms.NumericUpDown();
            this.buttonPickColor = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.comboBoxDestination = new System.Windows.Forms.ComboBox();
            this.label10 = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBoxEffects.SuspendLayout();
            this.groupBoxGrav.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownGravityUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownGravityLeftRight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlpha)).BeginInit();
            this.EmitterBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEmitHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEmitWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownNParticles)).BeginInit();
            this.Particle1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMinLife)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMaxLife)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.optionsToolStripMenuItem,
            this.advancedToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1215, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.loadToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(31, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.newToolStripMenuItem.Text = "New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.saveAsToolStripMenuItem.Text = "Save As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.loadToolStripMenuItem.Text = "Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadParticleImageToolStripMenuItem,
            this.loadBackgroundImageToolStripMenuItem});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // loadParticleImageToolStripMenuItem
            // 
            this.loadParticleImageToolStripMenuItem.Name = "loadParticleImageToolStripMenuItem";
            this.loadParticleImageToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
            this.loadParticleImageToolStripMenuItem.Text = "Load particle image";
            this.loadParticleImageToolStripMenuItem.Click += new System.EventHandler(this.loadParticleImageToolStripMenuItem_Click);
            // 
            // loadBackgroundImageToolStripMenuItem
            // 
            this.loadBackgroundImageToolStripMenuItem.Name = "loadBackgroundImageToolStripMenuItem";
            this.loadBackgroundImageToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
            this.loadBackgroundImageToolStripMenuItem.Text = "Load background image";
            this.loadBackgroundImageToolStripMenuItem.Click += new System.EventHandler(this.loadBackgroundImageToolStripMenuItem_Click);
            // 
            // advancedToolStripMenuItem
            // 
            this.advancedToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.particleToolStripMenuItem,
            this.effectsToolStripMenuItem});
            this.advancedToolStripMenuItem.Name = "advancedToolStripMenuItem";
            this.advancedToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.advancedToolStripMenuItem.Text = "Advanced";
            // 
            // particleToolStripMenuItem
            // 
            this.particleToolStripMenuItem.Name = "particleToolStripMenuItem";
            this.particleToolStripMenuItem.Size = new System.Drawing.Size(101, 22);
            this.particleToolStripMenuItem.Text = "Particle";
            this.particleToolStripMenuItem.Click += new System.EventHandler(this.particleToolStripMenuItem_Click);
            // 
            // effectsToolStripMenuItem
            // 
            this.effectsToolStripMenuItem.Name = "effectsToolStripMenuItem";
            this.effectsToolStripMenuItem.Size = new System.Drawing.Size(101, 22);
            this.effectsToolStripMenuItem.Text = "Effects";
            this.effectsToolStripMenuItem.Click += new System.EventHandler(this.effectsToolStripMenuItem_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 24);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.groupBox1);
            this.splitContainer1.Panel1.Controls.Add(this.buttonReset);
            this.splitContainer1.Panel1.Controls.Add(this.groupBoxEffects);
            this.splitContainer1.Panel1.Controls.Add(this.EmitterBox);
            this.splitContainer1.Panel1.Controls.Add(this.Particle1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.pictureBox);
            this.splitContainer1.Size = new System.Drawing.Size(1215, 714);
            this.splitContainer1.SplitterDistance = 239;
            this.splitContainer1.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBoxDestination);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.comboBoxSource);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Location = new System.Drawing.Point(4, 468);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(226, 112);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Blendmodes";
            // 
            // comboBoxSource
            // 
            this.comboBoxSource.FormattingEnabled = true;
            this.comboBoxSource.Items.AddRange(new object[] {
            "D3DBLEND_ZERO",
            "D3DBLEND_ONE",
            "D3DBLEND_SRCCOLOR",
            "D3DBLEND_INVSRCCOLOR",
            "D3DBLEND_SRCALPHA",
            "D3DBLEND_INVSRCALPHA",
            "D3DBLEND_DESTALPHA",
            "D3DBLEND_INVDESTALPHA",
            "D3DBLEND_DESTCOLOR",
            "D3DBLEND_INVDESTCOLOR",
            "D3DBLEND_SRCALPHASAT",
            "D3DBLEND_BOTHSRCALPHA",
            "D3DBLEND_BOTHINVSRCALPHA",
            "D3DBLEND_BLENDFACTOR"});
            this.comboBoxSource.Location = new System.Drawing.Point(8, 36);
            this.comboBoxSource.Name = "comboBoxSource";
            this.comboBoxSource.Size = new System.Drawing.Size(205, 21);
            this.comboBoxSource.TabIndex = 1;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(8, 20);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 13);
            this.label9.TabIndex = 0;
            this.label9.Text = "Source";
            // 
            // buttonReset
            // 
            this.buttonReset.Location = new System.Drawing.Point(155, 658);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(75, 23);
            this.buttonReset.TabIndex = 3;
            this.buttonReset.Text = "Reset";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // groupBoxEffects
            // 
            this.groupBoxEffects.Controls.Add(this.groupBoxGrav);
            this.groupBoxEffects.Controls.Add(this.numericUpDownAlpha);
            this.groupBoxEffects.Controls.Add(this.label6);
            this.groupBoxEffects.Location = new System.Drawing.Point(4, 279);
            this.groupBoxEffects.Name = "groupBoxEffects";
            this.groupBoxEffects.Size = new System.Drawing.Size(226, 182);
            this.groupBoxEffects.TabIndex = 2;
            this.groupBoxEffects.TabStop = false;
            this.groupBoxEffects.Text = "Effects";
            // 
            // groupBoxGrav
            // 
            this.groupBoxGrav.Controls.Add(this.checkBoxGravity);
            this.groupBoxGrav.Controls.Add(this.numericUpDownGravityUpDown);
            this.groupBoxGrav.Controls.Add(this.label8);
            this.groupBoxGrav.Controls.Add(this.numericUpDownGravityLeftRight);
            this.groupBoxGrav.Controls.Add(this.label7);
            this.groupBoxGrav.Location = new System.Drawing.Point(11, 60);
            this.groupBoxGrav.Name = "groupBoxGrav";
            this.groupBoxGrav.Size = new System.Drawing.Size(202, 105);
            this.groupBoxGrav.TabIndex = 7;
            this.groupBoxGrav.TabStop = false;
            this.groupBoxGrav.Text = "Initial Force";
            // 
            // checkBoxGravity
            // 
            this.checkBoxGravity.AutoSize = true;
            this.checkBoxGravity.Location = new System.Drawing.Point(71, 22);
            this.checkBoxGravity.Name = "checkBoxGravity";
            this.checkBoxGravity.Size = new System.Drawing.Size(116, 17);
            this.checkBoxGravity.TabIndex = 9;
            this.checkBoxGravity.Text = "Initial Force On/Off";
            this.checkBoxGravity.UseVisualStyleBackColor = true;
            this.checkBoxGravity.CheckedChanged += new System.EventHandler(this.checkBoxGravity_CheckedChanged);
            // 
            // numericUpDownGravityUpDown
            // 
            this.numericUpDownGravityUpDown.Location = new System.Drawing.Point(121, 76);
            this.numericUpDownGravityUpDown.Maximum = new decimal(new int[] {
            9001,
            0,
            0,
            0});
            this.numericUpDownGravityUpDown.Minimum = new decimal(new int[] {
            9001,
            0,
            0,
            -2147483648});
            this.numericUpDownGravityUpDown.Name = "numericUpDownGravityUpDown";
            this.numericUpDownGravityUpDown.Size = new System.Drawing.Size(66, 20);
            this.numericUpDownGravityUpDown.TabIndex = 8;
            this.numericUpDownGravityUpDown.ValueChanged += new System.EventHandler(this.numericUpDownGravityUpDown_ValueChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 78);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(99, 13);
            this.label8.TabIndex = 7;
            this.label8.Text = "Up ( - ) / Down ( + )";
            // 
            // numericUpDownGravityLeftRight
            // 
            this.numericUpDownGravityLeftRight.Location = new System.Drawing.Point(121, 42);
            this.numericUpDownGravityLeftRight.Maximum = new decimal(new int[] {
            9001,
            0,
            0,
            0});
            this.numericUpDownGravityLeftRight.Minimum = new decimal(new int[] {
            9001,
            0,
            0,
            -2147483648});
            this.numericUpDownGravityLeftRight.Name = "numericUpDownGravityLeftRight";
            this.numericUpDownGravityLeftRight.Size = new System.Drawing.Size(66, 20);
            this.numericUpDownGravityLeftRight.TabIndex = 6;
            this.numericUpDownGravityLeftRight.ValueChanged += new System.EventHandler(this.numericUpDownGravityLeftRight_ValueChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 44);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(100, 13);
            this.label7.TabIndex = 5;
            this.label7.Text = "Left ( - ) / Right ( + )";
            // 
            // numericUpDownAlpha
            // 
            this.numericUpDownAlpha.Location = new System.Drawing.Point(132, 31);
            this.numericUpDownAlpha.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericUpDownAlpha.Name = "numericUpDownAlpha";
            this.numericUpDownAlpha.Size = new System.Drawing.Size(66, 20);
            this.numericUpDownAlpha.TabIndex = 6;
            this.numericUpDownAlpha.ValueChanged += new System.EventHandler(this.numericUpDownAlpha_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 33);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(107, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "Alpha/Transparency:";
            // 
            // EmitterBox
            // 
            this.EmitterBox.Controls.Add(this.numericUpDownEmitHeight);
            this.EmitterBox.Controls.Add(this.numericUpDownEmitWidth);
            this.EmitterBox.Controls.Add(this.numericUpDownNParticles);
            this.EmitterBox.Controls.Add(this.label1);
            this.EmitterBox.Controls.Add(this.label5);
            this.EmitterBox.Controls.Add(this.label4);
            this.EmitterBox.Location = new System.Drawing.Point(4, 150);
            this.EmitterBox.Name = "EmitterBox";
            this.EmitterBox.Size = new System.Drawing.Size(226, 122);
            this.EmitterBox.TabIndex = 1;
            this.EmitterBox.TabStop = false;
            this.EmitterBox.Text = "Emitter";
            // 
            // numericUpDownEmitHeight
            // 
            this.numericUpDownEmitHeight.Location = new System.Drawing.Point(133, 57);
            this.numericUpDownEmitHeight.Maximum = new decimal(new int[] {
            1200,
            0,
            0,
            0});
            this.numericUpDownEmitHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownEmitHeight.Name = "numericUpDownEmitHeight";
            this.numericUpDownEmitHeight.Size = new System.Drawing.Size(65, 20);
            this.numericUpDownEmitHeight.TabIndex = 5;
            this.numericUpDownEmitHeight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownEmitHeight.ValueChanged += new System.EventHandler(this.numericUpDownEmitHeight_ValueChanged);
            // 
            // numericUpDownEmitWidth
            // 
            this.numericUpDownEmitWidth.Location = new System.Drawing.Point(134, 31);
            this.numericUpDownEmitWidth.Maximum = new decimal(new int[] {
            1200,
            0,
            0,
            0});
            this.numericUpDownEmitWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownEmitWidth.Name = "numericUpDownEmitWidth";
            this.numericUpDownEmitWidth.Size = new System.Drawing.Size(64, 20);
            this.numericUpDownEmitWidth.TabIndex = 4;
            this.numericUpDownEmitWidth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownEmitWidth.ValueChanged += new System.EventHandler(this.numericUpDownEmitWidth_ValueChanged);
            // 
            // numericUpDownNParticles
            // 
            this.numericUpDownNParticles.Location = new System.Drawing.Point(134, 83);
            this.numericUpDownNParticles.Maximum = new decimal(new int[] {
            9001,
            0,
            0,
            0});
            this.numericUpDownNParticles.Minimum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.numericUpDownNParticles.Name = "numericUpDownNParticles";
            this.numericUpDownNParticles.Size = new System.Drawing.Size(64, 20);
            this.numericUpDownNParticles.TabIndex = 3;
            this.numericUpDownNParticles.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.numericUpDownNParticles.ValueChanged += new System.EventHandler(this.numericUpDownNParticles_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 85);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(122, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Max number of particles:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 59);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "Height:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 33);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 13);
            this.label4.TabIndex = 0;
            this.label4.Text = "Width:";
            // 
            // Particle1
            // 
            this.Particle1.Controls.Add(this.numericUpDownMinLife);
            this.Particle1.Controls.Add(this.numericUpDownMaxLife);
            this.Particle1.Controls.Add(this.buttonPickColor);
            this.Particle1.Controls.Add(this.label3);
            this.Particle1.Controls.Add(this.label2);
            this.Particle1.Location = new System.Drawing.Point(3, 3);
            this.Particle1.Name = "Particle1";
            this.Particle1.Size = new System.Drawing.Size(227, 141);
            this.Particle1.TabIndex = 0;
            this.Particle1.TabStop = false;
            this.Particle1.Text = "Particles";
            // 
            // numericUpDownMinLife
            // 
            this.numericUpDownMinLife.Location = new System.Drawing.Point(134, 71);
            this.numericUpDownMinLife.Maximum = new decimal(new int[] {
            9000,
            0,
            0,
            0});
            this.numericUpDownMinLife.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMinLife.Name = "numericUpDownMinLife";
            this.numericUpDownMinLife.Size = new System.Drawing.Size(65, 20);
            this.numericUpDownMinLife.TabIndex = 6;
            this.numericUpDownMinLife.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMinLife.ValueChanged += new System.EventHandler(this.numericUpDownMinLife_ValueChanged);
            // 
            // numericUpDownMaxLife
            // 
            this.numericUpDownMaxLife.Location = new System.Drawing.Point(134, 42);
            this.numericUpDownMaxLife.Maximum = new decimal(new int[] {
            9001,
            0,
            0,
            0});
            this.numericUpDownMaxLife.Minimum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDownMaxLife.Name = "numericUpDownMaxLife";
            this.numericUpDownMaxLife.Size = new System.Drawing.Size(65, 20);
            this.numericUpDownMaxLife.TabIndex = 5;
            this.numericUpDownMaxLife.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDownMaxLife.ValueChanged += new System.EventHandler(this.numericUpDownMaxLife_ValueChanged);
            // 
            // buttonPickColor
            // 
            this.buttonPickColor.Location = new System.Drawing.Point(84, 99);
            this.buttonPickColor.Name = "buttonPickColor";
            this.buttonPickColor.Size = new System.Drawing.Size(75, 23);
            this.buttonPickColor.TabIndex = 4;
            this.buttonPickColor.Text = "Color Picker";
            this.buttonPickColor.UseVisualStyleBackColor = true;
            this.buttonPickColor.Click += new System.EventHandler(this.buttonPickColor_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 73);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(126, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Min particle life (sec/100)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 44);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(129, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Max particle life (sec/100)";
            // 
            // pictureBox
            // 
            this.pictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox.Location = new System.Drawing.Point(0, 0);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(972, 714);
            this.pictureBox.TabIndex = 0;
            this.pictureBox.TabStop = false;
            this.pictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseDown);
            this.pictureBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseUp);
            // 
            // comboBoxDestination
            // 
            this.comboBoxDestination.FormattingEnabled = true;
            this.comboBoxDestination.Items.AddRange(new object[] {
            "D3DBLEND_ZERO",
            "D3DBLEND_ONE",
            "D3DBLEND_SRCCOLOR",
            "D3DBLEND_INVSRCCOLOR",
            "D3DBLEND_SRCALPHA",
            "D3DBLEND_INVSRCALPHA",
            "D3DBLEND_DESTALPHA",
            "D3DBLEND_INVDESTALPHA",
            "D3DBLEND_DESTCOLOR",
            "D3DBLEND_INVDESTCOLOR",
            "D3DBLEND_SRCALPHASAT",
            "D3DBLEND_BOTHSRCALPHA",
            "D3DBLEND_BOTHINVSRCALPHA",
            "D3DBLEND_BLENDFACTOR"});
            this.comboBoxDestination.Location = new System.Drawing.Point(8, 76);
            this.comboBoxDestination.Name = "comboBoxDestination";
            this.comboBoxDestination.Size = new System.Drawing.Size(205, 21);
            this.comboBoxDestination.TabIndex = 3;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(8, 60);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(60, 13);
            this.label10.TabIndex = 2;
            this.label10.Text = "Destination";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1215, 738);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Particle Creator";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBoxEffects.ResumeLayout(false);
            this.groupBoxEffects.PerformLayout();
            this.groupBoxGrav.ResumeLayout(false);
            this.groupBoxGrav.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownGravityUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownGravityLeftRight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlpha)).EndInit();
            this.EmitterBox.ResumeLayout(false);
            this.EmitterBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEmitHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEmitWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownNParticles)).EndInit();
            this.Particle1.ResumeLayout(false);
            this.Particle1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMinLife)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMaxLife)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ToolStripMenuItem advancedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem particleToolStripMenuItem;
        private System.Windows.Forms.GroupBox Particle1;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadParticleImageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadBackgroundImageToolStripMenuItem;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numericUpDownMinLife;
        private System.Windows.Forms.NumericUpDown numericUpDownMaxLife;
        private System.Windows.Forms.Button buttonPickColor;
        private System.Windows.Forms.GroupBox EmitterBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numericUpDownNParticles;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDownEmitHeight;
        private System.Windows.Forms.NumericUpDown numericUpDownEmitWidth;
        private System.Windows.Forms.GroupBox groupBoxEffects;
        private System.Windows.Forms.NumericUpDown numericUpDownAlpha;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBoxGrav;
        private System.Windows.Forms.NumericUpDown numericUpDownGravityLeftRight;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown numericUpDownGravityUpDown;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button buttonReset;
        private System.Windows.Forms.ToolStripMenuItem effectsToolStripMenuItem;
        private System.Windows.Forms.CheckBox checkBoxGravity;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox comboBoxSource;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox comboBoxDestination;
        private System.Windows.Forms.Label label10;

    }
}

