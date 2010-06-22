#include "CCamera.h"

RECT CCamera::GetCollisionRect()
{
	RECT output;
	output.left = (int)m_fX;
	output.top = (int)m_fY;
	output.right = output.left + CGame::GetInstance()->GetScreenWidth();
	output.bottom = output.top + CGame::GetInstance()->GetScreenHeight();
	return output;
}