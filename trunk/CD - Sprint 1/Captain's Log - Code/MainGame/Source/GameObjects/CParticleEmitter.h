#ifndef CParticleEmitter_h__
#define CParticleEmitter_h__

#include "CBase.h"

class CParticle;

class CParticleEmitter : public CBase
{
	CParticle*	m_cParticleArray;

public:
	void	Initialize(int nImageID, int nHeight, int nWidth, float fPosX, float fPosY);
	void	Update(float fElapsedTime);
	void	Render();
};
#endif // CParticleEmitter_h__