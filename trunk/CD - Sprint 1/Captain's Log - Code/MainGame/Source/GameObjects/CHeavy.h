#ifndef CHeavy_h__
#define CHeavy_h__

#include "CPlayerUnit.h"

class CHeavy : public CPlayerUnit
{
public:
	void	Update(float fElapsedTime);
	void	Initialize();
};
#endif // CHeavy_h__