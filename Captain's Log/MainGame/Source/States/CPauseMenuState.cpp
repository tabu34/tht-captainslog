#include "precompiled_header.h"
#include "CPauseMenuState.h"
#include "COptionsMenuState.h"
#include "CMainMenuState.h"
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

	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_sCurrentChoice = 0;
}

bool CPauseMenuState::Input(void)
{
	m_nMouseX = CMovementControl::GetInstance()->MousePosX();
	m_nMouseY = CMovementControl::GetInstance()->MousePosY();
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->PopState();
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_UP))
	{
		if(m_sCurrentChoice==0)
			m_sCurrentChoice=5;
		else
			m_sCurrentChoice--;
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_DOWN))
	{
		if(m_sCurrentChoice==5)
			m_sCurrentChoice=0;
		else
			m_sCurrentChoice++;
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN) || CSGD_DirectInput::GetInstance()->MouseButtonPressed(0))
	{
		switch(m_sCurrentChoice)
		{
		case 0: //resume
			CGame::GetInstance()->PopState();
			break;
		case 1: //save
			break;
		case 2: //load
			break;
		case 3: //options
			CGame::GetInstance()->PushState(COptionsMenuState::GetInstance());
			break;
		case 4: //help
			break;
		case 5: //main menu
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			break;
		}
	}

	if(m_nMousePrevX!=m_nMouseX || m_nMousePrevY!=m_nMouseY)
	{
		POINT ptMouse = {m_nMouseX, m_nMouseY};
		RECT rMenu = {CGame::GetInstance()->GetScreenWidth()/3, 
			CGame::GetInstance()->GetScreenHeight()/3,
			2*CGame::GetInstance()->GetScreenWidth()/3,
			CGame::GetInstance()->GetScreenHeight()/3+192};

		if(PtInRect(&rMenu, ptMouse))
		{
			m_sCurrentChoice = (m_nMouseY - CGame::GetInstance()->GetScreenHeight()/3) / 32;
		}
	}
	m_nMousePrevX = m_nMouseX;
	m_nMousePrevY = m_nMouseY;

	return true;
}

void CPauseMenuState::Update(float fElapsedTime)
{
	if(m_nMouseX < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosX(0);

	if(m_nMouseX > CGame::GetInstance()->GetScreenWidth())
		CSGD_DirectInput::GetInstance()->MouseSetPosX(CGame::GetInstance()->GetScreenWidth());

	if(m_nMouseY < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosY(0);

	if(m_nMouseY > CGame::GetInstance()->GetScreenHeight())
		CSGD_DirectInput::GetInstance()->MouseSetPosY(CGame::GetInstance()->GetScreenHeight());
}

void CPauseMenuState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImageID, 0, 0, 0.75f, 0.75f);

	int nAdd = 0;

	CSGD_TextureManager::GetInstance()->Draw(m_nSelectorImageID, CGame::GetInstance()->GetScreenWidth()/3 - 20, CGame::GetInstance()->GetScreenHeight()/3+(32*m_sCurrentChoice)+8);

	nAdd = (m_sCurrentChoice==0) ? 0 : 23;
	m_bfFont.RenderText("Resume", nAdd+CGame::GetInstance()->GetScreenWidth()/3, CGame::GetInstance()->GetScreenHeight()/3);
	nAdd = (m_sCurrentChoice==1) ? 0 : 23;
	m_bfFont.RenderText("Save Progress", nAdd+CGame::GetInstance()->GetScreenWidth()/3, CGame::GetInstance()->GetScreenHeight()/3+32);
	nAdd = (m_sCurrentChoice==2) ? 0 : 23;
	m_bfFont.RenderText("Load Previous Sequence", nAdd+CGame::GetInstance()->GetScreenWidth()/3, CGame::GetInstance()->GetScreenHeight()/3+64);
	nAdd = (m_sCurrentChoice==3) ? 0 : 23;
	m_bfFont.RenderText("Adjust Parameters", nAdd+CGame::GetInstance()->GetScreenWidth()/3, CGame::GetInstance()->GetScreenHeight()/3+96);
	nAdd = (m_sCurrentChoice==4) ? 0 : 23;
	m_bfFont.RenderText("Reference Operation's Manual", nAdd+CGame::GetInstance()->GetScreenWidth()/3, CGame::GetInstance()->GetScreenHeight()/3+128);
	nAdd = (m_sCurrentChoice==5) ? 0 : 23;
	m_bfFont.RenderText("Exit to Main Menu", nAdd+CGame::GetInstance()->GetScreenWidth()/3, CGame::GetInstance()->GetScreenHeight()/3+160);


	CMovementControl::GetInstance()->RenderCursor();

}

void CPauseMenuState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImageID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSelectorImageID);
}