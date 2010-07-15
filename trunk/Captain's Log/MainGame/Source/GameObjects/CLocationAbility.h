#ifndef CLocationAbility_h__
#define CLocationAbility_h__

#include "CAbility.h"
#include <windows.h>

class CLocationAbility : public CAbility
{
	POINT	m_pLocation;
	bool	m_bLine;
	float	m_fRange;

public:

	CLocationAbility()
	{
		Type(2);
		m_pLocation.x = 0;
		m_pLocation.y = 0;
		m_bLine = false;
		m_fRange = 0.0f;
	}

	// Accessors ///////////////////////////////////
	POINT Location() const { return m_pLocation; }
	bool Line() const { return m_bLine; }
	float Range() const { return m_fRange; }
	////////////////////////////////////////////////

	void Location(int x, int y) { m_pLocation.x = x; m_pLocation.y = y; }
	void Line(bool line) { m_bLine = line; }
	void Range(float range) { m_fRange = range; }

};
#endif // CLocationAbility_h__