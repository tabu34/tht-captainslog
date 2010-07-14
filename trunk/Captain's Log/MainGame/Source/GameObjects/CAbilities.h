#ifndef CAbilities_h__
#define CAbilities_h__

#include "CTargetAbility.h"
#include "CLocationAbility.h"

class CAbility_DefensiveMatrix : public CTargetAbility
{
public:
	CAbility_DefensiveMatrix()
	{
		Cooldown(50);
		Duration(8);
	}

	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_PinningShot : public CTargetAbility
{
	float m_fMovementSpeed;
public:
	CAbility_PinningShot()
	{
		Cooldown(20);
		Duration(6);
	}

	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_Cloak : public CTargetAbility
{
public:
	void Activate();
};

class CAbility_Refresh : public CTargetAbility
{
public:
	CAbility_Refresh()
	{
		Cooldown(12);
	}

	void Activate();

	void Update(float fElapsedTime);
};

class CAbility_Overdrive : public CTargetAbility
{
	float m_fAttackSpeed;
public:
	CAbility_Overdrive()
	{
		Cooldown(60);
		Duration(15);
	}

	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_ArmorLockdown : public CTargetAbility
{
public:
	CAbility_ArmorLockdown()
	{
		Cooldown(60);
		Duration(12);
	}

	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_TacticalDrone : public CTargetAbility
{
public:
	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_RodOfLightning : public CTargetAbility
{
public:
	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_RocketBarrage : public CLocationAbility
{
public:
	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_StunGrenade : public CLocationAbility
{
public:
	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_FlameThrower : public CLocationAbility
{
public:
	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_StoneOfTheDead : public CLocationAbility
{
public:
};

class CAbility_TsunamiStone : public CLocationAbility
{
public:
};

class CAbility_MedusasTorch : public CLocationAbility
{
public:
};

class CAbility_RingOfWar : public CLocationAbility
{
public:
};

class CAbility_ArcOfLife : public CLocationAbility
{
public:
};

class CAbility_WizardsStaff : public CLocationAbility
{
public:
};
#endif // CAbilities_h__