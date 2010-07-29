#include "precompiled_header.h"
#include "CItemFactory.h"
#include "CAppliedItem.h"
#include "CPassive.h"
#include "CActive.h"

CItemFactory::CItemFactory()
{
	for (int i = 0; i < STARTING_ITEMS; i++)
	{
		ItemUnit* tempItemUnit = new ItemUnit();
		tempItemUnit->bIsBeingUsed = false;
		tempItemUnit->pItem = new CActive();
		m_vActiveItems.push_back(tempItemUnit);

		tempItemUnit = new ItemUnit();
		tempItemUnit->bIsBeingUsed = false;
		tempItemUnit->pItem = new CAppliedItem();
		m_vAppliedItems.push_back(tempItemUnit);

		tempItemUnit = new ItemUnit();
		tempItemUnit->bIsBeingUsed = false;
		tempItemUnit->pItem = new CPassive();
		m_vPassiveItems.push_back(tempItemUnit);
	}

	RegisterItems();
}

CItemFactory::~CItemFactory()
{
	for (unsigned int i = 0; i < m_vActiveItems.size(); i++)
	{
		SAFE_RELEASE(m_vActiveItems[i]->pItem);
		SAFE_DELETE(m_vActiveItems[i]);
	}
	m_vActiveItems.clear();

	for (unsigned int i = 0; i < m_vAppliedItems.size(); i++)
	{
		SAFE_RELEASE(m_vAppliedItems[i]->pItem);
		SAFE_DELETE(m_vAppliedItems[i]);
	}
	m_vAppliedItems.clear();

	for (unsigned int i = 0; i < m_vPassiveItems.size(); i++)
	{
		SAFE_RELEASE(m_vPassiveItems[i]->pItem);
		SAFE_DELETE(m_vPassiveItems[i]);
	}
	m_vPassiveItems.clear();

	while (!m_ItemTemplates.empty())
	{
		map<string, CItem*>::iterator iter = m_ItemTemplates.begin();
		SAFE_RELEASE(iter->second);
		m_ItemTemplates.erase(iter);
	}
}

CItemFactory* CItemFactory::GetInstance()
{
	static CItemFactory instance;
	return &instance;
}

CItem* CItemFactory::CreateItem(string id)
{
	map<string, CItem*>::iterator iter = m_ItemTemplates.find(id);

	if(iter == m_ItemTemplates.end())
		return NULL;

	CItem* returnItem;
	bool found = false;


	switch (iter->second->ItemType())
	{
	case CItem::ITEMTYPE_ACTIVE:
		for (unsigned int i = 0; i < m_vActiveItems.size(); i++)
		{
			if (!m_vActiveItems[i]->bIsBeingUsed)
			{
				m_vActiveItems[i]->bIsBeingUsed = true;
				returnItem = m_vActiveItems[i]->pItem;
				*returnItem = *(iter->second);
				returnItem->AddRef();
				found = true;
				break;
			}
		}
		if (!found)
		{
			ItemUnit* newItemUnit = new ItemUnit();
			newItemUnit->pItem = new CActive();
			newItemUnit->bIsBeingUsed = true;
			*(newItemUnit->pItem) = *(iter->second);
			returnItem = newItemUnit->pItem;
			returnItem->AddRef();
			m_vActiveItems.push_back(newItemUnit);
		}
		break;

	case CItem::ITEMTYPE_APPLIED:
		for (unsigned int i = 0; i < m_vAppliedItems.size(); i++)
		{
			if (!m_vAppliedItems[i]->bIsBeingUsed)
			{
				m_vAppliedItems[i]->bIsBeingUsed = true;
				returnItem = m_vAppliedItems[i]->pItem;
				*returnItem = *(iter->second);
				returnItem->AddRef();
				found = true;
				break;
			}
		}
		if (!found)
		{
			ItemUnit* newItemUnit = new ItemUnit();
			newItemUnit->pItem = new CAppliedItem();
			newItemUnit->bIsBeingUsed = true;
			*(newItemUnit->pItem) = *(iter->second);
			returnItem = newItemUnit->pItem;
			returnItem->AddRef();
			m_vAppliedItems.push_back(newItemUnit);
		}
		break;

	case CItem::ITEMTYPE_PASSIVE:
		for (unsigned int i = 0; i < m_vPassiveItems.size(); i++)
		{
			if (!m_vPassiveItems[i]->bIsBeingUsed)
			{
				m_vPassiveItems[i]->bIsBeingUsed = true;
				returnItem = m_vPassiveItems[i]->pItem;
				*returnItem = *(iter->second);
				returnItem->AddRef();
				found = true;
				break;
			}
		}
		if (!found)
		{
			ItemUnit* newItemUnit = new ItemUnit();
			newItemUnit->pItem = new CPassive();
			newItemUnit->bIsBeingUsed = true;
			*(newItemUnit->pItem) = *(iter->second);
			returnItem = newItemUnit->pItem;
			returnItem->AddRef();
			m_vPassiveItems.push_back(newItemUnit);
		}
		break;
	}

	returnItem->Height(67);
	returnItem->Width(70);

	return returnItem;
}

