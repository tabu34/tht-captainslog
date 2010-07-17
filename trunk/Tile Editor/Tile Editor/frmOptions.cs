using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Tile_Editor
{
    public partial class frmOptions : Form
    {
        int m_nMapRows;
        int m_nMapCols;
        int m_nTileRows;
        int m_nTileCols;
        int m_nTileWidth;
        int m_nTileHeight;
        int m_nSelectedLayer;
        int m_nSelectedBlocker;
        int m_nSelectedPoint;
        bool m_bBlock;

        public int MapRows
        {
            get { return m_nMapRows; }
            set { m_nMapRows = value; }
        }
        public int MapCols
        {
            get { return m_nMapCols; }
            set { m_nMapCols = value; }
        }
        public int TileRows
        {
            get { return m_nTileRows; }
            set { m_nTileRows = value; }
        }
        public int TileCols
        {
            get { return m_nTileCols; }
            set { m_nTileCols = value; }
        }
        public int TileWidth
        {
            get { return m_nTileWidth; }
            set { m_nTileWidth = value; }
        }
        public int TileHeight
        {
            get { return m_nTileHeight; }
            set { m_nTileHeight = value; }
        }
        public int SelectedLayer
        {
            get { return m_nSelectedLayer; }
            set { m_nSelectedLayer = value; }
        }
        public int SelectedBlocker
        {
            get { return m_nSelectedBlocker; }
            set { m_nSelectedBlocker = value; }
        }
        public int SelectedPoint
        {
            get { return m_nSelectedPoint; }
            set { m_nSelectedPoint = value; }
        }
        public bool Block
        {
            get { return m_bBlock; }
            set { m_bBlock = value; }
        }

        public event EventHandler optionsChanged;

        public event EventHandler layerAdded;
        public event EventHandler layerRemoved;

        public event EventHandler blockerAdded;
        public event EventHandler blockerRemoved;
        public event EventHandler pointAddToggle;


        public frmOptions()
        {
            InitializeComponent();
            SetInfo(256, 256, 64, 128, 16, 16, 0);
            lbLayers.SelectedIndex = 0;
        }

        public void SetInfo(int nMapRows, int nMapCols, int nTileRows, int nTileCols, int nTileWidth, int nTileHeight, int nSelectedLayer)
        {
            m_nMapRows = nMapRows;
            m_nMapCols = nMapCols;

            numMRows.Value = m_nMapRows;
            numMCols.Value = m_nMapCols;

            m_nTileRows = nTileRows;
            m_nTileCols = nTileCols;
            m_nTileWidth = nTileWidth;
            m_nTileHeight = nTileHeight;

            numTRows.Value = m_nTileRows;
            numTCols.Value = m_nTileCols;
            numWidth.Value = m_nTileWidth;
            numHeight.Value = m_nTileHeight;

            m_nSelectedLayer = nSelectedLayer;

            lbLayers.SelectedIndex = m_nSelectedLayer;
        }

        public void SetLayers(int numLayers)
        {
            for (int i = 0; i < lbLayers.Items.Count; i++)
            {
                lbLayers.Items.RemoveAt(0);
            }

            for (int i = 0; i < numLayers; i++)
            {
                lbLayers.Items.Add("Layer " + i);
            }
            lbLayers.SelectedIndex = 0;
        }

        private void numMRows_ValueChanged(object sender, EventArgs e)
        {
            m_nMapRows = (int)numMRows.Value;
            if (optionsChanged != null)
            {
                optionsChanged(this, new EventArgs());
            }
        }

        private void numMCols_ValueChanged(object sender, EventArgs e)
        {
            m_nMapCols = (int)numMCols.Value;
            if (optionsChanged != null)
            {
                optionsChanged(this, new EventArgs());
            }
        }

        private void numTRows_ValueChanged(object sender, EventArgs e)
        {
            m_nTileRows = (int)numTRows.Value;
            if (optionsChanged != null)
            {
                optionsChanged(this, new EventArgs());
            }
        }

        private void numTCols_ValueChanged(object sender, EventArgs e)
        {
            m_nTileCols = (int)numTCols.Value;
            if (optionsChanged != null)
            {
                optionsChanged(this, new EventArgs());
            }
        }

        private void numWidth_ValueChanged(object sender, EventArgs e)
        {
            m_nTileWidth = (int)numWidth.Value;
            if (optionsChanged != null)
            {
                optionsChanged(this, new EventArgs());
            }
        }

        private void numHeight_ValueChanged(object sender, EventArgs e)
        {
            m_nTileHeight = (int)numHeight.Value;
            if (optionsChanged != null)
            {
                optionsChanged(this, new EventArgs());
            }
        }

        private void lbLayers_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_nSelectedLayer = lbLayers.SelectedIndex;
            if (optionsChanged != null)
            {
                optionsChanged(this, new EventArgs());
            }
        }

        private void cmdAddLayer_Click(object sender, EventArgs e)
        {
            lbLayers.Items.Add("Layer " + lbLayers.Items.Count);
            if (layerAdded != null)
            {
                layerAdded(this, new EventArgs());
            }
        }

        private void cmdRemoveLayer_Click(object sender, EventArgs e)
        {
            if (lbLayers.Items.Count > 1 && m_nSelectedLayer != 0)
            {
                if (layerRemoved != null)
                {
                    layerRemoved(this, new EventArgs());
                } 

                lbLayers.Items.RemoveAt(m_nSelectedLayer);

                m_nSelectedLayer -= 1;
                if (m_nSelectedLayer < 0)
                {
                    m_nSelectedLayer = 0;
                }
            }
        }

        private void lbBlockers_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_nSelectedBlocker = lbBlockers.SelectedIndex;

            if (optionsChanged != null)
            {
                optionsChanged(this, new EventArgs());
            }
        }

        private void lbPoints_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_nSelectedPoint = lbPoints.SelectedIndex;
        }

        private void cmdAddBlock_Click(object sender, EventArgs e)
        {
            lbBlockers.Items.Add("Blocker " + lbBlockers.Items.Count);

            if (blockerAdded != null)
            {
                blockerAdded(this, new EventArgs());
            }
        }

        private void cmdRemoveBlock_Click(object sender, EventArgs e)
        {
            if (m_nSelectedBlocker != -1)
            {
                if (blockerRemoved != null)
                {
                    blockerRemoved(this, new EventArgs());
                }

                lbBlockers.Items.RemoveAt(m_nSelectedBlocker);
                
                m_nSelectedBlocker = -1;
            }   
        }

        private void cmdAddPoint_Click(object sender, EventArgs e)
        {
            if (m_bBlock)
            {
                cmdAddPoint.BackColor = Color.White;
            }
            else
            {
                cmdAddPoint.BackColor = Color.Red;
            }
            m_bBlock = !m_bBlock;

            if (pointAddToggle != null)
            {
                pointAddToggle(this, new EventArgs());
            }
        }
    }
}
