#include "precompiled_header.h"
#include "MovementControl.h"
#include "CObjectManager.h"
#include "CCamera.h"
#include "..\CGame.h"
#include "..\SGD Wrappers\CSGD_Direct3D.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\Managers\CWorldManager.h"
#include "..\GameObjects\CUnit.h"
#include "..\States\CGamePlayState.h"
#include "..\GameObjects\CAbilities.h"
#include "..\GameObjects\CMarine.h"
#include "..\GameObjects\CMedic.h"
#include "..\GameObjects\CScout.h"
#include "..\GameObjects\CHeavy.h"


CMovementControl* CMovementControl::GetInstance()
{
	static CMovementControl instance;
	return &instance;
}

void CMovementControl::Init()
{
	m_vObjectList = CObjectManager::GetInstance()->GetObjectList();
	m_vSelected = CObjectManager::GetInstance()->GetSelectedList();
	m_DI = CSGD_DirectInput::GetInstance();
	m_cCAM = CGame::GetInstance()->GetCamera();

	m_bDragging = false;
	m_ptStart.x = CMovementControl::GetInstance()->MousePosX();
	m_ptStart.y = CMovementControl::GetInstance()->MousePosY();
	m_nCursorImageID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource\\Graphics\\gameCursor.png");
	CSGD_DirectInput::GetInstance()->MouseSetPosX(100);
	CSGD_DirectInput::GetInstance()->MouseSetPosY(100);
	m_bCommand=false;
}

