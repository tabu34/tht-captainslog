#include "precompiled_header.h"
#include "CParticleEmitter.h"
#include "CParticle.h"

void CParticleEmitter::Initialize(int nImageID, int nWidth, int nHeight, int fPosX, int fPosY, int nNumParticles, int nMinPartLife, int nMaxPartLife,
		int AlphaValue, int initialForceX, int initialForceY, int BlendModeSource, int BlendModeDest,
		int minPartWidth, int minPartHeight, int maxPartWidth, int maxPartHeight, int nGravity,
		int GravitySourceX, int GravitySourceY, int RandomSpread, int red, int green, int blue)
{
	m_nImageID = nImageID;
    m_fPosX = (float)fPosX;
    m_fPosY = (float)fPosY;
    m_nNumParticles = nNumParticles;

    m_cParticleArray = new CParticle[m_nNumParticles];

    MaxParticleLife = nMaxPartLife;// 200;
    MinParticleLife = nMinPartLife;//50;

    m_nHeight = nHeight;
    m_nWidth = nWidth;

    //color = Color.White.ToArgb();

    m_bfixedAlpha = false;

	if(maxPartHeight > minPartHeight || maxPartWidth > minPartWidth)
	{
		m_bRandScaleOn = true;
	}else
	{
		m_bRandScaleOn = false;
	}
    m_fXScale = (float)minPartWidth*0.01f;
    m_fYscale = (float)minPartHeight*0.01f;
    m_fMaxXscale = (float)maxPartWidth*0.01f;
    m_dMaxYScale = (float)maxPartHeight*0.01f;

    
    for (int i = 0; i < m_nNumParticles; ++i)
    {
        m_cParticleArray[i];// = new CParticle();
        m_cParticleArray[i].Initialize(m_nImageID, 0, 1.0f, 1.0f, m_fPosX + ((float)(rand()%m_nWidth) - m_nWidth*0.5f), m_fPosY + ((float)(rand()%m_nHeight) - m_nHeight*0.5f), color);
    }

    m_nGravity = nGravity;
    m_nGravityPointX = GravitySourceX + (int)fPosX;
    m_nGravityPointY = GravitySourceY + (int)fPosY;

	m_nRed = red;
	m_nGreen = green;
	m_nBlue = blue;

    m_nSpread = RandomSpread;
}

void CParticleEmitter::Update( float fElapsedTime )
{
	static float passes = 0;
	for (int i = 0; i < m_nNumParticles; ++i)
    {
        m_cParticleArray[i].Update(fElapsedTime,m_nGravityPointX,m_nGravityPointY,m_nGravity, m_nSpread);
		//if(passes == 0){
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

			m_cParticleArray[i].Initialize(m_nImageID, rand()%(MaxParticleLife - MinParticleLife)+MinParticleLife, tempXScale, tempYSacle,
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
		//}
    }
	++passes;

}

void CParticleEmitter::Render()
{

	for (int i = 0; i < m_nNumParticles; ++i)
    {
        m_cParticleArray[i].Render(m_nImageID, m_nRed, m_nGreen, m_nBlue);
    }

}
/*
CParticleEmitter::~CParticleEmitter()
{
	delete m_cParticleArray;
}*/