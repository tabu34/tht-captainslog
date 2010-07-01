#ifndef CItemFactory_h__
#define CItemFactory_h__

#include <map>
using std::map;
using std::pair;

class CItem;

class CItemFactory
{
	
public:
	CItemFactory();
	~CItemFactory();
	CItemFactory(CItemFactory&);
	CItemFactory& operator=(CItemFactory&);
public:
	static CItemFactory* GetInstance();
};
#endif // CItemFactory_h__