void CMovementControl::Input()
{
	if(CGamePlayState::GetInstance()->CurrentCommand()!="")
		m_bCommand=true;

	// Update Mouse Pos


	if(MousePosX() < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosX(0);

	if(MousePosX() >CGame::GetInstance()->GetScreenWidth())
		CSGD_DirectInput::GetInstance()->MouseSetPosX(CGame::GetInstance()->GetScreenWidth());

	if(MousePosY() < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosY(0);

	if(MousePosY() > CGame::GetInstance()->GetScreenHeight())
		CSGD_DirectInput::GetInstance()->MouseSetPosY(CGame::GetInstance()->GetScreenHeight());

	// TODO: Mouse Input

	if(m_DI->MouseButtonPressed(MOUSE_RIGHT))
	{
		int nTarget;

		for(unsigned int i = 0; i < m_vSelected->size(); i++)
		{
			nTarget = -1;

			RECT mouseRect = {0, 0, 0, 0};
			mouseRect.left = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosX() + CGame::GetInstance()->GetCamera()->GetX());
			mouseRect.top = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosY() + CGame::GetInstance()->GetCamera()->GetY());
			mouseRect.right = mouseRect.left + 1;
			mouseRect.bottom = mouseRect.top +1;

			RECT hudRect = CGamePlayState::GetInstance()->GetButtons()[CGamePlayState::GetInstance()->FindButton("BottomHUD")].GetCollisionRect();

			RECT resultRect;

			if (IntersectRect(&resultRect, &mouseRect, &hudRect))
			{
				return;
			}

			for (unsigned int j = 0; j < m_vObjectList->size(); j++)
			{
				if (IntersectRect(&resultRect, &mouseRect, &((*m_vObjectList)[j]->GetCollisionRect())))
				{
					nTarget = j;
				}
			}
			if (nTarget != -1 && ((*m_vObjectList)[nTarget]->Type() == CBase::OBJ_ENEMY || (*m_vObjectList)[nTarget]->Type() == CBase::OBJ_PLAYER))
			{
				if (((*m_vObjectList)[nTarget]->Type() == CBase::OBJ_ENEMY || ((*m_vObjectList)[nTarget]->Type() == CBase::OBJ_PLAYER && ((CPlayerUnit*)(*m_vSelected)[0])->SubType() == CUnit::PLAYER_MEDIC)))
				{
					((CUnit*)(*m_vSelected)[i])->OrderAttack((CUnit*)(*m_vObjectList)[nTarget]);
				}
			}
			else if (nTarget != -1 && (*m_vObjectList)[nTarget]->Type() == CBase::OBJ_ITEM && 
				((*m_vObjectList)[nTarget]->PosX() - (*m_vSelected)[i]->PosX()) * 
				((*m_vObjectList)[nTarget]->PosX() - (*m_vSelected)[i]->PosX()) + 
				((*m_vObjectList)[nTarget]->PosY() - (*m_vSelected)[i]->PosY()) * 
				((*m_vObjectList)[nTarget]->PosY() - (*m_vSelected)[i]->PosY()) < ITEM_RANGE * ITEM_RANGE
				) 
			{
				if (((CItem*)(*m_vObjectList)[nTarget])->Collect((CUnit*)(*m_vSelected)[i]))
				{
					(*m_vObjectList).erase((*m_vObjectList).begin() + nTarget);
				}

			}
			else
			{
				((CUnit*)(*m_vSelected)[i])->VelX(0.0f);
				((CUnit*)(*m_vSelected)[i])->VelY(0.0f);
				((CUnit*)(*m_vSelected)[i])->OrderMove(mouseRect.left, mouseRect.top);
			}
		}
		//m_esEventSystem->SendEvent("LeftMouseButtonPressed");
	}

	if(CGamePlayState::GetInstance()->CurrentCommand()=="HoldOrder")
	{
		for(size_t i=0; i<m_vSelected->size(); i++)
		{
			(((CUnit*)(*m_vSelected)[i])->State(CUnit::UNIT_IDLE));
		}
		CGamePlayState::GetInstance()->ClearCommand();
		return;
	}

	if(CGamePlayState::GetInstance()->CurrentCommand()=="cooldown_cheat")
	{
		//select all PLAYER units
		for(size_t i=0; i<m_vObjectList->size(); i++)
		{
			if(((CUnit*)(*m_vObjectList)[i])->Type()==CBase::OBJ_PLAYER)
			{
				if(!((CUnit*)(*m_vObjectList)[i])->Selected())
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(true);
					(*m_vSelected).push_back((*m_vObjectList)[i]);
				}
			}
			else if(((CUnit*)(*m_vObjectList)[i])->Selected())
			{
				((CUnit*)(*m_vObjectList)[i])->Selected(false);
				CObjectManager::GetInstance()->FindAndRemove((CUnit*)(*m_vObjectList)[i]);
			}
		}

		for(size_t i=0; i<m_vSelected->size(); i++)
		{
			CUnit* pGuy = ((CUnit*)(*m_vSelected)[i]);
			for(size_t j=0; j<pGuy->Abilities()->size(); j++)
			{
				((CAbility*)(*pGuy->Abilities())[j])->Cooldown(0.0f);
			}
		}
		CGamePlayState::GetInstance()->ClearCommand();
		return;
	}

	if(CGamePlayState::GetInstance()->CurrentCommand()=="stats_cheat")
	{
		//select all PLAYER units
		for(size_t i=0; i<m_vObjectList->size(); i++)
		{
			if(((CUnit*)(*m_vObjectList)[i])->Type()==CBase::OBJ_PLAYER)
			{
				if(!((CUnit*)(*m_vObjectList)[i])->Selected())
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(true);
					(*m_vSelected).push_back((*m_vObjectList)[i]);
				}
			}
			else if(((CUnit*)(*m_vObjectList)[i])->Selected())
			{
				((CUnit*)(*m_vObjectList)[i])->Selected(false);
				CObjectManager::GetInstance()->FindAndRemove((CUnit*)(*m_vObjectList)[i]);
			}
		}

		for(size_t i=0; i<m_vSelected->size(); i++)
		{
			CUnit* pGuy = ((CUnit*)(*m_vSelected)[i]);
			pGuy->Armor(pGuy->Armor()+10);
			pGuy->AttackDamage(pGuy->AttackDamage()+10.0f);
			pGuy->AttackRange(pGuy->AttackRange()+10);
			pGuy->AttackSpeed(pGuy->AttackSpeed()*0.9f);
			pGuy->MaxHealth(pGuy->MaxHealth()+10);
			pGuy->CurHealth(pGuy->MaxHealth());
		}
		CGamePlayState::GetInstance()->ClearCommand();
		return;
	}

	if(CGamePlayState::GetInstance()->CurrentCommand()=="speed_cheat")
	{
		//select all PLAYER units
		for(size_t i=0; i<m_vObjectList->size(); i++)
		{
			if(((CUnit*)(*m_vObjectList)[i])->Type()==CBase::OBJ_PLAYER)
			{
				if(!((CUnit*)(*m_vObjectList)[i])->Selected())
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(true);
					(*m_vSelected).push_back((*m_vObjectList)[i]);
				}
			}
			else if(((CUnit*)(*m_vObjectList)[i])->Selected())
			{
				((CUnit*)(*m_vObjectList)[i])->Selected(false);
				CObjectManager::GetInstance()->FindAndRemove((CUnit*)(*m_vObjectList)[i]);
			}
		}

		for(size_t i=0; i<m_vSelected->size(); i++)
		{
			CUnit* pGuy = ((CUnit*)(*m_vSelected)[i]);
			pGuy->MovementSpeed(pGuy->MovementSpeed() * 1.5f);
		}
		CGamePlayState::GetInstance()->ClearCommand();
		return;
	}

	if(m_DI->MouseButtonPressed(MOUSE_LEFT) && CGamePlayState::GetInstance()->CurrentCommand() != "")
	{
		if(CGamePlayState::GetInstance()->CurrentCommand()=="MoveOrder")
		{
			for(size_t i = 0; i<m_vSelected->size(); i++)
			{
				((CUnit*)(*m_vSelected)[i])->OrderMove(MousePosX() + (int)CGame::GetInstance()->GetCamera()->GetX(), MousePosY() + (int)CGame::GetInstance()->GetCamera()->GetY());
			}
			CGamePlayState::GetInstance()->ClearCommand();
			return;
		}
		else if(CGamePlayState::GetInstance()->CurrentCommand() == "AttackOrder")
		{
			int nTarget;

			for(unsigned int i = 0; i < m_vSelected->size(); i++)
			{
				nTarget = -1;

				RECT mouseRect = {0, 0, 0, 0};
				mouseRect.left = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosX() + CGame::GetInstance()->GetCamera()->GetX());
				mouseRect.top = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosY() + CGame::GetInstance()->GetCamera()->GetY());
				mouseRect.right = mouseRect.left + 1;
				mouseRect.bottom = mouseRect.top + 1;

				RECT resultRect;

				for (unsigned int j = 0; j < m_vObjectList->size(); j++)
				{
					if (IntersectRect(&resultRect, &mouseRect, &((*m_vObjectList)[j]->GetCollisionRect())))
					{
						nTarget = j;
					}
				}
				if (nTarget != -1)
				{
					((CUnit*)(*m_vSelected)[i])->OrderAttack((CUnit*)(*m_vObjectList)[nTarget]);
					CGamePlayState::GetInstance()->ClearCommand();
				}
			}
			return;
		}
		else if (CGamePlayState::GetInstance()->CurrentCommand() == "Ability")
		{
			if (m_pUnitAbilitySelection == NULL || m_pUnitAbilitySelection->CurHealth() <= 0)
			{
				return;
			}
			if ((*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition] == NULL)
			{
				return;
			}

			if ((*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition]->Type() == 0)
			{
				(*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition]->Activate();
				CGamePlayState::GetInstance()->ClearCommand();
			}
			else if ((*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition]->Type() == 1)
			{
				RECT mouseRect = {0, 0, 0, 0};
				mouseRect.left = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosX() + CGame::GetInstance()->GetCamera()->GetX());
				mouseRect.top = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosY() + CGame::GetInstance()->GetCamera()->GetY());
				mouseRect.right = mouseRect.left + 1;
				mouseRect.bottom = mouseRect.top + 1;

				RECT resultRect;

				int nTarget = -1;

				for (unsigned int i = 0; i < m_vObjectList->size(); i++)
				{
					if (IntersectRect(&resultRect, &mouseRect, &((*m_vObjectList)[i]->GetCollisionRect())))
					{
						nTarget = i;
						break;
					}
				}

				if (nTarget == -1)
				{
					return;
				}

				((CTargetAbility*)((*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition]))->Target((CUnit*)((*m_vObjectList)[nTarget]));
				(*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition]->Activate();
				CGamePlayState::GetInstance()->ClearCommand();
			}
			else if ((*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition]->Type() == 2)
			{
				((CLocationAbility*)((*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition]))->Location(MousePosX() + (int)CGame::GetInstance()->GetCamera()->GetX(), MousePosY() + (int)CGame::GetInstance()->GetCamera()->GetY());
				(*m_pUnitAbilitySelection->Abilities())[m_nUnitAbilityPosition]->Activate();
				CGamePlayState::GetInstance()->ClearCommand();
			}
		}
	}

	if(m_DI->MouseButtonPressed(MOUSE_LEFT) && CGamePlayState::GetInstance()->CurrentCommand() == "" && !m_bCommand)
	{
		if (m_ptStart.x	== CSGD_DirectInput::GetInstance()->MouseGetPosX() && m_ptStart.y == CSGD_DirectInput::GetInstance()->MouseGetPosY())
		{
			RECT mouseRect = {0, 0, 0, 0};
			mouseRect.left = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosX() + CGame::GetInstance()->GetCamera()->GetX());
			mouseRect.top = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosY() + CGame::GetInstance()->GetCamera()->GetY());
			mouseRect.right = mouseRect.left + 1;
			mouseRect.bottom = mouseRect.top + 1;





			bool bSelectedOne = false;

			for(unsigned int i = 0; i < m_vObjectList->size(); i++)
			{
				RECT collide;
				RECT collisionRect = (*m_vObjectList)[i]->GetCollisionRect();
				if(bSelectedOne == false && IntersectRect(&collide, &mouseRect, &collisionRect))
				{
					if(!((CUnit*)(*m_vObjectList)[i])->Selected())	// If not selected
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(true);
						(*m_vSelected).push_back( (*m_vObjectList)[i] );
						bSelectedOne = true;
					}
				} 
				else
				{
					if( ((CUnit*)(*m_vObjectList)[i])->Selected() )	// If selected
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(false);
						CObjectManager::GetInstance()->FindAndRemove( (CUnit*)(*m_vObjectList)[i] );
					}
				}
			}



		}
	}

	RECT mouseRect = {0, 0, 0, 0};
	mouseRect.left = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosX() + CGame::GetInstance()->GetCamera()->GetX());
	mouseRect.top = LONG((float)CSGD_DirectInput::GetInstance()->MouseGetPosY() + CGame::GetInstance()->GetCamera()->GetY());
	mouseRect.right = mouseRect.left + 1;
	mouseRect.bottom = mouseRect.top +1;

	RECT hudRect = CGamePlayState::GetInstance()->GetButtons()[CGamePlayState::GetInstance()->FindButton("BottomHUD")].GetCollisionRect();
	RECT resultRect;

	if (!IntersectRect(&resultRect, &mouseRect, &hudRect))
	{
		if (CGamePlayState::GetInstance()->CurrentCommand()=="" && !m_bCommand)
		{
			if(m_DI->MouseButtonDown(MOUSE_LEFT))
			{
				// Unit Selection ---------------
				if(m_bDragging == false)
				{
					m_bDragging = true;
					m_ptStart.x = CSGD_DirectInput::GetInstance()->MouseGetPosX();
					m_ptStart.y = CSGD_DirectInput::GetInstance()->MouseGetPosY();
				}
				// END Unit Selection -----------
	
				//m_esEventSystem->SendEvent("RightMouseButtonPressed");
			} 
			else 
			{
				m_bDragging = false;
			}
		}
	}
	

	//UNIT SELECTION (KEYBOARD)
	if(m_DI->KeyPressed(CGame::GetInstance()->KeyBinds(CGame::KEY_UNIT1)))
	{
		//select the MARINE
		for(size_t i=0; i<m_vObjectList->size(); i++)
		{
			if ((*m_vObjectList)[i]->Type() != CBase::OBJ_ITEM)
			{
				if((*m_vObjectList)[i] == m_pMarine)
				{
					if(!((CUnit*)(*m_vObjectList)[i])->Selected())
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(true);
						(*m_vSelected).push_back((*m_vObjectList)[i]);
						CGamePlayState::GetInstance()->ClearCommand();
					}
				}
				else if(((CUnit*)(*m_vObjectList)[i])->Selected())
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(false);
					CObjectManager::GetInstance()->FindAndRemove((CUnit*)(*m_vObjectList)[i]);
				}
			}

		}
	}
	if(m_DI->KeyPressed(CGame::GetInstance()->KeyBinds(CGame::KEY_UNIT2)))
	{
		//select the HEAVY
		for(size_t i=0; i<m_vObjectList->size(); i++)
		{
			if ((*m_vObjectList)[i]->Type() != CBase::OBJ_ITEM)
			{
				if((*m_vObjectList)[i] == m_pHeavy)
				{
					if(!((CUnit*)(*m_vObjectList)[i])->Selected())
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(true);
						(*m_vSelected).push_back((*m_vObjectList)[i]);
						CGamePlayState::GetInstance()->ClearCommand();
					}
				}
				else if(((CUnit*)(*m_vObjectList)[i])->Selected())
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(false);
					CObjectManager::GetInstance()->FindAndRemove((CUnit*)(*m_vObjectList)[i]);
				}
			}
		}
	}
	if(m_DI->KeyPressed(CGame::GetInstance()->KeyBinds(CGame::KEY_UNIT3)))
	{
		//select the MEDIC
		for(size_t i=0; i<m_vObjectList->size(); i++)
		{
			if ((*m_vObjectList)[i]->Type() != CBase::OBJ_ITEM)
			{
				if((*m_vObjectList)[i] == m_pMedic)
				{
					if(!((CUnit*)(*m_vObjectList)[i])->Selected())
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(true);
						(*m_vSelected).push_back((*m_vObjectList)[i]);
						CGamePlayState::GetInstance()->ClearCommand();
					}
				}
				else if(((CUnit*)(*m_vObjectList)[i])->Selected())
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(false);
					CObjectManager::GetInstance()->FindAndRemove((CUnit*)(*m_vObjectList)[i]);
				}
			}
		}
	}
	if(m_DI->KeyPressed(CGame::GetInstance()->KeyBinds(CGame::KEY_UNIT4)))
	{
		//select the SCOUT
		for(size_t i=0; i<m_vObjectList->size(); i++)
		{
			if ((*m_vObjectList)[i]->Type() != CBase::OBJ_ITEM)
			{
				if((*m_vObjectList)[i] == m_pScout)
				{
					if(!((CUnit*)(*m_vObjectList)[i])->Selected())
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(true);
						(*m_vSelected).push_back((*m_vObjectList)[i]);
						CGamePlayState::GetInstance()->ClearCommand();
					}
				}
				else if(((CUnit*)(*m_vObjectList)[i])->Selected())
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(false);
					CObjectManager::GetInstance()->FindAndRemove((CUnit*)(*m_vObjectList)[i]);
				}
			}
		}
	}
	if(m_DI->KeyPressed(CGame::GetInstance()->KeyBinds(CGame::KEY_ALLUNIT)))
	{
		//select all PLAYER units
		for(size_t i=0; i<m_vObjectList->size(); i++)
		{
			if ((*m_vObjectList)[i]->Type() != CBase::OBJ_ITEM)
			{
				if(((CUnit*)(*m_vObjectList)[i])->Type()==CBase::OBJ_PLAYER)
				{
					if(!((CUnit*)(*m_vObjectList)[i])->Selected())
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(true);
						(*m_vSelected).push_back((*m_vObjectList)[i]);
						CGamePlayState::GetInstance()->ClearCommand();
					}
				}
				else if(((CUnit*)(*m_vObjectList)[i])->Selected())
				{
					((CUnit*)(*m_vObjectList)[i])->Selected(false);
					CObjectManager::GetInstance()->FindAndRemove((CUnit*)(*m_vObjectList)[i]);
				}
			}
		}
	}

	//Ability Keybinds
	if (m_DI->KeyPressed(CGame::GetInstance()->KeyBinds(CGame::KEY_ABILITY1)))
	{
		if ((*GetSelectedUnits()).size() < 1 || ((CUnit*)(*GetSelectedUnits())[0])->Type() != CUnit::OBJ_PLAYER)
		{
			return;
		}
		if((*((CUnit*)((*GetSelectedUnits())[0]))->Abilities())[0]->Type() == 0)
		{
			(*((CUnit*)((*GetSelectedUnits())[0]))->Abilities())[0]->Activate();
		}
		else
		{
			CGamePlayState::GetInstance()->SetCommand("Ability");
			SetUnit((CUnit*)((*GetSelectedUnits())[0]));
			SetPosition(0);
		}
	}
	if (m_DI->KeyPressed(CGame::GetInstance()->KeyBinds(CGame::KEY_ABILITY2)))
	{
		if ((*GetSelectedUnits()).size() < 1 || ((CUnit*)(*GetSelectedUnits())[0])->Type() != CUnit::OBJ_PLAYER)
		{
			return;
		}
		if((*((CUnit*)((*GetSelectedUnits())[0]))->Abilities())[1]->Type() == 0)
		{
			(*((CUnit*)((*GetSelectedUnits())[0]))->Abilities())[1]->Activate();
		}
		else
		{
			CGamePlayState::GetInstance()->SetCommand("Ability");
			SetUnit((CUnit*)((*GetSelectedUnits())[0]));
			SetPosition(1);
		}
	}

	float fSpeed = 1000;
	//CAMERA CONTROL (KEYBOARD)
	if(m_DI->KeyDown(CGame::GetInstance()->KeyBinds(CGame::KEY_LEFT)))
	{
		//CGame::GetInstance()->GetCamera()->SetX( CGame::GetInstance()->GetCamera()->GetX() - fSpeed );
		CGame::GetInstance()->GetCamera()->VelX(-fSpeed);
		if(CGame::GetInstance()->GetCamera()->GetX() < 0.0f)
			CGame::GetInstance()->GetCamera()->SetX( 0.0f );
		//m_esEventSystem->SendEvent("LeftKeyPressed");
	}

	if(m_DI->KeyDown(CGame::GetInstance()->KeyBinds(CGame::KEY_RIGHT)))
	{
		//CGame::GetInstance()->GetCamera()->SetX( CGame::GetInstance()->GetCamera()->GetX() + fSpeed );
		CGame::GetInstance()->GetCamera()->VelX(fSpeed);
		if(CGame::GetInstance()->GetCamera()->GetX() > CWorldManager::GetInstance()->WorldWidth() - CGame::GetInstance()->GetScreenWidth() )
			CGame::GetInstance()->GetCamera()->SetX( float(CWorldManager::GetInstance()->WorldWidth() - CGame::GetInstance()->GetScreenWidth()) );
		//m_esEventSystem->SendEvent("RightKeyPressed");
	}

		if(m_DI->KeyDown(CGame::GetInstance()->KeyBinds(CGame::KEY_UP)))
		{
			//CGame::GetInstance()->GetCamera()->SetY( CGame::GetInstance()->GetCamera()->GetY() - fSpeed );
			CGame::GetInstance()->GetCamera()->VelY(-fSpeed);
			if(CGame::GetInstance()->GetCamera()->GetY() < 0.0f)
				CGame::GetInstance()->GetCamera()->SetY( 0.0f );
			//m_esEventSystem->SendEvent("UpKeyPressed");
		}

	if(m_DI->KeyDown(CGame::GetInstance()->KeyBinds(CGame::KEY_DOWN)))
	{
		//CGame::GetInstance()->GetCamera()->SetY( CGame::GetInstance()->GetCamera()->GetY() + fSpeed );
		CGame::GetInstance()->GetCamera()->VelY(fSpeed);
		if(CGame::GetInstance()->GetCamera()->GetY() > CWorldManager::GetInstance()->WorldHeight() - CGame::GetInstance()->GetScreenHeight())
			CGame::GetInstance()->GetCamera()->SetY( float(CWorldManager::GetInstance()->WorldHeight() - CGame::GetInstance()->GetScreenHeight()));
		//m_esEventSystem->SendEvent("DownKeyPressed");
	}

	if(m_DI->MouseButtonUp(0) && CGamePlayState::GetInstance()->CurrentCommand()=="")
		m_bCommand=false;
}
void CMovementControl::Shutdown()
{
	
}

