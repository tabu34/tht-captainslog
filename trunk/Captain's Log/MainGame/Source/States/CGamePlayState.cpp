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
#include "..\GameObjects\CHeavy.h"
#include "..\Managers\CWorldManager.h"
#include "CPauseMenuState.h"
#include "..\GameObjects\CMedic.h"
#include "..\GameObjects\CScout.h"
#include "..\GameObjects\CBasicEnemies.h"

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
	m_vButtons.push_back(CHUDButton(1113, 688, 64, 64, "MoveOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/7.png").c_str())));
	m_vButtons.push_back(CHUDButton(1177, 688, 64, 64, "AttackOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/8.png").c_str())));
	m_vButtons.push_back(CHUDButton(1243, 688, 64, 64, "HoldOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/9.png").c_str())));
	m_vButtons.push_back(CHUDButton(1357, 819, 64, 64, "CancelOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str())));
	m_vButtons.push_back(CHUDButton(515, 0, 128, 64, "TipsHelpButton", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/11.png").c_str())));
	m_vButtons.push_back(CHUDButton(797, 0, 128, 32, "TacticalMapButton", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/12.png").c_str())));
	m_vButtons.push_back(CHUDButton(641, 0, 256, 64, "OverMenuButton", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/13.png").c_str())));
	m_vButtons.push_back(CHUDButton(28, 480, 512, 256, "SpeechBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/14.png").c_str())));
	m_vButtons.push_back(CHUDButton(32, 484, 128, 256, "SpeechSpeaker", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/15.png").c_str())));
	m_vButtons.push_back(CHUDButton(37, 577, 128, 32, "SpeechSpeakerNameLine", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/16.png").c_str())));
	m_vButtons.push_back(CHUDButton(41, 31, 256, 64, "ObjectivesSmallBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/17.png").c_str())));
	m_vButtons.push_back(CHUDButton(0, 0, 256, 64, "ToolTipBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/20.png").c_str()), false));

	m_vButtons.push_back(CHUDButton(1113, 752, 64, 64, "Ability 1", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str())));

	m_vButtons.push_back(CHUDButton(0, 0, 512, 32, "ObjectivesLargeBG-NoCheck", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/18.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(0, 0, 512, 32, "ObjectivesLargeBG-Check", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/19.png").c_str()), false));
	
	m_vButtonInstances = m_vButtons;

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
	CWorldManager::GetInstance()->Load("Resource//Graphics//Intro Level Take 2.mfl");
	m_nMiniMap = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("minimap.png").c_str());

	// Load Animations
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\marine\\marine.bin").c_str(), D3DCOLOR_XRGB(255, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\firebat\\firebat.bin").c_str(), D3DCOLOR_XRGB(255, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\medic\\medic.bin").c_str(), D3DCOLOR_XRGB(0, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\ghost\\ghost.bin").c_str(), D3DCOLOR_XRGB(0, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\tempenemy\\tempenemy.bin").c_str(), D3DCOLOR_XRGB(0, 255, 255));

	// Objects
	CMarine* alliedMarine = new CMarine();
	CHeavy*  alliedHeavy  = new CHeavy();
	CMedic*  alliedMedic  = new CMedic();
	CScout*  alliedScout  = new CScout();

	alliedMarine->PosX(50);
	alliedMarine->PosY(50);
	alliedHeavy->PosX(150);
	alliedHeavy->PosY(50);
	alliedScout->PosX(150);
	alliedScout->PosY(150);
	alliedMedic->PosX(50);
	alliedMedic->PosY(150);

	CMovementControl::GetInstance()->SetPlayerUnits(alliedMarine, alliedHeavy, alliedScout, alliedMedic);

	CObjectManager::GetInstance()->AddObject(alliedHeavy);
	CObjectManager::GetInstance()->AddObject(alliedMedic);
	CObjectManager::GetInstance()->AddObject(alliedScout);
	CObjectManager::GetInstance()->AddObject(alliedMarine);

	CMarine* badGuy = new CMarine();
	badGuy->Type(CBase::OBJ_ENEMY);
	badGuy->PosX(400);
	badGuy->PosY(200);
	CObjectManager::GetInstance()->AddObject(badGuy);

	// Test Speech
	m_nCurCount = 0;
	m_szSpeechText = "Test Speech, Test Speech, \nTest Speech, Test Speech, \nTest Speech, Test Speech";

	// Camera
	CGame::GetInstance()->GetCamera()->SetX( 0.0f );
	CGame::GetInstance()->GetCamera()->SetY( 0.0f );

	// Particles
	m_nParticleImageID = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("particle.png").c_str());
	m_peEmitter.Initialize(m_nParticleImageID, 64, 64, 50, 50, 30, 5, 50, 0, 1, 1, 0, 0, 16, 16, 32, 32, 0, 0, 0, 3, 255, 255, 255);
}

void CGamePlayState::Exit(void)
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nParticleImageID);

	for(unsigned int i = 0; i < m_vButtons.size(); i++)
	{
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_vButtons[i].TextureID());
	}

	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMiniMap);
	CAnimationManager::GetInstance()->Shutdown();
	CObjectManager::GetInstance()->RemoveAllObjects();
}

bool CGamePlayState::Input(void)
{
	// Tooltips
	RECT mousePos, collide, collider;
	mousePos.left = CMovementControl::GetInstance()->MousePosX();
	mousePos.top = CMovementControl::GetInstance()->MousePosY();
	mousePos.right = mousePos.left + 1;
	mousePos.bottom = mousePos.top + 1;

	if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("MoveOrder")].GetCollisionRect()), &mousePos)) {
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = "  Move To Position";
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_szSelectedCommand = "MoveOrder";
			return true;
		}
	} else if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("AttackOrder")].GetCollisionRect()), &mousePos)) {
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = "     Attack Target";
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_szSelectedCommand = "AttackOrder";
			return true;
		}
	} else if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("HoldOrder")].GetCollisionRect()), &mousePos)) {
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = "   Hold";
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_szSelectedCommand = "HoldOrder";
			return true;
		}
	} else if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("CancelOrder")].GetCollisionRect()), &mousePos)) {
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = " Cancel";
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_szSelectedCommand = "CancelOrder";
			return true;
		}
	} else {
		m_szTooltipText = "";
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(false);
	}


	RECT rMiniMap = {5, 690, 260, 896};
	if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0) && IntersectRect(&collide, &rMiniMap, &mousePos))
	{
		float fPercent;
		fPercent = (float)(mousePos.left-5)/255.0f;
		
		CGame::GetInstance()->GetCamera()->SetX(CWorldManager::GetInstance()->WorldWidth()*fPercent);
		if(CGame::GetInstance()->GetCamera()->GetX() > CWorldManager::GetInstance()->WorldWidth() - CGame::GetInstance()->GetScreenWidth() )
			CGame::GetInstance()->GetCamera()->SetX( CWorldManager::GetInstance()->WorldWidth() - CGame::GetInstance()->GetScreenWidth() );
		fPercent = (float)(mousePos.top-690)/206.0f;
		CGame::GetInstance()->GetCamera()->SetY(CWorldManager::GetInstance()->WorldHeight()*fPercent);
		if(CGame::GetInstance()->GetCamera()->GetY() > CWorldManager::GetInstance()->WorldHeight() - CGame::GetInstance()->GetScreenHeight())
			CGame::GetInstance()->GetCamera()->SetY( CWorldManager::GetInstance()->WorldHeight() - CGame::GetInstance()->GetScreenHeight());
		return true;
	}


	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->PushState(CPauseMenuState::GetInstance());
	}

	if (CSGD_DirectInput::GetInstance()->KeyPressed(DIK_B))
	{
		CMarine* badGuy = new CMarine();
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(400);
		badGuy->PosY(200);
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

	CMovementControl::GetInstance()->Input();

	return true;
}

