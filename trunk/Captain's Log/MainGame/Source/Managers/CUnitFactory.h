#ifndef CUnitFactory_h__
#define CUnitFactory_h__

#include <map>
using std::map;
using std::pair;

#define STARTING_ENEMIES 50

class CUnit;

struct tFactoryUnit 
{
	CUnit*	pUnit;
	bool	bIsBeingUsed;
};

class CUnitFactory
{
	map<string, CUnit*>	m_UnitTemplates;

	vector<tFactoryUnit*>	m_vBasicEnemies;
	vector<tFactoryUnit*>	m_vBossEnemies;

public:
	CUnitFactory();
	~CUnitFactory();
	CUnitFactory(CUnitFactory&);
	CUnitFactory& operator=(CUnitFactory&);

	void	RegisterItems();

public:
	static CUnitFactory* GetInstance();
	CUnit* CreateItem(string id);

};
#endif // CUnitFactory_h__