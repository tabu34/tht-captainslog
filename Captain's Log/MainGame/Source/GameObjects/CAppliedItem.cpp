#include "precompiled_header.h"
#include "CAppliedItem.h"

CAppliedItem::CAppliedItem()
{
	ItemType(ITEMTYPE_APPLIED);
}

void CAppliedItem::AddEffect()
{
	CItem::AddEffect();
}

void CAppliedItem::RemoveEffect()
{

}
