namespace Tile_Editor
{
    partial class frmOptions
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
            this.grpMap = new System.Windows.Forms.GroupBox();
            this.lblMCols = new System.Windows.Forms.Label();
            this.numMCols = new System.Windows.Forms.NumericUpDown();
            this.lblMRows = new System.Windows.Forms.Label();
            this.numMRows = new System.Windows.Forms.NumericUpDown();
            this.grpTile = new System.Windows.Forms.GroupBox();
            this.lblHeight = new System.Windows.Forms.Label();
            this.numHeight = new System.Windows.Forms.NumericUpDown();
            this.lblWidth = new System.Windows.Forms.Label();
            this.numWidth = new System.Windows.Forms.NumericUpDown();
            this.lblTCols = new System.Windows.Forms.Label();
            this.numTCols = new System.Windows.Forms.NumericUpDown();
            this.numTRows = new System.Windows.Forms.NumericUpDown();
            this.lblTRows = new System.Windows.Forms.Label();
            this.cmdObject = new System.Windows.Forms.Button();
            this.grpLayers = new System.Windows.Forms.GroupBox();
            this.cmdRemoveLayer = new System.Windows.Forms.Button();
            this.cmdAddLayer = new System.Windows.Forms.Button();
            this.lbLayers = new System.Windows.Forms.ListBox();
            this.grpCollision = new System.Windows.Forms.GroupBox();
            this.grpPoints = new System.Windows.Forms.GroupBox();
            this.lbPoints = new System.Windows.Forms.ListBox();
            this.cmdAddPoint = new System.Windows.Forms.Button();
            this.cmdRemovePoint = new System.Windows.Forms.Button();
            this.grpRegions = new System.Windows.Forms.GroupBox();
            this.lbBlockers = new System.Windows.Forms.ListBox();
            this.cmdAddBlock = new System.Windows.Forms.Button();
            this.cmdRemoveBlock = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.button2 = new System.Windows.Forms.Button();
            this.grpMap.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numMCols)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMRows)).BeginInit();
            this.grpTile.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTCols)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTRows)).BeginInit();
            this.grpLayers.SuspendLayout();
            this.grpCollision.SuspendLayout();
            this.grpPoints.SuspendLayout();
            this.grpRegions.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpMap
            // 
            this.grpMap.Controls.Add(this.lblMCols);
            this.grpMap.Controls.Add(this.numMCols);
            this.grpMap.Controls.Add(this.lblMRows);
            this.grpMap.Controls.Add(this.numMRows);
            this.grpMap.Location = new System.Drawing.Point(130, 12);
            this.grpMap.Name = "grpMap";
            this.grpMap.Size = new System.Drawing.Size(178, 75);
            this.grpMap.TabIndex = 1;
            this.grpMap.TabStop = false;
            this.grpMap.Text = "Map Size";
            // 
            // lblMCols
            // 
            this.lblMCols.AutoSize = true;
            this.lblMCols.Location = new System.Drawing.Point(122, 47);
            this.lblMCols.Name = "lblMCols";
            this.lblMCols.Size = new System.Drawing.Size(47, 13);
            this.lblMCols.TabIndex = 3;
            this.lblMCols.Text = "Columns";
            // 
            // numMCols
            // 
            this.numMCols.Location = new System.Drawing.Point(6, 45);
            this.numMCols.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numMCols.Name = "numMCols";
            this.numMCols.Size = new System.Drawing.Size(110, 20);
            this.numMCols.TabIndex = 2;
            this.numMCols.Value = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.numMCols.ValueChanged += new System.EventHandler(this.numMCols_ValueChanged);
            // 
            // lblMRows
            // 
            this.lblMRows.AutoSize = true;
            this.lblMRows.Location = new System.Drawing.Point(122, 21);
            this.lblMRows.Name = "lblMRows";
            this.lblMRows.Size = new System.Drawing.Size(34, 13);
            this.lblMRows.TabIndex = 1;
            this.lblMRows.Text = "Rows";
            // 
            // numMRows
            // 
            this.numMRows.Location = new System.Drawing.Point(6, 19);
            this.numMRows.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numMRows.Name = "numMRows";
            this.numMRows.Size = new System.Drawing.Size(110, 20);
            this.numMRows.TabIndex = 0;
            this.numMRows.Value = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.numMRows.ValueChanged += new System.EventHandler(this.numMRows_ValueChanged);
            // 
            // grpTile
            // 
            this.grpTile.Controls.Add(this.lblHeight);
            this.grpTile.Controls.Add(this.numHeight);
            this.grpTile.Controls.Add(this.lblWidth);
            this.grpTile.Controls.Add(this.numWidth);
            this.grpTile.Controls.Add(this.lblTCols);
            this.grpTile.Controls.Add(this.numTCols);
            this.grpTile.Controls.Add(this.numTRows);
            this.grpTile.Controls.Add(this.lblTRows);
            this.grpTile.Location = new System.Drawing.Point(130, 93);
            this.grpTile.Name = "grpTile";
            this.grpTile.Size = new System.Drawing.Size(178, 133);
            this.grpTile.TabIndex = 2;
            this.grpTile.TabStop = false;
            this.grpTile.Text = "Tileset Size";
            // 
            // lblHeight
            // 
            this.lblHeight.AutoSize = true;
            this.lblHeight.Location = new System.Drawing.Point(108, 109);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(58, 13);
            this.lblHeight.TabIndex = 11;
            this.lblHeight.Text = "Tile Height";
            // 
            // numHeight
            // 
            this.numHeight.Increment = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.numHeight.Location = new System.Drawing.Point(6, 107);
            this.numHeight.Maximum = new decimal(new int[] {
            1600,
            0,
            0,
            0});
            this.numHeight.Minimum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.numHeight.Name = "numHeight";
            this.numHeight.Size = new System.Drawing.Size(96, 20);
            this.numHeight.TabIndex = 10;
            this.numHeight.Value = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.numHeight.ValueChanged += new System.EventHandler(this.numHeight_ValueChanged);
            // 
            // lblWidth
            // 
            this.lblWidth.AutoSize = true;
            this.lblWidth.Location = new System.Drawing.Point(108, 83);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(55, 13);
            this.lblWidth.TabIndex = 9;
            this.lblWidth.Text = "Tile Width";
            // 
            // numWidth
            // 
            this.numWidth.Increment = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.numWidth.Location = new System.Drawing.Point(6, 81);
            this.numWidth.Maximum = new decimal(new int[] {
            1600,
            0,
            0,
            0});
            this.numWidth.Minimum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.numWidth.Name = "numWidth";
            this.numWidth.Size = new System.Drawing.Size(96, 20);
            this.numWidth.TabIndex = 8;
            this.numWidth.Value = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.numWidth.ValueChanged += new System.EventHandler(this.numWidth_ValueChanged);
            // 
            // lblTCols
            // 
            this.lblTCols.AutoSize = true;
            this.lblTCols.Location = new System.Drawing.Point(122, 46);
            this.lblTCols.Name = "lblTCols";
            this.lblTCols.Size = new System.Drawing.Size(47, 13);
            this.lblTCols.TabIndex = 7;
            this.lblTCols.Text = "Columns";
            // 
            // numTCols
            // 
            this.numTCols.Location = new System.Drawing.Point(6, 44);
            this.numTCols.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numTCols.Name = "numTCols";
            this.numTCols.Size = new System.Drawing.Size(110, 20);
            this.numTCols.TabIndex = 6;
            this.numTCols.Value = new decimal(new int[] {
            128,
            0,
            0,
            0});
            this.numTCols.ValueChanged += new System.EventHandler(this.numTCols_ValueChanged);
            // 
            // numTRows
            // 
            this.numTRows.Location = new System.Drawing.Point(6, 18);
            this.numTRows.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numTRows.Name = "numTRows";
            this.numTRows.Size = new System.Drawing.Size(110, 20);
            this.numTRows.TabIndex = 4;
            this.numTRows.Value = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.numTRows.ValueChanged += new System.EventHandler(this.numTRows_ValueChanged);
            // 
            // lblTRows
            // 
            this.lblTRows.AutoSize = true;
            this.lblTRows.Location = new System.Drawing.Point(122, 20);
            this.lblTRows.Name = "lblTRows";
            this.lblTRows.Size = new System.Drawing.Size(34, 13);
            this.lblTRows.TabIndex = 5;
            this.lblTRows.Text = "Rows";
            // 
            // cmdObject
            // 
            this.cmdObject.Location = new System.Drawing.Point(19, 176);
            this.cmdObject.Name = "cmdObject";
            this.cmdObject.Size = new System.Drawing.Size(99, 29);
            this.cmdObject.TabIndex = 1;
            this.cmdObject.Text = "Object/Trigger";
            this.cmdObject.UseVisualStyleBackColor = true;
            this.cmdObject.Visible = false;
            // 
            // grpLayers
            // 
            this.grpLayers.Controls.Add(this.cmdRemoveLayer);
            this.grpLayers.Controls.Add(this.cmdAddLayer);
            this.grpLayers.Controls.Add(this.lbLayers);
            this.grpLayers.Location = new System.Drawing.Point(12, 14);
            this.grpLayers.Name = "grpLayers";
            this.grpLayers.Size = new System.Drawing.Size(112, 143);
            this.grpLayers.TabIndex = 5;
            this.grpLayers.TabStop = false;
            this.grpLayers.Text = "Layers";
            // 
            // cmdRemoveLayer
            // 
            this.cmdRemoveLayer.Location = new System.Drawing.Point(6, 111);
            this.cmdRemoveLayer.Name = "cmdRemoveLayer";
            this.cmdRemoveLayer.Size = new System.Drawing.Size(100, 24);
            this.cmdRemoveLayer.TabIndex = 2;
            this.cmdRemoveLayer.Text = "Remove";
            this.cmdRemoveLayer.UseVisualStyleBackColor = true;
            this.cmdRemoveLayer.Click += new System.EventHandler(this.cmdRemoveLayer_Click);
            // 
            // cmdAddLayer
            // 
            this.cmdAddLayer.Location = new System.Drawing.Point(6, 81);
            this.cmdAddLayer.Name = "cmdAddLayer";
            this.cmdAddLayer.Size = new System.Drawing.Size(100, 24);
            this.cmdAddLayer.TabIndex = 1;
            this.cmdAddLayer.Text = "Add";
            this.cmdAddLayer.UseVisualStyleBackColor = true;
            this.cmdAddLayer.Click += new System.EventHandler(this.cmdAddLayer_Click);
            // 
            // lbLayers
            // 
            this.lbLayers.FormattingEnabled = true;
            this.lbLayers.Items.AddRange(new object[] {
            "Layer 0"});
            this.lbLayers.Location = new System.Drawing.Point(6, 19);
            this.lbLayers.Name = "lbLayers";
            this.lbLayers.Size = new System.Drawing.Size(100, 56);
            this.lbLayers.TabIndex = 0;
            this.lbLayers.SelectedIndexChanged += new System.EventHandler(this.lbLayers_SelectedIndexChanged);
            // 
            // grpCollision
            // 
            this.grpCollision.Controls.Add(this.grpPoints);
            this.grpCollision.Controls.Add(this.grpRegions);
            this.grpCollision.Location = new System.Drawing.Point(12, 227);
            this.grpCollision.Name = "grpCollision";
            this.grpCollision.Size = new System.Drawing.Size(296, 175);
            this.grpCollision.TabIndex = 6;
            this.grpCollision.TabStop = false;
            this.grpCollision.Text = "Collision";
            // 
            // grpPoints
            // 
            this.grpPoints.Controls.Add(this.lbPoints);
            this.grpPoints.Controls.Add(this.cmdAddPoint);
            this.grpPoints.Controls.Add(this.cmdRemovePoint);
            this.grpPoints.Location = new System.Drawing.Point(173, 19);
            this.grpPoints.Name = "grpPoints";
            this.grpPoints.Size = new System.Drawing.Size(117, 150);
            this.grpPoints.TabIndex = 7;
            this.grpPoints.TabStop = false;
            this.grpPoints.Text = "Points";
            // 
            // lbPoints
            // 
            this.lbPoints.FormattingEnabled = true;
            this.lbPoints.Location = new System.Drawing.Point(6, 49);
            this.lbPoints.Name = "lbPoints";
            this.lbPoints.Size = new System.Drawing.Size(100, 56);
            this.lbPoints.TabIndex = 0;
            this.lbPoints.SelectedIndexChanged += new System.EventHandler(this.lbPoints_SelectedIndexChanged);
            // 
            // cmdAddPoint
            // 
            this.cmdAddPoint.Location = new System.Drawing.Point(6, 19);
            this.cmdAddPoint.Name = "cmdAddPoint";
            this.cmdAddPoint.Size = new System.Drawing.Size(100, 24);
            this.cmdAddPoint.TabIndex = 1;
            this.cmdAddPoint.Text = "Add Points";
            this.cmdAddPoint.UseVisualStyleBackColor = true;
            this.cmdAddPoint.Click += new System.EventHandler(this.cmdAddPoint_Click);
            // 
            // cmdRemovePoint
            // 
            this.cmdRemovePoint.Location = new System.Drawing.Point(6, 111);
            this.cmdRemovePoint.Name = "cmdRemovePoint";
            this.cmdRemovePoint.Size = new System.Drawing.Size(100, 24);
            this.cmdRemovePoint.TabIndex = 2;
            this.cmdRemovePoint.Text = "Remove Selected";
            this.cmdRemovePoint.UseVisualStyleBackColor = true;
            // 
            // grpRegions
            // 
            this.grpRegions.Controls.Add(this.lbBlockers);
            this.grpRegions.Controls.Add(this.cmdAddBlock);
            this.grpRegions.Controls.Add(this.cmdRemoveBlock);
            this.grpRegions.Location = new System.Drawing.Point(7, 19);
            this.grpRegions.Name = "grpRegions";
            this.grpRegions.Size = new System.Drawing.Size(117, 150);
            this.grpRegions.TabIndex = 6;
            this.grpRegions.TabStop = false;
            this.grpRegions.Text = "Regions";
            // 
            // lbBlockers
            // 
            this.lbBlockers.FormattingEnabled = true;
            this.lbBlockers.Location = new System.Drawing.Point(6, 19);
            this.lbBlockers.Name = "lbBlockers";
            this.lbBlockers.Size = new System.Drawing.Size(100, 56);
            this.lbBlockers.TabIndex = 0;
            this.lbBlockers.SelectedIndexChanged += new System.EventHandler(this.lbBlockers_SelectedIndexChanged);
            // 
            // cmdAddBlock
            // 
            this.cmdAddBlock.Location = new System.Drawing.Point(7, 81);
            this.cmdAddBlock.Name = "cmdAddBlock";
            this.cmdAddBlock.Size = new System.Drawing.Size(100, 24);
            this.cmdAddBlock.TabIndex = 1;
            this.cmdAddBlock.Text = "Add";
            this.cmdAddBlock.UseVisualStyleBackColor = true;
            this.cmdAddBlock.Click += new System.EventHandler(this.cmdAddBlock_Click);
            // 
            // cmdRemoveBlock
            // 
            this.cmdRemoveBlock.Location = new System.Drawing.Point(7, 111);
            this.cmdRemoveBlock.Name = "cmdRemoveBlock";
            this.cmdRemoveBlock.Size = new System.Drawing.Size(100, 24);
            this.cmdRemoveBlock.TabIndex = 2;
            this.cmdRemoveBlock.Text = "Remove";
            this.cmdRemoveBlock.UseVisualStyleBackColor = true;
            this.cmdRemoveBlock.Click += new System.EventHandler(this.cmdRemoveBlock_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(82, 488);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(137, 23);
            this.button1.TabIndex = 7;
            this.button1.Text = "Add Helper Node";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(90, 413);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(120, 69);
            this.listBox1.TabIndex = 8;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(82, 512);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(137, 23);
            this.button2.TabIndex = 9;
            this.button2.Text = "Remove Helper Node";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // frmOptions
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(322, 546);
            this.ControlBox = false;
            this.Controls.Add(this.button2);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.grpCollision);
            this.Controls.Add(this.cmdObject);
            this.Controls.Add(this.grpLayers);
            this.Controls.Add(this.grpTile);
            this.Controls.Add(this.grpMap);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "frmOptions";
            this.Text = "Options";
            this.grpMap.ResumeLayout(false);
            this.grpMap.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numMCols)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMRows)).EndInit();
            this.grpTile.ResumeLayout(false);
            this.grpTile.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTCols)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTRows)).EndInit();
            this.grpLayers.ResumeLayout(false);
            this.grpCollision.ResumeLayout(false);
            this.grpPoints.ResumeLayout(false);
            this.grpRegions.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpMap;
        private System.Windows.Forms.Label lblMCols;
        private System.Windows.Forms.NumericUpDown numMCols;
        private System.Windows.Forms.Label lblMRows;
        private System.Windows.Forms.NumericUpDown numMRows;
        private System.Windows.Forms.GroupBox grpTile;
        private System.Windows.Forms.Label lblHeight;
        private System.Windows.Forms.NumericUpDown numHeight;
        private System.Windows.Forms.Label lblWidth;
        private System.Windows.Forms.NumericUpDown numWidth;
        private System.Windows.Forms.Label lblTCols;
        private System.Windows.Forms.NumericUpDown numTCols;
        private System.Windows.Forms.NumericUpDown numTRows;
        private System.Windows.Forms.Label lblTRows;
        private System.Windows.Forms.Button cmdObject;
        private System.Windows.Forms.GroupBox grpLayers;
        private System.Windows.Forms.ListBox lbLayers;
        private System.Windows.Forms.Button cmdRemoveLayer;
        private System.Windows.Forms.Button cmdAddLayer;
        private System.Windows.Forms.GroupBox grpCollision;
        private System.Windows.Forms.Button cmdRemoveBlock;
        private System.Windows.Forms.Button cmdAddBlock;
        private System.Windows.Forms.ListBox lbBlockers;
        private System.Windows.Forms.GroupBox grpRegions;
        private System.Windows.Forms.GroupBox grpPoints;
        private System.Windows.Forms.ListBox lbPoints;
        private System.Windows.Forms.Button cmdAddPoint;
        private System.Windows.Forms.Button cmdRemovePoint;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button2;
    }
}