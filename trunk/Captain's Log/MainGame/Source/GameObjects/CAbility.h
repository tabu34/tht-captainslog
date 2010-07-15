#ifndef CAbility_h__
#define CAbility_h__

class CAbility
{
	int		m_nType;
	bool	m_bIsActive;
	bool	m_bIsAuto;
	float	m_fCooldown;
	float	m_fDuration;
	float	m_fTimePassed;

public:

	virtual void Update(float fElapsedTime) {}

	virtual void Activate() {}

	// Accessors ///////////////////////////////////
	float Cooldown() const { return m_fCooldown; }
	float Duration() const { return m_fDuration; }
	float TimePassed() const { return m_fTimePassed; }
	bool IsAuto() const { return m_bIsAuto; }
	bool IsActive() const { return m_bIsActive; }
	int Type() const { return m_nType; }
	////////////////////////////////////////////////

	// Mutators ////////////////////////////////////
	void IsActive(bool val) { m_bIsActive = val; }
	void TimePassed(float val) { m_fTimePassed = val; }
	void Cooldown(float val) { m_fCooldown = val; }
	void Duration(float val) { m_fDuration = val; }
	void Type(int val) { m_nType = val; }
	////////////////////////////////////////////////

};
#endif // CAbility_h__