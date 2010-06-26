#ifndef CScout_h__
#define CScout_h__

#include "CPlayerUnit.h"

class CScout : public CPlayerUnit
{
public:
	void	Update(float fElapsedTime);
	void	Initialize();
};
#endif // CScout_h__