void CItemFactory::RegisterItems()
{
	// Applied Items

	// Book of Haste
	{
		pair<string, CItem*> objDef;

		CItem* BookOfHaste = new CAppliedItem();
		BookOfHaste->ItemName(CItem::ITEM_BOOKOFHASTE);
		BookOfHaste->AmountType(CItem::VALUETYPE_PERCENTAGE);
		BookOfHaste->AmountCategory(CItem::VALUECATEGORY_ATTACKSPEED);
		BookOfHaste->ItemType(CItem::ITEMTYPE_APPLIED);
		BookOfHaste->Amount(3);
		BookOfHaste->Type(CBase::OBJ_ITEM);

		objDef.first = "Book of Haste";
		objDef.second = BookOfHaste;

		m_ItemTemplates.insert(objDef);
	}

	// Book of Swiftness
	{
		pair<string, CItem*> objDef;

		CItem* BookOfSwiftness = new CAppliedItem();
		BookOfSwiftness->ItemName(CItem::ITEM_BOOKOFSWIFTNESS);
		BookOfSwiftness->AmountType(CItem::VALUETYPE_PERCENTAGE);
		BookOfSwiftness->AmountCategory(CItem::VALUECATEGORY_MOVEMENTSPEED);
		BookOfSwiftness->ItemType(CItem::ITEMTYPE_APPLIED);
		BookOfSwiftness->Amount(3);
		BookOfSwiftness->Type(CBase::OBJ_ITEM);

		objDef.first = "Book of Swiftness";
		objDef.second = BookOfSwiftness;

		m_ItemTemplates.insert(objDef);
	}

	// Book of Protection
	{
		pair<string, CItem*> objDef;

		CItem* BookOfProtection = new CAppliedItem();
		BookOfProtection->ItemName(CItem::ITEM_BOOKOFPROTECTION);
		BookOfProtection->AmountType(CItem::VALUETYPE_PERCENTAGE);
		BookOfProtection->AmountCategory(CItem::VALUECATEGORY_ARMOR);
		BookOfProtection->ItemType(CItem::ITEMTYPE_APPLIED);
		BookOfProtection->Amount(3);
		BookOfProtection->Type(CBase::OBJ_ITEM);

		objDef.first = "Book of Protection";
		objDef.second = BookOfProtection;

		m_ItemTemplates.insert(objDef);
	}

	// Book of Strength
	{
		pair<string, CItem*> objDef;

		CItem* BookOfStrength = new CAppliedItem();
		BookOfStrength->ItemName(CItem::ITEM_BOOKOFSTRENGTH);
		BookOfStrength->AmountType(CItem::VALUETYPE_PERCENTAGE);
		BookOfStrength->AmountCategory(CItem::VALUECATEGORY_ATTACKDAMAGE);
		BookOfStrength->ItemType(CItem::ITEMTYPE_APPLIED);
		BookOfStrength->Amount(3);
		BookOfStrength->Type(CBase::OBJ_ITEM);

		objDef.first = "Book of Strength";
		objDef.second = BookOfStrength;

		m_ItemTemplates.insert(objDef);
	}

	// Book of Vitality
	{
		pair<string, CItem*> objDef;

		CItem* BookOfVitality = new CAppliedItem();
		BookOfVitality->ItemName(CItem::ITEM_BOOKOFVITALITY);
		BookOfVitality->AmountType(CItem::VALUETYPE_INTEGER);
		BookOfVitality->AmountCategory(CItem::VALUECATEGORY_HP);
		BookOfVitality->ItemType(CItem::ITEMTYPE_APPLIED);
		BookOfVitality->Amount(3);
		BookOfVitality->Type(CBase::OBJ_ITEM);

		objDef.first = "Book of Vitality";
		objDef.second = BookOfVitality;

		m_ItemTemplates.insert(objDef);
	}

	// Passive (Held)

	// Gloves of Haste
	{
		pair<string, CItem*> objDef;

		CItem* GlovesOfHaste = new CPassive();
		GlovesOfHaste->ItemName(CItem::ITEM_GLOVESOFHASTE);
		GlovesOfHaste->AmountType(CItem::VALUETYPE_PERCENTAGE);
		GlovesOfHaste->AmountCategory(CItem::VALUECATEGORY_ATTACKSPEED);
		GlovesOfHaste->ItemType(CItem::ITEMTYPE_PASSIVE);
		GlovesOfHaste->Amount(10);
		GlovesOfHaste->Type(CBase::OBJ_ITEM);

		objDef.first = "Gloves of Haste";
		objDef.second = GlovesOfHaste;

		m_ItemTemplates.insert(objDef);
	}

	// Boots of Swiftness
	{
		pair<string, CItem*> objDef;

		CItem* BootsOfSwiftness = new CPassive();
		BootsOfSwiftness->ItemName(CItem::ITEM_BOOTSOFSWIFTNESS);
		BootsOfSwiftness->AmountType(CItem::VALUETYPE_PERCENTAGE);
		BootsOfSwiftness->AmountCategory(CItem::VALUECATEGORY_MOVEMENTSPEED);
		BootsOfSwiftness->ItemType(CItem::ITEMTYPE_PASSIVE);
		BootsOfSwiftness->Amount(10);
		BootsOfSwiftness->Type(CBase::OBJ_ITEM);

		objDef.first = "Boots of Swiftness";
		objDef.second = BootsOfSwiftness;

		m_ItemTemplates.insert(objDef);
	}

	// Shield of Angels
	{
		pair<string, CItem*> objDef;

		CItem* ShieldOfAngels = new CPassive();
		ShieldOfAngels->ItemName(CItem::ITEM_SHIELDOFANGELS);
		ShieldOfAngels->AmountType(CItem::VALUETYPE_PERCENTAGE);
		ShieldOfAngels->AmountCategory(CItem::VALUECATEGORY_ARMOR);
		ShieldOfAngels->ItemType(CItem::ITEMTYPE_PASSIVE);
		ShieldOfAngels->Amount(10);
		ShieldOfAngels->Type(CBase::OBJ_ITEM);

		objDef.first = "Shield of Angels";
		objDef.second = ShieldOfAngels;

		m_ItemTemplates.insert(objDef);
	}

	// Sword of Titans
	{
		pair<string, CItem*> objDef;

		CItem* SwordOfTitans = new CPassive();
		SwordOfTitans->ItemName(CItem::ITEM_SWORDOFTITANS);
		SwordOfTitans->AmountType(CItem::VALUETYPE_PERCENTAGE);
		SwordOfTitans->AmountCategory(CItem::VALUECATEGORY_ATTACKDAMAGE);
		SwordOfTitans->ItemType(CItem::ITEMTYPE_PASSIVE);
		SwordOfTitans->Amount(10);
		SwordOfTitans->Type(CBase::OBJ_ITEM);

		objDef.first = "Sword of Titans";
		objDef.second = SwordOfTitans;

		m_ItemTemplates.insert(objDef);
	}

	// Resurrection Stone
	{
		pair<string, CItem*> objDef;

		CItem* ResurrectionStone = new CPassive();
		ResurrectionStone->ItemName(CItem::ITEM_RESURRECTIONSTONE);
		ResurrectionStone->AmountType(CItem::VALUETYPE_PERCENTAGE);
		ResurrectionStone->AmountCategory(CItem::VALUECATEGORY_HP);
		ResurrectionStone->ItemType(CItem::ITEMTYPE_PASSIVE);
		ResurrectionStone->Amount(30);
		ResurrectionStone->Type(CBase::OBJ_ITEM);

		objDef.first = "Resurrection Stone";
		objDef.second = ResurrectionStone;

		m_ItemTemplates.insert(objDef);
	}

	// Gem of Life
	{
		pair<string, CItem*> objDef;

		CItem* GemOfLife = new CPassive();
		GemOfLife->ItemName(CItem::ITEM_GEMOFLIFE);
		GemOfLife->AmountType(CItem::VALUETYPE_INTEGER);
		GemOfLife->AmountCategory(CItem::VALUECATEGORY_HP);
		GemOfLife->ItemType(CItem::ITEMTYPE_PASSIVE);
		GemOfLife->Amount(1);
		GemOfLife->Type(CBase::OBJ_ITEM);

		objDef.first = "Gem of Life";
		objDef.second = GemOfLife;

		m_ItemTemplates.insert(objDef);
	}

	// Active (Held)

	// Medusa's Torch

	// Rod of Lightning

	// Tsunami Stone

	// Ring of War

	// Arc of Life

	// Wizard's Staff

	// Stone of the Dead
}
