#include "precompiled_header.h"
#include "CActive.h"

CActive::CActive()
{
	ItemType(ITEMTYPE_ACTIVE);
}

void CActive::AddEffect()
{
	CItem::AddEffect();
}

void CActive::RemoveEffect()
{

}
