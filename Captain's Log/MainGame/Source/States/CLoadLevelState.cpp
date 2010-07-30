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
#include "..\GameObjects\CPassive.h"
#include "..\GameObjects\CItemFactory.h"
#include "CGameWinState.h"
#include "..\GameObjects\CBossEnemies.h"
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

		CItem* testItem = CItemFactory::GetInstance()->CreateItem("Book of Haste");
		testItem->PosX(500);
		testItem->PosY(500);
		CObjectManager::GetInstance()->AddObject(testItem);

		testItem = CItemFactory::GetInstance()->CreateItem("Book of Protection");
		testItem->PosX(550);
		testItem->PosY(500);
		CObjectManager::GetInstance()->AddObject(testItem);

		
		testItem = CItemFactory::GetInstance()->CreateItem("Gloves of Haste");
		testItem->PosX(1500);
		testItem->PosY(1800);
		CObjectManager::GetInstance()->AddObject(testItem);

		
		testItem = CItemFactory::GetInstance()->CreateItem("Boots of Swiftness");
		testItem->PosX(1600);
		testItem->PosY(1850);
		CObjectManager::GetInstance()->AddObject(testItem);


		CBasicEnemy* badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1300);
		badGuy->PosY(1550);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1407);
		badGuy->PosY(1650);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1402);
		badGuy->PosY(1550);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1300);
		badGuy->PosY(1650);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(2850);
		badGuy->PosY(450);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(2950);
		badGuy->PosY(430);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(2830);
		badGuy->PosY(570);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(2950);
		badGuy->PosY(580);
		CObjectManager::GetInstance()->AddObject(badGuy);

		CBasicEnemy* Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1200);
		Cyclops->PosY(250);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1350);
		Cyclops->PosY(306);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1240);
		Cyclops->PosY(400);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1300);
		Cyclops->PosY(450);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1150);
		Cyclops->PosY(2800);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1276);
		Cyclops->PosY(2760);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1380);
		Cyclops->PosY(2790);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1120);
		Cyclops->PosY(2890);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1250);
		Cyclops->PosY(2920);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(1380);
		Cyclops->PosY(2860);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		CBasicEnemy* Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(2200);
		Colossus->PosY(1000);
		CObjectManager::GetInstance()->AddObject(Colossus);

		Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(2100);
		Colossus->PosY(950);
		CObjectManager::GetInstance()->AddObject(Colossus);

		Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(2300);
		Colossus->PosY(950);
		CObjectManager::GetInstance()->AddObject(Colossus);




		CBossEnemy* Medusa = (CBossEnemy*)CUnitFactory::GetInstance()->CreateUnit("Medusa");
		Medusa->Type(CBase::OBJ_ENEMY);
		Medusa->PosX(2830);
		Medusa->PosY(2860);
		CObjectManager::GetInstance()->AddObject(Medusa);

		//////////////////////////////////////////////////////////////////////////
		CGame::GetInstance()->ChangeState( CGamePlayState::GetInstance() );
	}

	if(m_nLevelNum == 2)
	{
		//for(unsigned int i = 0; i < CObjectManager::GetInstance()->GetObjectList()->size(); i++)
		//{
		//	if((*CObjectManager::GetInstance()->GetObjectList())[i]->Type() != CBase::OBJ_PLAYER)
		//		CObjectManager::GetInstance()->GetObjectList()->erase( CObjectManager::GetInstance()->GetObjectList()->begin() + i-- );
		//}

		CObjectManager::GetInstance()->RemoveAllObjects();

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

		CItem * testItem = CItemFactory::GetInstance()->CreateItem("Boots of Swiftness");
		testItem->PosX(1500);
		testItem->PosY(1850);
		CObjectManager::GetInstance()->AddObject(testItem);

		testItem = CItemFactory::GetInstance()->CreateItem("Book of Strength");
		testItem->PosX(1500);
		testItem->PosY(1950);
		CObjectManager::GetInstance()->AddObject(testItem);

		testItem = CItemFactory::GetInstance()->CreateItem("Book of Vitality");
		testItem->PosX(800);
		testItem->PosY(1200);
		CObjectManager::GetInstance()->AddObject(testItem);

		testItem = CItemFactory::GetInstance()->CreateItem("Book of Strength");
		testItem->PosX(800);
		testItem->PosY(1250);
		CObjectManager::GetInstance()->AddObject(testItem);

		CBasicEnemy* badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(500);
		badGuy->PosY(700);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(600);
		badGuy->PosY(900);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(580);
		badGuy->PosY(1060);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(690);
		badGuy->PosY(1250);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1300);
		badGuy->PosY(2100);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1450);
		badGuy->PosY(2000);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1390);
		badGuy->PosY(1800);
		CObjectManager::GetInstance()->AddObject(badGuy);

		badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Shade");
		badGuy->Type(CBase::OBJ_ENEMY);
		badGuy->PosX(1350);
		badGuy->PosY(1700);
		CObjectManager::GetInstance()->AddObject(badGuy);

		CBasicEnemy* Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(700);
		Cyclops->PosY(200);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(700);
		Cyclops->PosY(1800);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(750);
		Cyclops->PosY(2000);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		Cyclops->Type(CBase::OBJ_ENEMY);
		Cyclops->PosX(850);
		Cyclops->PosY(2100);
		CObjectManager::GetInstance()->AddObject(Cyclops);

		CBasicEnemy* Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(650);
		Colossus->PosY(400);
		CObjectManager::GetInstance()->AddObject(Colossus);

		Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(1350);
		Colossus->PosY(1200);
		CObjectManager::GetInstance()->AddObject(Colossus);

		Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(1400);
		Colossus->PosY(1100);
		CObjectManager::GetInstance()->AddObject(Colossus);

		Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(1800);
		Colossus->PosY(500);
		CObjectManager::GetInstance()->AddObject(Colossus);

		Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(1750);
		Colossus->PosY(420);
		CObjectManager::GetInstance()->AddObject(Colossus);

		Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		Colossus->Type(CBase::OBJ_ENEMY);
		Colossus->PosX(1950);
		Colossus->PosY(500);
		CObjectManager::GetInstance()->AddObject(Colossus);

		CBossEnemy* Mage = (CBossEnemy*)CUnitFactory::GetInstance()->CreateUnit("Mage");
		Mage->Type(CBase::OBJ_ENEMY);
		Mage->PosX(2200);
		Mage->PosY(1500);
		CObjectManager::GetInstance()->AddObject(Mage);

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

		//CBasicEnemy* Cyclops = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Cyclops");
		//Cyclops->Type(CBase::OBJ_ENEMY);
		//Cyclops->PosX(700);
		//Cyclops->PosY(200);
		//CObjectManager::GetInstance()->AddObject(Cyclops);

		//CBasicEnemy* Colossus = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Colossus");
		//Colossus->Type(CBase::OBJ_ENEMY);
		//Colossus->PosX(650);
		//Colossus->PosY(400);
		//CObjectManager::GetInstance()->AddObject(Colossus);

		CItem * testItem = CItemFactory::GetInstance()->CreateItem("Shield of Angels");
		testItem->PosX(750);
		testItem->PosY(1200);
		CObjectManager::GetInstance()->AddObject(testItem);

		testItem = CItemFactory::GetInstance()->CreateItem("Gloves of Haste");
		testItem->PosX(750);
		testItem->PosY(1250);
		CObjectManager::GetInstance()->AddObject(testItem);

		testItem = CItemFactory::GetInstance()->CreateItem("Book of Vitality");
		testItem->PosX(800);
		testItem->PosY(1200);
		CObjectManager::GetInstance()->AddObject(testItem);

		testItem = CItemFactory::GetInstance()->CreateItem("Book of Strength");
		testItem->PosX(800);
		testItem->PosY(1250);
		CObjectManager::GetInstance()->AddObject(testItem);


		CBossEnemy* Medusa = (CBossEnemy*)CUnitFactory::GetInstance()->CreateUnit("Medusa");
		Medusa->Type(CBase::OBJ_ENEMY);
		Medusa->PosX(900);
		Medusa->PosY(400);
		CObjectManager::GetInstance()->AddObject(Medusa);
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