void CMovementControl::CheckDragRect()
{
	if(m_bDragging)
	{
		RECT dragRect;
		dragRect.left = m_ptStart.x + (LONG)CGame::GetInstance()->GetCamera()->GetX();
		dragRect.top = m_ptStart.y + (LONG)CGame::GetInstance()->GetCamera()->GetY();
		dragRect.right = LONG((float)CMovementControl::GetInstance()->MousePosX() + CGame::GetInstance()->GetCamera()->GetX());
		dragRect.bottom = LONG((float)CMovementControl::GetInstance()->MousePosY() + CGame::GetInstance()->GetCamera()->GetY());

		if(dragRect.right < dragRect.left)
			swap(dragRect.left, dragRect.right);

		if(dragRect.bottom < dragRect.top)
			swap(dragRect.top, dragRect.bottom);

		for(unsigned int i = 0; i < m_vObjectList->size(); i++)
		{
			if (m_vObjectList->operator [](i)->Type() != CBase::OBJ_ITEM)
			{
				RECT collide;
				RECT collisionRect = (*m_vObjectList)[i]->GetCollisionRect();
				if(IntersectRect(&collide, &dragRect, &collisionRect))
				{
					if(!((CUnit*)(*m_vObjectList)[i])->Selected())	// If not selected
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(true);
						(*m_vSelected).push_back( (*m_vObjectList)[i] );
					}
				} 
				else
				{
					if( ((CUnit*)(*m_vObjectList)[i])->Selected() )	// If selected
					{
						((CUnit*)(*m_vObjectList)[i])->Selected(false);
						CObjectManager::GetInstance()->FindAndRemove( (CUnit*)(*m_vObjectList)[i] );
					}
				}
			}
		}
	}
}

