#ifndef CMedic_h__
#define CMedic_h__

#include "CPlayerUnit.h"

class CMedic : public CPlayerUnit
{
public:
	CMedic();

	void	Update(float fElapsedTime);
	void	Initialize();
	void	Render();
};
#endif // CMedic_h__