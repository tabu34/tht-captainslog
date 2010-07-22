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
#include "../Managers/CWorldManager.h"
#include "..\GameObjects\CMarine.h"
#include "..\GameObjects\CHeavy.h"
#include "..\GameObjects\CMedic.h"
#include "..\GameObjects\CScout.h"
#include "..\GameObjects\CBasicEnemies.h"
#include "..\Managers\CUnitFactory.h"
#include "..\GameObjects\CBMPFont.h"
#include "..\SGD Wrappers\CSGD_Direct3D.h"

CLoadLevelState::CLoadLevelState(void)
{
	m_nLevelNum = 1;
}

CLoadLevelState::~CLoadLevelState(void)
{

}

CLoadLevelState* CLoadLevelState::GetInstance()
{
	static CLoadLevelState instance;
	return &instance;
}

void CLoadLevelState::Enter(void)
{
	m_nMenuBG = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\cptLogLoadingScreen.png").c_str());
	m_nLoadBar = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\cptLogLoadingBar.png").c_str());
	m_fPercentage = 0.0f;
	m_ftText.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(0, 255, 0));
 	m_ftText.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	Load();
}

bool CLoadLevelState::Input(void)
{
	return true;
}

void CLoadLevelState::Update(float fElapsedTime)
{
	
}

void CLoadLevelState::Load()
{
	// Load animations
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\marine\\marine.bin").c_str(), D3DCOLOR_XRGB(255, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\firebat\\firebat.bin").c_str(), D3DCOLOR_XRGB(255, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\medic\\medic.bin").c_str(), D3DCOLOR_XRGB(0, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\ghost\\ghost.bin").c_str(), D3DCOLOR_XRGB(0, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\cyclops\\cyclops.bin").c_str(), D3DCOLOR_XRGB(255, 255, 255));
	CAnimationManager::GetInstance()->LoadAnimationsFromFile((char *)CGame::GetInstance()->GraphicsPath("units\\colossus\\colossus.bin").c_str(), D3DCOLOR_XRGB(255, 255, 255));

	// Do all our loading
	if(m_nLevelNum == 1)
	{
		CWorldManager::GetInstance()->Load("Resource//Graphics//Intro Level Take 2.mfl");

		CMarine* alliedMarine = new CMarine();
		CHeavy*  alliedHeavy  = new CHeavy();
		CMedic*  alliedMedic  = new CMedic();
		CScout*  alliedScout  = new CScout();

		//alliedMarine->Inventory()->push_back(BookOfHaste);
		//BookOfHaste->Collect(alliedMarine);

		CMovementControl::GetInstance()->SetPlayerUnits(alliedMarine, alliedHeavy, alliedScout, alliedMedic);

		alliedMarine->PosX(50);
		alliedMarine->PosY(50);
		alliedHeavy->PosX(150);
		alliedHeavy->PosY(50);
		alliedScout->PosX(150);
		alliedScout->PosY(150);
		alliedMedic->PosX(50);
		alliedMedic->PosY(150);

		CBasicEnemy* badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1700);
		badGuy->PosY(200);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1600);
		badGuy->PosY(230);
		CObjectManager::GetInstance()->AddObject(badGuy);


		CBasicEnemy* FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
		FElemental->Type(CBase::OBJ_ENEMY);
		FElemental->PosX(1800);
		FElemental->PosY(200);
		CObjectManager::GetInstance()->AddObject(FElemental);

		FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
		FElemental->Type(CBase::OBJ_ENEMY);
		FElemental->PosX(1800);
		FElemental->PosY(260);
		CObjectManager::GetInstance()->AddObject(FElemental);

		FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
		FElemental->Type(CBase::OBJ_ENEMY);
		FElemental->PosX(1860);
		FElemental->PosY(230);
		CObjectManager::GetInstance()->AddObject(FElemental);

		//////////////////////////////////////////////////////////////////////////

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1600);
		badGuy->PosY(900);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1700);
		badGuy->PosY(930);
		CObjectManager::GetInstance()->AddObject(badGuy);


		FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
		FElemental->Type(CBase::OBJ_ENEMY);
		FElemental->PosX(1500);
		FElemental->PosY(900);
		CObjectManager::GetInstance()->AddObject(FElemental);

		FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
		FElemental->Type(CBase::OBJ_ENEMY);
		FElemental->PosX(1500);
		FElemental->PosY(960);
		CObjectManager::GetInstance()->AddObject(FElemental);

		FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
		FElemental->Type(CBase::OBJ_ENEMY);
		FElemental->PosX(1560);
		FElemental->PosY(930);
		CObjectManager::GetInstance()->AddObject(FElemental);
	}

	if(m_nLevelNum == 2)
	{
		CWorldManager::GetInstance()->Load("Resource//Graphics//Level 2.mfl");

		CMarine* alliedMarine = CMovementControl::GetInstance()->Marine();
		CHeavy*  alliedHeavy  = CMovementControl::GetInstance()->Heavy();
		CMedic*  alliedMedic  = CMovementControl::GetInstance()->Medic();
		CScout*  alliedScout  = CMovementControl::GetInstance()->Scout();

		alliedMarine->PosX(50);
		alliedMarine->PosY(50);
		alliedHeavy->PosX(150);
		alliedHeavy->PosY(50);
		alliedScout->PosX(150);
		alliedScout->PosY(150);
		alliedMedic->PosX(50);
		alliedMedic->PosY(150);

		CBasicEnemy* badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1600);
		badGuy->PosY(230);
		CObjectManager::GetInstance()->AddObject(badGuy);
	}
	
	CGame::GetInstance()->ChangeState( CGamePlayState::GetInstance() );
}

void CLoadLevelState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0,0,0);
	CSGD_Direct3D::GetInstance()->DeviceBegin();
	CSGD_Direct3D::GetInstance()->SpriteBegin();

	CSGD_TextureManager::GetInstance()->Draw(m_nMenuBG, 0, 0, 1.0f, 1.0f);
	// Loading Bar
	RECT loadRect;
	loadRect.left = 0;
	loadRect.top = 0;
	loadRect.right = (LONG) ((m_fPercentage / 100.0f) * 642.0f);
	loadRect.bottom = 64;
	
	CSGD_TextureManager::GetInstance()->Draw(m_nLoadBar, 399, 671, 1.0f, 1.0f, &loadRect);

	CMovementControl::GetInstance()->RenderCursor();
	char* buffer = new char[50];
	char* loadBuffer = new char[50];
	char load1[] = "Initializing Maps";
	char load2[] = "Generating Pathing Data";
	char load3[] = "Generating MORE Pathing Data";
	char loadDone[] = "Done!";
	if(m_fPercentage < 50.0f)
		sprintf_s(loadBuffer, 50, "%s", load1);
	else if(m_fPercentage < 75.0f)
		sprintf_s(loadBuffer, 50, "%s", load2);
	else if(m_fPercentage < 100.0f)
		sprintf_s(loadBuffer, 50, "%s", load3);
	else
		sprintf_s(loadBuffer, 50, "%s", loadDone);

	sprintf_s(buffer, 50, "%0.2f %%", m_fPercentage);
	m_ftText.RenderText(buffer, 400, 640);
	m_ftText.RenderText(loadBuffer, 720, 640);
	delete[] buffer;
	delete[] loadBuffer;
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	CSGD_Direct3D::GetInstance()->DeviceEnd();
	CSGD_Direct3D::GetInstance()->Present();
}

void CLoadLevelState::Exit(void)
{
	CGamePlayState::GetInstance()->SetLevel( m_nLevelNum );
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuBG);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nLoadBar);
}