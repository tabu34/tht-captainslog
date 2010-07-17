#include "precompiled_header.h"
#include "CPlayerUnit.h"

void CPlayerUnit::Initialize()
{

}

void CPlayerUnit::Update( float fElapsedTime )
{
	int closestDistance = INT_MAX;
	int currentObjDistance;
	int sightRangeSqrd = AttackRange() * AttackRange();

	if (!UNIT_MOVING_ATTACK)
		Target(NULL);

	if (!Selected())
	{
		for (unsigned int i = 0; i < CCollisionManager::GetInstance()->Enemies()->size(); i++)
		{
			currentObjDistance = DistanceSquared(int((*CCollisionManager::GetInstance()->Enemies())[i]->PosX()), int((*CCollisionManager::GetInstance()->Enemies())[i]->PosY()));
			if (currentObjDistance < sightRangeSqrd)
			{
				if (currentObjDistance < closestDistance)
				{
					closestDistance = currentObjDistance;
					Target((CUnit*)(*CCollisionManager::GetInstance()->Enemies())[i]);
				}
			}
		}
		if (Target() != NULL && State() != UNIT_ATTACK && State() != UNIT_FIRE)
		{
			State(UNIT_ATTACK);
		}
	}

//	if(!Selected())



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

	CUnit::Update(fElapsedTime);



}
