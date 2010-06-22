#include "CObjectManager.h"
#include <windows.h>
#include "..\GameObjects\CBase.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"

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

bool CObjectManager::IsUnitOnscreen(CBase* pObject)
{
	RECT collision;
	BOOL result;
	result = IntersectRect(&collision, &(pObject->GetCollisionRect()), &(CGame::GetInstance()->GetCamera()->GetCollisionRect()));
	if(result)
		return true;
	else
		return false;
}
