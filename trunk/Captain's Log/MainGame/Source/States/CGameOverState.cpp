#include "precompiled_header.h"
#include "..\CGame.h"
#include "CGameOverState.h"
#include "CMainMenuState.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"

CGameOverState::CGameOverState()
{

}

CGameOverState::~CGameOverState()
{

}

CGameOverState* CGameOverState::GetInstance()
{
	static CGameOverState instance;
	return &instance;
}

void CGameOverState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\cptLogMainMenuBG.png").c_str());
	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
}

void CGameOverState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage);
}

bool CGameOverState::Input()
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
	}
	return true;
}

void CGameOverState::Update(float fElapsedTime)
{

}

void CGameOverState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImage, 0, 0, 0.75f, 0.75f);

	m_bfFont.RenderText("GAME OVER", CGame::GetInstance()->GetScreenWidth()/2, CGame::GetInstance()->GetScreenHeight()/2);
	m_bfFont.RenderText("Press <ENTER> to Return to the Main Menu", CGame::GetInstance()->GetScreenWidth()/3+30, CGame::GetInstance()->GetScreenHeight()/2+300);
}