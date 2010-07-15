#ifndef CBossEnemies_h__
#define CBossEnemies_h__

#include "CUnit.h"

class CBossEnemy : public CUnit
{
public:
	CBossEnemy();
//	void Update(float fElapsedTime);
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