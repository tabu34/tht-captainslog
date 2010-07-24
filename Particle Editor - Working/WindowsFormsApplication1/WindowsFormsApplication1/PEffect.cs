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
    public partial class PEffect : Form
    {
        public bool gravcrosshair;
        public bool prevgravcrosshair;
        public int m_nGravity;

        public bool randspread;
        public int randspreadvalue;

        public PEffect()
        {
            InitializeComponent();
            gravcrosshair = false;
            prevgravcrosshair = false;
        }

        private void AParticle_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            //gravcrosshair = prevgravcrosshair;
            this.Close();
        }

        private void checkBoxGCrosshair_CheckedChanged(object sender, EventArgs e)
        {
            gravcrosshair = checkBoxGCrosshair.Checked;
        }

        private void numericUpDownGravity_ValueChanged(object sender, EventArgs e)
        {
            m_nGravity = (int)numericUpDownGravity.Value;
        }

        private void checkBoxRSpread_CheckedChanged(object sender, EventArgs e)
        {
            randspread = checkBoxRSpread.Checked;
        }

        private void numericUpDownSpread_ValueChanged(object sender, EventArgs e)
        {
            randspreadvalue = (int)numericUpDownSpread.Value;
        }

        public void UpdateMe()
        {
            checkBoxRSpread.Checked = randspread;
            checkBoxGCrosshair.Checked = gravcrosshair;
            numericUpDownSpread.Value = randspreadvalue;
            numericUpDownGravity.Value = m_nGravity;
        }

    }
}
