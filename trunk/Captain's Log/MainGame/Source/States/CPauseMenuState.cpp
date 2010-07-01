#include "precompiled_header.h"
#include "CPauseMenuState.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../CGame.h"
#include "../Managers/MovementControl.h"

CPauseMenuState::CPauseMenuState(void)
{
}

CPauseMenuState::~CPauseMenuState(void)
{
}

CPauseMenuState* CPauseMenuState::GetInstance()
{
	static CPauseMenuState instance;
	return &instance;
}

void CPauseMenuState::Enter(void)
{
	m_nBGImageID = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\pauseMenu.png").c_str());
	m_nSelectorImageID = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\menuSelector.png").c_str());

}

bool CPauseMenuState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->PopState();
	}

	return true;
}

void CPauseMenuState::Update(float fElapsedTime)
{
	
}

void CPauseMenuState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImageID, 0, 0, 0.75f, 0.75f);
	CMovementControl::GetInstance()->RenderCursor();

}

void CPauseMenuState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImageID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSelectorImageID);
}