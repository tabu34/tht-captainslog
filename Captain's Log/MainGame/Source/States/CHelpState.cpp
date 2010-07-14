#include "precompiled_header.h"
#include "CHelpState.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"

CHelpState::CHelpState()
{

}

CHelpState::~CHelpState()
{

}

CHelpState* CHelpState::GetInstance()
{
	static CHelpState instance;
	return &instance;
}

void CHelpState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("howToPlayScreen.png").c_str());
}

void CHelpState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage);
}

bool CHelpState::Input()
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		CGame::GetInstance()->PopState();
	}
	return true;
}

void CHelpState::Update(float fElapsedTime)
{
	
}

void CHelpState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImage, 0, 0);
}