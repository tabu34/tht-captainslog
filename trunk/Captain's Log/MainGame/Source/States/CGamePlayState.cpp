//////////////////////////////////////////////////////////////////////////////////////////////
//	File			:	"CGamePlayState.h"
//
//	Authors			:	Tim Smith, Daniel Makin
//
//	Purpose			:	To define the functionality of the Game Play game state
//////////////////////////////////////////////////////////////////////////////////////////////
#include "precompiled_header.h"
#include "CGamePlayState.h"
#include "..\CGame.h"
#include "..\GameObjects\CMarine.h"
#include "..\Managers\CWorldManager.h"

CGamePlayState::CGamePlayState(void)
{

}

CGamePlayState::~CGamePlayState(void)
{

}

CGamePlayState* CGamePlayState::GetInstance()
{
	static CGamePlayState instance;
	return &instance;
}

void CGamePlayState::Enter(void)
{
	CMessageSystem::GetInstance()->InitMessageSystem(CGamePlayState::MessageProc);

	// Setup GUI
	m_vButtons.push_back(CHUDButton(-76, 645, 2048, 512, "BottomHUD", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/0.png").c_str())));
	m_vButtons.push_back(CHUDButton(270, 706, 256, 256, "UnitPortrait", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/1.png").c_str())));
	m_vButtons.push_back(CHUDButton(274, 852, 256, 32, "PortraitNameLine", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/2.png").c_str())));
	m_vButtons.push_back(CHUDButton(433, 728, 1024, 256, "MiddleHUDOutlines", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/3.png").c_str())));
	m_vButtons.push_back(CHUDButton(222, 689, 64, 64, "MinimapButton1", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/4.png").c_str())));
	m_vButtons.push_back(CHUDButton(222, 726, 64, 64, "MinimapButton2", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/5.png").c_str())));
	m_vButtons.push_back(CHUDButton(222, 764, 64, 64, "MinimapButton3", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/6.png").c_str())));
	m_vButtons.push_back(CHUDButton(1113, 688, 128, 128, "MoveOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/7.png").c_str())));
	m_vButtons.push_back(CHUDButton(1177, 688, 128, 128, "AttackOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/8.png").c_str())));
	m_vButtons.push_back(CHUDButton(1243, 688, 128, 128, "HoldOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/9.png").c_str())));
	m_vButtons.push_back(CHUDButton(1357, 819, 128, 128, "CancelOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str())));
	m_vButtons.push_back(CHUDButton(515, 0, 128, 64, "TipsHelpButton", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/11.png").c_str())));
	m_vButtons.push_back(CHUDButton(797, 0, 128, 32, "TacticalMapButton", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/12.png").c_str())));
	m_vButtons.push_back(CHUDButton(641, 0, 256, 64, "OverMenuButton", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/13.png").c_str())));
	m_vButtons.push_back(CHUDButton(28, 480, 512, 256, "SpeechBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/14.png").c_str())));
	m_vButtons.push_back(CHUDButton(32, 484, 128, 256, "SpeechSpeaker", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/15.png").c_str())));
	m_vButtons.push_back(CHUDButton(37, 577, 128, 32, "SpeechSpeakerNameLine", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/16.png").c_str())));
	m_vButtons.push_back(CHUDButton(41, 31, 256, 64, "ObjectivesSmallBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/17.png").c_str())));
	m_vButtons.push_back(CHUDButton(0, 0, 256, 64, "ToolTipBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/20.png").c_str()), false));

	m_vButtonInstances = m_vButtons;

	m_vButtons.push_back(CHUDButton(0, 0, 512, 32, "ObjectivesLargeBG-NoCheck", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/18.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(0, 0, 512, 32, "ObjectivesLargeBG-Check", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/19.png").c_str()), false));
	

	m_ftTextSmall.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.5f, 0.5f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(255, 255, 255));
 	m_ftTextSmall.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_ftTextSmallShadow.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.5f, 0.5f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(0, 0, 0));
 	m_ftTextSmallShadow.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_ftTextLarge.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.80f, 0.80f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(255, 255, 255));
 	m_ftTextLarge.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_ftTextLargeShadow.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.80f, 0.80f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(0, 0, 0));
 	m_ftTextLargeShadow.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());

	// Test BG
	//m_nBG = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("testBG.png").c_str());
	CWorldManager::GetInstance()->Load("Resource//Graphics//testmap.mfl");

	// Load Animations
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\marine\\idle.bin").c_str(), D3DCOLOR_XRGB(112, 38, 37));

	// Objects
	CObjectManager::GetInstance()->AddObject(new CMarine());

	CMarine* badGuy = new CMarine();
	badGuy->Type(CBase::OBJ_ENEMY);
	badGuy->PosX(400);
	CObjectManager::GetInstance()->AddObject(badGuy);

	// Test Speech
	m_nCurCount = 0;
	m_szSpeechText = "Test Speech, Test Speech, \nTest Speech, Test Speech, \nTest Speech, Test Speech";
}

void CGamePlayState::Exit(void)
{
	for(unsigned int i = 0; i < m_vButtons.size(); i++)
	{
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_vButtons[i].TextureID());
	}
}

bool CGamePlayState::Input(void)
{
	CMovementControl::GetInstance()->Input();

	// Tooltips
	RECT mousePos, collide, collider;
	mousePos.left = CSGD_DirectInput::GetInstance()->MouseGetPosX();
	mousePos.top = CSGD_DirectInput::GetInstance()->MouseGetPosY();
	mousePos.right = mousePos.left + 1;
	mousePos.bottom = mousePos.top + 1;

	if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("MinimapButton1")].GetCollisionRect()), &mousePos))
	{
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = "Tactical Minimap Overlay";
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
	} else {
		m_szTooltipText = "";
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(false);
	}

	if (CSGD_DirectInput::GetInstance()->KeyPressed(DIK_B))
	{
		CMarine* badGuy = new CMarine();
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(800);
		CObjectManager::GetInstance()->AddObject(badGuy);
	}

	if (CSGD_DirectInput::GetInstance()->KeyPressed(DIK_M))
	{
		for (unsigned int i = 0; i < CObjectManager::GetInstance()->GetObjectList()->size(); i++)
		{
			if ((*CObjectManager::GetInstance()->GetObjectList())[i]->Type() == CUnit::OBJ_PLAYER)
			{
				((CUnit*)((*CObjectManager::GetInstance()->GetObjectList())[i]))->CurHealth(((CUnit*)((*CObjectManager::GetInstance()->GetObjectList())[i]))->CurHealth() + 2);
			}
		}
	}

	if (CSGD_DirectInput::GetInstance()->KeyPressed(DIK_K))
	{
		for (unsigned int i = 0; i < CObjectManager::GetInstance()->GetObjectList()->size(); i++)
		{
			if ((*CObjectManager::GetInstance()->GetObjectList())[i]->Type() == CUnit::OBJ_PLAYER)
			{
				((CUnit*)((*CObjectManager::GetInstance()->GetObjectList())[i]))->CurHealth(((CUnit*)((*CObjectManager::GetInstance()->GetObjectList())[i]))->CurHealth() - 2);
			}
		}
	}
	return true;
}

void CGamePlayState::Update(float fElapsedTime)
{
	m_nCurCount += 25.0f * fElapsedTime;
	CMovementControl::GetInstance()->CheckDragRect();
	CObjectManager::GetInstance()->UpdateObjects(fElapsedTime);
	CMessageSystem::GetInstance()->ProcessMessages();
}

void CGamePlayState::RenderHUD(void)
{
	// Render all buttons
	for(unsigned int i = 0; i < m_vButtonInstances.size(); i++)
	{
		if(m_vButtonInstances[i].Visible())
			CSGD_TextureManager::GetInstance()->Draw(m_vButtonInstances[i].TextureID(), m_vButtonInstances[i].Point().x, m_vButtonInstances[i].Point().y, 1.0f, 1.0f);
	}

	// Render Names
	RenderSmallShadowText("Speaker", 42, 575);
	RenderLargeShadowText("Unit Name", 284, 852);

	// Render Objectives
	RenderLargeShadowText("Objectives", 54, 35);

	// Render Speech
	RenderLargeShadowText((char *)(m_szSpeechText.substr(0, (unsigned int)m_nCurCount)).c_str(), 135, 494);

	// Render ToolTip Text
	if(m_szTooltipText != "")
		m_ftTextSmallShadow.RenderText((char*)m_szTooltipText.c_str(), CSGD_DirectInput::GetInstance()->MouseGetPosX(), CSGD_DirectInput::GetInstance()->MouseGetPosY() - 25);
}

void CGamePlayState::Render(void)
{
	CWorldManager::GetInstance()->Render();
//	CSGD_TextureManager::GetInstance()->Draw(m_nBG, 0, 0, 1.0f, 1.0f);
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	CSGD_Direct3D::GetInstance()->SpriteBegin();

	CMovementControl::GetInstance()->RenderDragRect();
	RenderHUD();
	CObjectManager::GetInstance()->RenderObjects();
	CMovementControl::GetInstance()->RenderCursor();
}

int  CGamePlayState::FindButton(string _name)
{
	for(unsigned int i = 0; i < m_vButtons.size(); i++)
	{
		if(m_vButtons[i].Name() == _name)
			return i;
	}
	
	return -1;
}

void CGamePlayState::RenderSmallShadowText(char* _text, int _x, int _y)
{
	m_ftTextSmallShadow.RenderText(_text, _x + 1, _y + 1);
	m_ftTextSmall.RenderText(_text, _x, _y);
}

void CGamePlayState::RenderLargeShadowText(char* _text, int _x, int _y)
{
	m_ftTextLargeShadow.RenderText(_text, _x + 2, _y + 2);
	m_ftTextLarge.RenderText(_text, _x, _y);
}

void CGamePlayState::MessageProc(CBaseMessage* pMSG)
{
	switch (pMSG->GetMsgID())
	{
	case MSG_DESTROY_UNIT:
		CUnitDeathMessage* udMSG = (CUnitDeathMessage*)pMSG;

		CObjectManager::GetInstance()->RemoveObject(udMSG->GetUnit());
	}
}