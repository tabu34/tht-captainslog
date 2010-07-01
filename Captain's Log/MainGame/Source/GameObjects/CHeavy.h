#ifndef CHeavy_h__
#define CHeavy_h__

#include "CPlayerUnit.h"

class CHeavy : public CPlayerUnit
{
	int m_nCurFrame;

public:
	CHeavy();
	
	void	Update(float fElapsedTime);
	void	Render();
	void	Initialize();
};
#endif // CHeavy_h__