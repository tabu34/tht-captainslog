#ifndef CMedic_h__
#define CMedic_h__

#include "CPlayerUnit.h"

class CMedic : public CPlayerUnit
{
public:
	void	Update(float fElapsedTime);
	void	Initialize();
};
#endif // CMedic_h__