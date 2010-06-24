#include "precompiled_header.h"
#include "CParticleEmitter.h"
#include "CParticle.h"

void CParticleEmitter::Initialize(int nImageID, int nHeight, int nWidth, float fPosX, float fPosY, int nNumParticles, int nMaxPartLife, int nMinPartLife)
{
	m_nImageID = nImageID;
    m_fPosX = fPosX;
    m_fPosY = fPosY;
    m_nNumParticles = nNumParticles;

    m_cParticleArray = new CParticle[m_nNumParticles];

    MaxParticleLife = nMaxPartLife;// 200;
    MinParticleLife = nMinPartLife;//50;

    m_nHeight = nHeight;
    m_nWidth = nWidth;

    //color = Color.White.ToArgb();

    m_bfixedAlpha = false;

    m_bRandScaleOn = false;
    m_fXScale = 1.0f;
    m_fYscale = 1.0f;
    m_fMaxXscale = 0.0f;
    m_dMaxYScale = 0.0f;

    
    for (int i = 0; i < m_nNumParticles; ++i)
    {
        m_cParticleArray[i];// = new CParticle();
        m_cParticleArray[i].Initialize(m_nImageID, 0, 1.0f, 1.0f, m_fPosX + ((float)(rand()%m_nWidth) - m_nWidth*0.5f), m_fPosY + ((float)(rand()%m_nHeight) - m_nHeight*0.5f), color);
    }

    m_nGravity = 0;
    m_nGravityPointX = 0;
    m_nGravityPointY = 0;

    m_nSpread = 0;
}

void CParticleEmitter::Update( float fElapsedTime )
{
	for (int i = 0; i < m_nNumParticles; ++i)
    {
        m_cParticleArray[i].Update(fElapsedTime,m_nGravityPointX,m_nGravityPointY,m_nGravity, m_nSpread);
        if (m_cParticleArray[i].IsDead())
        {
            float tempXScale = m_fXScale;
            float tempYSacle = m_fYscale;

            if (m_bRandScaleOn)
            {
                tempXScale = (rand()%(((int)m_fXScale * 100) + (int)(m_fMaxXscale * 100)) - ((int)m_fXScale * 100)) * 0.01f;
                tempYSacle = (rand()%(((int)m_fYscale * 100) + (int)(m_dMaxYScale * 100)) - ((int)m_fYscale * 100)) * 0.01f;
            }

            //if(rand

			m_cParticleArray[i].Initialize(m_nImageID, rand()%(MinParticleLife + MaxParticleLife)+MinParticleLife, tempXScale, tempYSacle,
				m_fPosX + ((float)(rand()%m_nWidth) - m_nWidth*0.5f), m_fPosY + ((float)(rand()%m_nHeight) - m_nHeight*0.5f), color);

            if (m_bInitialForceOn)
            {
				m_cParticleArray[i].SetInitialForcePoint(m_pInitialForcePointX,m_pInitialForcePointY);
            }
            if (m_bfixedAlpha)
            {
				m_cParticleArray[i].SetFixedAlpha(m_nFixedAlpha);
            }
        }
    }

}

void CParticleEmitter::Render()
{

	for (int i = 0; i < m_nNumParticles; ++i)
    {
        m_cParticleArray[i].Render(m_nImageID);
    }

}
/*
CParticleEmitter::~CParticleEmitter()
{
	delete m_cParticleArray;
}*/