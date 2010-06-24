#include "precompiled_header.h"
#include "CCollisionManager.h"
#include "..\GameObjects\CBase.h"

CCollisionManager::~CCollisionManager()
{

}

CCollisionManager::CCollisionManager()
{

}

void CCollisionManager::RunProjectileCollision()
{

}

bool CCollisionManager::RunBorderCollision( CBase * pBaseOther , CBase * pBase )
{
	RECT tempRect;
	RECT pBaseCollision = pBase->GetCollisionRect();
	RECT pBaseOtherCollision = pBaseOther->GetCollisionRect();
	if(IntersectRect(&tempRect, &pBaseCollision, &pBaseOtherCollision))
	{
		if (tempRect.right - tempRect.left < tempRect.bottom - tempRect.top)
		{
			if (tempRect.left == pBaseCollision.left)
				pBase->PosX(float(pBaseOtherCollision.right + (pBase->Width() >> 1)));
			else if (tempRect.right == pBaseCollision.right)
				pBase->PosX(float(pBaseOtherCollision.left - (pBase->Width() >> 1)));
		}
		else if (tempRect.bottom - tempRect.top < tempRect.right - tempRect.left)
		{
			if (tempRect.top == pBaseCollision.top)
				pBase->PosY(float(pBaseOtherCollision.bottom + (pBase->Height() >> 1)));
			else if (tempRect.bottom == pBaseCollision.bottom)
				pBase->PosY(float(pBaseOtherCollision.top - (pBase->Height() >> 1)));
		}
		return true;
	}
	else
		return false;


}

void CCollisionManager::RunCollisions()
{
	CheckCollision();
}

void CCollisionManager::CheckCollision()
{	
	for (unsigned int i=0; i < m_vObstacles.size(); i++)
	{
		for(unsigned int j=0; j<m_vPlayers.size(); j++)
		{
			RunBorderCollision(m_vObstacles[i], m_vPlayers[j]);
		}
		for(unsigned int j=0; j<m_vEnemies.size(); j++)
		{
			RunBorderCollision(m_vObstacles[i], m_vEnemies[j]);
		}
	}



}

void CCollisionManager::AddObject( CBase* pBase )
{
	if (pBase->Type() == CBase::OBJ_OBSTACLE)
		m_vObstacles.push_back(pBase);
	else if (pBase->Type() == CBase::OBJ_PLAYER)
		m_vPlayers.push_back(pBase);
	else if (pBase->Type() == CBase::OBJ_ENEMY)
		m_vEnemies.push_back(pBase);
	else if (pBase->Type() == CBase::OBJ_PROJECTILE)
		m_vProjectiles.push_back(pBase);
}

CCollisionManager* CCollisionManager::GetInstance()
{
	static CCollisionManager instance;
	return &instance;
}
