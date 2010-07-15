#ifndef CAppliedItem_h__
#define CAppliedItem_h__

#include "CItem.h"

class CAppliedItem : public CItem
{
public:
	CAppliedItem();

	void	AddEffect();
	void	RemoveEffect();
};
#endif // CAppliedItem_h__