//////////////////////////////////////////////////////////////////////////////////////////////
//	File			:	"CMainMenuState.h"
//
//	Authors			:	Tim Smith, Daniel Makin
//
//	Purpose			:	To define the functionality of the Main Menu game state
//////////////////////////////////////////////////////////////////////////////////////////////
#include "precompiled_header.h"
#include "CMainMenuState.h"
#include "CGamePlayState.h"
#include "COptionsMenuState.h"
#include "..\CGame.h"

CMainMenuState::CMainMenuState(void)
{

}

CMainMenuState::~CMainMenuState(void)
{

}

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState instance;
	return &instance;
}

void CMainMenuState::Enter(void)
{
	m_nMenuBG = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\cptLogMainMenuBG.png").c_str());
	m_nMenuCur[0] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm0.png").c_str()); 
	m_nMenuCur[1] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm1.png").c_str()); 
	m_nMenuCur[2] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm2.png").c_str()); 
	m_nMenuCur[3] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm3.png").c_str()); 
	m_nMenuCur[4] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm4.png").c_str());
	m_sCurrentChoice = 0;
}

bool CMainMenuState::Input(void)
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_UP))
		m_sCurrentChoice--;
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_DOWN))
		m_sCurrentChoice++;

	if(m_sCurrentChoice < 0)
		m_sCurrentChoice = 4;
	if(m_sCurrentChoice > 4)
		m_sCurrentChoice = 0;

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		if(m_sCurrentChoice == 0)
			CGame::GetInstance()->ChangeState( CGamePlayState::GetInstance() );
		if(m_sCurrentChoice == 2)
			CGame::GetInstance()->PushState(COptionsMenuState::GetInstance());
	}

	return true;
}

void CMainMenuState::Update(float fElapsedTime)
{

}

void CMainMenuState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nMenuBG, 0, 0, 0.75f, 0.75f);
	CSGD_TextureManager::GetInstance()->Draw(m_nMenuCur[m_sCurrentChoice], (int)(632 * 0.75f), (int)(574 * 0.75f), 0.75f, 0.75f);
}

void CMainMenuState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuBG);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[0]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[1]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[2]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[3]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[4]); 
}