#include "precompiled_header.h"
#include "CUnitFactory.h"
#include "..\GameObjects\CBasicEnemies.h"
#include "..\GameObjects\CBossEnemies.h"

CUnitFactory::CUnitFactory()
{
	for (int i = 0; i < STARTING_ENEMIES; i++)
	{
		tFactoryUnit* tempFactoryUnit = new tFactoryUnit();
		tempFactoryUnit->bIsBeingUsed = false;
		tempFactoryUnit->pUnit = new CUnit();
		m_vBasicEnemies.push_back(tempFactoryUnit);

		tempFactoryUnit = new tFactoryUnit();
		tempFactoryUnit->bIsBeingUsed = false;
		tempFactoryUnit->pUnit = new CUnit();
		m_vBossEnemies.push_back(tempFactoryUnit);
	}
}

CUnitFactory::~CUnitFactory()
{
	for (unsigned int i = 0; i < m_vBasicEnemies.size(); i++)
	{
		SAFE_RELEASE(m_vBasicEnemies[i]->pUnit);
		SAFE_DELETE(m_vBasicEnemies[i]);
	}
	m_vBasicEnemies.clear();

	while (!m_UnitTemplates.empty())
	{
		map<string, CUnit*>::iterator iter = m_UnitTemplates.begin();
		SAFE_RELEASE(iter->second);
		m_UnitTemplates.erase(iter);
	}
}

CUnitFactory* CUnitFactory::GetInstance()
{
	static CUnitFactory instance;
	return &instance;
}

CUnit* CUnitFactory::CreateItem(string id)
{
	map<string, CUnit*>::iterator iter = m_UnitTemplates.find(id);

	if(iter == m_UnitTemplates.end())
		return NULL;

	CUnit* returnUnit;
	bool found = false;
	for (unsigned int i = 0; i < m_vBasicEnemies.size(); i++)
	{
		if (!m_vBasicEnemies[i]->bIsBeingUsed)
		{
			m_vBasicEnemies[i]->bIsBeingUsed = true;
			returnUnit = m_vBasicEnemies[i]->pUnit;
			*returnUnit = *(iter->second);
			returnUnit->AddRef();
			found = true;
			break;
		}
	}
	if (!found)
	{
		tFactoryUnit* newFactoryUnit = new tFactoryUnit();
		newFactoryUnit->pUnit = new CUnit();
		newFactoryUnit->bIsBeingUsed = true;
		*(newFactoryUnit->pUnit) = *(iter->second);
		returnUnit = newFactoryUnit->pUnit;
		returnUnit->AddRef();
		m_vBasicEnemies.push_back(newFactoryUnit);
	}

	return returnUnit;
}

void CUnitFactory::RegisterItems()
{

}
