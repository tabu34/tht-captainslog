#include "precompiled_header.h"
#include "CItem.h"
#include "CUnit.h"

CItem::CItem()
{
	m_nItemName = 0;
	m_nItemType = 0;
	m_nAmountType = 0;
	m_nAmountCategory = 0;
	m_fAmount = 0;
	m_pTarget = NULL;
}

CItem& CItem::operator=( CItem& pItem )
{
	m_nItemName = pItem.m_nItemName;
	m_nItemType = pItem.m_nItemType;
	m_nAmountType = pItem.m_nAmountType;
	m_nAmountCategory = pItem.m_nAmountCategory;
	m_fAmount = pItem.m_fAmount;

	return *this;
}

void CItem::Collect(CUnit* pTarget)
{
	m_pTarget = pTarget;
}

void CItem::AddEffect()
{

	switch (ItemType())
	{
	case ITEMTYPE_APPLIED:
	case ITEMTYPE_PASSIVE:
		switch (AmountCategory())
		{
		case VALUECATEGORY_ATTACKSPEED:
			switch (AmountType())
			{
			case VALUETYPE_INTEGER:
				break;
			case VALUETYPE_PERCENTAGE:
				Target()->AttackSpeed(Target()->AttackSpeed() * (Amount() * 0.01f + 1.0f));
				break;
			}
			break;
		case VALUECATEGORY_MOVEMENTSPEED:
			break;
		case VALUECATEGORY_ARMOR:
			break;
		case VALUECATEGORY_ATTACKDAMAGE:
			break;
		case VALUECATEGORY_HP:
			break;
		}
		break;
	case ITEMTYPE_ACTIVE:
		break;
	}
}

void CItem::RemoveEffect()
{

}

void CItem::Drop()
{
	m_pTarget = NULL;
	RemoveEffect();
}
