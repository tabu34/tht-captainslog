#include "precompiled_header.h"
#include "CMedic.h"

void CMedic::Update( float fElapsedTime )
{

}

void CMedic::Initialize()
{

}

void CMedic::Render()
{
	CUnit::Render();
	bool flipped = false;

	if (State() == 0)
	{
		switch (CurDirection())
		{
		case 0:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.CurFrame(0);
			break;
		case 1:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.CurFrame(1);
			break;
		case 2:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.CurFrame(2);
			break;
		case 3:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.CurFrame(3);
			break;
		case 4:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.CurFrame(4);
			break;
		case 5:
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.CurFrame(3);
			break;
		case 6:
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.CurFrame(2);
			break;
		case 7:
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.CurFrame(1);
			break;
		}
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
	}
	else if (State() == 1 || State() == 2)
	{
		switch (CurDirection())
		{
		case 0:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[0])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[0])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
			break;
		case 1:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
			break;
		case 2:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
			break;
		case 3:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
			break;
		case 4:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[4])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[4])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
			break;
		case 5:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Play();
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
			break;
		case 6:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Play();
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
			break;
		case 7:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Play();
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
			break;
		}
	}
	else if (State() == 3)
	{
		switch (CurDirection())
		{
		case 0:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.CurFrame(0);
			break;
		case 1:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.CurFrame(1);
			break;
		case 2:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.CurFrame(2);
			break;
		case 3:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.CurFrame(3);
			break;
		case 4:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.CurFrame(4);
			break;
		case 5:
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.CurFrame(3);
			break;
		case 6:
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.CurFrame(2);
			break;
		case 7:
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.CurFrame(1);
			break;
		}
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
	}
}
