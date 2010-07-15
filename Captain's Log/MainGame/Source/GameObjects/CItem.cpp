#include "precompiled_header.h"
#include "CItem.h"

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

}

void CItem::AddEffect()
{

}

void CItem::RemoveEffect()
{

}

void CItem::Drop()
{

}
