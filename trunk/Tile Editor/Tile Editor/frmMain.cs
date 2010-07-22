using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Forms;
using System.IO;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using SGD;

namespace Tile_Editor
{
    public partial class frmMain : Form
    {
        ManagedDirect3D D3D;
        ManagedTextureManager MTM;

        float m_nVersionNumber;

        frmTiles tileWindow;
        frmOptions optionsWindow;

        List<Layer> m_lOldLayers;

        List<Layer> m_lLayers;      // All of the layers on the map
        List<Object> m_lObjects;    // All of the objects on the map
        List<Blocker> m_lBlockers;  // All of the blockers on the map
        List<Point> m_lHelperNodes; // All of the helper nodes on the map

        Tileset m_Tiles;

        int m_nMapWidth;
        int m_nMapHeight;

        String m_sFileName;
        String m_sFilePath;

        int m_nOffsetX;
        int m_nOffsetY;

        bool m_bUpdated;
        bool m_bLooping;
        bool m_bBlock;
        bool m_bHelperNode;

        int m_nCurrentLayer;
        int m_nCurrentBlocker;

        selectedTile selected;


        public bool Looping
        {
            get { return m_bLooping; }
            set { m_bLooping = value; }
        }

        public frmMain()
        {
            m_nVersionNumber = 0.1f;

            InitializeComponent();

            D3D = ManagedDirect3D.Instance;
            D3D.InitManagedDirect3D(pnlWorld, false);

            tileWindow = new frmTiles();
            tileWindow.selectTile += new EventHandler(tileWindow_selectTile);
            tileWindow.Show();

            optionsWindow = new frmOptions();
            optionsWindow.optionsChanged += new EventHandler(optionsWindow_optionsChanged);
            optionsWindow.layerAdded += new EventHandler(optionsWindow_layerAdded);
            optionsWindow.layerRemoved += new EventHandler(optionsWindow_layerRemoved);
            optionsWindow.blockerAdded += new EventHandler(optionsWindow_blockerAdded);
            optionsWindow.blockerRemoved += new EventHandler(optionsWindow_blockerRemoved);
            optionsWindow.pointAddToggle += new EventHandler(optionsWindow_pointAddToggle);
            optionsWindow.helperNodeAddToggle += new EventHandler(optionsWindow_helperNodeAddToggle);
            optionsWindow.Show();

            MTM = ManagedTextureManager.Instance;
            MTM.InitManagedTextureManager(D3D.Device, D3D.Sprite);

            m_nMapWidth = 256;
            m_nMapHeight = 256;
            m_nOffsetY = 1;
            m_nOffsetX = 1;
            m_sFileName = @"Resource\Graphics\tilesetpok.png";
            m_sFilePath = Path.Combine(Environment.CurrentDirectory, m_sFileName);

            m_lLayers = new List<Layer>();
            m_lOldLayers = new List<Layer>();
            m_lObjects = new List<Object>();
            m_lBlockers = new List<Blocker>();
            m_lHelperNodes = new List<Point>();
            m_Tiles = new Tileset();
            
            m_Tiles.m_nImageID = MTM.LoadTexture(m_sFilePath, 0);

            Layer tempLayer = new Layer();
            tempLayer.m_tTiles = new Tile[m_nMapWidth,m_nMapHeight];

            for (int i = 0; i < m_nMapWidth; i++)
            {
                for (int j = 0; j < m_nMapHeight; j++)
                {
                    Tile tempTile = new Tile();
                    tempTile.m_nWidth = 16;
                    tempTile.m_nHeight = 16;
                    tempTile.m_nTileNumber = -1;
                    tempTile.m_nTop = 16 * j;
                    tempTile.m_nLeft = 16 * i;
                    tempLayer.m_tTiles[i,j] = tempTile;
                }
            }
            m_lLayers.Add(tempLayer);

            Looping = true;

            pnlWorld.AutoScrollMinSize = new Size(m_nMapWidth * 16 - 1, m_nMapHeight * 16 - 1);

            selected.tileNumber = 5;
            selected.rect = new Rectangle(0, 0, 16, 16);

            m_nCurrentLayer = 0;

            tileWindow.SetTileset(m_Tiles);

            m_bBlock = false;
            m_bHelperNode = false;

            SyncBackup();
            m_bUpdated = true;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public void Render()
        {
            Rectangle src;

            D3D.Clear(pnlWorld, 0, 0, 0);
            D3D.DeviceBegin();
            D3D.SpriteBegin();

            for (int l = 0; l < m_lLayers.Count; l++)
            {
                for (int i = ((pnlWorld.Left - pnlWorld.AutoScrollPosition.X) / 16) - 1; i < ((pnlWorld.Right - pnlWorld.AutoScrollPosition.X) / 16) + 1; i++)
                {
                    if (i == -1)
                    {
                        i = 0;
                    }
                    else if (i >= m_nMapWidth)
                    {
                        break;
                    }
                    for (int j = ((pnlWorld.Top - pnlWorld.AutoScrollPosition.Y) / 16) - 1; j < ((pnlWorld.Bottom - pnlWorld.AutoScrollPosition.Y) / 16) + 1; j++)
                    {
                        if (j == -1)
                        {
                            j = 0;
                        }
                        else if (j >= m_nMapHeight)
                        {
                            break;
                        }
                        if (m_lLayers[l].m_tTiles[i, j].m_nTileNumber != -1)
                        {
                            src = new Rectangle((m_lLayers[l].m_tTiles[i, j].m_nTileNumber % m_Tiles.m_nCols) * m_lLayers[l].m_tTiles[i, j].m_nWidth + (m_lLayers[l].m_tTiles[i, j].m_nTileNumber % m_Tiles.m_nCols), (m_lLayers[l].m_tTiles[i, j].m_nTileNumber / m_Tiles.m_nCols) * m_lLayers[l].m_tTiles[i, j].m_nHeight + (m_lLayers[l].m_tTiles[i, j].m_nTileNumber / m_Tiles.m_nCols), m_lLayers[l].m_tTiles[i, j].m_nWidth, m_lLayers[l].m_tTiles[i, j].m_nHeight);
                            MTM.Draw(m_Tiles.m_nImageID, m_lLayers[l].m_tTiles[i, j].m_nLeft + pnlWorld.AutoScrollPosition.X, m_lLayers[l].m_tTiles[i, j].m_nTop + pnlWorld.AutoScrollPosition.Y, 1.0f, 1.0f, src, 0, 0, 0.0f, 0);
                        }
                    }
                }
            }

            D3D.SpriteEnd();
            
            for (int i = 0; i < m_lBlockers.Count; i++)
            {
                for (int j = 0; j < m_lBlockers[i].m_Points.Count - 1; j++)
                {
                    D3D.DrawLine(m_lBlockers[i].m_Points[j].X + pnlWorld.AutoScrollPosition.X, m_lBlockers[i].m_Points[j].Y + pnlWorld.AutoScrollPosition.Y, m_lBlockers[i].m_Points[j + 1].X + pnlWorld.AutoScrollPosition.X, m_lBlockers[i].m_Points[j + 1].Y + pnlWorld.AutoScrollPosition.Y, 255, 0, 0);
                }
                if (m_lBlockers[i].m_Points.Count > 1)
                {
                    D3D.DrawLine(m_lBlockers[i].m_Points[0].X + pnlWorld.AutoScrollPosition.X, m_lBlockers[i].m_Points[0].Y + pnlWorld.AutoScrollPosition.Y, m_lBlockers[i].m_Points[m_lBlockers[i].m_Points.Count - 1].X + pnlWorld.AutoScrollPosition.X, m_lBlockers[i].m_Points[m_lBlockers[i].m_Points.Count - 1].Y + pnlWorld.AutoScrollPosition.Y, 255, 0, 0);
                }
            }

            D3D.DeviceEnd();
            D3D.Present(pnlWorld);

            if (tileWindow != null)
            {
                tileWindow.Render();
            }
        }

        void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            Looping = false;
            D3D.Shutdown();
            MTM.ShutdownManagedTextureManager();
        }

