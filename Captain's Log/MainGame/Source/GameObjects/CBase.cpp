#include "precompiled_header.h"
#include "CBase.h"

CBase::CBase()
{
	m_fPosX = 0;
	m_fPosY = 0;
	m_nZIndex = 0;
	m_nType = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_fVelX = 0;
	m_fVelY = 0;
	m_fRotation = 0;
	m_fScale = 1;
	AddRef();
}

RECT CBase::GetCollisionRect()
{
	RECT tempRect;
	tempRect.left=long((int)PosX() - Width() / 2);
	tempRect.top=long((int)PosY() - Height() / 2);
	tempRect.right=tempRect.left+Width();
	tempRect.bottom=tempRect.top+Height();

	return tempRect;
}

void CBase::Update( float fElapsedTime )
{
	PosX( PosX() + VelX() * fElapsedTime );
	PosY( PosY() + VelY() * fElapsedTime );
	return;
}

void CBase::Render()
{

}

void CBase::AddRef()
{

}

void CBase::Release()
{

}
