#include "precompiled_header.h"
#include "CCamera.h"

CCamera::CCamera()
{
	m_fX = 0;
	m_fY = 0;
	m_VelX = 0;
	m_VelY = 0;
}

RECT CCamera::GetCollisionRect()
{
	RECT output;
	output.left = (int)m_fX;
	output.top = (int)m_fY;
	output.right = output.left + CGame::GetInstance()->GetScreenWidth();
	output.bottom = output.top + CGame::GetInstance()->GetScreenHeight();
	return output;
}

void CCamera::Update( float fElapsedTime )
{
	m_fX = m_fX + m_VelX * fElapsedTime;
	m_fY = m_fY + m_VelY * fElapsedTime;
}
