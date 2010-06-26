#ifndef CParticle_h__
#define CParticle_h__

#include "CBase.h"

class CParticle : public CBase
{
	//int		m_nLife;

	//Particle Life
	float	m_fInitialLife;
    float	m_fLife;

	//Particle Scale
    float	m_fScaleX;
    float	m_fScaleY;

	//Particle Position
    float	m_fPosX;
    float	m_fPosY;

	//Particle Speed
    float	m_fSpeedX;
    float	m_fSpeedY;

	//Particle Forces (Forces applied to the particle)
    int		m_nForceX;
	int		m_nForceY;

	//Initial force information
    bool	m_bInitialForceOn;
    int 	m_nInitialForceX;
	int		m_nInitialForceY;
    
	//Gravity force
    float	m_fGravityForce;

	//Particle Color
    int		m_nColor;

	//Alpha Information
    bool	m_bfixedAlpha;
    int		m_nFixedAlpha;

	//Spread Information
    int		m_nSpreadx;
    int		m_nSpready;

	//Paint Rect
	RECT	m_rPaintRect;

public:

	void Initialize(int nImageID,int nLife, float fScaleX, float fScaleY, float fPosX, float fPosY, int ncolor);

	void Update( float fElapsedTime, int GravityPointX, int GravityPointY, int nGravity, int nSpread);

	void Render(int ImageID, int red = 255, int green = 255, int blue = 255);

    bool IsDead(){return (m_fLife <= 0);}

	void SetInitialForcePoint(int X, int Y);

	void SetFixedAlpha(int fixAlpha);

};
#endif // CParticle_h__