void CGamePlayState::Update(float fElapsedTime)
{
	m_nCurCount += 25.0f * fElapsedTime;
	CMovementControl::GetInstance()->CheckDragRect();
	CMovementControl::GetInstance()->UpdateCamera(fElapsedTime);
	CObjectManager::GetInstance()->UpdateObjects(fElapsedTime);
	CMessageSystem::GetInstance()->ProcessMessages();
	m_peEmitter.Update(fElapsedTime);
}

void CGamePlayState::RenderMiniMap()
{
	//background image
	//objects
	//screen rect
	CSGD_TextureManager::GetInstance()->Draw(m_nMiniMap, 5, 690);
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	int tempX, tempY, maxX, maxY;
	int OffsetX = 5, OffsetY = 690, CX = 255, CY = 206;
	unsigned char ucRed, ucBlue, ucGreen;
	RECT rObj;
	vector<CBase*>* pOM = CObjectManager::GetInstance()->GetObjectList();

	maxX = CWorldManager::GetInstance()->WorldWidth();
	maxY = CWorldManager::GetInstance()->WorldHeight();

	for(size_t i=0; i<pOM->size(); i++)
	{
		switch((*pOM)[i]->Type())
		{
		case CBase::OBJ_PLAYER:
			ucRed=0;
			ucGreen=255;
			ucBlue=0;
			break;
		case CBase::OBJ_ENEMY:
			ucRed=255;
			ucGreen=0;
			ucBlue=0;
			break;
		default:
			ucRed=255;
			ucGreen=255;
			ucBlue=255;
			break;
		}
		tempX = (int)(*pOM)[i]->PosX();
		tempY = (int)(*pOM)[i]->PosY();
		
		rObj.left = OffsetX + (int)(((float)tempX/(float)maxX)*(float)CX);
		rObj.top = OffsetY + (int)(((float)tempY/(float)maxY)*(float)CY);
		rObj.right = rObj.left+5;
		rObj.bottom = rObj.top+5;
		CSGD_Direct3D::GetInstance()->DrawRect(rObj, ucRed, ucGreen, ucBlue);

	}

	//screen rect
	tempX = CGame::GetInstance()->GetCamera()->GetX();
	tempY = CGame::GetInstance()->GetCamera()->GetY();
	rObj.left = OffsetX + (int)(((float)tempX/(float)maxX)*(float)CX);
	rObj.top = OffsetY + (int)(((float)tempY/(float)maxY)*(float)CY);
	float fPercent;
	fPercent = (float)CGame::GetInstance()->GetScreenWidth()/(float)CWorldManager::GetInstance()->WorldWidth();
	rObj.right = rObj.left+ (int)((float)CX*fPercent);
	fPercent = (float)CGame::GetInstance()->GetScreenHeight()/(float)CWorldManager::GetInstance()->WorldHeight();
	rObj.bottom = rObj.top + (int)((float)CY*fPercent);
	CSGD_Direct3D::GetInstance()->DrawLine(rObj.left, rObj.top, rObj.right, rObj.top);
	CSGD_Direct3D::GetInstance()->DrawLine(rObj.right, rObj.top, rObj.right, rObj.bottom);
	CSGD_Direct3D::GetInstance()->DrawLine(rObj.right, rObj.bottom, rObj.left, rObj.bottom);
	CSGD_Direct3D::GetInstance()->DrawLine(rObj.left, rObj.bottom, rObj.left, rObj.top);

	CSGD_Direct3D::GetInstance()->SpriteBegin();
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

	// Render selected object stats (if a single object is selected)
	if(CMovementControl::GetInstance()->GetSelectedUnits()->size() > 0)
	{
		CBase* pBase = (*CMovementControl::GetInstance()->GetSelectedUnits())[0];
		switch(pBase->Type())
		{
		case CBase::OBJ_PLAYER:
			{
				CUnit* pUnit = (CUnit*)pBase;
				m_ftTextSmall.RenderText("Health", 460, 755);
				char buff[128];
				sprintf_s(buff, 128, "%i/%i", pUnit->CurHealth(), pUnit->MaxHealth());
				m_ftTextSmall.RenderText(buff, 460, 770);
				sprintf_s(buff, 128, "Attack: %.2f", pUnit->AttackDamage());
				m_ftTextSmall.RenderText(buff, 840, 755);
				sprintf_s(buff, 128, "Speed: %.2f", pUnit->AttackSpeed());
				m_ftTextSmall.RenderText(buff, 840, 770);
				sprintf_s(buff, 128, "Armor: %i", pUnit->Armor());
				m_ftTextSmall.RenderText(buff, 840, 785);
			}
			break;
		case CBase::OBJ_ENEMY:
			{
				CUnit* pEnemy = (CUnit*)pBase;
				m_ftTextSmall.RenderText("Health", 460, 755);
				char buff[128];
				sprintf_s(buff, 128, "%i/%i", pEnemy->CurHealth(), pEnemy->MaxHealth());
				m_ftTextSmall.RenderText(buff, 460, 770);
				sprintf_s(buff, 128, "Attack: %.2f", pEnemy->AttackDamage());
				m_ftTextSmall.RenderText(buff, 840, 755);
				sprintf_s(buff, 128, "Speed: %.2f", pEnemy->AttackSpeed());
				m_ftTextSmall.RenderText(buff, 840, 770);
				sprintf_s(buff, 128, "Armor: %i", pEnemy->Armor());
				m_ftTextSmall.RenderText(buff, 840, 785);
			}
			break;
		}
	}

	RenderMiniMap();

	// Render ToolTip Text
	if(m_szTooltipText != "")
		m_ftTextSmallShadow.RenderText((char*)m_szTooltipText.c_str(), CMovementControl::GetInstance()->MousePosX(), CMovementControl::GetInstance()->MousePosY() - 25);
}

void CGamePlayState::Render(void)
{
	CWorldManager::GetInstance()->Render();
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	CSGD_Direct3D::GetInstance()->SpriteBegin();

	CObjectManager::GetInstance()->RenderObjects();
	CMovementControl::GetInstance()->RenderDragRect();
	m_peEmitter.Render();
	RenderHUD();
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

		CObjectManager::GetInstance()->FindAndRemove(udMSG->GetUnit());

		CObjectManager::GetInstance()->RemoveObject(udMSG->GetUnit());
	}
}