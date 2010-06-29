#ifndef CCamera_h__
#define CCamera_h__
#include <windows.h>
#include "..\CGame.h"
class CCamera
{
	float m_fX;
	float m_fY;

	float m_VelX;
	float m_VelY;

public:
	CCamera();

	float GetX() { return m_fX; }
	float GetY() { return m_fY; }
	float VelX() const { return m_VelX; }
	float VelY() const { return m_VelY; }

	void SetX(float _x) { m_fX = _x; }
	void SetY(float _y) { m_fY = _y; }
	void VelX(float val) { m_VelX = val; }
	void VelY(float val) { m_VelY = val; }

	RECT GetCollisionRect();
	void Input();
	void Update(float fElapsedTime);
};
#endif // CCamera_h__