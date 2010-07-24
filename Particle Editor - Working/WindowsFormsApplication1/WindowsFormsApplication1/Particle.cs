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
    class CParticle
    {
        private float m_fInitialLife;
        private float m_fLife;
        private float m_fScaleX;
        private float m_fScaleY;
        private float m_fPosX;
        private float m_fPosY;
        /*private float m_fXMove;
        private float m_fYMove;*/

        private float m_fSpeedX;
        private float m_fSpeedY;
        private Point m_pForce;

        public bool m_bInitialForceOn;
        public Point m_pInitialForcePoint;
        
        //public float m_fGravityForce;

        public int color;

        public bool fixedAlpha;
        public int m_nFixedAlpha;

        public int m_nSpreadx;
        public int m_nSpready;


        //FIX THIS
        private Rectangle painter;

        public void Initialize(int nImageID,int nLife, float fScaleX, float fScaleY, float fPosX, float fPosY, float fXMove, float fYMove, int ncolor)
        {
            m_fLife = (float)nLife;
            m_fInitialLife = m_fLife;
            m_fScaleX = fScaleX;
            m_fScaleY = fScaleY;
            m_fPosX = fPosX;
            m_fPosY = fPosY;

            /*m_fXMove = fXMove;
            m_fYMove = fYMove;*/

            m_bInitialForceOn = false;

            color = ncolor;

            m_fSpeedX = 0.0f;
            m_fSpeedY = 0.0f;

            m_pForce.X = 0;
            m_pForce.Y = 0;
            m_pInitialForcePoint.X = 0;
            m_pInitialForcePoint.Y = 0;

            Random QuickRand = new Random();
            int randomer = QuickRand.Next(0, 10);
            if (randomer <= 5)
            {
                m_nSpreadx = -randomer;
            }
            else
            {
                m_nSpreadx = randomer;
            }
            randomer = QuickRand.Next(0, 10);
            if (randomer <= 5)
            {
                m_nSpready = -randomer;
            }
            else
            {
                m_nSpready = randomer;
            }


            //FIX THIS
            painter = new Rectangle(0, 0, ManagedTextureManager.Instance.GetTextureWidth(nImageID), ManagedTextureManager.Instance.GetTextureHeight(nImageID));
        }

        public void Update(float fElapsedTime, Point GravityPoint, int nGravity, int nSpread)
        {
            //TODO
            if (m_bInitialForceOn)
            {
                m_pForce.X += m_pInitialForcePoint.X*1000;// *fElapsedTime; //m_fYMove* fElapsedTime;
                m_pForce.Y += m_pInitialForcePoint.Y*1000;// *fElapsedTime; //m_fXMove * fElapsedTime;
                //m_bInitialForceOn = false;
            }
            m_fLife -= fElapsedTime*1000;

            int gravityX = (GravityPoint.X - (int)m_fPosX) * nGravity;
            int gravityY = (GravityPoint.Y - (int)m_fPosY) * nGravity;

            m_fSpeedX = m_fSpeedX + (m_pForce.X + gravityX + m_nSpreadx*nSpread) * fElapsedTime;
            m_fSpeedY = m_fSpeedY + (m_pForce.Y + gravityY + m_nSpready*nSpread) * fElapsedTime;

            m_fPosX = m_fPosX + m_fSpeedX * fElapsedTime;
            m_fPosY = m_fPosY + m_fSpeedY * fElapsedTime;

            if (m_bInitialForceOn)
            {
                m_pForce.X -= m_pInitialForcePoint.X*1000;// *fElapsedTime; //m_fYMove* fElapsedTime;
                m_pForce.Y -= m_pInitialForcePoint.Y*1000;// *fElapsedTime; //m_fXMove * fElapsedTime;
                m_bInitialForceOn = false;
            }

        }

        public void Render(int nImageID)
        {
            //ManagedDirect3D.Instance.DrawRect(painter, 255, 255, 255);
            int Alpha;
            if (fixedAlpha)
            {
                Alpha = m_nFixedAlpha;
            }
            else
            {
                Alpha = (int)((m_fLife * 255) / m_fInitialLife);
                if (Alpha < 0)
                {
                    Alpha = 0;
                }
            }
            int newcolor = Color.FromArgb(Alpha, Color.FromArgb(color).R, Color.FromArgb(color).G, Color.FromArgb(color).B).ToArgb();
            
            ManagedTextureManager.Instance.Draw(nImageID, (int)m_fPosX, (int)m_fPosY, m_fScaleX, m_fScaleY, painter, 0, 0, 0.0f,newcolor);
        }

        public bool IsDead()
        {
            return (m_fLife <= 0);
        }
    }
}
