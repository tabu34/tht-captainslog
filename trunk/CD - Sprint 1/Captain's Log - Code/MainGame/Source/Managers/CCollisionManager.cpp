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

void CCollisionManager::RunBorderCollision()
{
	for (unsigned int i=0; i < m_vObstacles.size(); i++)
	{
		for(unsigned int j=0; j<m_vObstacles.size(); j++)
		{
			//if(m_vObstacles[i]->Type() !=m_vObstacles[j]->Type())
			//{
				if(CheckCollision(m_vObstacles[i], m_vObstacles[j]))
				{
					break;
				}
			//}
		}
	}

}

void CCollisionManager::RunCollisions()
{
	RunBorderCollision();
}

bool CCollisionManager::CheckCollision( CBase * pBase , CBase * pBaseOther)
{
	RECT tempRect;
	RECT pBaseCollision = pBase->GetCollisionRect();
	RECT pBaseOtherCollision = pBaseOther->GetCollisionRect();
	if(IntersectRect(&tempRect, &pBaseCollision, &pBaseOtherCollision))
	{
		if (tempRect.right - tempRect.left < tempRect.bottom - tempRect.top)
		{
			if (tempRect.left == pBaseCollision.left)
				pBase->PosX(pBaseOther->PosX() + pBaseOther->Width());
			else if (tempRect.right == pBaseCollision.right)
				pBase->PosX(pBaseOther->PosX() - pBase->Width());
		}
		else if (tempRect.bottom - tempRect.top < tempRect.right - tempRect.left)
		{
			if (tempRect.top == pBaseCollision.top)
				pBase->PosY(pBaseOther->PosY() + pBaseOther->Height());
			else if (tempRect.bottom == pBaseCollision.bottom)
				pBase->PosY(pBaseOther->PosY() - pBase->Height());
		}
		return true;
	}
	else
		return false;



}

void CCollisionManager::AddObject( CBase* pBase )
{
	m_vObstacles.push_back(pBase);
}

CCollisionManager* CCollisionManager::GetInstance()
{
	static CCollisionManager instance;
	return &instance;
}
