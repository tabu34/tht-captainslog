#include "precompiled_header.h"
#include "CMedic.h"
#include "CAbilities.h"

CMedic::CMedic()
{
	Type(OBJ_PLAYER);
	SubType(PLAYER_MEDIC);
	PosX(0);
	PosY(0);
	VelX(0);
	VelY(0);
	Width(64);
	Height(64);
	CurHealth(90);
	MaxHealth(90);
	AttackSpeed(2);
	AttackDamage(15);
	AttackTimer(0);
	AttackRange(125);
	SightRange(AttackRange() + 100);
	Armor(20);


	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medic-Walk-N"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medic-Walk-NE"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medic-Walk-E"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medic-Walk-SE"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medic-Walk-S"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medic-Idle"));
	Animations()->push_back(CAnimationManager::GetInstance()->GetAnimationID("Medic-Fire"));

	Abilities()->push_back(new CAbility_DefensiveMatrix());
	Abilities()->push_back(new CAbility_Refresh());
}

void CMedic::Initialize()
{

}

void CMedic::Update( float fElapsedTime )
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

void CMedic::Attack(float fElapsedTime)
{
	if (Target()->Type() != OBJ_PLAYER)
	{
		if (Target()->CurHealth() <= 0)
		{
			State(1);
			Destination((LONG)PosX(), (LONG)PosY());
		}
		else if (fabs(((PosX() - Target()->PosX()) * (PosX() - Target()->PosX()) +
			(PosY() - Target()->PosY()) * (PosY() - Target()->PosY()))) > (AttackRange() * AttackRange()))
		{
			State(2);
		}
		else
		{
			if (FireLineTime() <= 0)
			{
				State(3);
			}
			AttackTimer(AttackTimer() + fElapsedTime);
			if (AttackTimer() >= AttackSpeed())
			{
				if (Target()->Invulnerable() == false)
				{
					Target()->CurHealth(Target()->CurHealth() - (int)(AttackDamage() - (AttackDamage() * Target()->Armor() * 0.01f)));
				}
				AttackTimer(0);
				FireLineTime(0.2f);
				State(4);
			}
		}
	} 
	else
	{
		if (Target()->CurHealth() <= 0)
		{
			State(1);
			Destination((LONG)PosX(), (LONG)PosY());
		}
		else if (fabs(((PosX() - Target()->PosX()) * (PosX() - Target()->PosX()) +
			(PosY() - Target()->PosY()) * (PosY() - Target()->PosY()))) > (AttackRange() * AttackRange()))
		{
			State(2);
		}
		else
		{
			if (FireLineTime() <= 0)
			{
				State(3);
			}
			AttackTimer(AttackTimer() + fElapsedTime);
			if (AttackTimer() >= AttackSpeed())
			{
				Target()->CurHealth(Target()->CurHealth() + (int)(AttackDamage()));
				AttackTimer(0);
				FireLineTime(0.2f);
				State(4);
			}
		}
	}
}

void CMedic::Render()
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
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f);
	}
}
