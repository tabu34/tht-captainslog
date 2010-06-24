//////////////////////////////////////////////////////////////////////////////////////////////
//	File			:	"CMainMenuState.h"
//
//	Authors			:	Tim Smith, Daniel Makin
//
//	Purpose			:	To define the functionality of the Main Menu game state
//////////////////////////////////////////////////////////////////////////////////////////////
#include "precompiled_header.h"
#include "CMainMenuState.h"
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
	m_nMenuBG = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\cptLogMainMenuBG.png"));
	m_nMenuCur[0] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm0.png")); 
	m_nMenuCur[1] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm1.png")); 
	m_nMenuCur[2] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm2.png")); 
	m_nMenuCur[3] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm3.png")); 
	m_nMenuCur[4] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm4.png")); 
}

bool CMainMenuState::Input(void)
{
	return true;
}

void CMainMenuState::Update(float fElapsedTime)
{

}

void CMainMenuState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nMenuBG, 0, 0, 0.75f, 0.75f);
	CSGD_TextureManager::GetInstance()->Draw(m_nMenuCur[m_sCurrentChoice], 0, 0, 0.75f, 0.75f);
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