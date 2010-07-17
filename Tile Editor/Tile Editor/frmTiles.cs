using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using SGD;

namespace Tile_Editor
{
    public partial class frmTiles : Form
    {
        Tileset tileset;

        public event EventHandler selectTile;

        ManagedDirect3D D3D;
        ManagedTextureManager MTM;

        public selectedTile selected;

        public frmTiles()
        {
            InitializeComponent();

            D3D = ManagedDirect3D.Instance;
            MTM = ManagedTextureManager.Instance;

            D3D.InitManagedDirect3D(pnlTiles, false);

            tileset = new Tileset();

            selected.tileNumber = 5;
            selected.rect = new Rectangle(0, 0, 16, 16);

            pnlTiles.AutoScrollMinSize = new Size(tileset.m_nRows * tileset.m_nWidth, tileset.m_nCols * tileset.m_nHeight);
        }

        public void Render()
        {
            D3D.Clear(pnlTiles, 255, 0, 255);
            D3D.DeviceBegin();
            D3D.SpriteBegin();

            MTM.Draw(tileset.m_nImageID, pnlTiles.AutoScrollPosition.X, pnlTiles.AutoScrollPosition.Y, 1.0f, 1.0f, Rectangle.Empty, 0, 0, 0.0f, 0);

            D3D.SpriteEnd(); 
            
            for (int i = 0; i <= tileset.m_nCols; i++)
            {
                D3D.DrawLine(i * tileset.m_nWidth + pnlTiles.AutoScrollPosition.X, pnlTiles.AutoScrollPosition.Y, 
                            i * tileset.m_nWidth + pnlTiles.AutoScrollPosition.X, pnlTiles.AutoScrollMinSize.Height + pnlTiles.AutoScrollPosition.Y, 0, 0, 0);
            }

            for (int i = 0; i <= tileset.m_nRows; i++)
            {
                D3D.DrawLine(pnlTiles.AutoScrollPosition.X, i * tileset.m_nHeight + pnlTiles.AutoScrollPosition.Y,
                            pnlTiles.AutoScrollMinSize.Width + pnlTiles.AutoScrollPosition.X,
                            i * tileset.m_nHeight + pnlTiles.AutoScrollPosition.Y, 0, 0, 0);
            }

            Rectangle selectedRect = new Rectangle((selected.rect.X - 1) * tileset.m_nWidth + pnlTiles.AutoScrollPosition.X, (selected.rect.Y - 1) * tileset.m_nHeight + pnlTiles.AutoScrollPosition.Y, selected.rect.Width, selected.rect.Height);
            D3D.DrawRect(selectedRect, 255, 0, 0);

            D3D.DeviceEnd();
            D3D.Present(pnlTiles);
        }

        public void SetTileset(Tileset other)
        {
            tileset.m_nRows = other.m_nRows;
            tileset.m_nCols = other.m_nCols;
            tileset.m_nWidth = other.m_nWidth;
            tileset.m_nHeight = other.m_nHeight;
            tileset.m_nImageID = other.m_nImageID;

            pnlTiles.AutoScrollMinSize = new Size(tileset.m_nCols * tileset.m_nWidth, tileset.m_nRows * tileset.m_nHeight);
        }

        public Panel GetPanel()
        {
            return pnlTiles;
        }

        private void frmTiles_KeyDown (object sender, System.Windows.Forms.KeyEventArgs e)
        {
            if (e.Alt && e.KeyCode == Keys.F4)
            {
                e.Handled = true;
            }
        }

        private void pnlTiles_Resize(object sender, EventArgs e)
        {
            D3D.ChangeDisplayParam(pnlTiles, false);
        }

        private void pnlTiles_MouseClick(object sender, MouseEventArgs e)
        {
            Point location = e.Location;

            location.X = (location.X + (location.X / (pnlTiles.Width / 20)) - pnlTiles.AutoScrollPosition.X) / tileset.m_nWidth;
            location.Y = (location.Y + (location.Y / (pnlTiles.Height / 20)) - pnlTiles.AutoScrollPosition.Y) / tileset.m_nHeight;

            if (location.X >= 0 && location.X < pnlTiles.AutoScrollMinSize.Width && location.Y >= 0 && location.Y < pnlTiles.AutoScrollMinSize.Height
                && location.X < tileset.m_nCols && location.Y < tileset.m_nRows)
            {
                selected.rect.X = location.X + 1;
                selected.rect.Y = location.Y + 1;
                selected.rect.Width = tileset.m_nWidth;
                selected.rect.Height = tileset.m_nHeight;

                selected.tileNumber = location.Y * tileset.m_nCols + location.X;
                
                if (selectTile != null)
                {
                    selectTile(this, new EventArgs());
                }
            }
        }
    }
}
