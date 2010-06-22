#include "precompiled_header.h"
#include "MovementControl.h"
#include "CObjectManager.h"
#include "CCamera.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_Direct3D.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
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
	m_ptStart.x = CSGD_DirectInput::GetInstance()->MouseGetPosX();
	m_ptStart.y = CSGD_DirectInput::GetInstance()->MouseGetPosY();
	m_nCursorImageID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource\\Graphics\\gameCursor.png");
}

void CMovementControl::Input()
{
	// TODO: Mouse Input

	if(m_DI->MouseButtonPressed(MOUSE_RIGHT))
	{
		//m_esEventSystem->SendEvent("LeftMouseButtonPressed");
	}

	if(m_DI->MouseButtonDown(MOUSE_LEFT))
	{
		// Unit Selection ---------------
		if(m_bDragging == false)
		{
			m_bDragging = true;
			m_ptStart.x = CSGD_DirectInput::GetInstance()->MouseGetPosX();
			m_ptStart.y = CSGD_DirectInput::GetInstance()->MouseGetPosY();
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

void CMovementControl::RenderDragRect()
{
	if(m_bDragging)
	{
		RECT dragRect;
		dragRect.left = m_ptStart.x;
		dragRect.top = m_ptStart.y;
		dragRect.right = CSGD_DirectInput::GetInstance()->MouseGetPosX();
		dragRect.bottom = CSGD_DirectInput::GetInstance()->MouseGetPosY();

		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.left, dragRect.top, dragRect.right, dragRect.top, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.right, dragRect.top, dragRect.right, dragRect.bottom, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.right, dragRect.bottom, dragRect.left, dragRect.bottom, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.left, dragRect.bottom, dragRect.left, dragRect.top, 0, 255, 0);
	}
}

void CMovementControl::RenderCursor()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nCursorImageID, CSGD_DirectInput::GetInstance()->MouseGetPosX(), CSGD_DirectInput::GetInstance()->MouseGetPosY(), 0.5f, 0.5f);
}