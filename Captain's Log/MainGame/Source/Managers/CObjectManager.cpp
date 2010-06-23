#include "precompiled_header.h"
#include "CObjectManager.h"
#include <windows.h>
#include "..\GameObjects\CBase.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "..\GameObjects\CUnit.h"

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

void CObjectManager::ToggleUnitSelection(CUnit* pObject)
{
	if (pObject->Selected())
	{
		pObject->Selected(false);
		FindAndRemove(pObject);
	}
	else
	{
		pObject->Selected(true);
		m_vSelected.push_back(pObject);
	}
}

void CObjectManager::FindAndRemove(CUnit* pObject)
{
	for (unsigned int i = 0; i < m_vSelected.size(); i++)
	{
		if(m_vSelected[i] == pObject)
		{
			m_vSelected.erase(m_vSelected.begin() + i);
			return;
		}
	}
}