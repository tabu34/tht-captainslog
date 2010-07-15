#ifndef CItemFactory_h__
#define CItemFactory_h__

#include <map>
using std::map;
using std::pair;

#define STARTING_ITEMS 25

class CItem;

struct ItemUnit 
{
	CItem*	pItem;
	bool	bIsBeingUsed;
};

class CItemFactory
{
	map<string, CItem*>	m_ItemTemplates;

	vector<ItemUnit*>	m_vActiveItems;
	vector<ItemUnit*>	m_vAppliedItems;
	vector<ItemUnit*>	m_vPassiveItems;

public:
	CItemFactory();
	~CItemFactory();
	CItemFactory(CItemFactory&);
	CItemFactory& operator=(CItemFactory&);

	void	RegisterItems();

public:
	static CItemFactory* GetInstance();
	CItem* CreateItem(string id);

};
#endif // CItemFactory_h__