#include "precompiled_header.h"
#include "CUnit.h"
#include "../Managers/CMessageSystem.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include <cmath>

CUnit::CUnit()
{
	m_nState = UNIT_IDLE;
	m_nCurDirection = 0;
	m_fAttackTimer = 0;
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

void CUnit::OrderAttack(CUnit* pTarget)
{
	m_nState = UNIT_MOVING_ATTACK;
	m_pTarget = pTarget;
}

void CUnit::Update(float fElapsedTime)
{
	CBase::Update(fElapsedTime);

	//DEBUG
	if (m_fFireLineTime > 0)
	{
		m_fFireLineTime -= fElapsedTime;
	}
	//END

	if (m_nCurHealth <= 0)
	{
		CMessageSystem::GetInstance()->SendMessage(new CUnitDeathMessage(this));
		return;
	}

	if (m_nState == UNIT_IDLE)
	{

	}
	else if(m_nState == UNIT_MOVING)
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
			m_nState = UNIT_IDLE;
	}
	else if (m_nState == UNIT_MOVING_ATTACK)
	{
		if (m_pTarget->CurHealth() <= 0)
		{
			m_nState = UNIT_MOVING;
			m_pDestinationMove.x = (LONG)PosX();
			m_pDestinationMove.y = (LONG)PosY();
		}
		else if (fabs(((PosX() - m_pTarget->PosX()) * (PosX() - m_pTarget->PosX()) +
		   (PosY() - m_pTarget->PosY()) * (PosY() - m_pTarget->PosY()))) < (m_fAttackRange * m_fAttackRange))
		{
			VelX(0);
			VelY(0);
			m_nState = UNIT_ATTACK;
		}
		else
		{
			if(PosX() < m_pTarget->PosX())
				VelX(100.0f);
			else
				VelX(-100.0f);

			if(PosY() < m_pTarget->PosY())
				VelY(100.0f);
			else
				VelY(-100.0f);
		}
	}
	else if (m_nState == UNIT_ATTACK || UNIT_FIRE)
	{
		Attack(fElapsedTime);
	}
}

void CUnit::Attack(float fElapsedTime)
{
	if (m_pTarget->Type() != OBJ_ENEMY)
	{
		m_nState = UNIT_MOVING;
		m_pDestinationMove.x = (LONG)PosX();
		m_pDestinationMove.y = (LONG)PosY();
		return;
	}

	if (m_pTarget->CurHealth() <= 0)
	{
		m_nState = UNIT_MOVING;
		m_pDestinationMove.x = (LONG)PosX();
		m_pDestinationMove.y = (LONG)PosY();
	}
	else if (fabs(((PosX() - m_pTarget->PosX()) * (PosX() - m_pTarget->PosX()) +
		(PosY() - m_pTarget->PosY()) * (PosY() - m_pTarget->PosY()))) > (m_fAttackRange * m_fAttackRange))
	{
		m_nState = UNIT_MOVING_ATTACK;
	}
	else
	{
		if (m_fFireLineTime <= 0)
		{
			m_nState = UNIT_ATTACK;
		}
		m_fAttackTimer += fElapsedTime;
		if (m_fAttackTimer >= m_fAttackSpeed)
		{
			m_pTarget->CurHealth(m_pTarget->CurHealth() - (int)(m_fAttackDamage - (m_fAttackDamage * m_pTarget->Armor() * 0.01f)));
			m_fAttackTimer = 0;
			m_fFireLineTime = 0.2f;
			m_nState = UNIT_FIRE;
		}
	}
}

void CUnit::Render()
{
	CBase::Render();

	char szHP[16];
	sprintf_s(szHP, 16, "%i", CurHealth());

	//DEBUG
	if (m_fFireLineTime > 0)
	{
		CSGD_Direct3D::GetInstance()->DrawLine(int(PosX() - CGame::GetInstance()->GetCamera()->GetX()), int(PosY() - CGame::GetInstance()->GetCamera()->GetY()), int(m_pTarget->PosX() - CGame::GetInstance()->GetCamera()->GetX()), int(m_pTarget->PosY() - CGame::GetInstance()->GetCamera()->GetY()), 255, 255, 255);
	}
	//END
}