#ifndef CActive_h__
#define CActive_h__

#include "CItem.h"

class CActive : public CItem
{
public:
	void	AddEffect();
	void	RemoveEffect();
	void	Activate();
};
#endif // CActive_h__