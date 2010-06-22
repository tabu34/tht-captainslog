#include "precompiled_header.h"
#include "CTestState.h"
#include "..\Managers\CCollisionManager.h"
#include "..\GameObjects\CMarine.h"
#include "..\GameObjects\CAnimationManager.h"
#include "..\CGame.h"
#include "..\Managers\MovementControl.h"

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
 
 	Marine1.PosX(300);
 	Marine1.PosY(300);
 	Marine1.Width(50);
 	Marine1.Height(50);
 	Marine1.MovementSpeed(5);
 
 	Marine2.PosX(400);
 	Marine2.PosY(400);
 	Marine2.Width(50);
 	Marine2.Height(50);
 	Marine2.MovementSpeed(5);
 
 	CAnimationManager::GetInstance()->LoadAnimationsFromFile("C:\\Users\\Preston Stoll\\Desktop\\test.bin");
 	CAnimationManager::GetInstance()->GetAnimation("Untitled Animation")->anAnimation.Play();
 	CCollisionManager::GetInstance()->AddObject(&Marine1);
 	CCollisionManager::GetInstance()->AddObject(&Marine2);
 
 
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

	return true;
}

void CTestState::Update(float fElapsedTime)
{
 	CCollisionManager::GetInstance()->RunCollisions();
 	CAnimationManager::GetInstance()->GetAnimation("Untitled Animation")->anAnimation.Update(fElapsedTime);
}

void CTestState::Render(void)
{
 	CSGD_TextureManager::GetInstance()->Draw(m_nBackgroundID, 0, 0, 0.35f, 0.35f);
 	CAnimationManager::GetInstance()->GetAnimation("Untitled Animation")->anAnimation.Render(150,150);
 	CSGD_Direct3D::GetInstance()->SpriteEnd();
 	CSGD_Direct3D::GetInstance()->SpriteBegin();
 	CSGD_Direct3D::GetInstance()->DrawRect(Marine1.GetCollisionRect(), 255, 0, 0);
 	CSGD_Direct3D::GetInstance()->DrawRect(Marine2.GetCollisionRect(), 0, 255, 0);
 	CMovementControl::GetInstance()->RenderDragRect();
 	CMovementControl::GetInstance()->RenderCursor();
 
 	testFont.RenderText("Hello", 300, 300);
}

void CTestState::Exit(void)
{
 	CAnimationManager::GetInstance()->Shutdown();
}