#include "precompiled_header.h"
#include "CScout.h"
#include "CAbilities.h"

CScout::CScout()
{
	Type(OBJ_PLAYER);
	SubType(PLAYER_SCOUT);
	PosX(0);
	PosY(0);
	VelX(0);
	VelY(0);
	Width(32);
	Height(32);
	CurHealth(80);
	MaxHealth(80);
	AttackSpeed(3);
	AttackDamage(60);
	AttackTimer(0);
	AttackRange(250);
	SightRange(AttackRange() + 100);
	Armor(15);
	Cloaked(false);

	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-N"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-NE"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-E"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-SE"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Walk-S"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Idle"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Ghost-Fire"));

	Abilities()->push_back(new CAbility_Cloak(this));
	Abilities()->push_back(new CAbility_PinningShot());
}

void CScout::Update( float fElapsedTime )
{
	CPlayerUnit::Update(fElapsedTime);

	if(VelX() == 0.0f && VelY() < 0.0f)
	{
		CurDirection(0);
	} 
	else if(VelX() > 0.0f && VelY() < 0.0f)
	{
		CurDirection(1);
	} 
	else if(VelX() > 0.0f && VelY() == 0.0f)
	{
		CurDirection(2);
	} 
	else if(VelX() > 0.0f && VelY() > 0.0f)
	{
		CurDirection(3);
	} 
	else if(VelX() == 0.0f && VelY() > 0.0f)
	{
		CurDirection(4);
	} 
	else if(VelX() < 0.0f && VelY() > 0.0f)
	{
		CurDirection(5);
	} 
	else if(VelX() < 0.0f && VelY() == 0.0f)
	{
		CurDirection(6);
	} 
	else if(VelX() < 0.0f && VelY() < 0.0f)
	{
		CurDirection(7);
	}

	if (CurDirection() < 5)
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection()])->anAnimation.Update(fElapsedTime);
	}
	else if (CurDirection() == 5)
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Update(fElapsedTime);
	}
	else if (CurDirection() == 6)
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Update(fElapsedTime);
	}
	else
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Update(fElapsedTime);
	}

}

void CScout::Initialize()
{

}

void CScout::Render()
{
	CUnit::Render();
	bool flipped = false;

	if (State() == 0 || State() == 3)
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
		if (Cloaked())
		{
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, D3DCOLOR_ARGB(128, 255, 255, 255));
		}
		else
		{
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
		}	
	}
	else if (State() == 1 || State() == 2)
	{
		int nAnim = -1;
		switch (CurDirection())
		{
		case 0:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[0])->anAnimation.Play();
			nAnim = 0;
			break;
		case 1:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Play();
			nAnim = 1;
			break;
		case 2:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Play();
			nAnim = 2;
			break;
		case 3:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Play();
			nAnim = 3;
			break;
		case 4:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[4])->anAnimation.Play();
			nAnim = 4;
			break;
		case 5:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Play();
			flipped = true;
			nAnim = 3;
			break;
		case 6:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Play();
			flipped = true;
			nAnim = 2;
			break;
		case 7:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Play();
			flipped = true;
			nAnim = 1;
			break;
		}
		if (Cloaked())
		{
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[nAnim])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, D3DCOLOR_ARGB(128, 255, 255, 255));
		}
		else
		{
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[nAnim])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
		}
	}
	else if (State() == 4)
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
		if (Cloaked())
		{
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, D3DCOLOR_ARGB(128, 255, 255, 255));
		}
		else
		{
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
		}
	}
}
