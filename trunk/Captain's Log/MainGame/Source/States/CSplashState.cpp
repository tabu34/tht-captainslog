#include "precompiled_header.h"
#include "..\CGame.h"
#include "CSplashState.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "CMainMenuState.h"

CSplashState::CSplashState()
{

}

CSplashState::~CSplashState()
{

}

CSplashState* CSplashState::GetInstance()
{
	static CSplashState instance;
	return &instance;
}

void CSplashState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\cptLogMainMenuBG.png").c_str());
	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
}

void CSplashState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage);
}

bool CSplashState::Input()
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		CGame::GetInstance()->PopState();
	}
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		return false;
	}
	return true;
}

void CSplashState::Update(float fElapsedTime)
{
	
}

void CSplashState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImage, 0, 0, 0.75f, 0.75f);

	m_bfFont.RenderText("Press <ENTER> to Launch", CGame::GetInstance()->GetScreenWidth()/3+30, CGame::GetInstance()->GetScreenHeight()/2+300);
}