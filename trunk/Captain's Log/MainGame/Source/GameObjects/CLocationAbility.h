#ifndef CLocationAbility_h__
#define CLocationAbility_h__

#include "CAbility.h"

class CLocationAbility : public CAbility
{
	POINT	m_pLocation;
	bool	m_bLine;
	float	m_fRange;

public:

	// Accessors ///////////////////////////////////
	POINT Location() const { return m_pLocation; }
	bool Line() const { return m_bLine; }
	float Range() const { return m_fRange; }
	////////////////////////////////////////////////

};
#endif // CLocationAbility_h__