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
		Footman->Width(32);
		Footman->Height(32);
		Footman->MaxHealth(120);
		Footman->CurHealth(Footman->MaxHealth());
		Footman->AttackDamage(10);
		Footman->AttackSpeed(1);
		Footman->AttackRange(50);
		Footman->Armor(15);
		Footman->Burned(false);
		Footman->Cloaked(false);
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
		FireElemental->Width(32);
		FireElemental->Height(32);
		FireElemental->MaxHealth(200);
		FireElemental->CurHealth(FireElemental->MaxHealth());
		FireElemental->AttackDamage(10);
		FireElemental->AttackSpeed(2);
		FireElemental->AttackRange(225);
		FireElemental->Armor(25);
		FireElemental->Burned(false);
		FireElemental->Cloaked(false);
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
		Cyclops->Width(65);
		Cyclops->Height(115);
		Cyclops->MaxHealth(300);
		Cyclops->CurHealth(Cyclops->MaxHealth());
		Cyclops->AttackDamage(40);
		Cyclops->AttackSpeed(3);
		Cyclops->AttackRange(50);
		Cyclops->Armor(35);
		Cyclops->Burned(false);
		Cyclops->Cloaked(false);
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

	// Colossus
	{
		pair<string, CUnit*> objDef;

		CUnit* Colossus = new CBasicEnemy();
		Colossus->Width(70);
		Colossus->Height(140);
		Colossus->MaxHealth(450);
		Colossus->CurHealth(Colossus->MaxHealth());
		Colossus->AttackDamage(60);
		Colossus->AttackSpeed(4);
		Colossus->AttackRange(50);
		Colossus->Armor(35);
		Colossus->Burned(false);
		Colossus->Cloaked(false);
		Colossus->Invulnerable(false);
		Colossus->MovementSpeed(75);
		Colossus->Ranged(false);
		Colossus->Selected(false);
		Colossus->SightRange(300);
		Colossus->Stunned(false);
		Colossus->CurDirection();
		Colossus->State(CUnit::UNIT_IDLE);
		((CBasicEnemy*)Colossus)->SetMirrored(false);

		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Walk-N"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Walk-NE"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Walk-E"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Walk-SE"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Walk-S"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Walk-SW"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Walk-W"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Walk-NW"));

		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Attack-N"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Attack-NE"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Attack-E"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Attack-SE"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Attack-S"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Attack-SW"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Attack-W"));
		Colossus->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Colossus-Attack-NW"));

		objDef.first = "Colossus";
		objDef.second = Colossus;

		m_UnitTemplates.insert(objDef);
	}

	// Shade
	{
		pair<string, CUnit*> objDef;

		CUnit* Shade = new CBasicEnemy();
		Shade->Width(50);
		Shade->Height(100);
		Shade->Scale(0.5f);
		Shade->MaxHealth(200);
		Shade->CurHealth(Shade->MaxHealth());
		Shade->AttackDamage(10);
		Shade->AttackSpeed(0.8f);
		Shade->AttackRange(50);
		Shade->Armor(15);
		Shade->Burned(false);
		Shade->Cloaked(false);
		Shade->Invulnerable(false);
		Shade->MovementSpeed(75);
		Shade->Ranged(false);
		Shade->Selected(false);
		Shade->SightRange(300);
		Shade->Stunned(false);
		Shade->CurDirection();
		Shade->State(CUnit::UNIT_IDLE);
		((CBasicEnemy*)Shade)->SetMirrored(false);

		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Walk-N"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Walk-NE"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Walk-E"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Walk-SE"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Walk-S"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Walk-SW"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Walk-W"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Walk-NW"));

		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Attack-N"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Attack-NE"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Attack-E"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Attack-SE"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Attack-S"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Attack-SW"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Attack-W"));
		Shade->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Shade-Attack-NW"));

		objDef.first = "Shade";
		objDef.second = Shade;

		m_UnitTemplates.insert(objDef);
	}

	// Medusa
	{
		pair<string, CUnit*> objDef;

		CUnit* Medusa = new CBossEnemy();
		Medusa->Width(72);
		Medusa->Height(72);
		Medusa->Scale(0.75f);
		Medusa->MaxHealth(1500);
		Medusa->CurHealth(Medusa->MaxHealth());
		Medusa->AttackDamage(45);
		Medusa->AttackSpeed(3);
		Medusa->Armor(50);
		Medusa->AttackRange(250);
		Medusa->Burned(false);
		Medusa->Cloaked(false);
		Medusa->Invulnerable(false);
		Medusa->MovementSpeed(75);
		Medusa->Ranged(true);
		Medusa->Selected(false);
		Medusa->SightRange(350);
		Medusa->Stunned(false);
		Medusa->CurDirection();
		Medusa->State(CUnit::UNIT_IDLE);
		((CBossEnemy*)Medusa)->SetMirrored(false);

		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Walk-N"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Walk-NE"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Walk-E"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Walk-SE"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Walk-S"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Walk-SW"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Walk-W"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Walk-NW"));

		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Attack-N"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Attack-NE"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Attack-E"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Attack-SE"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Attack-S"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Attack-SW"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Attack-W"));
		Medusa->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medusa-Attack-NW"));

		objDef.first = "Medusa";
		objDef.second = Medusa;

		m_UnitTemplates.insert(objDef);
	}

	// Mage
	{
		pair<string, CUnit*> objDef;

		CUnit* Mage = new CBasicEnemy();
		Mage->Width(30);
		Mage->Height(82);
		Mage->Scale(0.5f);
		Mage->MaxHealth(200);
		Mage->CurHealth(Mage->MaxHealth());
		Mage->AttackDamage(30);
		Mage->AttackSpeed(3);
		Mage->Armor(15);
		Mage->AttackRange(200);
		Mage->Burned(false);
		Mage->Cloaked(false);
		Mage->Invulnerable(false);
		Mage->MovementSpeed(75);
		Mage->Ranged(false);
		Mage->Selected(false);
		Mage->SightRange(300);
		Mage->Stunned(false);
		Mage->CurDirection();
		Mage->State(CUnit::UNIT_IDLE);
		((CBasicEnemy*)Mage)->SetMirrored(false);

		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Walk-N"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Walk-NE"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Walk-E"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Walk-SE"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Walk-S"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Walk-SW"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Walk-W"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Walk-NW"));

		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Attack-N"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Attack-NE"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Attack-E"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Attack-SE"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Attack-S"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Attack-SW"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Attack-W"));
		Mage->Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Mage-Attack-NW"));

		objDef.first = "Mage";
		objDef.second = Mage;

		m_UnitTemplates.insert(objDef);
	}

}
