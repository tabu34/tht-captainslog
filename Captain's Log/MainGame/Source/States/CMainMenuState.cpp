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
#include "CHelpState.h"
#include "CLoadState.h"
#include "../Managers/MovementControl.h"
#include "..\SGD Wrappers\CSGD_FModManager.h"
#include "..\CGame.h"
#include "CLoadLevelState.h"
#include "CCreditsState.h"

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
	m_nMenuCur[5] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm5.png").c_str());
	m_nMenuCur[6] = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\mm6.png").c_str());

	m_nMenuMusic = CSGD_FModManager::GetInstance()->LoadSound((char*)CGame::GetInstance()->SoundPath("No_Allies.mp3").c_str(), FMOD_LOOP_NORMAL);

	CSGD_FModManager::GetInstance()->PlaySound(m_nMenuMusic);
	CSGD_FModManager::GetInstance()->SetVolume(m_nMenuMusic, (float)CGame::GetInstance()->MusicVolume() / 100.0f);

	m_sCurrentChoice = 0;
}

bool CMainMenuState::Input(void)
{
	m_nMouseX = CMovementControl::GetInstance()->MousePosX();
	m_nMouseY = CMovementControl::GetInstance()->MousePosY();

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_UP))
		m_sCurrentChoice--;
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_DOWN))
		m_sCurrentChoice++;

	if(m_sCurrentChoice < 0)
		m_sCurrentChoice = 5;
	if(m_sCurrentChoice > 5 && m_sCurrentChoice != 9001)
		m_sCurrentChoice = 0;

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN) || CSGD_DirectInput::GetInstance()->MouseButtonPressed(0))
	{
		if(m_sCurrentChoice == 0)
		{
			CLoadLevelState::GetInstance()->SetLoadLevel(1);
			CGame::GetInstance()->ChangeState( CLoadLevelState::GetInstance() );
		}
		if(m_sCurrentChoice == 1)
		{
			//load game
			CGame::GetInstance()->PushState(CLoadState::GetInstance());
		}
		if(m_sCurrentChoice == 2)
			CGame::GetInstance()->PushState(COptionsMenuState::GetInstance());
		if(m_sCurrentChoice == 3)
			CGame::GetInstance()->PushState(CHelpState::GetInstance());
		if(m_sCurrentChoice == 4)
			CGame::GetInstance()->PushState(CCreditsState::GetInstance());
		if(m_sCurrentChoice == 5)
			return false;
	}

	int nItemHeight=20;
	if((m_nMouseX!=m_nMousePrevX || m_nMouseY!=m_nMousePrevY))
	{
		m_sCurrentChoice = (m_nMouseY-(short)(574 * 0.75f))/20 - 2;

		if(m_nMouseY > 470 && m_nMouseY < 618 && m_nMouseX > 480 && m_nMouseX < 950)
		{
			if(m_sCurrentChoice < 0)
				m_sCurrentChoice = 0;
			if(m_sCurrentChoice > 5)
				m_sCurrentChoice = 5;
		} else {
			m_sCurrentChoice = 9001;
		}
	}

	m_nMousePrevX = m_nMouseX;
	m_nMousePrevY = m_nMouseY;
	return true;
}

void CMainMenuState::Update(float fElapsedTime)
{
	CSGD_FModManager::GetInstance()->SetVolume(m_nMenuMusic, (float)CGame::GetInstance()->MusicVolume() / 100.0f);

	if(m_nMouseX < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosX(0);

	if(m_nMouseX > CGame::GetInstance()->GetScreenWidth())
		CSGD_DirectInput::GetInstance()->MouseSetPosX(CGame::GetInstance()->GetScreenWidth());

	if(m_nMouseY < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosY(0);

	if(m_nMouseY > CGame::GetInstance()->GetScreenHeight())
		CSGD_DirectInput::GetInstance()->MouseSetPosY(CGame::GetInstance()->GetScreenHeight());
}

void CMainMenuState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nMenuBG, 0, 0, 0.75f, 0.75f);
	if(m_sCurrentChoice != 9001)
		CSGD_TextureManager::GetInstance()->Draw(m_nMenuCur[m_sCurrentChoice], (int)(632 * 0.75f), (int)(574 * 0.75f), 0.75f, 0.75f);
	else
		CSGD_TextureManager::GetInstance()->Draw(m_nMenuCur[6], (int)(632 * 0.75f), (int)(574 * 0.75f), 0.75f, 0.75f);
	CMovementControl::GetInstance()->RenderCursor();
}

void CMainMenuState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuBG);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[0]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[1]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[2]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[3]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[4]); 
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuCur[5]); 
	CSGD_FModManager::GetInstance()->StopSound(m_nMenuMusic);
}