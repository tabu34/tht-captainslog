#include "precompiled_header.h"
#include "COptionsMenuState.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../CGame.h"

COptionsMenuState::COptionsMenuState()
{

}

COptionsMenuState::~COptionsMenuState()
{

}

COptionsMenuState* COptionsMenuState::GetInstance()
{
	static COptionsMenuState instance;
	return &instance;
}

void COptionsMenuState::Enter()
{
	m_nBGImageID = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\optionsMenu.png").c_str());
	m_nSliderImageID = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\optionsMenuSlider.png").c_str());
}

bool COptionsMenuState::Input()
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->PopState();
	}
	return true;
}

void COptionsMenuState::Update(float fElapsedTime)
{

}

void COptionsMenuState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImageID, 0, 0, 0.75f, 0.75f);
}

void COptionsMenuState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImageID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSliderImageID);
}

