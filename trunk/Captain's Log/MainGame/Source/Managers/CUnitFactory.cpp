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
		tempFactoryUnit->pUnit = new CBasicEnemy();
		m_vBasicEnemies.push_back(tempFactoryUnit);

		tempFactoryUnit = new tFactoryUnit();
		tempFactoryUnit->bIsBeingUsed = false;
		tempFactoryUnit->pUnit = new CBossEnemy();
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

	for (unsigned int i = 0; i < m_vBossEnemies.size(); i++)
	{
		SAFE_RELEASE(m_vBossEnemies[i]->pUnit);
		SAFE_DELETE(m_vBossEnemies[i]);
	}
	m_vBossEnemies.clear();

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

	switch (iter->second->SubType())
	{
	case CUnit::ENEMY_BASIC:
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
			newFactoryUnit->pUnit = new CBasicEnemy();
			newFactoryUnit->bIsBeingUsed = true;
			*(newFactoryUnit->pUnit) = *(iter->second);
			returnUnit = newFactoryUnit->pUnit;
			returnUnit->AddRef();
			m_vBasicEnemies.push_back(newFactoryUnit);
		}
		break;

	case CUnit::ENEMY_BOSS:
		for (unsigned int i = 0; i < m_vBossEnemies.size(); i++)
		{
			if (!m_vBossEnemies[i]->bIsBeingUsed)
			{
				m_vBossEnemies[i]->bIsBeingUsed = true;
				returnUnit = m_vBossEnemies[i]->pUnit;
				*returnUnit = *(iter->second);
				returnUnit->AddRef();
				found = true;
				break;
			}
		}
		if (!found)
		{
			tFactoryUnit* newFactoryUnit = new tFactoryUnit();
			newFactoryUnit->pUnit = new CBossEnemy();
			newFactoryUnit->bIsBeingUsed = true;
			*(newFactoryUnit->pUnit) = *(iter->second);
			returnUnit = newFactoryUnit->pUnit;
			returnUnit->AddRef();
			m_vBossEnemies.push_back(newFactoryUnit);
		}
		break;
	}

	return returnUnit;
}

void CUnitFactory::RegisterItems()
{

}
