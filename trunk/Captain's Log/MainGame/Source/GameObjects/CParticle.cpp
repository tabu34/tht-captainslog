#include "precompiled_header.h"
#include "CParticle.h"
#include <CTime>
#include "../SGD Wrappers/CSGD_TextureManager.h"

void CParticle::Initialize(int nImageID,int nLife, float fScaleX, float fScaleY, float fPosX, float fPosY, int ncolor)
{

    m_fLife = (float)nLife;
    m_fInitialLife = m_fLife;
    m_fScaleX = fScaleX;
    m_fScaleY = fScaleY;
    m_fPosX = fPosX;
    m_fPosY = fPosY;

	m_fGravityForce = 0;
	m_bfixedAlpha = false;
	m_nFixedAlpha = 0;

    m_bInitialForceOn = false;

    m_nColor = ncolor;

    m_fSpeedX = 0.0f;
    m_fSpeedY = 0.0f;

    m_nForceX = 0;
    m_nForceY = 0;
    m_nInitialForceX = 0;
    m_nInitialForceY = 0;

	srand(unsigned int(time(0)));

	int RandomInt = rand()%10;
	
	if(RandomInt <= 5 )
	{
		m_nSpreadx = -RandomInt;
	}else
	{
		m_nSpreadx = RandomInt-5;
	}

	RandomInt = rand()%10;

	if(RandomInt <= 5)
	{
		m_nSpready = -RandomInt;
	}else
	{
		m_nSpready = RandomInt-5;
	}

	m_rPaintRect.top = 0;
	m_rPaintRect.left = 0;
	m_rPaintRect.bottom = CSGD_TextureManager::GetInstance()->GetTextureHeight(nImageID);
	m_rPaintRect.right = CSGD_TextureManager::GetInstance()->GetTextureWidth(nImageID);

}
void CParticle::Update( float fElapsedTime, int GravityPointX, int GravityPointY, int nGravity, int nSpread)
{

	if (m_bInitialForceOn)
        {
            m_nForceX += m_nInitialForceX*1000;// *fElapsedTime; //m_fYMove* fElapsedTime;
            m_nForceY += m_nInitialForceY*1000;// *fElapsedTime; //m_fXMove * fElapsedTime;
            //m_bInitialForceOn = false;
        }
        m_fLife -= fElapsedTime*1000;

        int gravityX = (GravityPointX - (int)m_fPosX) * nGravity;
        int gravityY = (GravityPointY - (int)m_fPosY) * nGravity;

        m_fSpeedX = m_fSpeedX + (m_nForceX + gravityX + m_nSpreadx*nSpread) * fElapsedTime;
        m_fSpeedY = m_fSpeedY + (m_nForceY + gravityY + m_nSpready*nSpread) * fElapsedTime;

        m_fPosX = m_fPosX + m_fSpeedX * fElapsedTime;
        m_fPosY = m_fPosY + m_fSpeedY * fElapsedTime;

        if (m_bInitialForceOn)
        {
            m_nForceX -= m_nInitialForceX*1000;// *fElapsedTime; //m_fYMove* fElapsedTime;
            m_nForceY -= m_nInitialForceY*1000;// *fElapsedTime; //m_fXMove * fElapsedTime;
            m_bInitialForceOn = false;
        }

}

void CParticle::Render(int ImageID)
{
	
	//ManagedDirect3D.Instance.DrawRect(painter, 255, 255, 255);
    int Alpha;
    if (m_bfixedAlpha)
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
    //int newcolor = Color.FromArgb(Alpha, Color.FromArgb(m_nColor).R, Color.FromArgb(m_nColor).G, Color.FromArgb(m_nColor).B).ToArgb();
    
    //ManagedTextureManager.Instance.Draw(nImageID, (int)m_fPosX, (int)m_fPosY, m_fScaleX, m_fScaleY, painter, 0, 0, 0.0f,newcolor);
	//CSGD_TextureManager
	CSGD_TextureManager::GetInstance()->Draw(ImageID, (int)m_fPosX, (int)m_fPosY, m_fScaleX, m_fScaleY, &m_rPaintRect, 0.0f,0.0f,0.0f);//,m_nColor);

}

void CParticle::SetInitialForcePoint(int X, int Y)
{
	/*m_cParticleArray[i].m_bInitialForceOn = true;
                //m_cParticleArray[i].m_fGravity = m_fGravity;
                m_cParticleArray[i].m_pInitialForcePoint.X = m_pInitialForcePoint.X;
                m_cParticleArray[i].m_pInitialForcePoint.Y = m_pInitialForcePoint.Y;*/
	m_bInitialForceOn = true;
	m_nInitialForceX = X;
	m_nInitialForceY = Y;
}

void CParticle::SetFixedAlpha(int fixAlpha)
{
	m_bfixedAlpha = true;
	m_nFixedAlpha = fixAlpha;
}