        private void pnlWorld_MouseClick(object sender, MouseEventArgs e)
        {
            Point location = e.Location;
            
            if (m_bBlock == false && m_bHelperNode == false)
            {
                location.X = (location.X + (location.X / (pnlWorld.Width / 20)) - pnlWorld.AutoScrollPosition.X) / (selected.rect.Right - selected.rect.Left);
                location.Y = (location.Y + (location.Y / (pnlWorld.Height / 20)) - pnlWorld.AutoScrollPosition.Y) / (selected.rect.Bottom - selected.rect.Top);

                location.X = location.X * ((selected.rect.Right - selected.rect.Left) / 16);
                location.Y = location.Y * ((selected.rect.Bottom - selected.rect.Top) / 16);

                if (location.X >= 0 && location.X < m_nMapWidth && location.Y >= 0 && location.Y < m_nMapHeight)
                {
                    m_lLayers[m_nCurrentLayer].m_tTiles[location.X, location.Y].m_nWidth = selected.rect.Width;
                    m_lLayers[m_nCurrentLayer].m_tTiles[location.X, location.Y].m_nHeight = selected.rect.Height;
                    m_lLayers[m_nCurrentLayer].m_tTiles[location.X, location.Y].m_nTileNumber = selected.tileNumber;

                    if (m_bUpdated)
                    {
                        m_bUpdated = false;
                    }
                    else
                    {
                        SyncBackup();
                    }
                }
            }
            
            if(m_bBlock == true && m_bHelperNode == false)
            {
                location.X = (location.X + (location.X / (pnlWorld.Width / 20)) - pnlWorld.AutoScrollPosition.X);
                location.Y = (location.Y + (location.Y / (pnlWorld.Height / 20)) - pnlWorld.AutoScrollPosition.Y);

                if (location.X >= 0 && location.X < m_nMapWidth * 16 && location.Y >= 0 && location.Y < m_nMapHeight * 16)
                {
                    Point tempPoint = new Point();
                    tempPoint.X = location.X;
                    tempPoint.Y = location.Y;
                    m_lBlockers[m_nCurrentBlocker].m_Points.Add(tempPoint);
                }
            }

            if (m_bHelperNode == true && m_bBlock == false)
            {
                location.X = (location.X + (location.X / (pnlWorld.Width / 20)) - pnlWorld.AutoScrollPosition.X);
                location.Y = (location.Y + (location.Y / (pnlWorld.Height / 20)) - pnlWorld.AutoScrollPosition.Y);

                if (location.X >= 0 && location.X < m_nMapWidth * 16 && location.Y >= 0 && location.Y < m_nMapHeight * 16)
                {
                    Point tempPoint = new Point();
                    tempPoint.X = location.X;
                    tempPoint.Y = location.Y;
                    m_lHelperNodes.Add(tempPoint);
                }
            }
        }

