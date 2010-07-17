namespace Tile_Editor
{
    partial class frmTiles
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
            this.pnlTiles = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // pnlTiles
            // 
            this.pnlTiles.AutoScroll = true;
            this.pnlTiles.BackColor = System.Drawing.Color.White;
            this.pnlTiles.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlTiles.Location = new System.Drawing.Point(0, 0);
            this.pnlTiles.Name = "pnlTiles";
            this.pnlTiles.Size = new System.Drawing.Size(516, 394);
            this.pnlTiles.TabIndex = 0;
            this.pnlTiles.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pnlTiles_MouseClick);
            this.pnlTiles.Resize += new System.EventHandler(this.pnlTiles_Resize);
            // 
            // frmTiles
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(516, 394);
            this.ControlBox = false;
            this.Controls.Add(this.pnlTiles);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.KeyPreview = true;
            this.Name = "frmTiles";
            this.Text = "Tiles";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.frmTiles_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlTiles;
    }
}