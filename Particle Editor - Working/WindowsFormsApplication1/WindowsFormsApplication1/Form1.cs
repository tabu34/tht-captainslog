using System;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
//using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
//using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

using SGD;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public bool Looping;
        public CParticleEmitter MyEmitter;
        public int defaulttID;
        public int tID;
        public int bID;
        public Stopwatch myTimer;
        public float currentTime;
        public float prevTime;
        public bool isMouseDown;
        public bool isLMouseDown;
        public int nParticles;
        public string FileName;

        public bool anychange;

        public bool aparticlecreated;
        public AParticle MyAparticle;
        public AdvancedParticleStuff myadvancedparticlestuff;

        public GravityPointer MyGravityP;

        public PEffect MyPEffectForm;

        public void InitD3D()
        {
            ManagedDirect3D.Instance.InitManagedDirect3D(pictureBox/*splitContainer1.Panel2*/, true);
            ManagedTextureManager.Instance.InitManagedTextureManager(ManagedDirect3D.Instance.Device, ManagedDirect3D.Instance.Sprite);
        }

        public Form1()
        {
            isMouseDown = false;
            Looping = true;
            InitializeComponent();
            InitD3D();

            tID = ManagedTextureManager.Instance.LoadTexture("Resource/spark.png", 0);
            defaulttID = tID;
            bID = -1;
            MyEmitter = new CParticleEmitter();
            nParticles = 500;
            MyEmitter.Initialize(tID,431,200,nParticles,500,200,200,500);
            numericUpDownNParticles.Value = nParticles;
            numericUpDownMaxLife.Value = MyEmitter.MaxParticleLife;
            numericUpDownMinLife.Value = MyEmitter.MinParticleLife;

            numericUpDownEmitHeight.Value = 200;
            numericUpDownEmitWidth.Value = 500;

            FileName = "NULL";
            anychange = false;

            aparticlecreated = false;
            myadvancedparticlestuff = new AdvancedParticleStuff();

            MyGravityP = new GravityPointer();
            MyGravityP.InitializeGravityPointer();
            //MyGravityP.inuse = true;

            CreatePeffectForm();

            comboBoxSource.SelectedIndex = 4;
            comboBoxDestination.SelectedIndex = 2;

            myTimer = new Stopwatch();
        }

        private void buttonPickColor_Click(object sender, EventArgs e)
        {
            ColorDialog MyDialog = new ColorDialog();
            // Keeps the user from selecting a custom color.
            MyDialog.AllowFullOpen = false;
            // Allows the user to get help. (The default is false.)
            MyDialog.ShowHelp = true;
            // Sets the initial color select to the current text color.
            //MyDialog.Color = textBox1.ForeColor;
            if (MyDialog.ShowDialog() == DialogResult.OK)
                MyEmitter.ChangeParticleColor(255,MyDialog.Color);

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;

        }

        public void Render()
        {
            //while (true)
            {
                ManagedDirect3D.Instance.DeviceBegin();

                ManagedDirect3D.Instance.Clear(0, 0, 0);                

                ManagedDirect3D.Instance.SpriteBegin();

                ManagedDirect3D.Instance.Device.SetRenderState(RenderStates.SourceBlend, 5);

                if (bID != -1)
                {
                    Rectangle recty = new Rectangle();
                    recty.X = 0;
                    recty.Y = 0;
                    recty.Width = ManagedTextureManager.Instance.GetTextureWidth(bID);
                    recty.Height = ManagedTextureManager.Instance.GetTextureHeight(bID);
                    ManagedTextureManager.Instance.Draw(bID, 0, 0, 1.0f, 1.0f, recty, 0, 0, 0.0f, 0);
                    
                }
                

                if (MyPEffectForm.gravcrosshair)
                {
                    MyGravityP.RenderGP();
                }


                ManagedDirect3D.Instance.SpriteEnd();

                ManagedDirect3D.Instance.DeviceEnd();

                //PARTICLE RENDERING/////////////////

                ManagedDirect3D.Instance.DeviceBegin();

                ManagedDirect3D.Instance.SpriteBegin();

                ManagedDirect3D.Instance.Device.SetRenderState(RenderStates.SourceBlend, comboBoxSource.SelectedIndex + 1);
                ManagedDirect3D.Instance.Device.SetRenderState(RenderStates.DestinationBlend, comboBoxDestination.SelectedIndex + 1);

                MyEmitter.Render();

                ManagedDirect3D.Instance.SpriteEnd();

                ManagedDirect3D.Instance.DeviceEnd();

                ManagedDirect3D.Instance.Present();
            }
        }

        public void Updater(float fElapsedTime)
        {
            if (isMouseDown)
            {
                Point newpoint;
                newpoint = pictureBox.PointToClient(MousePosition);
                MyEmitter.ChangePosition((float)newpoint.X, (float)newpoint.Y);
            }
            if (MyPEffectForm.gravcrosshair)
            {
                MyEmitter.m_nGravity = MyPEffectForm.m_nGravity;
            }
            else
            {
                MyEmitter.m_nGravity = 0;
            }
            if (MyPEffectForm.randspread)
            {
                MyEmitter.m_nSpread = MyPEffectForm.randspreadvalue;
            }
            else
            {
                MyEmitter.m_nSpread = 0;
            }
            MyEmitter.m_fXScale = myadvancedparticlestuff.minimumwidth*0.01f;
            MyEmitter.m_fYscale = myadvancedparticlestuff.minimumheight*0.01f;
            MyEmitter.m_fMaxXscale = myadvancedparticlestuff.maximumwidth*0.01f;
            MyEmitter.m_dMaxYScale = myadvancedparticlestuff.maximumheight * 0.01f;
            MyEmitter.m_bRandScaleOn = myadvancedparticlestuff.randomsacle;
            MyEmitter.Update(fElapsedTime);
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            ManagedTextureManager.Instance.ShutdownManagedTextureManager();
            Looping = false;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {

            /////////////////////////////////
            //SAVE BEFORE EXITING
            if (anychange == true)
            {
                DialogResult MyResult = MessageBox.Show("Would you like to save before quiting?", "Exit",
                    MessageBoxButtons.YesNoCancel, MessageBoxIcon.Asterisk);
                if (MyResult == DialogResult.Yes)
                {
                    SaveFile(FileName);
                    if (FileName == "NULL")
                    {
                        SaveFileDialog MySaveFileDialog = new SaveFileDialog();
                        MySaveFileDialog.Filter = "particle files (*.par)|*.par";
                        if (MySaveFileDialog.ShowDialog() == DialogResult.OK)
                        {
                            string FN = MySaveFileDialog.FileName.ToString();
                            SaveFile(FN);
                        }
                    }
                    else
                    {
                        if (MessageBox.Show("Saving will overwrite the current file,\nare you sure you want to save?", "Save",
                            MessageBoxButtons.OKCancel, MessageBoxIcon.Asterisk) == DialogResult.OK)
                        {
                            SaveFile(FileName);
                        }
                    }
                    this.Close();
                }
                else if (MyResult == DialogResult.No)
                {
                    this.Close();
                }
            }
            ////////////////////////////////

            //ManagedTextureManager.Instance.ShutdownManagedTextureManager();
            //Looping = false;
            this.Close();
            
        }

        public void DoWork()
        {
            if (!myTimer.IsRunning)
            {
                myTimer.Start();
                prevTime = 0.0f;
            }
            currentTime = myTimer.ElapsedMilliseconds * 0.0001f;
            Updater(currentTime - prevTime);
            prevTime = currentTime;
            Render();
        }


        private void pictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                isMouseDown = true;
            }
            else if (e.Button == MouseButtons.Right)
            {
                MyGravityP.m_igFX = e.X;
                MyGravityP.m_igFY = e.Y;
                MyEmitter.m_pGravityPoint.X = MyGravityP.m_igFX;
                MyEmitter.m_pGravityPoint.Y = MyGravityP.m_igFY;
            }
            //MyEmitter.ChangePosition(e.Location.X, e.Location.Y);//(float)MousePosition.X, (float)MousePosition.Y);
        }

        private void pictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            isMouseDown = false;
        }

        private void numericUpDownMaxLife_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDownMaxLife.Value <= numericUpDownMinLife.Value)
            {
                numericUpDownMaxLife.Value = numericUpDownMinLife.Value + 1;
            }
            MyEmitter.MaxParticleLife = (int)numericUpDownMaxLife.Value;

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }

        private void numericUpDownMinLife_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDownMinLife.Value >= numericUpDownMaxLife.Value)
            {
                numericUpDownMinLife.Value = numericUpDownMaxLife.Value - 1;
            }
            MyEmitter.MinParticleLife = (int)numericUpDownMinLife.Value;

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }

        private void numericUpDownNParticles_ValueChanged(object sender, EventArgs e)
        {
            nParticles = (int)numericUpDownNParticles.Value;
            MyEmitter.ChangeParticleNumber(nParticles);

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }
        public void RESET()
        {
            MyEmitter = null;
            MyEmitter = new CParticleEmitter();
            nParticles = 500;
            MyEmitter.Initialize(defaulttID,431,200,nParticles,500,200,200,500);
            numericUpDownNParticles.Value = nParticles;
            numericUpDownMaxLife.Value = MyEmitter.MaxParticleLife;
            numericUpDownMinLife.Value = MyEmitter.MinParticleLife;
            numericUpDownAlpha.Value = 0;
            numericUpDownEmitHeight.Value = 200;
            numericUpDownEmitWidth.Value = 500;
            if (defaulttID != tID)
            {
                ManagedTextureManager.Instance.ReleaseTexture(tID);
                tID = defaulttID;
            }
            if (bID != -1)
            {
                ManagedTextureManager.Instance.ReleaseTexture(bID);
                bID = -1;
            }
            myadvancedparticlestuff.RESET();
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            RESET();
        }

        private void checkBoxGravity_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxGravity.Checked)
            {
                MyEmitter.ChangeParticleInitialForce(true, (int)numericUpDownGravityLeftRight.Value, (int)numericUpDownGravityUpDown.Value);
            }
            else
            {
                MyEmitter.ChangeParticleInitialForce(false, (int)numericUpDownGravityLeftRight.Value, (int)numericUpDownGravityUpDown.Value);
            }

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }

        private void numericUpDownGravityUpDown_ValueChanged(object sender, EventArgs e)
        {
            if (checkBoxGravity.Checked)
            {
                MyEmitter.ChangeParticleInitialForce(true, (int)numericUpDownGravityLeftRight.Value, (int)numericUpDownGravityUpDown.Value);
            }
            else
            {
                MyEmitter.ChangeParticleInitialForce(false, (int)numericUpDownGravityLeftRight.Value, (int)numericUpDownGravityUpDown.Value);
            }

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }

        private void numericUpDownGravityLeftRight_ValueChanged(object sender, EventArgs e)
        {
            if (checkBoxGravity.Checked)
            {
                MyEmitter.ChangeParticleInitialForce(true, (int)numericUpDownGravityLeftRight.Value, (int)numericUpDownGravityUpDown.Value);
            }
            else
            {
                MyEmitter.ChangeParticleInitialForce(false, (int)numericUpDownGravityLeftRight.Value, (int)numericUpDownGravityUpDown.Value);
            }

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }

        private void numericUpDownAlpha_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDownAlpha.Value == 0)
            {
                MyEmitter.fixedAlpha = false;
            }
            else
            {
                MyEmitter.fixedAlpha = true;
                MyEmitter.m_nFixedAlpha = (int)numericUpDownAlpha.Value;
            }

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }

        private void numericUpDownEmitWidth_ValueChanged(object sender, EventArgs e)
        {
            MyEmitter.m_nWidth = (int)numericUpDownEmitWidth.Value;

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }

        private void numericUpDownEmitHeight_ValueChanged(object sender, EventArgs e)
        {
            MyEmitter.m_nHeight = (int)numericUpDownEmitHeight.Value;

            //MAKE SURE YOU KNOW THAT SOME CHANGED
            anychange = true;
        }

        private void loadParticleImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog LoadTextureSpark = new OpenFileDialog();
            if (LoadTextureSpark.ShowDialog() == DialogResult.OK)
            {
                string FN = LoadTextureSpark.FileName.ToString();
                int FNcount = FN.Length;
                string MyExtension = FN[FNcount - 3].ToString() + FN[FNcount - 2].ToString() + FN[FNcount - 1].ToString();
                if ("png" != MyExtension)
                {
                    MessageBox.Show("Please select a PNG", "Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                }
                else
                {
                    if (tID != defaulttID)
                    {
                        ManagedTextureManager.Instance.ReleaseTexture(tID);
                    }
                    tID = ManagedTextureManager.Instance.LoadTexture(FN, 0);
                    MyEmitter.m_nImageID = tID;
                }
            }
        }

        private void loadBackgroundImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog LoadTextureBG = new OpenFileDialog();
            if (LoadTextureBG.ShowDialog() == DialogResult.OK)
            {
                string FN = LoadTextureBG.FileName.ToString();
                int FNcount = FN.Length;
                string MyExtension = FN[FNcount - 3].ToString() + FN[FNcount - 2].ToString() + FN[FNcount - 1].ToString();
                if ("png" != MyExtension && "jpg" != MyExtension && "bmp" != MyExtension)
                {
                    MessageBox.Show("Please select an image file (PNG, jpg, bmp)", "Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                }
                else
                {
                    if (bID != -1)
                    {
                        ManagedTextureManager.Instance.ReleaseTexture(bID);
                    }
                    bID = ManagedTextureManager.Instance.LoadTexture(FN, 0);
                }
            }
        }

        public void SaveFile(string FN)
        {
            using (FileStream MyFS = new FileStream(FN, FileMode.Create))
            {
                using (BinaryWriter writer = new BinaryWriter(MyFS))
                {
                    writer.Write((int)numericUpDownMinLife.Value);
                    writer.Write((int)numericUpDownMaxLife.Value);
                    writer.Write((int)numericUpDownEmitWidth.Value);
                    writer.Write((int)numericUpDownEmitHeight.Value);
                    writer.Write((int)numericUpDownNParticles.Value);
                    writer.Write((int)numericUpDownAlpha.Value);
                    if (checkBoxGravity.Checked)
                    {
                        writer.Write((int)numericUpDownGravityLeftRight.Value);
                        writer.Write((int)numericUpDownGravityUpDown.Value);
                    }
                    else
                    {
                        writer.Write((int)0);
                        writer.Write((int)0);
                    }
                    writer.Write((int)comboBoxSource.SelectedIndex);
                    writer.Write((int)comboBoxDestination.SelectedIndex);
                    writer.Write((int)myadvancedparticlestuff.minimumwidth);
                    writer.Write((int)myadvancedparticlestuff.minimumheight);
                    if (myadvancedparticlestuff.randomsacle)
                    {
                        writer.Write((int)myadvancedparticlestuff.maximumwidth);
                        writer.Write((int)myadvancedparticlestuff.maximumheight);
                    }
                    else
                    {
                        writer.Write((int)0);
                        writer.Write((int)0);
                    }
                    if (MyPEffectForm.gravcrosshair)
                    {
                        writer.Write((int)MyPEffectForm.m_nGravity);
                        writer.Write((int)MyEmitter.m_pGravityPoint.X - (int)MyEmitter.m_fPosX);
                        writer.Write((int)MyEmitter.m_pGravityPoint.Y - (int)MyEmitter.m_fPosY);
                    }
                    else
                    {
                        writer.Write((int)0);
                        writer.Write((int)0);
                        writer.Write((int)0);
                    }
                    if (MyPEffectForm.randspread)
                    {
                        writer.Write((int)MyPEffectForm.randspreadvalue);
                    }
                    else
                    {
                        writer.Write((int)0);
                    }

                    writer.Write((int)MyEmitter.coloor.B);
                    writer.Write((int)MyEmitter.coloor.G);
                    writer.Write((int)MyEmitter.coloor.R);
                    writer.Close();
                }

            }
            FileName = FN;

            //MAKE SURE YOU KNOW THAT NONE CHANGED
            anychange = false;
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog MySaveFileDialog = new SaveFileDialog();
            MySaveFileDialog.Filter = "particle files (*.par)|*.par";
            if (MySaveFileDialog.ShowDialog() == DialogResult.OK)
            {
                string FN = MySaveFileDialog.FileName.ToString();
                SaveFile(FN);
            }
        }


        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (FileName == "NULL")
            {
                SaveFileDialog MySaveFileDialog = new SaveFileDialog();
                MySaveFileDialog.Filter = "particle files (*.par)|*.par";
                if (MySaveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    string FN = MySaveFileDialog.FileName.ToString();
                    SaveFile(FN);
                }
            }
            else
            {
                if (MessageBox.Show("Saving will overwrite the current file,\nare you sure you want to save?", "Save",
                    MessageBoxButtons.OKCancel, MessageBoxIcon.Asterisk) == DialogResult.OK)
                {
                    SaveFile(FileName);
                }
            }
            /*if ("png" != MyExtension && "jpg" != MyExtension && "bmp" != MyExtension)
            {
                MessageBox.Show("Please select an image file (PNG, jpg, bmp)", "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
            }*/
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog MyOpenFileDialog = new OpenFileDialog();
            MyOpenFileDialog.Filter = "particle files (*.par)|*.par";
            if (MyOpenFileDialog.ShowDialog() == DialogResult.OK)
            {
                string FN = MyOpenFileDialog.FileName.ToString();
                using (FileStream MyFS = new FileStream(FN, FileMode.Open))
                {
                    using (BinaryReader reader = new BinaryReader(MyFS))
                    {
                        reader.BaseStream.Position = 0;
                        numericUpDownMaxLife.Value = numericUpDownMaxLife.Maximum;
                        numericUpDownMinLife.Value = numericUpDownMinLife.Minimum;
                        numericUpDownMinLife.Value = reader.ReadInt32();//reader.ReadDecimal();
                        numericUpDownMaxLife.Value = reader.ReadInt32();//reader.ReadDecimal();
                        numericUpDownEmitWidth.Value = reader.ReadInt32();//reader.ReadDecimal();
                        numericUpDownEmitHeight.Value = reader.ReadInt32();//reader.ReadDecimal();
                        numericUpDownNParticles.Value = reader.ReadInt32();//reader.ReadDecimal();
                        numericUpDownAlpha.Value = reader.ReadInt32();//reader.ReadDecimal();
                        numericUpDownGravityLeftRight.Value = reader.ReadInt32();//reader.ReadDecimal();
                        numericUpDownGravityUpDown.Value = reader.ReadInt32();//reader.ReadDecimal();
                        if (numericUpDownGravityLeftRight.Value == 0 && numericUpDownGravityUpDown.Value == 0)
                        {
                            checkBoxGravity.Checked = true;
                        }
                        else
                        {
                            checkBoxGravity.Checked = false;
                        }

                        comboBoxSource.SelectedIndex = reader.ReadInt32();
                        comboBoxDestination.SelectedIndex = reader.ReadInt32();

                        myadvancedparticlestuff.minimumwidth = reader.ReadInt32();
                        myadvancedparticlestuff.minimumheight = reader.ReadInt32();
                        myadvancedparticlestuff.maximumwidth = reader.ReadInt32();
                        myadvancedparticlestuff.maximumheight = reader.ReadInt32();
                        if (myadvancedparticlestuff.maximumheight == 0 && myadvancedparticlestuff.maximumwidth == 0)
                        {
                            myadvancedparticlestuff.randomsacle = false;
                        }
                        else
                        {
                            myadvancedparticlestuff.randomsacle = true;
                        }
                        MyPEffectForm.m_nGravity = reader.ReadInt32();
                        MyEmitter.m_pGravityPoint.X = reader.ReadInt32()+ (int)MyEmitter.m_fPosX;
                        MyEmitter.m_pGravityPoint.Y = reader.ReadInt32() + (int)MyEmitter.m_fPosY;
                        MyGravityP.m_igFX = MyEmitter.m_pGravityPoint.X;
                        MyGravityP.m_igFY = MyEmitter.m_pGravityPoint.Y;
                        if (MyPEffectForm.m_nGravity == 0)
                        {
                            MyPEffectForm.gravcrosshair = false;
                        }
                        else
                        {
                            MyPEffectForm.gravcrosshair = true;
                        }
                        MyPEffectForm.randspreadvalue = reader.ReadInt32();
                        if (MyPEffectForm.randspreadvalue == 0)
                        {
                            MyPEffectForm.randspread = false;
                        }
                        else
                        {
                            MyPEffectForm.randspread = true;
                        }

                        /*Color mycolor;
                        mycolor.ToArgb = (byte)reader.ReadInt32();
                        mycolor.G = (byte)reader.ReadInt32();
                        mycolor.R = (byte)reader.ReadInt32();*/

                        reader.Close();
                    }

                }
                FileName = FN;

                //MAKE SURE YOU KNOW THAT SOME CHANGED
                anychange = false;
            }
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //check if anything changed
            if (anychange == true)
            {
                DialogResult MyResult = MessageBox.Show("Would you like to save before creating a new particle?", "New",
                    MessageBoxButtons.YesNoCancel, MessageBoxIcon.Asterisk);
                if (MyResult == DialogResult.Yes)
                {
                    SaveFile(FileName);
                    if (FileName == "NULL")
                    {
                        SaveFileDialog MySaveFileDialog = new SaveFileDialog();
                        MySaveFileDialog.Filter = "particle files (*.par)|*.par";
                        if (MySaveFileDialog.ShowDialog() == DialogResult.OK)
                        {
                            string FN = MySaveFileDialog.FileName.ToString();
                            SaveFile(FN);
                        }
                    }
                    else
                    {
                        if (MessageBox.Show("Saving will overwrite the current file,\nare you sure you want to save?", "Save",
                            MessageBoxButtons.OKCancel, MessageBoxIcon.Asterisk) == DialogResult.OK)
                        {
                            SaveFile(FileName);
                        }
                    }
                    RESET();
                    FileName = "NULL";
                    anychange = false;
                }
                else if (MyResult == DialogResult.No)
                {
                    RESET();
                    FileName = "NULL";
                    anychange = false;
                }
            }
            else
            {
                RESET();
                FileName = "NULL";
                anychange = false;
            }
        }

        ////////////////////////////////////////////////////////
        //MAKE SURE THAT THE WINDOWS COMMUNICATE
        ////////////////////////////////////////////////////////
        private void particleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (aparticlecreated == false)
            {
                aparticlecreated = true;
                MyAparticle = new AParticle(this);
                MyAparticle.DataUpdated += new AParticle.DataUpdateHandler(GetData);
            }
            if (!MyAparticle.Visible)
            {
                MyAparticle.myaps = myadvancedparticlestuff;
                //MyAparticle.myprevaps = myadvancedparticlestuff;
                MyAparticle.coordinate();
                MyAparticle.Show();
            }
        }
        private void GetData(object sender, customArgs e)
        {
            //float minwidth = e.SendFormData.minwidth;
            if (aparticlecreated == true)
            {
                myadvancedparticlestuff = MyAparticle.myaps;
            }
        }
        private void CreatePeffectForm()
        {
            MyPEffectForm = new PEffect();
        }

        private void effectsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!MyPEffectForm.Visible)
            {
                MyPEffectForm.UpdateMe();
                MyPEffectForm.Show();
            }
        }
    }

    //////////////////////////
    //AParticle args
    public class customArgs
    {
        //private int data;
        public customArgs()
        {
        //data = input;
        }
        //create property to send data back
        /*public AparticleStruct SendFormData
        {
            get { return data; }
        }*/
    }

    public class AdvancedParticleStuff
    {
        public int minimumwidth;
        public int maximumwidth;
        public bool randomsacle;
        public int minimumheight;
        public int maximumheight;

        public AdvancedParticleStuff()
        {
            this.RESET();
        }
        public void RESET()
        {
            minimumwidth = 100;
            maximumwidth = 100;
            randomsacle = false;
            minimumheight = 100;
            maximumheight = 100;
        }
    }
}