        private void pnlWorld_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left && m_bBlock == false && m_bHelperNode == false)
            {
                pnlWorld_MouseClick(sender, e);
            }
        }

        void tileWindow_selectTile(object sender, EventArgs e)
        {
            frmTiles window = (frmTiles)sender;
            selected = window.selected;
        }

        void optionsWindow_optionsChanged(object sender, EventArgs e)
        {
            frmOptions window = (frmOptions)sender;            
            
            for (int l = 0; l < m_lLayers.Count; l++)
            {
                Tile[,] tempTiles = new Tile[m_nMapWidth, m_nMapHeight];
                Array.Copy(m_lLayers[l].m_tTiles, tempTiles, m_lLayers[l].m_tTiles.Length);
                m_lLayers[l].m_tTiles = new Tile[window.MapCols, window.MapRows];

                for (int i = 0; i < window.MapCols; i++)
                {
                    for (int j = 0; j < window.MapRows; j++)
                    {
                        Tile tempTile = new Tile();
                        tempTile.m_nWidth = 16;
                        tempTile.m_nHeight = 16;
                        tempTile.m_nTileNumber = 0;
                        tempTile.m_nTop = 16 * j;
                        tempTile.m_nLeft = 16 * i;
                        m_lLayers[l].m_tTiles[i, j] = tempTile;
                    }
                }
                if (m_lLayers[l].m_tTiles.Length < tempTiles.Length)
                {
                    //Array.Copy(m_lLayers[l].m_tTiles, tempTiles, m_lLayers[l].m_tTiles.Length);
                    for (int i = 0; i < window.MapCols; i++)
                    {
                        for (int j = 0; j < window.MapRows; j++)
                        {
                            m_lLayers[l].m_tTiles[i,j] = tempTiles[i,j];
                        }
                    }
                }
                else
                {
                    //Array.Copy(tempTiles, m_lLayers[l].m_tTiles, tempTiles.Length);
                    for (int i = 0; i < m_nMapWidth; i++)
                    {
                        for (int j = 0; j < m_nMapHeight; j++)
                        {
                            m_lLayers[l].m_tTiles[i, j] = tempTiles[i, j];
                        }
                    }
                }
            }
            
            m_nMapWidth = window.MapCols;
            m_nMapHeight = window.MapRows;

            m_Tiles.m_nRows = window.TileRows;
            m_Tiles.m_nCols = window.TileCols;
            m_Tiles.m_nWidth = window.TileWidth;
            m_Tiles.m_nHeight = window.TileHeight;

            m_nCurrentLayer = window.SelectedLayer;
            m_nCurrentBlocker = window.SelectedBlocker;

            tileWindow.SetTileset(m_Tiles);
        }

        void optionsWindow_layerAdded(object sender, EventArgs e)
        {
            Layer newLayer = new Layer();
            newLayer.m_tTiles = new Tile[m_nMapWidth, m_nMapHeight];

            for (int i = 0; i < m_nMapWidth; i++)
            {
                for (int j = 0; j < m_nMapHeight; j++)
                {
                    Tile tempTile = new Tile();
                    tempTile.m_nWidth = 16;
                    tempTile.m_nHeight = 16;
                    tempTile.m_nTileNumber = -1;
                    tempTile.m_nTop = 16 * j;
                    tempTile.m_nLeft = 16 * i;
                    newLayer.m_tTiles[i, j] = tempTile;
                }
            }

            m_lLayers.Add(newLayer);

            if (m_bUpdated)
            {
                m_bUpdated = false;
            }
            else
            {
                SyncBackup();
            }
        }

        void optionsWindow_layerRemoved(object sender, EventArgs e)
        {
            frmOptions window = (frmOptions)sender;
            m_lLayers.Remove(m_lLayers[window.SelectedLayer]);
            m_nCurrentLayer--;
            if (m_nCurrentLayer < 0)
            {
                m_nCurrentLayer = 0;
            }

            if (m_bUpdated)
            {
                m_bUpdated = false;
            }
            else
            {
                SyncBackup();
            }
        }

        void optionsWindow_blockerAdded(object sender, EventArgs e)
        {
            Blocker tempBlocker = new Blocker();
            tempBlocker.m_Points = new List<Point>();

            m_lBlockers.Add(tempBlocker);
        }

        void optionsWindow_blockerRemoved(object sender, EventArgs e)
        {
            frmOptions window = (frmOptions)sender;

            if (window.SelectedBlocker != -1)
            {
	            m_lBlockers.Remove(m_lBlockers[window.SelectedBlocker]);
            }
        }

        void optionsWindow_pointAddToggle(object sender, EventArgs e)
        {
            frmOptions window = (frmOptions)sender;
            m_nCurrentBlocker = window.SelectedBlocker;
            m_bBlock = !m_bBlock;
        }

        void optionsWindow_helperNodeAddToggle(object sender, EventArgs e)
        {
            frmOptions window = (frmOptions)sender;
            m_bHelperNode = !m_bHelperNode;
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "Map File(*.mfl)|*.mfl|Text File(*.txt)|.txt";
            dlg.DefaultExt = "mfl";

            if (DialogResult.OK == dlg.ShowDialog())
            {
                if (dlg.FileName.Contains(".mfl"))
                {
                    using (BinaryWriter binWriter = new BinaryWriter(File.Open(dlg.FileName, FileMode.Create)))
                    {
                        binWriter.Write(m_nVersionNumber);
                        binWriter.Write(m_sFileName.Length);
                        binWriter.Write(m_sFileName.ToCharArray());
                        binWriter.Write(m_Tiles.m_nRows);
                        binWriter.Write(m_Tiles.m_nCols);
                        binWriter.Write(m_nMapWidth);
                        binWriter.Write(m_nMapHeight);
                        binWriter.Write(m_lLayers.Count);
                        for (int l = 0; l < m_lLayers.Count; l++)
                        {
                            for (int i = 0; i < m_nMapWidth; i++)
                            {
                                for (int j = 0; j < m_nMapHeight; j++)
                                {
                                    binWriter.Write(m_lLayers[l].m_tTiles[i, j].m_nWidth);
                                    binWriter.Write(m_lLayers[l].m_tTiles[i, j].m_nHeight);
                                    binWriter.Write(m_lLayers[l].m_tTiles[i, j].m_nTileNumber);
                                    binWriter.Write(m_lLayers[l].m_tTiles[i, j].m_nTop);
                                    binWriter.Write(m_lLayers[l].m_tTiles[i, j].m_nLeft);
                                }
                            }
                        }

                        binWriter.Write(m_lHelperNodes.Count);
                        for (int i = 0; i < m_lHelperNodes.Count; i++)
                        {
                            binWriter.Write(m_lHelperNodes[i].X);
                            binWriter.Write(m_lHelperNodes[i].Y);
                        }

                        binWriter.Write(m_lBlockers.Count);
                        for (int i = 0; i < m_lBlockers.Count; i++)
                        {
                            binWriter.Write(m_lBlockers[i].m_Points.Count);
                            for (int j = 0; j < m_lBlockers[i].m_Points.Count; j++)
                            {
                                binWriter.Write(m_lBlockers[i].m_Points[j].X);
                                binWriter.Write(m_lBlockers[i].m_Points[j].Y);
                            }
                        }
                        


                    }
                }
                else
                {
                    TextWriter textWriter = new StreamWriter(dlg.FileName);

                    textWriter.WriteLine(m_nVersionNumber);
                    textWriter.WriteLine(m_sFileName);
                    textWriter.WriteLine(m_nMapWidth);
                    textWriter.WriteLine(m_nMapHeight);
                    textWriter.WriteLine(m_lLayers.Count);
                    textWriter.WriteLine("");
                    for (int l = 0; l < m_lLayers.Count; l++)
                    {
                        for (int i = 0; i < m_nMapWidth; i++)
                        {
                            for (int j = 0; j < m_nMapHeight; j++)
                            {
                                textWriter.WriteLine(m_lLayers[l].m_tTiles[i, j].m_nWidth);
                                textWriter.WriteLine(m_lLayers[l].m_tTiles[i, j].m_nHeight);
                                textWriter.WriteLine(m_lLayers[l].m_tTiles[i, j].m_nTileNumber);
                                textWriter.WriteLine(m_lLayers[l].m_tTiles[i, j].m_nTop);
                                textWriter.WriteLine(m_lLayers[l].m_tTiles[i, j].m_nLeft);
                                textWriter.WriteLine("");
                            }
                        }
                    }

                    textWriter.WriteLine(m_lObjects.Count);
                    textWriter.WriteLine("");
                    for (int i = 0; i < m_lObjects.Count; i++)
                    {
                        textWriter.WriteLine(m_lObjects[i].m_nTop);
                        textWriter.WriteLine(m_lObjects[i].m_nLeft);
                        textWriter.WriteLine(m_lObjects[i].m_nID);
                        textWriter.WriteLine("");
                    }

                    textWriter.WriteLine(m_lBlockers.Count);
                    textWriter.WriteLine("");
                    for (int i = 0; i < m_lBlockers.Count; i++)
                    {
                        textWriter.WriteLine(m_lBlockers[i].m_Points.Count);
                        for (int j = 0; j < m_lBlockers[i].m_Points.Count; j++)
                        {
                            textWriter.WriteLine(m_lBlockers[i].m_Points[j].X);
                            textWriter.WriteLine(m_lBlockers[i].m_Points[j].Y);
                            textWriter.WriteLine("");
                        }
                    }

                    textWriter.Close();
                }
            }
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Map File(*.mfl)|*.mfl";
            dlg.DefaultExt = "mfl";

            if (DialogResult.OK == dlg.ShowDialog())
            {
                BinaryReader binReader = new BinaryReader(File.Open(dlg.FileName, FileMode.Open));

                m_nVersionNumber = binReader.ReadSingle();

                int nFileNameSize = binReader.ReadInt32();

                char[] szFileName = new char[nFileNameSize];
                szFileName = binReader.ReadChars(nFileNameSize);

                m_sFileName = new String(szFileName);

                m_sFilePath = Path.Combine(Environment.CurrentDirectory, m_sFileName);
                m_Tiles.m_nImageID = MTM.LoadTexture(m_sFilePath, 0);

                m_Tiles.m_nWidth = binReader.ReadInt32();
                m_Tiles.m_nHeight = binReader.ReadInt32();

                m_nMapWidth = binReader.ReadInt32();
                m_nMapHeight = binReader.ReadInt32();
                int layerCount = binReader.ReadInt32();

                m_lLayers.RemoveRange(0, m_lLayers.Count);
                m_lLayers = new List<Layer>();

                for (int l = 0; l < layerCount; l++)
                {
                    Layer tempLayer = new Layer();
                    tempLayer.m_tTiles = new Tile[m_nMapWidth, m_nMapHeight];
                    for (int i = 0; i < m_nMapWidth; i++)
                    {
                        for (int j = 0; j < m_nMapHeight; j++)
                        {
                            Tile tempTile = new Tile();

                            tempTile.m_nWidth = binReader.ReadInt32();
                            tempTile.m_nHeight = binReader.ReadInt32();
                            tempTile.m_nTileNumber = binReader.ReadInt32();
                            tempTile.m_nTop = binReader.ReadInt32();
                            tempTile.m_nLeft = binReader.ReadInt32();

                            tempLayer.m_tTiles[i, j] = tempTile;
                        }
                    }
                    m_lLayers.Add(tempLayer);
                }


                int helperNodeCount = binReader.ReadInt32();
                m_lHelperNodes.Clear();
                for (int i = 0; i < helperNodeCount; i++)
                {
                    Point tempPoint = new Point();
                    tempPoint.X = binReader.ReadInt32();
                    tempPoint.Y = binReader.ReadInt32();
                    m_lHelperNodes.Add(tempPoint);
                }

                int blockerCount = binReader.ReadInt32();
                for (int i = 0; i < m_lBlockers.Count; i++)
                {
                    int pointCount = binReader.ReadInt32();
                    for (int j = 0; j < pointCount; j++)
                    {
                        Point tempPoint = new Point();
                        tempPoint.X = binReader.ReadInt32();
                        tempPoint.Y = binReader.ReadInt32();
                    }
                }


            }
            optionsWindow.SetInfo(m_nMapHeight, m_nMapWidth, m_Tiles.m_nRows, m_Tiles.m_nCols, m_Tiles.m_nWidth, m_Tiles.m_nHeight, 0);
            optionsWindow.SetLayers(m_lLayers.Count);
            m_nCurrentLayer = 0;
        }

        private void loadTilesetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.Filter = "Bitmap(*.bmp)|*.bmp|PNG Image(*.png)|*.png";

            ofd.InitialDirectory = Environment.CurrentDirectory;

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                m_Tiles.m_nImageID = MTM.LoadTexture(ofd.FileName, 0);

                m_sFilePath = ofd.FileName;

                SaveFilePath(ofd.FileName);

                tileWindow.SetTileset(m_Tiles);
            }
        }

        private void SaveFilePath(string sFilePath)
        {
            string[] splitPath;
            splitPath = sFilePath.Split("\\".ToCharArray());
            string[] currentPath; 
            currentPath = Environment.CurrentDirectory.Split("\\".ToCharArray());

            m_sFileName = null;
            int nFirstDiffIndex = currentPath.Length;

            for (int i = 0; i < currentPath.Length && i < splitPath.Length; i++)
            {
                if (splitPath[i] == currentPath[i])
                {
                    continue;
                }
                else
                {
                    nFirstDiffIndex = i;
                    break;
                }
            }

            for (int i = nFirstDiffIndex; i < splitPath.Length; i++)
            {
                m_sFileName += splitPath[i];
                if (i + 1 < splitPath.Length)
                {
                    m_sFileName += "\\";
                }
            }
        }

        private void newFile()
        {
            m_nMapWidth = 256;
            m_nMapHeight = 256;

            m_lLayers = new List<Layer>();
            m_lObjects = new List<Object>();
            m_lBlockers = new List<Blocker>();

            m_Tiles = new Tileset();

            m_Tiles.m_nImageID = MTM.LoadTexture(m_sFilePath, 0);

            Layer tempLayer = new Layer();
            tempLayer.m_tTiles = new Tile[m_nMapWidth, m_nMapHeight];

            for (int i = 0; i < m_nMapWidth; i++)
            {
                for (int j = 0; j < m_nMapHeight; j++)
                {
                    Tile tempTile = new Tile();
                    tempTile.m_nWidth = 16;
                    tempTile.m_nHeight = 16;
                    tempTile.m_nTileNumber = 0;
                    tempTile.m_nTop = 16 * j;
                    tempTile.m_nLeft = 16 * i;
                    tempLayer.m_tTiles[i, j] = tempTile;
                }
            }
            m_lLayers.Add(tempLayer);

            Looping = true;

            pnlWorld.AutoScrollMinSize = new Size(m_nMapWidth * 16 - 1, m_nMapHeight * 16 - 1);

            selected.tileNumber = 5;
            selected.rect = new Rectangle(0, 0, 16, 16);

            m_nCurrentLayer = 0;

            tileWindow.SetTileset(m_Tiles);

            m_bBlock = false;

            SyncBackup();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            newFile();
        }

        private void frmMain_Resize(object sender, EventArgs e)
        {
            D3D.ChangeDisplayParam(pnlWorld, false);
        }

        private void Undo()
        {
            m_lLayers.RemoveRange(0, m_lLayers.Count);
            m_lLayers = new List<Layer>();
            for (int l = 0; l < m_lOldLayers.Count; l++)
            {
                Layer tempLayer = new Layer();

                tempLayer.m_tTiles = new Tile[m_nMapWidth, m_nMapHeight];

                for (int i = 0; i < m_nMapWidth; i++)
                {
                    for (int j = 0; j < m_nMapHeight; j++)
                    {
                        Tile tempTile = new Tile();

                        tempTile.m_nHeight = m_lOldLayers[l].m_tTiles[i, j].m_nHeight;
                        tempTile.m_nLeft = m_lOldLayers[l].m_tTiles[i, j].m_nLeft;
                        tempTile.m_nTileNumber = m_lOldLayers[l].m_tTiles[i, j].m_nTileNumber;
                        tempTile.m_nTop = m_lOldLayers[l].m_tTiles[i, j].m_nTop;
                        tempTile.m_nWidth = m_lOldLayers[l].m_tTiles[i, j].m_nWidth;

                        tempLayer.m_tTiles[i, j] = tempTile;
                    }
                }

                m_lLayers.Add(tempLayer);
            }
            m_bUpdated = true;
        }

        private void SyncBackup()
        {
            m_lOldLayers.RemoveRange(0, m_lOldLayers.Count);
            m_lOldLayers = new List<Layer>();
            for (int l = 0; l < m_lLayers.Count; l++)
            {
                Layer tempLayer = new Layer();

                tempLayer.m_tTiles = new Tile[m_nMapWidth, m_nMapHeight];

                for (int i = 0; i < m_nMapWidth; i++)
                {
                    for (int j = 0; j < m_nMapHeight; j++)
                    {
                        Tile tempTile = new Tile();

                        tempTile.m_nHeight = m_lLayers[l].m_tTiles[i, j].m_nHeight;
                        tempTile.m_nLeft = m_lLayers[l].m_tTiles[i, j].m_nLeft;
                        tempTile.m_nTileNumber = m_lLayers[l].m_tTiles[i, j].m_nTileNumber;
                        tempTile.m_nTop = m_lLayers[l].m_tTiles[i, j].m_nTop;
                        tempTile.m_nWidth = m_lLayers[l].m_tTiles[i, j].m_nWidth;

                        tempLayer.m_tTiles[i, j] = tempTile;
                    }
                }

                m_lOldLayers.Add(tempLayer);
            }
            m_bUpdated = true;
        }

        private void undoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Undo();
        }

        private void fillToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for(int x = 0; x < m_nMapWidth; x++)
                for (int y = 0; y < m_nMapHeight; y++)
                {
                    m_lLayers[m_nCurrentLayer].m_tTiles[x, y].m_nWidth = selected.rect.Width;
                    m_lLayers[m_nCurrentLayer].m_tTiles[x, y].m_nHeight = selected.rect.Height;
                    m_lLayers[m_nCurrentLayer].m_tTiles[x, y].m_nTileNumber = selected.tileNumber;
                }
        }

    }

    public struct selectedTile
    {
        public Rectangle rect;
        public int tileNumber;
    };

    public class Tileset
    {
        public int m_nWidth;
        public int m_nHeight;

        public int m_nRows;
        public int m_nCols;

        public int m_nImageID;

        public Tileset()
        {
            m_nWidth = 16;
            m_nHeight = 16;
            m_nRows = 64;
            m_nCols = 128;
            m_nImageID = -1;
        }

    }

    class Tile                 // Used for a tile
    {
        public int m_nWidth;
        public int m_nHeight;
        public int m_nTileNumber;
        public int m_nTop;
        public int m_nLeft;

        public Tile()
        {
            m_nWidth = 0;
            m_nHeight = 0;
            m_nTileNumber = 0;
            m_nTop = 0;
            m_nLeft = 0;
        }
    };

    class Object               // Used for an object or a trigger
    {
        public int m_nTop;
        public int m_nLeft;
        public int m_nID;

        public Object()
        {
            m_nTop = 0;
            m_nLeft = 0;
            m_nID = 0;
        }
    };

    class Blocker              // Used to block off an area
    {
        public List<Point> m_Points;
            
        public Blocker()
        {
            m_Points = new List<Point>();
        }
    };

    class Layer                // Stores all of the tiles in a layer
    {
        public Tile[,] m_tTiles;
    };


}
