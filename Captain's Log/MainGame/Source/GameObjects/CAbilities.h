#ifndef CAbilities_h__
#define CAbilities_h__

#include "CTargetAbility.h"
#include "CLocationAbility.h"

class CAbility_DefensiveMatrix : public CTargetAbility
{
public:
	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_PinningShot : public CTargetAbility
{
	float m_fMovementSpeed;
public:

	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_Cloak : public CTargetAbility
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

class CAbility_Refresh : public CTargetAbility
{
public:
	void Activate();

	void Update(float fElapsedTime);
};

class CAbility_Overdrive : public CTargetAbility
{
public:
	void Activate();
	void Deactivate();

	void Update(float fElapsedTime);
};

class CAbility_ArmorLockdown : public CTargetAbility
{
public:
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