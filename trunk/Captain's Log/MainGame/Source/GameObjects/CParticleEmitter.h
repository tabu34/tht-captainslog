#ifndef CParticleEmitter_h__
#define CParticleEmitter_h__

#include "CBase.h"

class CParticle;

class CParticleEmitter : public CBase
{
	//CParticle*	m_cParticleArray;

	int m_nImageID;
    int m_nNumParticles;
    float m_fPosX;
	float m_fPosY;
	CParticle* m_cParticleArray;

    int MaxParticleLife;
    int MinParticleLife;

    bool m_bInitialForceOn;
    int m_pInitialForcePointX;
	int m_pInitialForcePointY;


    int m_nGravity;
    int m_nGravityPointX;
	int m_nGravityPointY;

    int color;

    bool m_bfixedAlpha;
    int m_nFixedAlpha;

    int m_nHeight;
    int m_nWidth;

    float m_fXScale;
    float m_fYscale;
    float m_fMaxXscale;
    float m_dMaxYScale;
    bool m_bRandScaleOn;

    int m_nSpread;

	int m_nRed;
	int m_nGreen;
	int m_nBlue;

	

public:
	float PosX() const { return m_fPosX; }
	void PosX(float val) { m_fPosX = val; }
	float PosY() const { return m_fPosY; }
	void PosY(float val) { m_fPosY = val; }

	void	Initialize(int nImageID, int nWidth, int nHeight, int fPosX, int fPosY, int nNumParticles = 500, int nMinPartLife = 200, int nMaxPartLife = 500,
		int AlphaValue = 0, int initialForceX = 0, int initialForceY = 0, int BlendModeSource = 0, int BlendModeDest = 0,
		int minPartWidth = 100, int minPartHeight = 100, int maxPartWidth = 100, int maxPartHeight = 100, int nGravity = 0,
		int GravitySourceX = 0, int GravitySourceY = 0, int RandomSpread = 0, int red = 255, int green= 255, int blue= 255);
	void	Update(float fElapsedTime);
	void	Render();
	//~CParticleEmitter();

};
#endif // CParticleEmitter_h__