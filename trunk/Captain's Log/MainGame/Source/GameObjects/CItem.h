#ifndef CItem_h__
#define CItem_h__

#include "CBase.h"

class CUnit;

class CItem : public CBase
{
	int		m_nItemName;
	int		m_nItemType;
	int		m_nAmountType;
	int		m_nAmountCategory;
	float	m_fAmount;
	CUnit*	m_pTarget;

protected:
	void ItemType (int val) { m_nItemType = val; }

public:

	int ItemName() const { return m_nItemName; }
	int ItemType() const { return m_nItemType; }
	int AmountType() const { return m_nAmountType; }
	int AmountCategory() const { return m_nAmountCategory; }
	float Amount() const { return m_fAmount; }
	CUnit* Target() { return m_pTarget; }

	void ItemName(int val) { m_nItemName = val; }
	void AmountType(int val) { m_nAmountType = val; }
	void AmountCategory(int val) { m_nAmountCategory = val; }
	void Amount(float val) { m_fAmount = val; }

	enum {ITEM_NULL, 
	ITEM_BOOKOFHASTE, ITEM_BOOKOFSWIFTNESS, ITEM_BOOKOFPROTECTION,
	ITEM_BOOKOFSTRENGTH, ITEM_BOOKOFVITALITY, ITEM_GLOVESOFHASTE, ITEM_BOOTSOFSWIFTNESS, 
	ITEM_SHIELDOFANGELS, ITEM_SWORDOFTITANS, ITEM_RESURRECTIONSTONE, ITEM_GEMOFLIFE, 
	ITEM_MEDUSASTORCH, ITEM_RODOFLIGHTNING, ITEM_TSUNAMISTONE, ITEM_RINGOFWAR, 
	ITEM_ARCOFLIFE, ITEM_WIZARDSSTAFF, ITEM_STONEOFTHEDEAD,
	ITEM_MAX};

	enum {ITEMTYPE_NULL, ITEMTYPE_PASSIVE, ITEMTYPE_APPLIED, ITEMTYPE_ACTIVE, ITEMTYPE_MAX};

	enum {VALUECATEGORY_NULL, 
		VALUECATEGORY_ATTACKSPEED, VALUECATEGORY_MOVEMENTSPEED, 
		VALUECATEGORY_ARMOR, VALUECATEGORY_ATTACKDAMAGE, VALUECATEGORY_HP, 
		VALUECATEGORY_MAX};

	enum {VALUETYPE_NULL, VALUETYPE_PERCENTAGE, VALUETYPE_INTEGER, VALUETYPE_MAX};

	CItem();
	CItem& operator=(CItem& pItem);

	virtual void	AddEffect();
	virtual void	RemoveEffect();

	void	Collect(CUnit* pTarget);
	void	Drop();

};
#endif // CItem_h__