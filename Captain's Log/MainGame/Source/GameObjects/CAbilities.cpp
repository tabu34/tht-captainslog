#include "precompiled_header.h"
#include "CAbilities.h"
#include "CUnit.h"

void CAbility_DefensiveMatrix::Activate()
{
	if (TimePassed() >= Cooldown())
	{
		TimePassed(0);
		IsActive(true);
		Target()->Invulnerable(true);
	}
}

void CAbility_DefensiveMatrix::Deactivate()
{
	Target()->Invulnerable(false);
	IsActive(false);
}

void CAbility_DefensiveMatrix::Update(float fElapsedTime)
{

	if (TimePassed() < Cooldown())
	{
		TimePassed(TimePassed() + fElapsedTime);
	}
	else
	{
		TimePassed(Cooldown());
	}

	if (IsActive() && TimePassed() > Duration())
	{
		Deactivate();
	}
}

void CAbility_PinningShot::Activate()
{
	if (TimePassed() >= Cooldown())
	{
		TimePassed(0);
		IsActive(true);
		m_fMovementSpeed = Target()->MovementSpeed();
		Target()->MovementSpeed(0);
	}
}

void CAbility_PinningShot::Deactivate()
{
	Target()->MovementSpeed(m_fMovementSpeed);
	IsActive(false);
}

void CAbility_PinningShot::Update(float fElapsedTime)
{
	if (TimePassed() < Cooldown())
	{
		TimePassed(TimePassed() + fElapsedTime);
	}
	else
	{
		TimePassed(Cooldown());
	}

	if (IsActive() && TimePassed() > Duration())
	{
		Deactivate();
	}
}

void CAbility_Cloak::Activate()
{
	if (!IsActive())
	{
		IsActive(true);
		Target()->Cloaked(true);
	}
	else
	{
		Target()->Cloaked(false);
		IsActive(false);
	}
}

void CAbility_Refresh::Activate()
{
	if (TimePassed() >= Cooldown())
	{
		Target()->CurHealth(Target()->CurHealth() + 20);
		TimePassed(0);
	}
}

void CAbility_Refresh::Update(float fElapsedTime)
{
	if (TimePassed() < Cooldown())
	{
		TimePassed(TimePassed() + fElapsedTime);
	}
	else
	{
		TimePassed(Cooldown());
	}
}

void CAbility_Overdrive::Activate()
{
	if (TimePassed() >= Cooldown())
	{
		TimePassed(0);
		IsActive(true);
		m_fAttackSpeed = Target()->AttackSpeed();
		Target()->AttackSpeed(Target()->AttackSpeed() - (Target()->AttackSpeed() * 0.5f));
	}
}

void CAbility_Overdrive::Deactivate()
{
	Target()->AttackSpeed(m_fAttackSpeed);
	IsActive(false);
}

void CAbility_Overdrive::Update(float fElapsedTime)
{
	if (TimePassed() < Cooldown())
	{
		TimePassed(TimePassed() + fElapsedTime);
	}
	else
	{
		TimePassed(Cooldown());
	}

	if (IsActive() && TimePassed() > Duration())
	{
		Deactivate();
	}
}

void CAbility_ArmorLockdown::Activate()
{
	if (TimePassed() >= Cooldown())
	{
		Target()->Armor(Target()->Armor() + 50);
		TimePassed(0);
		IsActive(true);
	}
}

void CAbility_ArmorLockdown::Deactivate()
{
	Target()->Armor(Target()->Armor() - 50);
	IsActive(false);
}

void CAbility_ArmorLockdown::Update(float fElapsedTime)
{
	if (TimePassed() < Cooldown())
	{
		TimePassed(TimePassed() + fElapsedTime);
	}
	else
	{
		TimePassed(Cooldown());
	}

	if (IsActive() && TimePassed() > Duration())
	{
		Deactivate();
	}
}

void CAbility_StunGrenade::Activate()
{
	if (TimePassed() >= Cooldown())
	{
		for (unsigned int i = 0; i < CObjectManager::GetInstance()->GetObjectList()->size(); i++)
		{
			if ((*CObjectManager::GetInstance()->GetObjectList())[i]->Type() != CUnit::OBJ_PLAYER)
			{
				if(((*CObjectManager::GetInstance()->GetObjectList())[i]->PosX() - Location().x) * ((*CObjectManager::GetInstance()->GetObjectList())[i]->PosX() - Location().x) + ((*CObjectManager::GetInstance()->GetObjectList())[i]->PosY() - Location().y) * ((*CObjectManager::GetInstance()->GetObjectList())[i]->PosY() - Location().y) < (Range() * Range()))
				{
					((CUnit*)(*CObjectManager::GetInstance()->GetObjectList())[i])->Stunned(true);
					((CUnit*)(*CObjectManager::GetInstance()->GetObjectList())[i])->StunnedEndTime(5);
					((CUnit*)(*CObjectManager::GetInstance()->GetObjectList())[i])->StunnedCurrTime(0);
				}
			}
		}
		TimePassed(0);
	}
}

void CAbility_StunGrenade::Update(float fElapsedTime)
{
	if (TimePassed() < Cooldown())
	{
		TimePassed(TimePassed() + fElapsedTime);
	}
	else
	{
		TimePassed(Cooldown());
	}
}

void CAbility_RocketBarrage::Activate()
{
	if (TimePassed() >= Cooldown())
	{
		for (unsigned int i = 0; i < CObjectManager::GetInstance()->GetObjectList()->size(); i++)
		{
			if ((*CObjectManager::GetInstance()->GetObjectList())[i]->Type() != CUnit::OBJ_PLAYER)
			{
				if(((*CObjectManager::GetInstance()->GetObjectList())[i]->PosX() - Location().x) * ((*CObjectManager::GetInstance()->GetObjectList())[i]->PosX() - Location().x) + ((*CObjectManager::GetInstance()->GetObjectList())[i]->PosY() - Location().y) * ((*CObjectManager::GetInstance()->GetObjectList())[i]->PosY() - Location().y) < (Range() * Range()))
				{
					((CUnit*)(*CObjectManager::GetInstance()->GetObjectList())[i])->CurHealth(((CUnit*)(*CObjectManager::GetInstance()->GetObjectList())[i])->CurHealth() - 50);
				}
			}
		}
		TimePassed(0);
	}
}

void CAbility_RocketBarrage::Update(float fElapsedTime)
{
	if (TimePassed() < Cooldown())
	{
		TimePassed(TimePassed() + fElapsedTime);
	}
	else
	{
		TimePassed(Cooldown());
	}
}