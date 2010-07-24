#ifndef CCollisionManager_h__
#define CCollisionManager_h__

#include <vector>
using namespace std;

class CBase;

class CCollisionManager
{
	vector<CBase*>		m_vProjectiles;
	vector<CBase*>		m_vPlayers;
	vector<CBase*>		m_vEnemies;
	vector<CBase*>		m_vObstacles;

	~CCollisionManager();
	CCollisionManager();
	CCollisionManager(CCollisionManager&);
	CCollisionManager& operator=(CCollisionManager&);

	void	RunProjectileCollision();
	bool RunBorderCollision( CBase * pBase , CBase * pBaseOther);

public:
	static CCollisionManager* GetInstance();

	vector<CBase*>* Enemies() { return &m_vEnemies; }
	vector<CBase*>* Players() { return &m_vPlayers; }

	void	RunCollisions();
	void	AddObject(CBase* pBase);
	void	CheckCollision();
	void	RemoveObject( CBase* pObject );
	void	RemoveAllObjects();
};
#endif // CCollisionManager_h__