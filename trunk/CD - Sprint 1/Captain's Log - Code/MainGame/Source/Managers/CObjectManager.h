#ifndef CObjectManager_h__
#define CObjectManager_h__

#include <vector>
using namespace std;

class CBase;

class CObjectManager
{
	vector<CBase*>	m_vObjectList;

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
};
#endif // CObjectManager_h__