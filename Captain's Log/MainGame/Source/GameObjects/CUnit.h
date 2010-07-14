#ifndef CUnit_h__
#define CUnit_h__

#include <vector>
#include "CBase.h"
#include "..\Managers\CPathManager.h"
using namespace std;

class CAbility;

class CUnit : public CBase
{
	bool				m_bBurned;
	bool				m_bCloaked;
	bool				m_bInvulnerable;
	bool				m_bRanged;
	bool				m_bSelected;
	bool				m_bStunned;
	float				m_fAttackDamage;
	float				m_fAttackSpeed;
	float				m_fAttackTimer;
	float				m_fMovementSpeed;
	float				m_fStunnedEndTime;
	int					m_fAttackRange;
	int					m_nArmor;
	int					m_nCurHealth;
	int					m_nHealthRegenRate;
	int					m_nLevel;
	int					m_nMaxHealth;
	int					m_nPortraitID;
	int					m_nCurDirection;
	vector<CAbility*>	m_vAbilities;
	vector<int>			m_vAnimations;

	//DEBUGGING
	float				m_fFireLineTime;
	//END

	//PATHING
	vector<tNode*>		m_vDirections;
	size_t				m_nNextMove;

	POINT				m_pFinalDest;

	POINT				m_pDestinationMove;
	int					m_nState;

	CUnit*				m_pTarget;



public:
		enum { UNIT_IDLE, UNIT_MOVING, UNIT_MOVING_ATTACK, UNIT_ATTACK, UNIT_FIRE };
	CUnit();
	virtual void Update(float fElapsedTime);
	virtual void Render();
	virtual void Attack(float fElapsedTime);

	// Orders //////////////////////////////////////
	void OrderMove( POINT _dest );
	void OrderMove( int _x, int _y);
	void OrderAttack( CUnit* pTarget);

	// Accessors ///////////////////////////////////
	bool Burned() const { return m_bBurned; }
	bool Cloaked() const { return m_bCloaked; }
	bool Invulnerable() const { return m_bInvulnerable; }
	bool Ranged() const { return m_bRanged; }
	bool Selected() const { return m_bSelected; }
	bool Stunned() const { return m_bStunned; }
	float AttackDamage() const { return m_fAttackDamage; }
	float AttackSpeed() const { return m_fAttackSpeed; }
	float AttackTimer() const { return m_fAttackTimer; }
	float MovementSpeed() const { return m_fMovementSpeed; }
	float StunnedEndTime() const { return m_fStunnedEndTime; }
	float FireLineTime() const { return m_fFireLineTime; }
	int Armor() const { return m_nArmor; }
	int AttackRange() const { return m_fAttackRange; }
	int CurHealth() const { return m_nCurHealth; }
	int HealthRegenRate() const { return m_nHealthRegenRate; }
	int Level() const { return m_nLevel; }
	int MaxHealth() const { return m_nMaxHealth; }
	int PortraitID() const { return m_nPortraitID; }
	int CurDirection() const { return m_nCurDirection; }
	int State() const { return m_nState; }
	POINT Destination() const { return m_pDestinationMove; }
	CUnit* Target() const { return m_pTarget; }
	vector<CAbility*> Abilities() const { return m_vAbilities; }
	vector<int>* Animations() { return &m_vAnimations; }
	////////////////////////////////////////////////

	// Mutators ////////////////////////////////////
	void Abilities(vector<CAbility*> val) { m_vAbilities = val; }
	void Animations(vector<int> val) { m_vAnimations = val; }
	void Armor(int val) { m_nArmor = val; }
	void AttackDamage(float val) { m_fAttackDamage = val; }
	void AttackRange(int val) { m_fAttackRange = val; }
	void AttackSpeed(float val) { m_fAttackSpeed = val; }
	void AttackTimer(float val) { m_fAttackTimer = val; }
	void FireLineTime(float val) { m_fFireLineTime = val; }
	void Burned(bool val) { m_bBurned = val; }
	void Cloaked(bool val) { m_bCloaked = val; }
	void CurHealth(int val) { m_nCurHealth = val; }
	void HealthRegenRate(int val) { m_nHealthRegenRate = val; }
	void Invulnerable(bool val) { m_bInvulnerable = val; }
	void Level(int val) { m_nLevel = val; }
	void MaxHealth(int val) { m_nMaxHealth = val; }
	void MovementSpeed(float val) { m_fMovementSpeed = val; }
	void PortraitID(int val) { m_nPortraitID = val; }
	void Ranged(bool val) { m_bRanged = val; }
	void Selected(bool val) { m_bSelected = val; }
	void Stunned(bool val) { m_bStunned = val; }
	void StunnedEndTime(float val) { m_fStunnedEndTime = val; }
	void CurDirection(int val) { m_nCurDirection = val; }
	void State(int val) { m_nState = val; }
	void Target(CUnit* val) { m_pTarget = val; }
	void Destination (LONG x, LONG y) { m_pDestinationMove.x = x; m_pDestinationMove.y = y; }
	////////////////////////////////////////////////
};
#endif // CUnit_h__