#ifndef CObjectManager_h__
#define CObjectManager_h__

#include <vector>
using namespace std;

class CBase;
class CUnit;

class CObjectManager
{
	vector<CBase*>	m_vObjectList;
	vector<CBase*>	m_vSelected;
	
	~CObjectManager();
	CObjectManager();
	CObjectManager(CObjectManager&);
	CObjectManager& operator=(CObjectManager&);

public:
	static CObjectManager* GetInstance();

	void	AddObject(CBase* pObject);
	void	RemoveAllObjects();
	void	RemoveObject(CBase* pObject);
	void	RenderObjects();
	void	UpdateObjects(float fElapsedTime);
	bool	IsUnitOnscreen(CBase * pObject);
	void	FindAndRemove(CUnit* pObject);
	void	ToggleUnitSelection(CUnit* pObject);

	vector<CBase*>*	GetObjectList()
	{
		return &m_vObjectList;
	}

	vector<CBase*>*	GetSelectedList()
	{
		return &m_vSelected;
	}
};
#endif // CObjectManager_h__