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
	if (pObject == NULL)
		return;
	m_vObjectList.push_back(pObject);
	CCollisionManager::GetInstance()->AddObject(pObject);
	pObject->AddRef();
}

void CObjectManager::RemoveAllObjects()
{
	for (unsigned int i = 0; i < m_vObjectList.size(); i++)
	{
		m_vObjectList[i]->Release();
	}

	while (m_vSelected.size())
	{
		m_vSelected.erase(m_vSelected.begin());
	}

	m_vObjectList.clear();
}

void CObjectManager::RemoveObject( CBase* pObject )
{
	if (pObject == NULL)
		return;

	for (vector<CBase*>::iterator iter = m_vObjectList.begin();
		iter != m_vObjectList.end();
		iter++)
	{
		if ((*iter) == pObject)
		{
			(*iter)->Release();

			iter = m_vObjectList.erase(iter);
			break;
		}
	}
}

void CObjectManager::RenderObjects()
{
	RECT rScreen;
	rScreen.left = (LONG)CGame::GetInstance()->GetCamera()->GetX();
	rScreen.top = (LONG)CGame::GetInstance()->GetCamera()->GetY();
	rScreen.right = rScreen.left + CGame::GetInstance()->GetScreenWidth();
	rScreen.bottom = rScreen.top + CGame::GetInstance()->GetScreenHeight();
	for (unsigned int i=0; i < m_vObjectList.size(); i++)
	{
		RECT rCollisionRect;
		if (IntersectRect(&rCollisionRect, &rScreen, &m_vObjectList[i]->GetCollisionRect()))
			m_vObjectList[i]->Render();
	}
}

void CObjectManager::UpdateObjects( float fElapsedTime )
{
	vector<CBase*>::iterator iter = m_vObjectList.begin();

	while(iter != m_vObjectList.end())
	{
		(*iter)->Update(fElapsedTime);
		iter++;
	}
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