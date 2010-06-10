#ifndef CBase_h__
#define CBase_h__

#include "IBaseInterface.h"
#include <Windows.h>

class CBase : public IBaseInterface
{
	float		m_fPosX;
	float		m_fPosY;
	int			m_nZIndex;
	int			m_nType;
	int			m_nWidth;
	int			m_nHeight;
	float		m_fVelX;
	float		m_fVelY;
	float		m_fRotation;
	float		m_fScale;

public:
	// Accessors ///////////////////////////////////
	float PosX() const { return m_fPosX; }
	float PosY() const { return m_fPosY; }
	int ZIndex() const { return m_nZIndex; }
	int Type() const { return m_nType; }
	int Width() const { return m_nWidth; }
	int Height() const { return m_nHeight; }
	float VelX() const { return m_fVelX; }
	float VelY() const { return m_fVelY; }
	float Rotation() const { return m_fRotation; }
	float Scale() const { return m_fScale; }
	////////////////////////////////////////////////

	// Mutators ////////////////////////////////////
	void PosX(float val) { m_fPosX = val; }
	void PosY(float val) { m_fPosY = val; }
	void ZIndex(int val) { m_nZIndex = val; }
	void Type(int val) { m_nType = val; }
	void Width(int val) { m_nWidth = val; }
	void Height(int val) { m_nHeight = val; }
	void VelX(float val) { m_fVelX = val; }
	void VelY(float val) { m_fVelY = val; }
	void Rotation(float val) { m_fRotation = val; }
	void Scale(float val) { m_fScale = val; }
	////////////////////////////////////////////////

	RECT GetCollisionRect();

	void	Update(float fElapsedTime);
	void	Render();
	void	AddRef();
	void	Release();
};
#endif // CBase_h__