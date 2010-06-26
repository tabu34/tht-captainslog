#ifndef CAbility_h__
#define CAbility_h__

class CAbility
{
	int		m_nType;
	bool	m_bIsActive;
	bool	m_bIsAuto;
	float	m_fCooldown;

public:

	// Accessors ///////////////////////////////////
	float Cooldown() const { return m_fCooldown; }
	bool IsAuto() const { return m_bIsAuto; }
	bool IsActive() const { return m_bIsActive; }
	int Type() const { return m_nType; }
	////////////////////////////////////////////////

	// Mutators ////////////////////////////////////
	void IsActive(bool val) { m_bIsActive = val; }
	////////////////////////////////////////////////

};
#endif // CAbility_h__