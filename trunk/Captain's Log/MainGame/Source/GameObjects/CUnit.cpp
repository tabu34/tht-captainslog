#include "precompiled_header.h"
#include "CUnit.h"
#include <cmath>

CUnit::CUnit()
{
	m_nState = -1;
}

void CUnit::OrderMove( POINT _dest )
{
	m_nState = UNIT_MOVING;
	m_pDestinationMove = _dest;
}

void CUnit::OrderMove( int _x, int _y)
{
	m_nState = UNIT_MOVING;
	m_pDestinationMove.x = _x;
	m_pDestinationMove.y = _y;
}

void CUnit::Update(float fElapsedTime)
{
	CBase::Update(fElapsedTime);

	if(m_nState == UNIT_MOVING)
	{
		if(PosX() < m_pDestinationMove.x)
			VelX(100.0f);
		else
			VelX(-100.0f);

		if(PosY() < m_pDestinationMove.y)
			VelY(100.0f);
		else
			VelY(-100.0f);

		if(fabs(PosX() - m_pDestinationMove.x) < 1.0f)
		{
			VelX(0.0f);
		}

		if(fabs(PosY() - m_pDestinationMove.y) < 1.0f)
		{
			VelY(0.0f);
		}

		if(VelX() == 0.0f && VelY() == 0.0f)
			m_nState = -1;
	}

}