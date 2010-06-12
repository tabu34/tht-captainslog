#ifndef CTargetAbility_h__
#define CTargetAbility_h__

#include "CAbility.h"

class CTargetAbility
{
	CBase*	m_pTarget;

public:

	// Accessors ///////////////////////////////////
	CBase* Target() const { return m_pTarget; }
	////////////////////////////////////////////////

};
#endif // CTargetAbility_h__