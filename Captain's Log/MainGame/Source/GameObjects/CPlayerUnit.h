#ifndef CPlayerUnit_h__
#define CPlayerUnit_h__

#include <vector>
#include "CUnit.h"
using namespace std;

class CItem;

class CPlayerUnit : public CUnit
{
	vector<CItem*>		m_vInventory;

public:
	// Accessors ///////////////////////////////////
	vector<CItem*>* Inventory() { return &m_vInventory; }
	////////////////////////////////////////////////

	void	Initialize();
};
#endif // CPlayerUnit_h__