#include "precompiled_header.h"
#include "MovementControl.h"
#include "CObjectManager.h"
#include "CCamera.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_Direct3D.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\GameObjects\CUnit.h"

CMovementControl* CMovementControl::GetInstance()
{
	static CMovementControl instance;
	return &instance;
}

void CMovementControl::Init()
{
	m_vObjectList = CObjectManager::GetInstance()->GetObjectList();
	m_vSelected = CObjectManager::GetInstance()->GetSelectedList();
	m_DI = CSGD_DirectInput::GetInstance();
	m_cCAM = CGame::GetInstance()->GetCamera();

	m_bDragging = false;
	m_ptStart.x = CMovementControl::GetInstance()->MousePosX();
	m_ptStart.y = CMovementControl::GetInstance()->MousePosY();
	m_nCursorImageID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource\\Graphics\\gameCursor.png");
	m_pCursorLocation.x = 100;
	m_pCursorLocation.y = 100;
}

void CMovementControl::Input()
{

	// Update Mouse Pos
	m_pCursorLocation.x += CSGD_DirectInput::GetInstance()->MouseMovementX();
	m_pCursorLocation.y += CSGD_DirectInput::GetInstance()->MouseMovementY();

	if(MousePosX() < CGame::GetInstance()->GetCamera()->GetX())
		m_pCursorLocation.x = (LONG)CGame::GetInstance()->GetCamera()->GetX();

	if(MousePosX() >CGame::GetInstance()->GetCamera()->GetCollisionRect().right)
		m_pCursorLocation.x = CGame::GetInstance()->GetCamera()->GetCollisionRect().right;

	if(MousePosY() < CGame::GetInstance()->GetCamera()->GetY())
		m_pCursorLocation.y = (LONG)CGame::GetInstance()->GetCamera()->GetY();

	if(MousePosY() >CGame::GetInstance()->GetCamera()->GetCollisionRect().bottom)
		m_pCursorLocation.y = CGame::GetInstance()->GetCamera()->GetCollisionRect().bottom;
	// TODO: Mouse Input

	if(m_DI->MouseButtonPressed(MOUSE_RIGHT))
	{
		int nTarget;

		for(unsigned int i = 0; i < m_vSelected->size(); i++)
		{
			nTarget = -1;

			RECT mouseRect = {0, 0, 0, 0};
			mouseRect.left = CMovementControl::GetInstance()->MousePosX();
			mouseRect.top = CMovementControl::GetInstance()->MousePosY();
			mouseRect.right = mouseRect.left + 1;
			mouseRect.bottom = mouseRect.top +1;

			RECT resultRect;

			for (unsigned int j = 0; j < m_vObjectList->size(); j++)
			{
				if ((*m_vObjectList)[j]->Type() != CBase::OBJ_ENEMY)
				{
					continue;
				}
				if (IntersectRect(&resultRect, &mouseRect, &((*m_vObjectList)[j]->GetCollisionRect())))
				{
					nTarget = j;
				}
			}
			if (nTarget != -1)
			{
				((CUnit*)(*m_vSelected)[i])->OrderAttack((CUnit*)(*m_vObjectList)[nTarget]);
			}
			else
			{
				((CUnit*)(*m_vSelected)[i])->OrderMove(mouseRect.left, mouseRect.top);
			}
		}
		//m_esEventSystem->SendEvent("LeftMouseButtonPressed");
	}

	if(m_DI->MouseButtonDown(MOUSE_LEFT))
	{
		// Unit Selection ---------------
		if(m_bDragging == false)
		{
			m_bDragging = true;
			m_ptStart.x = CMovementControl::GetInstance()->MousePosX();
			m_ptStart.y = CMovementControl::GetInstance()->MousePosY();
		}
		// END Unit Selection -----------

		//m_esEventSystem->SendEvent("RightMouseButtonPressed");
	} else {
		m_bDragging = false;
	}

	if(m_DI->KeyDown(DIK_LEFT))
	{
		//m_esEventSystem->SendEvent("LeftKeyPressed");
	}

	if(m_DI->KeyDown(DIK_RIGHT))
	{
		//m_esEventSystem->SendEvent("RightKeyPressed");
	}

	if(m_DI->KeyDown(DIK_UP))
	{
		//m_esEventSystem->SendEvent("UpKeyPressed");
	}

	if(m_DI->KeyDown(DIK_DOWN))
	{
		//m_esEventSystem->SendEvent("DownKeyPressed");
	}
}

void CMovementControl::Shutdown()
{
	
}

void CMovementControl::CheckDragRect()
{
	if(m_bDragging)
	{
		RECT dragRect;
		dragRect.left = m_ptStart.x;
		dragRect.top = m_ptStart.y;
		dragRect.right = CMovementControl::GetInstance()->MousePosX();
		dragRect.bottom = CMovementControl::GetInstance()->MousePosY();

		if(dragRect.right < dragRect.left)
			swap(dragRect.left, dragRect.right);

		if(dragRect.bottom < dragRect.top)
			swap(dragRect.top, dragRect.bottom);

		for(unsigned int i = 0; i < m_vObjectList->size(); i++)
		{
			RECT collide;
			RECT collisionRect = (*m_vObjectList)[i]->GetCollisionRect();
			if(IntersectRect(&collide, &dragRect, &collisionRect))
			{
				if(!((CUnit*)(*m_vObjectList)[i])->Selected())	// If not selected
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(true);
					(*m_vSelected).push_back( (*m_vObjectList)[i] );
				}
			} else {
				if( ((CUnit*)(*m_vObjectList)[i])->Selected() )	// If selected
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(false);
					CObjectManager::GetInstance()->FindAndRemove( (CUnit*)(*m_vObjectList)[i] );
				}
			}
		}
	}
}

void CMovementControl::RenderDragRect()
{
	if(m_bDragging)
	{
		RECT dragRect;
		dragRect.left = m_ptStart.x;
		dragRect.top = m_ptStart.y;
		dragRect.right = CMovementControl::GetInstance()->MousePosX();
		dragRect.bottom = CMovementControl::GetInstance()->MousePosY();

		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.left, dragRect.top, dragRect.right, dragRect.top, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.right, dragRect.top, dragRect.right, dragRect.bottom, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.right, dragRect.bottom, dragRect.left, dragRect.bottom, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.left, dragRect.bottom, dragRect.left, dragRect.top, 0, 255, 0);
	}
}

void CMovementControl::RenderCursor()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nCursorImageID, CMovementControl::GetInstance()->MousePosX(), CMovementControl::GetInstance()->MousePosY(), 0.75f, 0.75f);
}