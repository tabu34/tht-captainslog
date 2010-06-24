#ifndef CMarine_h__
#define CMarine_h__

#include "CPlayerUnit.h"

class CMarine : public CPlayerUnit
{
public:
	void	Update(float fElapsedTime);
	void	Render();
	void	Initialize();
};
#endif // CMarine_h__