#ifndef CBossEnemies_h__
#define CBossEnemies_h__

#include "CUnit.h"

class CBossEnemy : public CUnit
{
	bool m_bMirrored;

public:
	CBossEnemy();
	void Update(float fElapsedTime);
	void Update7(float fElapsedTime);
	void Update16(float fElapsedTime);
	void Render();
	void Render7();
	void Render16();

	void SetMirrored(bool val) { m_bMirrored = val; }
};

//////////////////////////////////////////////////////////////////////////

class CMedusa : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CPoseidon : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CAres : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CAthena : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CZeus : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};
#endif // CBossEnemies_h__