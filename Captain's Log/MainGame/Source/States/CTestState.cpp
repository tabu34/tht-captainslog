#include "precompiled_header.h"
#include "CTestState.h"
#include "CGamePlayState.h"
#include "..\Managers\CCollisionManager.h"
#include "..\GameObjects\CMarine.h"
#include "..\GameObjects\CAnimationManager.h"
#include "..\CGame.h"
#include "..\Managers\MovementControl.h"
#include "..\Managers\CWorldManager.h"

CTestState::CTestState(void)
{

}

CTestState::~CTestState(void)
{

}

CTestState* CTestState::GetInstance()
{
	static CTestState instance;
	return &instance;
}

void CTestState::Enter(void)
{
 	m_nBackgroundID = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("cptLogMainMenu.png").c_str());
 
	CMessageSystem::GetInstance()->InitMessageSystem(CTestState::MessageProc);

 	Marine1.PosX(300);
 	Marine1.PosY(300);
 	Marine1.Width(50);
 	Marine1.Height(50);
 	Marine1.MovementSpeed(5);
	Marine1.AttackRange(250);
	Marine1.AttackSpeed(2);
	Marine1.AttackDamage(2);
	Marine1.MaxHealth(10);
	Marine1.CurHealth(10);
 
 	Marine2.PosX(400);
 	Marine2.PosY(400);
 	Marine2.Width(50);
	Marine2.Height(50);
	Marine2.MovementSpeed(5);
	Marine2.AttackRange(250);
	Marine2.AttackSpeed(2);
	Marine2.AttackDamage(2);
	Marine2.MaxHealth(10);
	Marine2.CurHealth(10);

	temporaryBlocker.PosX(float(500 + (CGame::GetInstance()->GetScreenWidth() >> 1)));
	temporaryBlocker.PosY(float(100 + (CGame::GetInstance()->GetScreenHeight() >> 1)));
	temporaryBlocker.Width(100);
	temporaryBlocker.Height(CGame::GetInstance()->GetScreenHeight() - 200);
	temporaryBlocker.MovementSpeed(0);
	temporaryBlocker.Type(CBase::OBJ_OBSTACLE);

	testEnemy.PosX(500);
	testEnemy.PosY(550);
	testEnemy.Width(50);
	testEnemy.Height(50);
	testEnemy.MovementSpeed(5);
	testEnemy.MaxHealth(10);
	testEnemy.CurHealth(10);
	testEnemy.Type(CBase::OBJ_ENEMY);

	CGame::GetInstance()->GetCamera()->SetX(0.0f);
	CGame::GetInstance()->GetCamera()->SetY(0.0f);
 
 	CAnimationManager::GetInstance()->LoadAnimationsFromFile("Resource\\Graphics\\test.bin", D3DCOLOR_ARGB(255, 0, 0, 0));
 	CAnimationManager::GetInstance()->GetAnimation("Untitled Animation")->anAnimation.Play();
	CObjectManager::GetInstance()->AddObject(&Marine1);
	CObjectManager::GetInstance()->AddObject(&Marine2);
	CObjectManager::GetInstance()->AddObject(&temporaryBlocker);
	CObjectManager::GetInstance()->AddObject(&testEnemy);

	CWorldManager::GetInstance()->Load("Resource\\Graphics\\test.mfl");
 
 
 	testFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1, 1, 3, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(0, 255, 0));
 	testFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	
}

bool CTestState::Input(void)
{
	
 	CMovementControl::GetInstance()->Input();
 
 	if (CSGD_DirectInput::GetInstance()->KeyDown(DIK_DOWNARROW))
 		Marine1.PosY(Marine1.PosY() + Marine1.MovementSpeed());
 	if (CSGD_DirectInput::GetInstance()->KeyDown(DIK_UPARROW))
 		Marine1.PosY(Marine1.PosY() - Marine1.MovementSpeed());
 	if (CSGD_DirectInput::GetInstance()->KeyDown(DIK_LEFTARROW))
 		Marine1.PosX(Marine1.PosX() - Marine1.MovementSpeed());
 	if (CSGD_DirectInput::GetInstance()->KeyDown(DIK_RIGHTARROW))
 		Marine1.PosX(Marine1.PosX() + Marine1.MovementSpeed());

	if (CSGD_DirectInput::GetInstance()->KeyDown(DIK_1))
		CGame::GetInstance()->ChangeState( CGamePlayState::GetInstance() );

	
	return true;
}

void CTestState::Update(float fElapsedTime)
{
	
 	CCollisionManager::GetInstance()->RunCollisions();
 	CAnimationManager::GetInstance()->GetAnimation("Untitled Animation")->anAnimation.Update(fElapsedTime);
	CMovementControl::GetInstance()->CheckDragRect();
	CObjectManager::GetInstance()->UpdateObjects(fElapsedTime);
	CMessageSystem::GetInstance()->ProcessMessages();
}

void CTestState::Render(void)
{
	
 	//CSGD_TextureManager::GetInstance()->Draw(m_nBackgroundID, 0, 0, 0.75f, 0.75f);
	CWorldManager::GetInstance()->Render();

 	CAnimationManager::GetInstance()->GetAnimation("Untitled Animation")->anAnimation.Render(150,150);
 	CSGD_Direct3D::GetInstance()->SpriteEnd();
 	CSGD_Direct3D::GetInstance()->SpriteBegin();
	CObjectManager::GetInstance()->RenderObjects();
 	CMovementControl::GetInstance()->RenderDragRect();
 	CMovementControl::GetInstance()->RenderCursor();
 
 	testFont.RenderText("Hello", 300, 300);
	
}

void CTestState::Exit(void)
{
	CObjectManager::GetInstance()->RemoveAllObjects();
 	CAnimationManager::GetInstance()->Shutdown();
	
}

void CTestState::MessageProc(CBaseMessage* pMSG)
{
	switch (pMSG->GetMsgID())
	{
	case MSG_DESTROY_UNIT:
		CUnitDeathMessage* udMSG = (CUnitDeathMessage*)pMSG;

		CObjectManager::GetInstance()->RemoveObject(udMSG->GetUnit());
	}
}