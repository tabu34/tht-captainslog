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
#include "CGameWinState.h"
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
	// Do all our loading
	if(m_nLevelNum == 1)
	{
		CWorldManager::GetInstance()->Load("Resource//Graphics//lvl1.mfl");

		CMarine* alliedMarine = new CMarine();
		CHeavy*  alliedHeavy  = new CHeavy();
		CMedic*  alliedMedic  = new CMedic();
		CScout*  alliedScout  = new CScout();

		//alliedMarine->Inventory()->push_back(BookOfHaste);
		//BookOfHaste->Collect(alliedMarine);

		CMovementControl::GetInstance()->SetPlayerUnits(alliedMarine, alliedHeavy, alliedScout, alliedMedic);

		alliedMarine->PosX(50);
		alliedMarine->PosY(250);
		alliedHeavy->PosX(150);
		alliedHeavy->PosY(250);
		alliedScout->PosX(150);
		alliedScout->PosY(350);
		alliedMedic->PosX(50);
		alliedMedic->PosY(350);

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

		CBasicEnemy* Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(700);
		Cyclops->PosY(200);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		CBasicEnemy* Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(900);
		Colossus->PosY(200);
		CObjectManager::GetInstance()->AddObject(Colossus);


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

		CGame::GetInstance()->ChangeState( CGamePlayState::GetInstance() );
	}

	if(m_nLevelNum == 2)
	{

		CWorldManager::GetInstance()->Load("Resource//Graphics//lvl2.mfl");

		CMarine * alliedMarine = CMovementControl::GetInstance()->Marine();
		CHeavy* alliedHeavy = CMovementControl::GetInstance()->Heavy();
		CMedic* alliedMedic = CMovementControl::GetInstance()->Medic();
		CScout* alliedScout = CMovementControl::GetInstance()->Scout();

		alliedMarine->CurHealth(alliedMarine->MaxHealth());
		alliedHeavy->CurHealth(alliedHeavy->MaxHealth());
		alliedScout->CurHealth(alliedScout->MaxHealth());
		alliedMedic->CurHealth(alliedMedic->MaxHealth());
		
		alliedMarine->PosX(250);
		alliedMarine->PosY(50);
		alliedHeavy->PosX(250);
		alliedHeavy->PosY(150);
		alliedScout->PosX(350);
		alliedScout->PosY(50);
		alliedMedic->PosX(350);
		alliedMedic->PosY(150);

		CBasicEnemy* Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(700);
		Cyclops->PosY(200);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		CBasicEnemy* Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(650);
		Colossus->PosY(400);
		CObjectManager::GetInstance()->AddObject(Colossus);

		CGame::GetInstance()->ChangeState( CGamePlayState::GetInstance() );
		
	}
	
	if(m_nLevelNum == 3)
	{

		CWorldManager::GetInstance()->Load("Resource//Graphics//lvl3.mfl");

		CMarine * alliedMarine = CMovementControl::GetInstance()->Marine();
		CHeavy* alliedHeavy = CMovementControl::GetInstance()->Heavy();
		CMedic* alliedMedic = CMovementControl::GetInstance()->Medic();
		CScout* alliedScout = CMovementControl::GetInstance()->Scout();

		alliedMarine->CurHealth(alliedMarine->MaxHealth());
		alliedHeavy->CurHealth(alliedHeavy->MaxHealth());
		alliedScout->CurHealth(alliedScout->MaxHealth());
		alliedMedic->CurHealth(alliedMedic->MaxHealth());

		alliedMarine->PosX(250);
		alliedMarine->PosY(150);
		alliedHeavy->PosX(250);
		alliedHeavy->PosY(250);
		alliedScout->PosX(350);
		alliedScout->PosY(150);
		alliedMedic->PosX(350);
		alliedMedic->PosY(250);

		CBasicEnemy* Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(700);
		Cyclops->PosY(200);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		CBasicEnemy* Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(650);
		Colossus->PosY(400);
		CObjectManager::GetInstance()->AddObject(Colossus);
		//CGame::GetInstance()->
		
		CGame::GetInstance()->ChangeState( CGamePlayState::GetInstance() );
	}
	
	if(m_nLevelNum == 4)
	{
		CGame::GetInstance()->ChangeState( CGameWinState::GetInstance() );
	}
	
	
}

void CLoadLevelState::Render(void)
{
	CSGD_Direct3D::GetInstance()->Clear(0,0,0);
	CSGD_Direct3D::GetInstance()->DeviceBegin();
	CSGD_Direct3D::GetInstance()->SpriteBegin();

	CSGD_TextureManager::GetInstance()->Draw(CGame::GetInstance()->GetLoadBG(), 0, 0, 1.0f, 1.0f);
	// Loading Bar
	RECT loadRect;
	loadRect.left = 0;
	loadRect.top = 0;
	loadRect.right = (LONG) ((m_fPercentage / 100.0f) * 642.0f);
	loadRect.bottom = 64;
	
	CSGD_TextureManager::GetInstance()->Draw(CGame::GetInstance()->GetLoadBar(), 399, 671, 1.0f, 1.0f, &loadRect);

//	CMovementControl::GetInstance()->RenderCursor();
	char* buffer = new char[50];
	char* loadBuffer = new char[50];
	char load1[] = "Initializing Maps";
	char load2[] = "Generating Pathing Data";
	char load3[] = "Generating MORE Pathing Data";
	char loadDone[] = "Done!";
	if(m_fPercentage < 29.0f)
		sprintf_s(loadBuffer, 50, "%s", load1);
	else if(m_fPercentage < 68.0f)
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
}