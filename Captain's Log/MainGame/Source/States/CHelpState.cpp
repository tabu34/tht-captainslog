#include "precompiled_header.h"
#include "CHelpState.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "..\Managers\\MovementControl.h"

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
	m_nBGImage[0] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("howToPlayScreen.png").c_str());
	m_nBGImage[1] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("howToPlayScreen2.png").c_str());
	curPage = 0;
}

void CHelpState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage[0]);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage[1]);
}

bool CHelpState::Input()
{
	if(CSGD_DirectInput::GetInstance()->KeyPressedEx(DIK_SPACE))
		curPage++;

	if(CSGD_DirectInput::GetInstance()->KeyPressedEx(DIK_TAB))
		curPage--;

	if(curPage == 2)
		CGame::GetInstance()->PopState();

	if(curPage == -1)
		curPage = 1;

	CMovementControl::GetInstance()->Input();
	return true;
}

void CHelpState::Update(float fElapsedTime)
{

}

void CHelpState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImage[curPage], 0, 0);
	CMovementControl::GetInstance()->RenderCursor();
}