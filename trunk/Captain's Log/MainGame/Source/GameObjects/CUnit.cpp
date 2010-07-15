#include "precompiled_header.h"
#include "CUnit.h"
#include "../Managers/CMessageSystem.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../States/CGamePlayState.h"
#include "CAbilities.h"
#include <cmath>

CUnit::CUnit()
{
	m_nState = UNIT_IDLE;
	m_nCurDirection = 0;
	m_fAttackTimer = 0;
	m_bStunned = false;
	m_bInvulnerable = false;
	m_bSelected=false;
	MovementSpeed(100);
}

void CUnit::OrderMove( POINT _dest )
{
	m_nState = UNIT_MOVING;
	if(CPathManager::GetInstance()->CheckPath(PosX(), PosY(), (float)_dest.x, (float)_dest.y) && !CPathManager::GetInstance()->IsPointInside(_dest))
	{
		m_vDirections.clear();
		m_pDestinationMove = _dest;
	}
	else
	{
		m_vDirections = CPathManager::GetInstance()->GetPath(PosX(), PosY(), (float)_dest.x, (float)_dest.y);
		if(m_vDirections.size()>0)
		{
			m_pDestinationMove.x = (LONG)m_vDirections[0]->fX;
			m_pDestinationMove.y = (LONG)m_vDirections[0]->fY;
			m_nNextMove = 1;

			POINT p = _dest;
			if(!CPathManager::GetInstance()->IsPointInside(p))
			{
				m_pFinalDest = p;
			}
			else
			{
				m_pFinalDest.x = m_pFinalDest.y = -1;
			}
		}
		else
			m_nState = UNIT_IDLE;
	}
}

void CUnit::OrderMove( int _x, int _y)
{
	m_nState = UNIT_MOVING;
	POINT pP = {_x, _y};
	if(CPathManager::GetInstance()->CheckPath(PosX(), PosY(), (float)_x, (float)_y) && !CPathManager::GetInstance()->IsPointInside(pP))
	{
		m_vDirections.clear();
		m_pDestinationMove.x = _x;
		m_pDestinationMove.y = _y;
	}
	else
	{
		m_vDirections = CPathManager::GetInstance()->GetPath(PosX(), PosY(), (float)_x, (float)_y);
		if(m_vDirections.size()>0)
		{
			m_pDestinationMove.x = (LONG)m_vDirections[0]->fX;
			m_pDestinationMove.y = (LONG)m_vDirections[0]->fY;
			m_nNextMove = 1;

			POINT p = {_x, _y};
			if(!CPathManager::GetInstance()->IsPointInside(p))
			{
				m_pFinalDest = p;
			}
			else
			{
				m_pFinalDest.x = m_pFinalDest.y = -1;
			}
		}
		else
			m_nState = UNIT_IDLE;
	}
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

	if (m_nCurHealth > m_nMaxHealth)
	{
		m_nCurHealth--;
	}

	if (m_bStunned)
	{
		return;
	}

	if (m_nState == UNIT_IDLE)
	{
		VelX(0.0f);
		VelY(0.0f);
	}
	else if(m_nState == UNIT_MOVING)
	{
		if(PosX() < m_pDestinationMove.x)
			VelX(MovementSpeed());
		else
			VelX(-MovementSpeed());

		if(PosY() < m_pDestinationMove.y)
			VelY(MovementSpeed());
		else
			VelY(-MovementSpeed());

		if(fabs(PosX() - m_pDestinationMove.x) < 1.0f)
		{
			VelX(0.0f);
		}

		if(fabs(PosY() - m_pDestinationMove.y) < 1.0f)
		{
			VelY(0.0f);
		}

		if(VelX() == 0.0f && VelY() == 0.0f)
		{
			if(m_vDirections.size()>0)
			{
				if(m_nNextMove<m_vDirections.size())
				{
					m_pDestinationMove.x = (LONG)m_vDirections[m_nNextMove]->fX;
					m_pDestinationMove.y = (LONG)m_vDirections[m_nNextMove]->fY;
					m_nNextMove++;
				}
				else
				{
					if(m_pFinalDest.x!=-1 && m_pFinalDest.y!=-1)
					{
						m_pDestinationMove=m_pFinalDest;
						m_vDirections.clear();
					}
					else
						m_nState=UNIT_IDLE;
				}
			}
			else
			{
				m_nState=UNIT_IDLE;
			}
		}
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
				VelX(MovementSpeed());
			else
				VelX(-MovementSpeed());

			if(PosY() < m_pTarget->PosY())
				VelY(MovementSpeed());
			else
				VelY(-MovementSpeed());
		}
	}
	else if (m_nState == UNIT_ATTACK || UNIT_FIRE)
	{
		Attack(fElapsedTime);
	}

	for (unsigned int i = 0; i < m_vAbilities.size(); i++)
	{
		m_vAbilities[i]->Update(fElapsedTime);
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
			if (m_pTarget->Invulnerable() == false && !CGamePlayState::GetInstance()->GodMode())
			{
				m_pTarget->CurHealth(m_pTarget->CurHealth() - (int)(m_fAttackDamage - (m_fAttackDamage * m_pTarget->Armor() * 0.01f)));
			}
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