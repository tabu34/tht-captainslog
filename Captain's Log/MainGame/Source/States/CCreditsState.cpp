#include "precompiled_header.h"
#include "CCreditsState.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "..\Managers\\MovementControl.h"
#include "CMainMenuState.h"

CCreditsState::CCreditsState()
{

}

CCreditsState::~CCreditsState()
{

}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState instance;
	return &instance;
}

void CCreditsState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("credits.png").c_str());
}

void CCreditsState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage);
}

bool CCreditsState::Input()
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		CGame::GetInstance()->ChangeState( CMainMenuState::GetInstance() );
	}
	CMovementControl::GetInstance()->Input();
	return true;
}

void CCreditsState::Update(float fElapsedTime)
{
	
}

void CCreditsState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImage, 0, 0);
	CMovementControl::GetInstance()->RenderCursor();
}