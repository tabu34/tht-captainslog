#include "precompiled_header.h"
#include "CBasicEnemies.h"
#include "..\Managers\MovementControl.h"
#include "CMarine.h"
#include "CMedic.h"
#include "CScout.h"
#include "CHeavy.h"

CBasicEnemy::CBasicEnemy()
{
	SubType(ENEMY_BASIC);

}

void CBasicEnemy::Update( float fElapsedTime )
{
	int closestDistance = INT_MAX;
	int currentObjDistance;
	int sightRangeSqrd = SightRange() * SightRange();
	bool found = false;

	Target(NULL);


	for (unsigned int i = 0; i < CCollisionManager::GetInstance()->Players()->size(); i++)
	{
		currentObjDistance = DistanceSquared(int((*CCollisionManager::GetInstance()->Players())[i]->PosX()), int((*CCollisionManager::GetInstance()->Players())[i]->PosY()));

		if (currentObjDistance < sightRangeSqrd)
		{
			if (currentObjDistance < closestDistance)
			{
				closestDistance = currentObjDistance;
				Target((CUnit*)(*CCollisionManager::GetInstance()->Players())[i]);
				found = true;
			}
		}
	}


	//currentObjDistance = DistanceSquared((int)CMovementControl::GetInstance()->Marine()->PosX(), (int)CMovementControl::GetInstance()->Marine()->PosY());
	//if (currentObjDistance < sightRangeSqrd)
	//{
	//	if (currentObjDistance < closestDistance)
	//	{
	//		closestDistance = currentObjDistance;
	//		Target(CMovementControl::GetInstance()->Marine());
	//		found = true;
	//	}
	//}

	//currentObjDistance = DistanceSquared((int)CMovementControl::GetInstance()->Medic()->PosX(), (int)CMovementControl::GetInstance()->Medic()->PosY());
	//if (currentObjDistance < sightRangeSqrd)
	//{
	//	if (currentObjDistance < closestDistance)
	//	{
	//		closestDistance = currentObjDistance;
	//		Target(CMovementControl::GetInstance()->Medic());
	//		found = true;
	//	}
	//}

	//currentObjDistance = DistanceSquared((int)CMovementControl::GetInstance()->Heavy()->PosX(), (int)CMovementControl::GetInstance()->Heavy()->PosY());
	//if (currentObjDistance < sightRangeSqrd)
	//{
	//	if (currentObjDistance < closestDistance)
	//	{
	//		closestDistance = currentObjDistance;
	//		Target(CMovementControl::GetInstance()->Heavy());
	//		found = true;
	//	}
	//}

	//currentObjDistance = DistanceSquared((int)CMovementControl::GetInstance()->Scout()->PosX(), (int)CMovementControl::GetInstance()->Scout()->PosY());
	//if (currentObjDistance < sightRangeSqrd && !CMovementControl::GetInstance()->Scout()->Cloaked())
	//{
	//	if (currentObjDistance < closestDistance)
	//	{
	//		closestDistance = currentObjDistance;
	//		Target(CMovementControl::GetInstance()->Scout());
	//		found = true;
	//	}
	//}
	if (!found)
		State(UNIT_IDLE);

	if (Target() != NULL && State() != UNIT_ATTACK && State() != UNIT_FIRE)
	{
		State(UNIT_MOVING_ATTACK);
	}


	CUnit::Update(fElapsedTime);


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

void CBasicEnemy::Render()
{
	CUnit::Render();
	bool flipped = false;
	DWORD dwColor = D3DCOLOR_XRGB(255, 0, 0);

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
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[5])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
	}
	else if (State() == 1 || State() == 2)
	{
		switch (CurDirection())
		{
		case 0:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[0])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[0])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
			break;
		case 1:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
			break;
		case 2:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
			break;
		case 3:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
			break;
		case 4:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[4])->anAnimation.Play();
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[4])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
			break;
		case 5:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Play();
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
			break;
		case 6:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Play();
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
			break;
		case 7:
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Play();
			flipped = true;
			CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
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
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[6])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), flipped, 2.0f, dwColor);
	}

}