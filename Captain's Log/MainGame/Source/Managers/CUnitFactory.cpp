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

	RegisterItems();
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

CUnit* CUnitFactory::CreateUnit(string id)
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
//	// Book of Haste
//	{
//		pair<string, CItem*> objDef;
//
//		CItem* BookOfHaste = new CAppliedItem();
//		BookOfHaste->ItemName(CItem::ITEM_BOOKOFHASTE);
//		BookOfHaste->AmountType(CItem::VALUETYPE_PERCENTAGE);
//		BookOfHaste->AmountCategory(CItem::VALUECATEGORY_ATTACKSPEED);
//		BookOfHaste->Amount(3);
//
//		objDef.first = "Book of Haste";
//		objDef.second = BookOfHaste;
//
//		m_ItemTemplates.insert(objDef);
//	}

	// Footman
	{
		pair<string, CUnit*> objDef;

		CUnit* Footman = new CBasicEnemy();
		Footman->Armor(15);
		Footman->AttackDamage(4);
		Footman->AttackRange(50);
		Footman->AttackSpeed(1);
		Footman->Burned(false);
		Footman->Cloaked(false);
		Footman->MaxHealth(120);
		Footman->CurHealth(Footman->MaxHealth());
		Footman->Invulnerable(false);
		Footman->MovementSpeed(80);
		Footman->Ranged(false);
		Footman->Selected(false);
		Footman->SightRange(150);
		Footman->Stunned(false);
		Footman->CurDirection();
		Footman->State(CUnit::UNIT_IDLE);

		Footman->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Marine-Walk-N"));
		Footman->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Marine-Walk-NE"));
		Footman->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Marine-Walk-E"));
		Footman->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Marine-Walk-SE"));
		Footman->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Marine-Walk-S"));
		Footman->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Marine-Idle"));
		Footman->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Marine-Fire"));

		objDef.first = "Footman";
		objDef.second = Footman;

		m_UnitTemplates.insert(objDef);

	}

	// Fire Elemental
	{
		pair<string, CUnit*> objDef;

		CUnit* FireElemental = new CBasicEnemy();
		FireElemental->Armor(25);
		FireElemental->AttackDamage(10);
		FireElemental->AttackRange(200);
		FireElemental->AttackSpeed(2);
		FireElemental->Burned(false);
		FireElemental->Cloaked(false);
		FireElemental->MaxHealth(200);
		FireElemental->CurHealth(FireElemental->MaxHealth());
		FireElemental->Invulnerable(false);
		FireElemental->MovementSpeed(80);
		FireElemental->Ranged(false);
		FireElemental->Selected(false);
		FireElemental->SightRange(300);
		FireElemental->Stunned(false);
		FireElemental->CurDirection();
		FireElemental->State(CUnit::UNIT_IDLE);

		FireElemental->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-N"));
		FireElemental->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-NE"));
		FireElemental->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-E"));
		FireElemental->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-SE"));
		FireElemental->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-S"));
		FireElemental->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Idle"));
		FireElemental->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Fire"));

		objDef.first = "Fire Elemental";
		objDef.second = FireElemental;

		m_UnitTemplates.insert(objDef);
	}

	// Cyclops
	{
		pair<string, CUnit*> objDef;

		CUnit* Cyclops = new CBasicEnemy();
		Cyclops->Armor(35);
		Cyclops->AttackDamage(15);
		Cyclops->AttackRange(50);
		Cyclops->AttackSpeed(2);
		Cyclops->Burned(false);
		Cyclops->Cloaked(false);
		Cyclops->MaxHealth(200);
		Cyclops->CurHealth(Cyclops->MaxHealth());
		Cyclops->Invulnerable(false);
		Cyclops->MovementSpeed(75);
		Cyclops->Ranged(false);
		Cyclops->Selected(false);
		Cyclops->SightRange(300);
		Cyclops->Stunned(false);
		Cyclops->CurDirection();
		Cyclops->State(CUnit::UNIT_IDLE);
		((CBasicEnemy*)Cyclops)->SetMirrored(false);

		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Walk-N"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Walk-NE"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Walk-E"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Walk-SE"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Walk-S"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Walk-SW"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Walk-W"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Walk-NW"));

		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Attack-N"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Attack-NE"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Attack-E"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Attack-SE"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Attack-S"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Attack-SW"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Attack-W"));
		Cyclops->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Cyclops-Attack-NW"));

		objDef.first = "Cyclops";
		objDef.second = Cyclops;

		m_UnitTemplates.insert(objDef);
	}

}
