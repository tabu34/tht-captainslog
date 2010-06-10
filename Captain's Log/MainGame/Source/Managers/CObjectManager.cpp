#include "CObjectManager.h"

CObjectManager::~CObjectManager()
{

}

CObjectManager::CObjectManager()
{

}

CObjectManager* CObjectManager::GetInstance()
{
	static CObjectManager instance;
	return &instance;
}

void CObjectManager::AddObject( CBase* pObject )
{

}

void CObjectManager::RemoveAllObjects()
{

}

void CObjectManager::RemoveObject( CBase* pObject )
{

}

void CObjectManager::RenderObjects()
{

}

void CObjectManager::UpdateObjects( float fElapsedTime )
{

}
