#ifndef CTargetAbility_h__
#define CTargetAbility_h__

#include "CAbility.h"

class CUnit;

class CTargetAbility : public CAbility
{
	CUnit*	m_pTarget;

public:
	CTargetAbility()
	{
		Type(1);
		m_pTarget = NULL;
	}

	// Accessors ///////////////////////////////////
	CUnit* Target() const { return m_pTarget; }
	////////////////////////////////////////////////
	void Target(CUnit* tar) { m_pTarget = tar;} 

};
#endif // CTargetAbility_h__