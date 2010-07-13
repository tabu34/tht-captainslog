#include "precompiled_header.h"
#include "COptionsMenuState.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../CGame.h"
#include "../Managers/MovementControl.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"

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
	m_pCurrentControl = NULL;

	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.7f, 0.7f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());

	//add controls to the vector (ALL OF THEM..GAH)
	tMenuControl mcInit;
	SetRect(&mcInit.rArea, 511, 235, 646, 259);
	mcInit.szIdentifier = "fullscreen";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 415, 396, 600, 413);
	mcInit.szIdentifier = "sfxvolume";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 415, 474, 600, 490);
	mcInit.szIdentifier = "voiceovervolume";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 415, 550, 600, 567);
	mcInit.szIdentifier = "musicvolume";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 865, 237, 1045, 260);
	mcInit.szIdentifier = "layout";
	m_vControls.push_back(mcInit);


	//ALL THE FRIGGIN KEYBINDS
	char buffer[128];
	for(int i=0; i<18; i++)
	{
		sprintf_s(buffer, 128, "key%i", i);
		SetRect(&mcInit.rArea, 779, 272+(i*25)+(int)(i*1.5f), 1041, 298+(i*25)+(int)(i*1.5f));
		mcInit.szIdentifier = buffer;
		m_vControls.push_back(mcInit);
	}

	SetRect(&mcInit.rArea, 362, 651, 662, 687);
	mcInit.szIdentifier = "saveexit";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 362, 690, 662, 727);
	mcInit.szIdentifier = "exit";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 362, 730, 662, 767);
	mcInit.szIdentifier = "restoredefaults";
	m_vControls.push_back(mcInit);

}

bool COptionsMenuState::Input()
{
	m_nMouseX = CMovementControl::GetInstance()->MousePosX();
	m_nMouseY = CMovementControl::GetInstance()->MousePosY();
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->PopState();
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RIGHT))
	{
		if(m_pCurrentControl)
		{
			if(m_pCurrentControl->szIdentifier == "fullscreen")
				m_pCurrentControl = &m_vControls[4];
			else if(m_pCurrentControl->szIdentifier == "sfxvolume")
				m_pCurrentControl = &m_vControls[4];
			else if(m_pCurrentControl->szIdentifier == "voiceovervolume")
				m_pCurrentControl = &m_vControls[4];
			else if(m_pCurrentControl->szIdentifier == "musicvolume")
				m_pCurrentControl = &m_vControls[4];
		}
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_LEFT))
	{
		if(m_pCurrentControl)
		{
			if(m_pCurrentControl->szIdentifier == "layout")
				m_pCurrentControl = &m_vControls[0];
		}
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_TAB))
	{
		//find index we're at
		unsigned int nCurIndex=-1;
		if(m_pCurrentControl == NULL)
			nCurIndex = -1;
		else
		{
			for(size_t i=0; i<m_vControls.size(); i++)
			{
				if(m_pCurrentControl == &m_vControls[i])
				{
					nCurIndex = i;
					break;
				}
			}
		}

		nCurIndex = (nCurIndex+1<m_vControls.size()) ? nCurIndex+1 : 0;

		m_pCurrentControl = &m_vControls[nCurIndex];
	}

	if(m_nMouseX!=m_nMousePrevX || m_nMouseY!=m_nMousePrevY)
	{
		m_pCurrentControl = NULL;
		for(size_t i=0; i<m_vControls.size(); i++)
		{
			POINT ptMouse = {m_nMouseX, m_nMouseY};
			if(PtInRect(&m_vControls[i].rArea, ptMouse))
			{
				m_pCurrentControl = &m_vControls[i];
				break;
			}
		}
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN) || CSGD_DirectInput::GetInstance()->MouseButtonPressed(0))
	{
		if(m_pCurrentControl)
		{
			if(m_pCurrentControl->szIdentifier == "saveexit")
			{
				//save options
				CGame::GetInstance()->PopState();
			}
			else if(m_pCurrentControl->szIdentifier == "exit")
			{
				CGame::GetInstance()->PopState();
			}
			else if(m_pCurrentControl->szIdentifier == "fullscreen")
			{
				CGame::GetInstance()->ToggleFullScreen();
			}
		}
	}

	if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
	{
		if(m_pCurrentControl)
		{
			if(m_pCurrentControl->szIdentifier == "musicvolume")
			{
				
			}
			else if(m_pCurrentControl->szIdentifier == "sfxvolume")
			{

			}
			else if(m_pCurrentControl->szIdentifier == "voiceovervolume")
			{

			}
		}
	}

	m_nMousePrevX = m_nMouseX;
	m_nMousePrevY = m_nMouseY;
	return true;
}

void COptionsMenuState::Update(float fElapsedTime)
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

void DrawHollowRect(const RECT *rDraw, unsigned char ucRed = 255, unsigned char ucGreen = 255, unsigned char ucBlue = 255)
{
	CSGD_Direct3D::GetInstance()->SpriteEnd();

	CSGD_Direct3D::GetInstance()->DrawLine(rDraw->left - 1, rDraw->top - 1, rDraw->right - 1, rDraw->top - 1, ucRed, ucGreen, ucBlue);
	CSGD_Direct3D::GetInstance()->DrawLine(rDraw->right - 1, rDraw->top - 1, rDraw->right - 1, rDraw->bottom - 1, ucRed, ucGreen, ucBlue);
	CSGD_Direct3D::GetInstance()->DrawLine(rDraw->right - 1, rDraw->bottom - 1, rDraw->left - 1, rDraw->bottom - 1, ucRed, ucGreen, ucBlue);
	CSGD_Direct3D::GetInstance()->DrawLine(rDraw->left - 1, rDraw->bottom - 1, rDraw->left - 1, rDraw->top - 1, ucRed, ucGreen, ucBlue);

	CSGD_Direct3D::GetInstance()->SpriteBegin();
}

void COptionsMenuState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImageID, 0, 0, 0.75f, 0.75f);

	
	if(m_pCurrentControl)
		DrawHollowRect(&m_pCurrentControl->rArea);

	CSGD_TextureManager::GetInstance()->Draw(m_nSliderImageID, (int)(415.0f + ((float)m_nSFXVolume/100.0f)*185.0f), 396, 0.75f, 0.75f);
	CSGD_TextureManager::GetInstance()->Draw(m_nSliderImageID, (int)(415.0f + ((float)m_nVoiceVolume/100.0f)*185.0f), 474, 0.75f, 0.75f);
	CSGD_TextureManager::GetInstance()->Draw(m_nSliderImageID, (int)(415.0f + ((float)m_nMusicVolume/100.0f)*185.0f), 550, 0.75f, 0.75f);

	m_bfFont.RenderText(((CGame::GetInstance()->IsWindowed()) ? "False" : "True"), 511, 235);

	CMovementControl::GetInstance()->RenderCursor();
}

void COptionsMenuState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImageID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSliderImageID);
}

