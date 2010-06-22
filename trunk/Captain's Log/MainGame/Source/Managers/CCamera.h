#ifndef CCamera_h__
#define CCamera_h__
#include <windows.h>
#include "..\CGame.h"
class CCamera
{
	float m_fX;
	float m_fY;

public:
	float GetX() { return m_fX; }
	float GetY() { return m_fY; }
	RECT GetCollisionRect();
};
#endif // CCamera_h__