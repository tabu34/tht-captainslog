#ifndef CBasicEnemies_h__
#define CBasicEnemies_h__

#include "CUnit.h"

class CBasicEnemy : public CUnit
{
public:
	CBasicEnemy();
	//void Update(float fElapsedTime);
};

//////////////////////////////////////////////////////////////////////////

class CFootman : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CMinotaur : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CHarpie : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CElemental : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CChimera : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CCentaur : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CHydra : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CDemigod : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CCyclops : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};

class CTitan : public CUnit
{
public:
	void Update(float fElapsedTime);
	void Initialize();
};
#endif // CBasicEnemies_h__