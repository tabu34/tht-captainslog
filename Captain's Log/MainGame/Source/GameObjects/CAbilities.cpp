#include "precompiled_header.h"
#include "CAbilities.h"
#include "CUnit.h"

void CAbility_DefensiveMatrix::Activate()
{
	if (TimePassed() > Cooldown())
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
	TimePassed(TimePassed() + fElapsedTime);

	if (IsActive() && TimePassed() > Duration())
	{
		Deactivate();
	}
}

void CAbility_PinningShot::Activate()
{
	if (TimePassed() > Cooldown())
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
	TimePassed(TimePassed() + fElapsedTime);

	if (IsActive() && TimePassed() > Duration())
	{
		Deactivate();
	}
}

void CAbility_Cloak::Activate()
{
	if (TimePassed() > Cooldown())
	{
		TimePassed(0);
		IsActive(true);
		Target()->Cloaked(true);
	}
}

void CAbility_Cloak::Deactivate()
{
	Target()->Cloaked(false);
	IsActive(false);
}

void CAbility_Cloak::Update(float fElapsedTime)
{
	TimePassed(TimePassed() + fElapsedTime);

	if (IsActive() && TimePassed() > Duration())
	{
		Deactivate();
	}
}

void CAbility_Refresh::Activate()
{
	if (TimePassed() > Cooldown())
	{
		Target()->CurHealth(Target()->CurHealth() + 20);
		TimePassed(0);
	}
}

void CAbility_Refresh::Update(float fElapsedTime)
{
	TimePassed(TimePassed() + fElapsedTime);
}

void CAbility_ArmorLockdown::Activate()
{
	if (TimePassed() > Cooldown())
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
	TimePassed(TimePassed() + fElapsedTime);

	if (IsActive() && TimePassed() > Duration())
	{
		Deactivate();
	}
}