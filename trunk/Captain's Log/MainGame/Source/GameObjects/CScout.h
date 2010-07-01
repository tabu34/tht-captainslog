#ifndef CScout_h__
#define CScout_h__

#include "CPlayerUnit.h"

class CScout : public CPlayerUnit
{
public:
	CScout();

	void	Update(float fElapsedTime);
	void	Initialize();
	void	Render();
};
#endif // CScout_h__