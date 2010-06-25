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
	void	RunBorderCollision();

public:
	static CCollisionManager* GetInstance();

	void	RunCollisions();
	void	AddObject(CBase* pBase);
	bool	CheckCollision( CBase * pBase , CBase * pBaseOther);

};
#endif // CCollisionManager_h__