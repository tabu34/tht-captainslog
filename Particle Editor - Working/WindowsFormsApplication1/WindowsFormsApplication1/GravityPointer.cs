using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Data;
using System.Drawing;

using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

using SGD;

namespace WindowsFormsApplication1
{
    public class GravityPointer
    {
        public int m_igFX;
        public int m_igFY;
        //public bool inuse;
        public int m_nImageID;
        public Rectangle m_nImageRectangle;

        public void InitializeGravityPointer()
        {
            //inuse = false;
            m_igFX = 0;
            m_igFY = 0;
            m_nImageID = ManagedTextureManager.Instance.LoadTexture("Resource/GC.png", 0);
            m_nImageRectangle = new Rectangle(0, 0, 32, 32);
        }

        public void RenderGP()
        {
            ManagedTextureManager.Instance.Draw(m_nImageID, m_igFX, m_igFY, 0.5f, 0.5f, m_nImageRectangle, 0, 0, 0.0f, 0);
        }
    }
}
