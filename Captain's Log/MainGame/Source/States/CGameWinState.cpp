#include "precompiled_header.h"
#include "CGameWinState.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "..\Managers\\MovementControl.h"
#include "CMainMenuState.h"

CGameWinState::CGameWinState()
{

}

CGameWinState::~CGameWinState()
{

}

CGameWinState* CGameWinState::GetInstance()
{
	static CGameWinState instance;
	return &instance;
}

void CGameWinState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("gamewin.png").c_str());
}

void CGameWinState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage);
}

bool CGameWinState::Input()
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		CGame::GetInstance()->ChangeState( CMainMenuState::GetInstance() );
	}
	CMovementControl::GetInstance()->Input();
	return true;
}

void CGameWinState::Update(float fElapsedTime)
{
	
}

void CGameWinState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImage, 0, 0);
	CMovementControl::GetInstance()->RenderCursor();
}