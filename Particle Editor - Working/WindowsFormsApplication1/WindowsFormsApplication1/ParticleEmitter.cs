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
    public class CParticleEmitter
    {
        public int m_nImageID;
        private int m_nNumParticles;
        public float m_fPosX;   //THESE ARE PRIVATE
        public float m_fPosY;   // PRIVATE
        private CParticle[] m_cParticleArray;
        private Random myRand;

        public int MaxParticleLife;
        public int MinParticleLife;

        public bool m_bInitialForceOn;
        public Point m_pInitialForcePoint;


        public int m_nGravity;
        public Point m_pGravityPoint;

        public int color;

        public bool fixedAlpha;
        public int m_nFixedAlpha;

        public int m_nHeight;
        public int m_nWidth;

        public float m_fXScale;
        public float m_fYscale;
        public float m_fMaxXscale;
        public float m_dMaxYScale;
        public bool m_bRandScaleOn;

        public int m_nSpread;

        public Color coloor;

        public void Initialize(int nImageID, float fPosX, float fPosY, int nNumParticles, int nMaxPartLife, int nMinPartLife, int nHeight, int nWidth)
        {
            m_nImageID = nImageID;
            m_fPosX = fPosX;
            m_fPosY = fPosY;
            m_nNumParticles = nNumParticles;

            m_cParticleArray = new CParticle[m_nNumParticles];

            myRand = new Random(0);

            MaxParticleLife = nMaxPartLife;// 200;
            MinParticleLife = nMinPartLife;//50;

            m_nHeight = nHeight;
            m_nWidth = nWidth;

            color = Color.White.ToArgb();

            fixedAlpha = false;

            m_bRandScaleOn = false;
            m_fXScale = 1.0f;
            m_fYscale = 1.0f;
            m_fMaxXscale = 0.0f;
            m_dMaxYScale = 0.0f;

            
            for (int i = 0; i < m_nNumParticles; ++i)
            {
                m_cParticleArray[i] = new CParticle();
                m_cParticleArray[i].Initialize(m_nImageID, 0, 1.0f, 1.0f, m_fPosX + ((float)myRand.Next(m_nWidth) - m_nWidth*0.5f), m_fPosY + ((float)myRand.Next(m_nHeight) - m_nHeight*0.5f), myRand.Next(500) * 1.0f, myRand.Next(1500, 5000) * 1.0f, color);
            }

            m_nGravity = 0;
            m_pGravityPoint.X = 0;
            m_pGravityPoint.Y = 0;

            m_nSpread = 0;
        }

        public void Update(float fElapsedTime)
        {
            for (int i = 0; i < m_nNumParticles; ++i)
            {
                m_cParticleArray[i].Update(fElapsedTime,m_pGravityPoint,m_nGravity, m_nSpread);
                if (m_cParticleArray[i].IsDead())
                {
                    float tempXScale = m_fXScale;
                    float tempYSacle = m_fYscale;

                    if (m_bRandScaleOn)
                    {
                        tempXScale = myRand.Next((int)(m_fXScale * 100), (int)(m_fMaxXscale * 100))*0.01f;
                        tempYSacle = myRand.Next((int)(m_fYscale * 100), (int)(m_dMaxYScale * 100)) * 0.01f;
                    }

                    //if(rand

                    m_cParticleArray[i].Initialize(m_nImageID, myRand.Next(MinParticleLife, MaxParticleLife), tempXScale, tempYSacle, m_fPosX + ((float)myRand.Next(m_nWidth) - m_nWidth * 0.5f), m_fPosY + ((float)myRand.Next(m_nHeight) - m_nHeight * 0.5f), myRand.Next(500) * 1.0f, myRand.Next(1500, 5000) * 1.0f, color);
                    if (m_bInitialForceOn)
                    {
                        m_cParticleArray[i].m_bInitialForceOn = true;
                        //m_cParticleArray[i].m_fGravity = m_fGravity;
                        m_cParticleArray[i].m_pInitialForcePoint.X = m_pInitialForcePoint.X;
                        m_cParticleArray[i].m_pInitialForcePoint.Y = m_pInitialForcePoint.Y;
                    }
                    if (fixedAlpha)
                    {
                        m_cParticleArray[i].fixedAlpha = true;
                        m_cParticleArray[i].m_nFixedAlpha = m_nFixedAlpha;
                    }
                    else {
                        m_cParticleArray[i].fixedAlpha = false; 
                    }
                }
            }
        }
        public void Render()
        {
            for (int i = 0; i < m_nNumParticles; ++i)
            {
                m_cParticleArray[i].Render(m_nImageID);
            }
        }
        public void ChangePosition(float newX, float newY)
        {
            m_fPosX = newX;
            m_fPosY = newY;
        }
        public void ChangeParticleNumber(int nNew)
        {
            m_nNumParticles = nNew;
            m_cParticleArray = new CParticle[m_nNumParticles];
            for (int i = 0; i < m_nNumParticles; ++i)
            {
                m_cParticleArray[i] = new CParticle();
                m_cParticleArray[i].Initialize(m_nImageID, myRand.Next(MinParticleLife, MaxParticleLife), 1.0f, 1.0f, m_fPosX + ((float)myRand.Next(m_nWidth) - m_nWidth * 0.5f), m_fPosY + ((float)myRand.Next(m_nHeight) - m_nHeight * 0.5f), myRand.Next(500) * 1.0f, myRand.Next(1500, 5000) * 1.0f, color);
            }
        }

        public void ChangeParticleInitialForce(bool isInitialForceOn, int X, int Y)//, float fGravity)
        {
            m_bInitialForceOn = isInitialForceOn;
            m_pInitialForcePoint.X = X;
            m_pInitialForcePoint.Y = Y;
            //m_fGravity = fGravity;

            for (int i = 0; i < m_nNumParticles; ++i)
            {
                m_cParticleArray[i].m_bInitialForceOn = isInitialForceOn;
                //m_cParticleArray[i].m_fGravity = fGravity;
                m_cParticleArray[i].m_pInitialForcePoint.X = X;
                m_cParticleArray[i].m_pInitialForcePoint.Y = Y;
            }
        }

        public void ChangeParticleColor(int Alpha, Color nColor)
        {
            coloor = nColor;
            color = Color.FromArgb(Alpha, nColor).ToArgb();

            for (int i = 0; i < m_nNumParticles; ++i)
            {
                m_cParticleArray[i].color = color;
            }
        }
    }
}