void CMovementControl::RenderDragRect()
{
	if(m_bDragging)
	{
		RECT dragRect;
		dragRect.left = m_ptStart.x;
		dragRect.top = m_ptStart.y;
		dragRect.right = CMovementControl::GetInstance()->MousePosX();
		dragRect.bottom = CMovementControl::GetInstance()->MousePosY();

		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.left, dragRect.top, dragRect.right, dragRect.top, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.right, dragRect.top, dragRect.right, dragRect.bottom, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.right, dragRect.bottom, dragRect.left, dragRect.bottom, 0, 255, 0);
		CSGD_Direct3D::GetInstance()->DrawLine(dragRect.left, dragRect.bottom, dragRect.left, dragRect.top, 0, 255, 0);
	}
}	

void CMovementControl::RenderCursor()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nCursorImageID, CSGD_DirectInput::GetInstance()->MouseGetPosX(), CSGD_DirectInput::GetInstance()->MouseGetPosY(), 0.75f, 0.75f);
}

void CMovementControl::UpdateCamera( float fElapsedTime )
{
	m_cCAM->Update(fElapsedTime);


	int nBuffer		= 5;
	float nSpeed	= 2000;

	RECT rCameraBounds;
	SetRect(&rCameraBounds, 0, 0, CWorldManager::GetInstance()->WorldWidth(), CWorldManager::GetInstance()->WorldHeight());

	m_cCAM->VelX(0);
	m_cCAM->VelY(0);

	if (CSGD_DirectInput::GetInstance()->MouseGetPosX() < nBuffer)
	{
		m_cCAM->VelX(-nSpeed);
	}
	else if (CSGD_DirectInput::GetInstance()->MouseGetPosX() > + CGame::GetInstance()->GetScreenWidth() - nBuffer)
		m_cCAM->VelX(nSpeed);

	if (CSGD_DirectInput::GetInstance()->MouseGetPosY() < nBuffer)
		m_cCAM->VelY(-nSpeed);
	else if (CSGD_DirectInput::GetInstance()->MouseGetPosY() > CGame::GetInstance()->GetScreenHeight() - nBuffer)
		m_cCAM->VelY(nSpeed);




 	if (m_cCAM->GetX() < rCameraBounds.left)
 	{
 		m_cCAM->SetX((float)rCameraBounds.left);
 		m_cCAM->VelX(0);
 	}
 	else if (m_cCAM->GetX() + CGame::GetInstance()->GetScreenWidth() > rCameraBounds.right)
 	{
 		m_cCAM->SetX((float)(rCameraBounds.right - CGame::GetInstance()->GetScreenWidth()));
 		m_cCAM->VelX(0);
 	}
 
 	if (m_cCAM->GetY() < rCameraBounds.top)
 	{
 		m_cCAM->SetY((float)rCameraBounds.top);
 		m_cCAM->VelY(0);
 	}
 	else if (m_cCAM->GetY() + CGame:: GetInstance()->GetScreenHeight() > rCameraBounds.bottom)
 	{
 		m_cCAM->SetY((float)(rCameraBounds.bottom - CGame::GetInstance()->GetScreenHeight()));
 		m_cCAM->VelY(0);
 	}


}
