using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    

    public partial class AParticle : Form
    {
        public float m_fMinWidth;
        public float m_fMaxWidth;
        public float m_fMinHeight;
        public float m_fMaxHeight;
        public float m_bRandScale;
        public bool m_bScaleChange;

        public float m_fPrevMinWidth;
        public float m_fPrevMaxWidth;
        public float m_fPrevMinHeight;
        public float m_fPrevMaxHeight;
        public bool m_bPrevRandScale;
        public bool m_bPrevScaleChange;

        private Form1 parent;

        public delegate void DataUpdateHandler(object sender, customArgs e);
        public event DataUpdateHandler DataUpdated;

        public AdvancedParticleStuff myaps;
        public AdvancedParticleStuff myprevaps;


        public AParticle(Form1 theparent)
        {
            InitializeComponent();
            parent = theparent;
            myaps = new AdvancedParticleStuff();
            myprevaps = new AdvancedParticleStuff();
            //parent
        }

        public void coordinate()
        {
            numericUpDownScaleMinWidth.Value = myaps.minimumwidth;
            numericUpDownScaleMinHeight.Value = myaps.minimumheight;
            if (myaps.maximumwidth >= numericUpDownMaxWidth.Minimum)
            {
                numericUpDownMaxWidth.Value = myaps.maximumwidth;
            }
            else
            {
                numericUpDownMaxWidth.Value = numericUpDownMaxWidth.Minimum;
            }
            if (myaps.maximumheight >= numericUpDownMaxHeight.Minimum)
            {
                numericUpDownMaxHeight.Value = myaps.maximumheight;
            }
            else
            {
                numericUpDownMaxHeight.Value = numericUpDownMaxHeight.Minimum;
            }
            checkBoxRandScale.Checked = myaps.randomsacle;
            //myprevaps = myaps;
        }

        private void buttonApply_Click(object sender, EventArgs e)
        {
            //AparticleStruct mystruct = new AparticleStruct();
            //mystruct.minwidth = (float)numericUpDownScaleMinWidth.Value;
            //AParticleArgs args = new AParticleArgs(mystruct); //store data here
            //raise event
            myprevaps.maximumheight = myaps.maximumheight;
            myprevaps.maximumwidth = myaps.maximumwidth;
            myprevaps.minimumheight = myaps.minimumheight;
            myprevaps.minimumwidth = myaps.minimumwidth;
            myprevaps.randomsacle = myaps.randomsacle;


            myaps.minimumwidth = (int)numericUpDownScaleMinWidth.Value;
            myaps.minimumheight = (int)numericUpDownScaleMinHeight.Value;
            myaps.maximumheight = (int)numericUpDownMaxHeight.Value;
            myaps.maximumwidth = (int)numericUpDownMaxWidth.Value;
            myaps.randomsacle = checkBoxRandScale.Checked;

            if (myaps.maximumheight < myaps.minimumheight)
            {
                myaps.maximumheight = myaps.minimumheight+1;
            }
            if (myaps.maximumwidth < myaps.minimumwidth)
            {
                myaps.maximumwidth = myaps.minimumwidth+1;
            }

            customArgs args = new customArgs();
            DataUpdated(this, args);
        }

        private void AParticle_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

        private void buttonGoBack_Click(object sender, EventArgs e)
        {
            myaps.maximumheight = myprevaps.maximumheight;
            myaps.maximumwidth = myprevaps.maximumwidth;
            myaps.minimumheight = myprevaps.minimumheight;
            myaps.minimumwidth = myprevaps.minimumwidth;
            myaps.randomsacle = myprevaps.randomsacle;
            coordinate();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            buttonApply_Click(sender, e);
            this.Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        

    }
}
