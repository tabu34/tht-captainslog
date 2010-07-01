#ifndef CItemFactory_h__
#define CItemFactory_h__

class CItemFactory
{
	CItemFactory();
	~CItemFactory();
	CItemFactory(CItemFactory&);
	CItemFactory& operator=(CItemFactory&);
public:
	static CItemFactory* GetInstance();
protected:
private:
};
#endif // CItemFactory_h__