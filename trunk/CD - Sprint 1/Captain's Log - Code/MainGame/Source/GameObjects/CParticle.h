#ifndef CParticle_h__
#define CParticle_h__

#include "CBase.h"

class CParticle : public CBase
{
	int		m_nLife;

public:
	void	Initialize(int nImageID, int nLife, float fPosX, float fPosY);
	void	Update(float fElapsedTime);
	void	Render();

};
#endif // CParticle_h__