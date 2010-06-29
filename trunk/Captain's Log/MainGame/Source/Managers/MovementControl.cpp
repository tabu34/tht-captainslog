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
	CSGD_DirectInput::GetInstance()->MouseSetPosX(100);
	CSGD_DirectInput::GetInstance()->MouseSetPosY(100);
	m_pCursorLocation.x = CSGD_DirectInput::GetInstance()->MouseGetPosX();
	m_pCursorLocation.y = CSGD_DirectInput::GetInstance()->MouseGetPosY();
}

void CMovementControl::Input()
{

	// Update Mouse Pos


	//if(MousePosX() < m_cCAM->GetX())
	//	CSGD_DirectInput::GetInstance()->MouseSetPosX((LONG)m_cCAM->GetX());

	//if(MousePosX() > m_cCAM->GetX() + CGame::GetInstance()->GetScreenWidth())
	//	CSGD_DirectInput::GetInstance()->MouseSetPosX( (LONG)m_cCAM->GetX() + CGame::GetInstance()->GetScreenWidth());

	//if(MousePosY() < m_cCAM->GetY())
	//	CSGD_DirectInput::GetInstance()->MouseSetPosY( (LONG)m_cCAM->GetY());

	//if(MousePosY() > m_cCAM->GetY() + CGame::GetInstance()->GetScreenHeight())
	//	CSGD_DirectInput::GetInstance()->MouseSetPosY( (LONG)m_cCAM->GetY() + CGame::GetInstance()->GetScreenHeight());

	m_pCursorLocation.x = CSGD_DirectInput::GetInstance()->MouseGetPosX();
	m_pCursorLocation.y = CSGD_DirectInput::GetInstance()->MouseGetPosY();
	// TODO: Mouse Input

	if(m_DI->MouseButtonPressed(MOUSE_RIGHT))
	{
		int nTarget;

		for(unsigned int i = 0; i < m_vSelected->size(); i++)
		{
			nTarget = -1;

			RECT mouseRect = {0, 0, 0, 0};
			mouseRect.left = LONG((float)CMovementControl::GetInstance()->MousePosX() + CGame::GetInstance()->GetCamera()->GetX());
			mouseRect.top = LONG((float)CMovementControl::GetInstance()->MousePosY() + CGame::GetInstance()->GetCamera()->GetY());
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
		CGame::GetInstance()->GetCamera()->SetX( CGame::GetInstance()->GetCamera()->GetX() - 1.5f );
		if(CGame::GetInstance()->GetCamera()->GetX() < 0.0f)
			CGame::GetInstance()->GetCamera()->SetX( 0.0f );
		//m_esEventSystem->SendEvent("LeftKeyPressed");
	}

	if(m_DI->KeyDown(DIK_RIGHT))
	{
		CGame::GetInstance()->GetCamera()->SetX( CGame::GetInstance()->GetCamera()->GetX() + 1.5f );
		if(CGame::GetInstance()->GetCamera()->GetX() > 1000.0f)
			CGame::GetInstance()->GetCamera()->SetX( 1000.0f );
		//m_esEventSystem->SendEvent("RightKeyPressed");
	}

	if(m_DI->KeyDown(DIK_UP))
	{
		CGame::GetInstance()->GetCamera()->SetY( CGame::GetInstance()->GetCamera()->GetY() - 1.5f );
		if(CGame::GetInstance()->GetCamera()->GetY() < 0.0f)
			CGame::GetInstance()->GetCamera()->SetY( 0.0f );
		//m_esEventSystem->SendEvent("UpKeyPressed");
	}

	if(m_DI->KeyDown(DIK_DOWN))
	{
		CGame::GetInstance()->GetCamera()->SetY( CGame::GetInstance()->GetCamera()->GetY() + 1.5f );
		if(CGame::GetInstance()->GetCamera()->GetY() > 1000.0f)
			CGame::GetInstance()->GetCamera()->SetY( 1000.0f );
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
		dragRect.left = m_ptStart.x + (LONG)CGame::GetInstance()->GetCamera()->GetX();
		dragRect.top = m_ptStart.y + (LONG)CGame::GetInstance()->GetCamera()->GetY();
		dragRect.right = LONG((float)CMovementControl::GetInstance()->MousePosX() + CGame::GetInstance()->GetCamera()->GetX());
		dragRect.bottom = LONG((float)CMovementControl::GetInstance()->MousePosY() + CGame::GetInstance()->GetCamera()->GetY());

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

void CMovementControl::UpdateCamera( float fElapsedTime )
{
	int nBuffer		= 20;
	float nSpeed	= 100;

	RECT rCameraBounds;
	SetRect(&rCameraBounds, 0, 0, 10000, 10000);

	m_cCAM->VelX(0);
	m_cCAM->VelY(0);

	if (CSGD_DirectInput::GetInstance()->MouseGetPosX() < nBuffer + m_cCAM->GetX())
		m_cCAM->VelX(-nSpeed);
	else if (CSGD_DirectInput::GetInstance()->MouseGetPosX() > m_cCAM->GetX() + CGame::GetInstance()->GetScreenWidth() - nBuffer)
		m_cCAM->VelX(nSpeed);

	if (CSGD_DirectInput::GetInstance()->MouseGetPosY() < nBuffer + m_cCAM->GetY())
		m_cCAM->VelY(-nSpeed);
	else if (CSGD_DirectInput::GetInstance()->MouseGetPosY() > m_cCAM->GetY() + CGame::GetInstance()->GetScreenHeight() - nBuffer)
		m_cCAM->VelY(nSpeed);


	m_cCAM->Update(fElapsedTime);


	if (m_cCAM->GetX() < rCameraBounds.left)
	{
		m_cCAM->SetX((float)rCameraBounds.left);
		m_cCAM->VelX(0);
	}
	//else if (m_cCAM->GetX() + CGame::GetInstance()->GetScreenWidth() > rCameraBounds.right)
	//{
	//	m_cCAM->SetX((float)(rCameraBounds.right - CGame::GetInstance()->GetScreenWidth()));
	//	m_cCAM->VelY(0);
	//}

	//if (m_cCAM->GetY() < rCameraBounds.top)
	//	m_cCAM->SetY((float)rCameraBounds.top);
	//else if (m_cCAM->GetY() + CGame:: GetInstance()->GetScreenHeight() > rCameraBounds.bottom)
	//	m_cCAM->SetY((float)(rCameraBounds.bottom - CGame::GetInstance()->GetScreenHeight()));


}
