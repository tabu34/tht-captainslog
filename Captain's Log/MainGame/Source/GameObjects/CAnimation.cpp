#include "precompiled_header.h"
#include "CAnimation.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"

CAnimation::CAnimation()
{
	m_nImageID		= -1;
	m_nCurFrame		= 0;
	m_fTimeWaited	= 0.0f;
	m_fSpeed		= 0.0f;
	m_bIsPlaying	= false;
	m_bIsLooping	= false;
}

CAnimation::~CAnimation()
{
	//Shutdown();
}

void CAnimation::Init( char* szAnimationName, char* szImageID, DWORD dwKeyColor, float fSpeed, bool bIsLooping, int nNumFrames, tFrame* pFrames)
{
	m_nImageID		= CSGD_TextureManager::GetInstance()->LoadTexture(szImageID, dwKeyColor);
	m_fSpeed		= fSpeed;
	m_bIsLooping	= bIsLooping;
	strcpy_s(m_szName, 50, szAnimationName);

	for (int i = 0; i < nNumFrames; i++)
	{
		tFrame tempFrame;
		tempFrame.rFrame	= pFrames[i].rFrame;
		tempFrame.ptAnchor	= pFrames[i].ptAnchor;
		tempFrame.fDuration	= pFrames[i].fDuration;
		strcpy_s(tempFrame.szTrigger, 100, pFrames[i].szTrigger);
		tempFrame.cFrame	= pFrames[i].cFrame;
		m_vFrames.push_back(tempFrame);
	}

	Reset();
}

void CAnimation::Shutdown()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nImageID);
}

void CAnimation::Update( float fElapsedTime )
{
	//Return if not playing
	if (m_bIsPlaying == false)
		return;

	m_fTimeWaited += fElapsedTime * m_fSpeed;

	if (m_fTimeWaited > m_vFrames[m_nCurFrame].fDuration)
	{

		m_fTimeWaited = 0.0f;
		//m_fTimeWaited -= m_vFrames[m_nCurFrame].fDuration;

		m_nCurFrame++;

		if (m_nCurFrame >= m_vFrames.size())
		{
			if (m_bIsLooping)
				Reset();
			else
			{
				Stop();
				m_nCurFrame = m_vFrames.size() - 1;
			}
		}
	}
}

void CAnimation::Render( int nPosX, int nPosY, bool bIsFlipped, float fScale, DWORD dwColor )
{
	RECT rFrame = m_vFrames[m_nCurFrame].rFrame;
	POINT ptAnchor = m_vFrames[m_nCurFrame].ptAnchor;

	float fScaleX = fScale;
	if (bIsFlipped)
	{
		fScaleX *= -1;
		int width = rFrame.right - rFrame.left;
		nPosX += int((float)width * fScale);
		ptAnchor.x = width - ptAnchor.x;
	}	
	CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nPosX - int(ptAnchor.x * fScale), nPosY - int(ptAnchor.y * fScale), fScaleX, fScale, &rFrame, 0, 0, 0, dwColor);
}

void CAnimation::Reset()
{
	m_nCurFrame = 0;
	m_fTimeWaited = 0.0f;
}

RECT CAnimation::GetCollisionRect( bool bIsFlipped )
{
	RECT rFrame;
	POINT ptAnchor;

	rFrame = m_vFrames[CurFrame()].rFrame;
	ptAnchor = m_vFrames[CurFrame()].ptAnchor;

	if (bIsFlipped)
		ptAnchor.x = rFrame.right - rFrame.left - ptAnchor.x;

	RECT tempRect;

	SetRect(&tempRect,
		0 - ptAnchor.x,
		0 - ptAnchor.y,
		0 - ptAnchor.x + rFrame.right - rFrame.left,
		0 - ptAnchor.y + rFrame.bottom - rFrame.top);

	return tempRect;
}