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
		TimePassed(50);
		Duration(8);
		IsActive(false);
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
		TimePassed(20);
		Duration(6);
		IsActive(false);
	}

	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_Cloak : public CTargetAbility
{
public:
	CAbility_Cloak(CUnit* tar)
	{
		Type(0);
		Target(tar);
		IsActive(false);
	}
	void Activate();
};

class CAbility_Refresh : public CTargetAbility
{
public:
	CAbility_Refresh()
	{
		TimePassed(12);
		Cooldown(12);
		IsActive(false);
	}

	void Activate();

	void Update(float fElapsedTime);
};

class CAbility_Overdrive : public CTargetAbility
{
	float m_fAttackSpeed;
public:
	CAbility_Overdrive(CUnit* tar)
	{
		Type(0);
		Target(tar);
		TimePassed(30);
		Cooldown(30);
		Duration(7);
		IsActive(false);
	}

	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_ArmorLockdown : public CTargetAbility
{
public:
	CAbility_ArmorLockdown(CUnit* tar)
	{
		Type(0);
		Target(tar);
		TimePassed(60);
		Cooldown(60);
		Duration(12);
		IsActive(false);
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
	CAbility_RocketBarrage()
	{
		TimePassed(30);
		Cooldown(30);
		Range(150);
	}

	void Activate();

	void Update(float fElapsedTime);
};

class CAbility_StunGrenade : public CLocationAbility
{
public:
	CAbility_StunGrenade()
	{
		TimePassed(30);
		Cooldown(30);
		Range(150);
	}

	void Activate();

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