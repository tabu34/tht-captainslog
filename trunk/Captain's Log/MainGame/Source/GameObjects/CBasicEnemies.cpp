#include "precompiled_header.h"
#include "CBasicEnemies.h"
#include "..\Managers\MovementControl.h"
#include "CMarine.h"
#include "CMedic.h"
#include "CScout.h"
#include "CHeavy.h"
#include "../States/CGamePlayState.h"

CBasicEnemy::CBasicEnemy()
{
	SubType(ENEMY_BASIC);
	SetMirrored(true);
	Stuck(false);
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
		if (((CUnit*)(*CCollisionManager::GetInstance()->Players())[i])->Cloaked())
		{
			continue;
		}

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

	if (!found)
	{
		State(UNIT_IDLE);
	}

	if (Target() != NULL && State() != UNIT_ATTACK && State() != UNIT_FIRE)
	{
		State(UNIT_MOVING_ATTACK);
	}


	CUnit::Update(fElapsedTime);

	if ((*Animations()).size() == 7)
	{
		Update7(fElapsedTime);
	}
	else
	{
		Update16(fElapsedTime);
	}
}

void CBasicEnemy::Update7(float fElapsedTime)
{
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

	if (m_bMirrored)
	{
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
	else
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection()])->anAnimation.Update(fElapsedTime);
	}
}

void CBasicEnemy::Update16(float fElapsedTime)
{
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
	if (State() < 3)
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection()])->anAnimation.Update(fElapsedTime);
	}
	else
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection() + 7])->anAnimation.Update(fElapsedTime);
	}
}

void CBasicEnemy::Render()
{
	CUnit::Render();

	if ((*Animations()).size() == 7)
	{
		Render7();
	}
	else
	{
		Render16();
	}
}

void CBasicEnemy::Render7()
{
	bool flipped = false;
	DWORD dwColor = D3DCOLOR_XRGB(255, 0, 0);

	// Selection Cirle
	if(Selected())
		CSGD_TextureManager::GetInstance()->Draw(CGamePlayState::GetInstance()->GetSelectionCircleID(), (int)PosX() - ((int)PosX() / 2) + (int)CGame::GetInstance()->GetCamera()->GetX(), int(PosY()) - 16 - (int)CGame::GetInstance()->GetCamera()->GetY(), 1.0f, 1.0f,0,0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0));

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

void CBasicEnemy::Render16()
{
	if(Selected() || State() == 3)
		CSGD_TextureManager::GetInstance()->Draw(CGamePlayState::GetInstance()->GetSelectionCircleID(), int((PosX()) - 32 - CGame::GetInstance()->GetCamera()->GetX()), int(PosY() - 16 - CGame::GetInstance()->GetCamera()->GetY()), 1.0f, 1.0f,0,0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0));
	if (State() == 0)
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection()])->anAnimation.CurFrame(0);
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection()])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), false, 0.75f);
	}
	else if (State() == 1 || State() == 2)
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection()])->anAnimation.Play();
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection()])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), false, 0.75f);
	}
	else if (State() == 3 || State() == 4)
	{
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection() + 7])->anAnimation.Play();
		CAnimationManager::GetInstance()->GetAnimation((*Animations())[CurDirection() + 7])->anAnimation.Render((int)PosX() - (int)CGame::GetInstance()->GetCamera()->GetX(), (int)PosY() - (int)CGame::GetInstance()->GetCamera()->GetY(), false, 0.75f);
	}
}