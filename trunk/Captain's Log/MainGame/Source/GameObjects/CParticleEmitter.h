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

	~CParticleEmitter();

public:
	void	Initialize(int nImageID, int nHeight, int nWidth, float fPosX, float fPosY, int nNumParticles, int nMaxPartLife, int nMinPartLife);
	void	Update(float fElapsedTime);
	void	Render();


};
#endif // CParticleEmitter_h__