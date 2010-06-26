#ifndef CItem_h__
#define CItem_h__

#include "CBase.h"

class CUnit;

class CItem : public CBase
{
	int		m_nType;
	float	m_fAmount;
	CUnit*	m_pUnit;

public:
	virtual void	AddEffect();
	virtual void	RemoveEffect();

	void	Collect();
	void	Drop();

};
#endif // CItem_h__