#include "precompiled_header.h"
#include "CPlayerUnit.h"

void CPlayerUnit::Initialize()
{

}

void CPlayerUnit::Update( float fElapsedTime )
{
	CUnit::Update(fElapsedTime);

	//int closestDistance = INT_MAX;
	//int currentObjDistance;
	//int sightRangeSqrd = SightRange() * SightRange();


	//currentObjDistance = DistanceSquared((int)CMovementControl::GetInstance()->Marine()->PosX(), (int)CMovementControl::GetInstance()->Marine()->PosY());
	//if (currentObjDistance < sightRangeSqrd)
	//{
	//	if (currentObjDistance < closestDistance)
	//	{
	//		closestDistance = currentObjDistance;
	//		Target(CMovementControl::GetInstance()->Marine());
	//	}
	//}

	//currentObjDistance = DistanceSquared((int)CMovementControl::GetInstance()->Medic()->PosX(), (int)CMovementControl::GetInstance()->Medic()->PosY());
	//if (currentObjDistance < sightRangeSqrd)
	//{
	//	if (currentObjDistance < closestDistance)
	//	{
	//		closestDistance = currentObjDistance;
	//		Target(CMovementControl::GetInstance()->Medic());
	//	}
	//}

	//currentObjDistance = DistanceSquared((int)CMovementControl::GetInstance()->Heavy()->PosX(), (int)CMovementControl::GetInstance()->Heavy()->PosY());
	//if (currentObjDistance < sightRangeSqrd)
	//{
	//	if (currentObjDistance < closestDistance)
	//	{
	//		closestDistance = currentObjDistance;
	//		Target(CMovementControl::GetInstance()->Heavy());
	//	}
	//}

	//currentObjDistance = DistanceSquared((int)CMovementControl::GetInstance()->Scout()->PosX(), (int)CMovementControl::GetInstance()->Scout()->PosY());
	//if (currentObjDistance < sightRangeSqrd && !CMovementControl::GetInstance()->Scout()->Cloaked())
	//{
	//	if (currentObjDistance < closestDistance)
	//	{
	//		closestDistance = currentObjDistance;
	//		Target(CMovementControl::GetInstance()->Scout());
	//	}
	//}

	//if (Target() != NULL && State() != UNIT_ATTACK && State() != UNIT_FIRE)
	//{
	//	State(UNIT_MOVING_ATTACK);
	//}


	//CUnit::Update(fElapsedTime);


	//if(VelX() == 0.0f && VelY() < 0.0f)
	//{
	//	CurDirection(0);
	//} 
	//else if(VelX() > 0.0f && VelY() < 0.0f)
	//{
	//	CurDirection(1);
	//} 
	//else if(VelX() > 0.0f && VelY() == 0.0f)
	//{
	//	CurDirection(2);
	//} 
	//else if(VelX() > 0.0f && VelY() > 0.0f)
	//{
	//	CurDirection(3);
	//} 
	//else if(VelX() == 0.0f && VelY() > 0.0f)
	//{
	//	CurDirection(4);
	//} 
	//else if(VelX() < 0.0f && VelY() > 0.0f)
	//{
	//	CurDirection(5);
	//} 
	//else if(VelX() < 0.0f && VelY() == 0.0f)
	//{
	//	CurDirection(6);
	//} 
	//else if(VelX() < 0.0f && VelY() < 0.0f)
	//{
	//	CurDirection(7);
	//}

	//if (CurDirection() < 5)
	//{
	//	CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection()])->anAnimation.Update(fElapsedTime);
	//}
	//else if (CurDirection() == 5)
	//{
	//	CAnimationManager::GetInstance()->GetAnimation((*Animations())[3])->anAnimation.Update(fElapsedTime);
	//}
	//else if (CurDirection() == 6)
	//{
	//	CAnimationManager::GetInstance()->GetAnimation((*Animations())[2])->anAnimation.Update(fElapsedTime);
	//}
	//else
	//{
	//	CAnimationManager::GetInstance()->GetAnimation((*Animations())[1])->anAnimation.Update(fElapsedTime);
	//}

}
