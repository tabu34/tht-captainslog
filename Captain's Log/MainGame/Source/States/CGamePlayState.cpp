//////////////////////////////////////////////////////////////////////////////////////////////
//	File			:	"CGamePlayState.h"
//
//	Authors			:	Tim Smith, Daniel Makin
//
//	Purpose			:	To define the functionality of the Game Play game state
//////////////////////////////////////////////////////////////////////////////////////////////
#include "precompiled_header.h"
#include "CGamePlayState.h"
#include "..\CGame.h"
#include "..\GameObjects\CMarine.h"
#include "..\GameObjects\CHeavy.h"
#include "..\Managers\CWorldManager.h"
#include "CPauseMenuState.h"
#include "CSaveState.h"
#include "CGameOverState.h"
#include "CDebriefState.h"
#include "..\GameObjects\CMedic.h"
#include "..\GameObjects\CScout.h"
#include "..\GameObjects\CBasicEnemies.h"
#include "..\GameObjects\CAbilities.h"
#include "..\Managers\CUnitFactory.h"
#include "..\SGD Wrappers\CSGD_FModManager.h"
#include <fstream>
#include "..\GameObjects\CPassive.h"
#include "..\GameObjects\CItemFactory.h"
#include "..\States\CLoadLevelState.h"
using std::ifstream;

void ActivateAbilityOne();
void ActivateAbilityTwo();

CGamePlayState::CGamePlayState(void)
{

}

CGamePlayState::~CGamePlayState(void)
{

}

CGamePlayState* CGamePlayState::GetInstance()
{
	static CGamePlayState instance;
	return &instance;
}

void CGamePlayState::LoadProfile(int nOffsetInBytes)
{
	ifstream fin;

	std::string szPath = CGame::GetInstance()->ResourcePath();
	szPath += "Save.bin";
	fin.open(szPath.c_str(), ios_base::in | ios_base::binary);

	fin.seekg(nOffsetInBytes);

	int nNumUnits;
	fin.read((char*)&nNumUnits, sizeof(int));

	CMarine* pMar;
	CHeavy* pHeav;
	CMedic* pMed;
	CScout* pSco;

	CObjectManager::GetInstance()->RemoveAllObjects();
	for(int i=0; i<nNumUnits; i++)
	{
		tUnitSaveInfo tempUnitInfo;
		fin.read((char*)&tempUnitInfo, sizeof(tUnitSaveInfo));
		if(i==0) //marine
		{
			CMarine* pMarine = new CMarine();
			pMarine->Armor(tempUnitInfo.nArmor);
			pMarine->AttackDamage(tempUnitInfo.fAttackDamage);
			pMarine->AttackRange(tempUnitInfo.fAttackRange);
			pMarine->AttackSpeed(tempUnitInfo.fAttackSpeed);
			pMarine->HealthRegenRate(tempUnitInfo.nHealthRegenRate);
			pMarine->Burned(tempUnitInfo.bBurned);
			pMarine->Cloaked(tempUnitInfo.bCloaked);
			pMarine->CurHealth(tempUnitInfo.nCurHealth);
			pMarine->Invulnerable(tempUnitInfo.bInvulnerable);
			pMarine->MaxHealth(tempUnitInfo.nMaxHealth);
			pMarine->MovementSpeed(tempUnitInfo.fMovementSpeed);
			pMarine->PosX(tempUnitInfo.fPosX);
			pMarine->PosY(tempUnitInfo.fPosY);
			pMarine->SightRange(tempUnitInfo.nSightRange);
			pMarine->SubType(tempUnitInfo.nSubType);
			pMarine->Type(tempUnitInfo.nType);
			pMarine->Ranged(tempUnitInfo.bRanged);
			pMarine->Stunned(tempUnitInfo.bStunned);
			CObjectManager::GetInstance()->AddObject(pMarine);
			pMar = pMarine;
		}
		else if(i==1) //heavy
		{
			CHeavy* pMarine = new CHeavy();
			pMarine->Armor(tempUnitInfo.nArmor);
			pMarine->AttackDamage(tempUnitInfo.fAttackDamage);
			pMarine->AttackRange(tempUnitInfo.fAttackRange);
			pMarine->AttackSpeed(tempUnitInfo.fAttackSpeed);
			pMarine->HealthRegenRate(tempUnitInfo.nHealthRegenRate);
			pMarine->Burned(tempUnitInfo.bBurned);
			pMarine->Cloaked(tempUnitInfo.bCloaked);
			pMarine->CurHealth(tempUnitInfo.nCurHealth);
			pMarine->Invulnerable(tempUnitInfo.bInvulnerable);
			pMarine->MaxHealth(tempUnitInfo.nMaxHealth);
			pMarine->MovementSpeed(tempUnitInfo.fMovementSpeed);
			pMarine->PosX(tempUnitInfo.fPosX);
			pMarine->PosY(tempUnitInfo.fPosY);
			pMarine->SightRange(tempUnitInfo.nSightRange);
			pMarine->SubType(tempUnitInfo.nSubType);
			pMarine->Type(tempUnitInfo.nType);
			pMarine->Ranged(tempUnitInfo.bRanged);
			pMarine->Stunned(tempUnitInfo.bStunned);
			CObjectManager::GetInstance()->AddObject(pMarine);
			pHeav=pMarine;
		}
		else if(i==2)
		{
			CMedic* pMarine = new CMedic();
			pMarine->Armor(tempUnitInfo.nArmor);
			pMarine->AttackDamage(tempUnitInfo.fAttackDamage);
			pMarine->AttackRange(tempUnitInfo.fAttackRange);
			pMarine->AttackSpeed(tempUnitInfo.fAttackSpeed);
			pMarine->HealthRegenRate(tempUnitInfo.nHealthRegenRate);
			pMarine->Burned(tempUnitInfo.bBurned);
			pMarine->Cloaked(tempUnitInfo.bCloaked);
			pMarine->CurHealth(tempUnitInfo.nCurHealth);
			pMarine->Invulnerable(tempUnitInfo.bInvulnerable);
			pMarine->MaxHealth(tempUnitInfo.nMaxHealth);
			pMarine->MovementSpeed(tempUnitInfo.fMovementSpeed);
			pMarine->PosX(tempUnitInfo.fPosX);
			pMarine->PosY(tempUnitInfo.fPosY);
			pMarine->SightRange(tempUnitInfo.nSightRange);
			pMarine->SubType(tempUnitInfo.nSubType);
			pMarine->Type(tempUnitInfo.nType);
			pMarine->Ranged(tempUnitInfo.bRanged);
			pMarine->Stunned(tempUnitInfo.bStunned);
			CObjectManager::GetInstance()->AddObject(pMarine);
			pMed = pMarine;
		}
		else if(i==3)
		{
			CScout* pMarine = new CScout();
			pMarine->Armor(tempUnitInfo.nArmor);
			pMarine->AttackDamage(tempUnitInfo.fAttackDamage);
			pMarine->AttackRange(tempUnitInfo.fAttackRange);
			pMarine->AttackSpeed(tempUnitInfo.fAttackSpeed);
			pMarine->HealthRegenRate(tempUnitInfo.nHealthRegenRate);
			pMarine->Burned(tempUnitInfo.bBurned);
			pMarine->Cloaked(tempUnitInfo.bCloaked);
			pMarine->CurHealth(tempUnitInfo.nCurHealth);
			pMarine->Invulnerable(tempUnitInfo.bInvulnerable);
			pMarine->MaxHealth(tempUnitInfo.nMaxHealth);
			pMarine->MovementSpeed(tempUnitInfo.fMovementSpeed);
			pMarine->PosX(tempUnitInfo.fPosX);
			pMarine->PosY(tempUnitInfo.fPosY);
			pMarine->SightRange(tempUnitInfo.nSightRange);
			pMarine->SubType(tempUnitInfo.nSubType);
			pMarine->Type(tempUnitInfo.nType);
			pMarine->Ranged(tempUnitInfo.bRanged);
			pMarine->Stunned(tempUnitInfo.bStunned);
			CObjectManager::GetInstance()->AddObject(pMarine);
			pSco = pMarine;
		}
		else
		{
			//
			//
			//NOTE: VERY HACKED
			//TODO:  Make some way of reading in the type of enemy
			//
			CBasicEnemy* pMarine = (rand()%2==0) ? (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman") : (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
			pMarine->Armor(tempUnitInfo.nArmor);
			pMarine->AttackDamage(tempUnitInfo.fAttackDamage);
			pMarine->AttackRange(tempUnitInfo.fAttackRange);
			pMarine->AttackSpeed(tempUnitInfo.fAttackSpeed);
			pMarine->HealthRegenRate(tempUnitInfo.nHealthRegenRate);
			pMarine->Burned(tempUnitInfo.bBurned);
			pMarine->Cloaked(tempUnitInfo.bCloaked);
			pMarine->CurHealth(tempUnitInfo.nCurHealth);
			pMarine->Invulnerable(tempUnitInfo.bInvulnerable);
			pMarine->MaxHealth(tempUnitInfo.nMaxHealth);
			pMarine->MovementSpeed(tempUnitInfo.fMovementSpeed);
			pMarine->PosX(tempUnitInfo.fPosX);
			pMarine->PosY(tempUnitInfo.fPosY);
			pMarine->SightRange(tempUnitInfo.nSightRange);
			pMarine->SubType(tempUnitInfo.nSubType);
			pMarine->Type(tempUnitInfo.nType);
			pMarine->Ranged(tempUnitInfo.bRanged);
			pMarine->Stunned(tempUnitInfo.bStunned);
			CObjectManager::GetInstance()->AddObject(pMarine);
		}

	}
	CMovementControl::GetInstance()->SetPlayerUnits(pMar, pHeav, pSco, pMed);
	fin.close();
}

void CGamePlayState::Enter(void)
{
	CMessageSystem::GetInstance()->InitMessageSystem(CGamePlayState::MessageProc);

	InitHud();

	// Assets
	m_nGunshotSound = CSGD_FModManager::GetInstance()->LoadSound((char*)CGame::GetInstance()->SoundPath("\\THT_gunshoot.wav").c_str(), FMOD_LOOP_OFF);
	m_nMiniMap = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("minimap_lvl1.png").c_str());
	m_nSelectionCircle = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("selectionCircle.png").c_str());
	//LoadNextLevel();

	CObjectManager::GetInstance()->AddObject(CMovementControl::GetInstance()->Marine());
	CObjectManager::GetInstance()->AddObject(CMovementControl::GetInstance()->Heavy());
	CObjectManager::GetInstance()->AddObject(CMovementControl::GetInstance()->Scout());
	CObjectManager::GetInstance()->AddObject(CMovementControl::GetInstance()->Medic());


	// Test Speech
	m_nCurCount = 0;
	m_szSpeechText = "Destroy all enemies to \ncomplete the level...";

	// Camera
	CGame::GetInstance()->GetCamera()->SetX( 0.0f );
	CGame::GetInstance()->GetCamera()->SetY( 0.0f );

	// Cheats
	m_szCheatBuffer		= "                             ";
	m_bEnteringCheat	= false;
	m_bGodMode			= false;
	m_bNoCooldown		= false;

	// Tooltip Offset
	m_nToolTipOffsetY = 0;

	m_fTotalGameTime = 0.0f;

}

void CGamePlayState::Exit(void)
{

	for(unsigned int i = 0; i < m_vButtons.size(); i++)
	{
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_vButtons[i].TextureID());
	}

	m_vButtons.clear();

	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMiniMap);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSelectionCircle);
	CAnimationManager::GetInstance()->Shutdown();
	CObjectManager::GetInstance()->RemoveAllObjects();
	CSGD_FModManager::GetInstance()->StopSound(m_nGunshotSound);
}

bool CGamePlayState::Input(void)
{
	if(CheckButtonInput())
	{
		return true;
	}

	RECT mousePos, collide;
	mousePos.left	= CMovementControl::GetInstance()->MousePosX();
	mousePos.top	= CMovementControl::GetInstance()->MousePosY();
	mousePos.right	= mousePos.left + 1;
	mousePos.bottom	= mousePos.top + 1;

	RECT rMiniMap = {5, 690, 260, 896};
	
	if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0) && IntersectRect(&collide, &rMiniMap, &mousePos))
	{
		float fPercent;
		fPercent = (float)(mousePos.left - 5) / 255.0f;
		
		CGame::GetInstance()->GetCamera()->SetX(CWorldManager::GetInstance()->WorldWidth() * fPercent - (CGame::GetInstance()->GetScreenWidth() >> 1));

		if(CGame::GetInstance()->GetCamera()->GetX() > CWorldManager::GetInstance()->WorldWidth() - CGame::GetInstance()->GetScreenWidth() )
		{
			CGame::GetInstance()->GetCamera()->SetX( float(CWorldManager::GetInstance()->WorldWidth() - CGame::GetInstance()->GetScreenWidth()) );
		}
		
		fPercent = (float)(mousePos.top - 690) / 206.0f;

		CGame::GetInstance()->GetCamera()->SetY(CWorldManager::GetInstance()->WorldHeight() * fPercent - (CGame::GetInstance()->GetScreenHeight() >> 1));

		if(CGame::GetInstance()->GetCamera()->GetY() > CWorldManager::GetInstance()->WorldHeight() - CGame::GetInstance()->GetScreenHeight())
		{
			CGame::GetInstance()->GetCamera()->SetY( float(CWorldManager::GetInstance()->WorldHeight() - CGame::GetInstance()->GetScreenHeight()));
		}
		return true;
	}

	CheckCheats();

	if(m_bEnteringCheat)
	{
		return true;
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE) /*|| ((CSGD_DirectInput::GetInstance()->KeyPressed(DIK_LALT) || CSGD_DirectInput::GetInstance()->KeyPressed(DIK_TAB)))*/)
	{
		CGame::GetInstance()->PushState(CPauseMenuState::GetInstance());
	}

	CMovementControl::GetInstance()->Input();

	return true;
}

bool CGamePlayState::CheckButtonInput()
{
	RECT mousePos, collide, collider;
	mousePos.left = CMovementControl::GetInstance()->MousePosX();
	mousePos.top = CMovementControl::GetInstance()->MousePosY();
	mousePos.right = mousePos.left + 1;
	mousePos.bottom = mousePos.top + 1;

	// Tooltips
	if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("MoveOrder")].GetCollisionRect()), &mousePos)) 
	{
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = "  Move To Position";
		m_nToolTipOffsetY = 0;
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_szSelectedCommand = "MoveOrder";
			return true;
		}
	} 
	else if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("AttackOrder")].GetCollisionRect()), &mousePos)) 
	{
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = " Attack Target";
		m_nToolTipOffsetY = 0;
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_szSelectedCommand = "AttackOrder";
			return true;
		}
	} 
	else if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("HoldOrder")].GetCollisionRect()), &mousePos)) 
	{
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = " Hold";
		m_nToolTipOffsetY = 0;
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_szSelectedCommand = "HoldOrder";
			return true;
		}
	} 
	else if(IntersectRect(&collide, &(collider = m_vButtons[FindButton("CancelOrder")].GetCollisionRect()), &mousePos)) 
	{
		m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
		m_szTooltipText = " Cancel";
		m_nToolTipOffsetY = 0;
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_szSelectedCommand = "";
			return true;
		}
	} else {
		m_szTooltipText = "";
		if(!m_bEnteringCheat)
		{
			m_vButtonInstances[FindButton("ToolTipBG")].Visible(false);
		}
	}
	
	if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Marine 1")].GetCollisionRect()), &mousePos) && m_vButtonInstances[FindButton("Marine 1")].Visible())
	{
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Point(mousePos.left - 4, mousePos.top - 64);
		m_szTooltipText = " Overdrive\n 50% Attack Speed for \n  7 Seconds\n     30sec Cooldown";
		m_nToolTipOffsetY = 32;
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_vButtons[FindButton("Marine 1")].Activate();
			return true;
		}
	}
	else if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Marine 2")].GetCollisionRect()), &mousePos) && m_vButtonInstances[FindButton("Marine 2")].Visible())
	{
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Point(mousePos.left - 4, mousePos.top - 64);
		m_szTooltipText = " Stun Grenade\n 5sec area effect stun\n     30sec Cooldown";
		m_nToolTipOffsetY = 32;
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_vButtons[FindButton("Marine 2")].Activate();
			return true;
		}
	}
	else if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Heavy 1")].GetCollisionRect()), &mousePos) && m_vButtonInstances[FindButton("Heavy 1")].Visible())
	{
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Point(mousePos.left - 4, mousePos.top - 64);
		m_szTooltipText = " Armor Lockdown\n Increases armor by 50 \n  for 12sec\n     60sec Cooldown";
		m_nToolTipOffsetY = 32;
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_vButtons[FindButton("Heavy 1")].Activate();
			return true;
		}
	}
	else if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Heavy 2")].GetCollisionRect()), &mousePos) && m_vButtonInstances[FindButton("Heavy 2")].Visible())
	{
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Point(mousePos.left - 4, mousePos.top - 64);
		m_szTooltipText = " Missile Barrage\n Deals 50 damage tonenemies in range\n     30sec Cooldown";
		m_nToolTipOffsetY = 32;
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_vButtons[FindButton("Heavy 2")].Activate();
			return true;
		}
	}
	else if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Medic 1")].GetCollisionRect()), &mousePos) && m_vButtonInstances[FindButton("Medic 1")].Visible())
	{
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Point(mousePos.left - 4, mousePos.top - 64);
		m_szTooltipText = " Defensive Matrix\n Makes target invulnerable for \n  8sec\n     50sec Cooldown";
		m_nToolTipOffsetY = 32;
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_vButtons[FindButton("Medic 1")].Activate();
			return true;
		}
	}
	else if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Medic 2")].GetCollisionRect()), &mousePos) && m_vButtonInstances[FindButton("Medic 2")].Visible())
	{
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Point(mousePos.left - 4, mousePos.top - 64);
		m_szTooltipText = " Refresh\n Heal target for 20hp\n     12sec Cooldown";
		m_nToolTipOffsetY = 32;
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_vButtons[FindButton("Medic 2")].Activate();
			return true;
		}
	}
	else if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Scout 1")].GetCollisionRect()), &mousePos) && m_vButtonInstances[FindButton("Scout 1")].Visible())
	{
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Point(mousePos.left - 4, mousePos.top - 64);
		m_szTooltipText = " Cloak\n Become invisible/visible\n     No Cooldown";
		m_nToolTipOffsetY = 32;
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_vButtons[FindButton("Scout 1")].Activate();
			return true;
		}
	}
	else if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Scout 2")].GetCollisionRect()), &mousePos) && m_vButtonInstances[FindButton("Scout 2")].Visible())
	{
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Point(mousePos.left - 4, mousePos.top - 64);
		m_szTooltipText = " Pinning Shot\n Immobilize a unit for 6sec\n     20sec Cooldown";
		m_nToolTipOffsetY = 32;
		m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(true);
		if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
		{
			m_vButtons[FindButton("Scout 2")].Activate();
			return true;
		}
	} else {
			m_vButtonInstances[FindButton("ToolTipLargeBG")].Visible(false);
	}
	//else if (IntersectRect(&collide, &(collider = m_vButtons[FindButton("Item1")].GetCollisionRect()), &mousePos))
	//{
	//	m_vButtonInstances[FindButton("ToolTipBG")].Point(mousePos.left - 4, mousePos.top - 32);
	//	m_szTooltipText = " Book of Haste";
	//	m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
	//	if(CSGD_DirectInput::GetInstance()->MouseButtonReleased(0))
	//	{
	//		(*(CMovementControl::GetInstance()->Marine()->Inventory()))[0]->AddEffect();
	//		return true;
	//	}
	//}

	return false;
}

void CGamePlayState::CheckCheats()
{
	if(CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx() != '\0' && m_bEnteringCheat)
	{
		m_szCheatBuffer += CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx();
		m_szCheatBuffer = (m_szCheatBuffer.c_str() + 1);

		if(strstr(m_szCheatBuffer.c_str(), "dog"))
		{
			m_szCheatBuffer="                             ";
			m_bGodMode =! m_bGodMode;
			m_bEnteringCheat = false;
		}
		else if(strstr(m_szCheatBuffer.c_str(), "gogo"))
		{
			m_szCheatBuffer = "                             ";
			m_bNoCooldown = true;
			m_szSelectedCommand = "cooldown_cheat";
			m_bEnteringCheat = false;

		}
		else if(strstr(m_szCheatBuffer.c_str(), "stats"))
		{
			m_szCheatBuffer = "                             ";
			m_szSelectedCommand = "stats_cheat";
			m_bEnteringCheat = false;
		}
		else if(strstr(m_szCheatBuffer.c_str(), "deeps"))
		{
			m_szCheatBuffer = "                             ";
			m_szSelectedCommand = "speed_cheat";
			m_bEnteringCheat = false;
		}
		else if(strstr(m_szCheatBuffer.c_str(), "bored"))
		{
			m_szCheatBuffer = "                             ";
			m_bEnteringCheat = false;
			//TODO: skip level
		}
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		m_bEnteringCheat = !m_bEnteringCheat;
	}
}
void CGamePlayState::Update(float fElapsedTime)
{
	for (unsigned int i = 0; i < CObjectManager::GetInstance()->GetObjectList()->size(); i++)
	{
		if ((*CObjectManager::GetInstance()->GetObjectList())[i]->Type() == CBase::OBJ_PLAYER)
		{
			break;
		}
		if (i == CObjectManager::GetInstance()->GetObjectList()->size() - 1 && (*CObjectManager::GetInstance()->GetObjectList())[i]->Type() != CBase::OBJ_PLAYER)
		{
			CGame::GetInstance()->ChangeState(CGameOverState::GetInstance());
		}
	}

	m_vButtonInstances[FindButton("Marine 1")].Visible(false);
	m_vButtonInstances[FindButton("Marine 2")].Visible(false);
	m_vButtonInstances[FindButton("Heavy 1")].Visible(false);
	m_vButtonInstances[FindButton("Heavy 2")].Visible(false);
	m_vButtonInstances[FindButton("Medic 1")].Visible(false);
	m_vButtonInstances[FindButton("Medic 2")].Visible(false);
	m_vButtonInstances[FindButton("Scout 1")].Visible(false);
	m_vButtonInstances[FindButton("Scout 2")].Visible(false);

	if(CMovementControl::GetInstance()->GetSelectedUnits()->size() > 0)
	{
		CBase* pSelected = (*CMovementControl::GetInstance()->GetSelectedUnits())[0];
		if (pSelected->Type() == CUnit::OBJ_PLAYER)
		{
			switch (((CUnit*)pSelected)->SubType())
			{
			case CUnit::PLAYER_MARINE:
				m_vButtonInstances[FindButton("Marine 1")].Visible(true);
				m_vButtonInstances[FindButton("Marine 2")].Visible(true);
				break;
			case CUnit::PLAYER_HEAVY:
				m_vButtonInstances[FindButton("Heavy 1")].Visible(true);
				m_vButtonInstances[FindButton("Heavy 2")].Visible(true);
				break;
			case CUnit::PLAYER_MEDIC:
				m_vButtonInstances[FindButton("Medic 1")].Visible(true);
				m_vButtonInstances[FindButton("Medic 2")].Visible(true);
				break;
			case CUnit::PLAYER_SCOUT:
				m_vButtonInstances[FindButton("Scout 1")].Visible(true);
				m_vButtonInstances[FindButton("Scout 2")].Visible(true);
				break;
			}
		}
	}

	m_nCurCount += 25.0f * fElapsedTime;
	CMovementControl::GetInstance()->CheckDragRect();
	CMovementControl::GetInstance()->UpdateCamera(fElapsedTime);
	CObjectManager::GetInstance()->UpdateObjects(fElapsedTime);
	CMessageSystem::GetInstance()->ProcessMessages();
	m_peEmitter.Update(fElapsedTime);

	m_fTotalGameTime+=fElapsedTime;

	//Check for level clear

	for (unsigned int i = 0; i < CObjectManager::GetInstance()->GetObjectList()->size(); i++)
	{
		if ((*CObjectManager::GetInstance()->GetObjectList())[i]->Type() == CBase::OBJ_ENEMY)
		{
			return;
		}
	}

	CLoadLevelState::GetInstance()->SetLoadLevel( CGamePlayState::GetInstance()->NextLevel() );
	CGame::GetInstance()->ChangeState( CLoadLevelState::GetInstance() );
}

void CGamePlayState::RenderMiniMap()
{
	//background image
	//objects
	//screen rect
	CSGD_TextureManager::GetInstance()->Draw(m_nMiniMap, 5, 690);
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	int tempX, tempY, maxX, maxY;
	int OffsetX = 5, OffsetY = 690, CX = 255, CY = 204;
	unsigned char ucRed, ucBlue, ucGreen;
	RECT rObj;
	vector<CBase*>* pOM = CObjectManager::GetInstance()->GetObjectList();

	maxX = CWorldManager::GetInstance()->WorldWidth();
	maxY = CWorldManager::GetInstance()->WorldHeight();

	for(size_t i=0; i<pOM->size(); i++)
	{
		switch((*pOM)[i]->Type())
		{
		case CBase::OBJ_PLAYER:
			ucRed=0;
			ucGreen=255;
			ucBlue=0;
			break;
		case CBase::OBJ_ENEMY:
			ucRed=255;
			ucGreen=0;
			ucBlue=0;
			break;
		default:
			ucRed=255;
			ucGreen=255;
			ucBlue=255;
			break;
		}
		tempX = (int)(*pOM)[i]->PosX();
		tempY = (int)(*pOM)[i]->PosY();
		
		rObj.left = OffsetX + (int)(((float)tempX/(float)maxX)*(float)CX);
		rObj.top = OffsetY + (int)(((float)tempY/(float)maxY)*(float)CY);
		rObj.right = rObj.left+5;
		rObj.bottom = rObj.top+5;
		CSGD_Direct3D::GetInstance()->DrawRect(rObj, ucRed, ucGreen, ucBlue);

	}

	//screen rect
	tempX = (int)CGame::GetInstance()->GetCamera()->GetX();
	tempY = (int)CGame::GetInstance()->GetCamera()->GetY();
	rObj.left = OffsetX + (int)(((float)tempX/(float)maxX)*(float)CX);
	rObj.top = OffsetY + (int)(((float)tempY/(float)maxY)*(float)CY);
	float fPercent;
	fPercent = (float)CGame::GetInstance()->GetScreenWidth()/(float)CWorldManager::GetInstance()->WorldWidth();
	rObj.right = rObj.left+ (int)((float)CX*fPercent);
	fPercent = (float)CGame::GetInstance()->GetScreenHeight()/(float)CWorldManager::GetInstance()->WorldHeight();
	rObj.bottom = rObj.top + (int)((float)CY*fPercent);
	CSGD_Direct3D::GetInstance()->DrawLine(rObj.left, rObj.top, rObj.right, rObj.top);
	CSGD_Direct3D::GetInstance()->DrawLine(rObj.right, rObj.top, rObj.right, rObj.bottom);
	CSGD_Direct3D::GetInstance()->DrawLine(rObj.right, rObj.bottom, rObj.left, rObj.bottom);
	CSGD_Direct3D::GetInstance()->DrawLine(rObj.left, rObj.bottom, rObj.left, rObj.top);

	CSGD_Direct3D::GetInstance()->SpriteBegin();
}

void CGamePlayState::RenderHUD(void)
{
	// Render all buttons
	for(unsigned int i = 0; i < m_vButtonInstances.size(); i++)
	{
		if(m_vButtonInstances[i].Visible())
		{
			CSGD_TextureManager::GetInstance()->Draw(m_vButtonInstances[i].TextureID(), m_vButtonInstances[i].Point().x, m_vButtonInstances[i].Point().y, 1.0f, 1.0f);
		}
	}

	// Render Names
	RenderSmallShadowText("Speaker", 42, 575);

	// Render Objectives
	//RenderLargeShadowText("Objectives", 54, 35);

	// Render Speech
	RenderLargeShadowText((char *)(m_szSpeechText.substr(0, (unsigned int)m_nCurCount)).c_str(), 135, 494);

	// Render selected object stats (if a single object is selected)
	if(CMovementControl::GetInstance()->GetSelectedUnits()->size() > 0)
	{
		CBase* pBase = (*CMovementControl::GetInstance()->GetSelectedUnits())[0];
		switch(pBase->Type())
		{
		case CBase::OBJ_PLAYER:
			{
				CUnit* pUnit = (CUnit*)pBase;
				m_ftTextSmall.RenderText("Health", 460, 755);
				char buff[128];
				sprintf_s(buff, 128, "%i/%i", pUnit->CurHealth(), pUnit->MaxHealth());
				m_ftTextSmall.RenderText(buff, 460, 770);
				sprintf_s(buff, 128, "Attack: %.2f", pUnit->AttackDamage());
				m_ftTextSmall.RenderText(buff, 840, 755);
				sprintf_s(buff, 128, "Speed: %.2f", pUnit->AttackSpeed());
				m_ftTextSmall.RenderText(buff, 840, 770);
				sprintf_s(buff, 128, "Armor: %i", pUnit->Armor());
				m_ftTextSmall.RenderText(buff, 840, 785);

				switch(pUnit->SubType())
				{
				case CUnit::PLAYER_MARINE:
					RenderLargeShadowText("  Marine", 284, 852);
					sprintf_s(buff, 128, "%.0f", (*pUnit->Abilities())[0]->Cooldown() - (*pUnit->Abilities())[0]->TimePassed());
					RenderLargeShadowText(buff, 1129, 768);
					sprintf_s(buff, 128, "%.0f", (*pUnit->Abilities())[1]->Cooldown() - (*pUnit->Abilities())[1]->TimePassed());
					RenderLargeShadowText(buff, 1193, 768);
					break;
				case CUnit::PLAYER_HEAVY:
					RenderLargeShadowText("  Heavy", 284, 852);
					sprintf_s(buff, 128, "%.0f", (*pUnit->Abilities())[0]->Cooldown() - (*pUnit->Abilities())[0]->TimePassed());
					RenderLargeShadowText(buff, 1129, 768);
					sprintf_s(buff, 128, "%.0f", (*pUnit->Abilities())[1]->Cooldown() - (*pUnit->Abilities())[1]->TimePassed());
					RenderLargeShadowText(buff, 1193, 768);
					break;
				case CUnit::PLAYER_MEDIC:
					RenderLargeShadowText("  Medic", 284, 852);
					sprintf_s(buff, 128, "%.0f", (*pUnit->Abilities())[0]->Cooldown() - (*pUnit->Abilities())[0]->TimePassed());
					RenderLargeShadowText(buff, 1129, 768);
					sprintf_s(buff, 128, "%.0f", (*pUnit->Abilities())[1]->Cooldown() - (*pUnit->Abilities())[1]->TimePassed());
					RenderLargeShadowText(buff, 1193, 768);
					break;
				case CUnit::PLAYER_SCOUT:
					RenderLargeShadowText("  Scout", 284, 852);
					sprintf_s(buff, 128, "%.0f", (*pUnit->Abilities())[0]->Cooldown() - (*pUnit->Abilities())[0]->TimePassed());
					RenderLargeShadowText(buff, 1129, 768);
					sprintf_s(buff, 128, "%.0f", (*pUnit->Abilities())[1]->Cooldown() - (*pUnit->Abilities())[1]->TimePassed());
					RenderLargeShadowText(buff, 1193, 768);
					break;
				}
			}
			break;
		case CBase::OBJ_ENEMY:
			{
				CUnit* pEnemy = (CUnit*)pBase;
				m_ftTextSmall.RenderText("Health", 460, 755);
				char buff[128];
				sprintf_s(buff, 128, "%i/%i", pEnemy->CurHealth(), pEnemy->MaxHealth());
				m_ftTextSmall.RenderText(buff, 460, 770);
				sprintf_s(buff, 128, "Attack: %.2f", pEnemy->AttackDamage());
				m_ftTextSmall.RenderText(buff, 840, 755);
				sprintf_s(buff, 128, "Speed: %.2f", pEnemy->AttackSpeed());
				m_ftTextSmall.RenderText(buff, 840, 770);
				sprintf_s(buff, 128, "Armor: %i", pEnemy->Armor());
				m_ftTextSmall.RenderText(buff, 840, 785);
				RenderLargeShadowText("Unknown", 284, 852);
			}
			break;
		}
	}

	RenderMiniMap();

	//cheat text
	if(m_bGodMode)
		RenderSmallShadowText("God Mode Enabled", 10, 10);
	if(m_bNoCooldown)
		RenderSmallShadowText("Cooldowns Disabled", 10, 20);
	if(m_bEnteringCheat)
	{
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(true);
		m_vButtonInstances[FindButton("ToolTipBG")].Point(0, 35);
		m_ftTextLargeShadow.RenderText("Enter a Cheat", 10, 37);	
	}
	else
		m_vButtonInstances[FindButton("ToolTipBG")].Visible(false);

	// Render ToolTip Text
	if(m_szTooltipText != "")
	{
		m_ftTextSmallShadow.RenderText((char*)m_szTooltipText.c_str(), CMovementControl::GetInstance()->MousePosX(), CMovementControl::GetInstance()->MousePosY() - 25 - m_nToolTipOffsetY);
	}
}

void CGamePlayState::Render(void)
{
	CWorldManager::GetInstance()->Render();
	CSGD_Direct3D::GetInstance()->SpriteEnd();
	CSGD_Direct3D::GetInstance()->SpriteBegin();

	CObjectManager::GetInstance()->RenderObjects();
	CMovementControl::GetInstance()->RenderDragRect();
	m_peEmitter.Render();
	RenderHUD();
	//CPathManager::GetInstance()->RenderLines();
	CMovementControl::GetInstance()->RenderCursor();
}

int  CGamePlayState::FindButton(string _name)
{
	for(unsigned int i = 0; i < m_vButtons.size(); i++)
	{
		if(m_vButtons[i].Name() == _name)
			return i;
	}
	
	return -1;
}

void CGamePlayState::RenderSmallShadowText(char* _text, int _x, int _y)
{
	m_ftTextSmallShadow.RenderText(_text, _x + 1, _y + 1);
	m_ftTextSmall.RenderText(_text, _x, _y);
}

void CGamePlayState::RenderLargeShadowText(char* _text, int _x, int _y)
{
	m_ftTextLargeShadow.RenderText(_text, _x + 2, _y + 2);
	m_ftTextLarge.RenderText(_text, _x, _y);
}

void CGamePlayState::MessageProc(CBaseMessage* pMSG)
{
	switch (pMSG->GetMsgID())
	{
	case MSG_DESTROY_UNIT:
		CUnitDeathMessage* udMSG = (CUnitDeathMessage*)pMSG;

		CObjectManager::GetInstance()->FindAndRemove(udMSG->GetUnit());

		CObjectManager::GetInstance()->RemoveObject(udMSG->GetUnit());
	}
}

void CGamePlayState::LoadNextLevel()
{
	if (m_nLevel > 2)
	{
		m_nLevel = 1;
	}

	//debrief(level success)
	if(m_nLevel!=0)
		CGame::GetInstance()->PushState(CDebriefState::GetInstance());

	switch (m_nLevel)
	{
	case 0:
		m_nLevel++;
	case 1:
		{
			CWorldManager::GetInstance()->Load("Resource//Graphics//Intro Level Take 2.mfl");

			CMarine* alliedMarine = CMovementControl::GetInstance()->Marine();
			CHeavy* alliedHeavy  = CMovementControl::GetInstance()->Heavy();
			CMedic* alliedMedic  = CMovementControl::GetInstance()->Medic();
			CScout* alliedScout  = CMovementControl::GetInstance()->Scout();

			alliedMarine->PosX(50);
			alliedMarine->PosY(50);
			alliedHeavy->PosX(150);
			alliedHeavy->PosY(50);
			alliedScout->PosX(150);
			alliedScout->PosY(150);
			alliedMedic->PosX(50);
			alliedMedic->PosY(150);

			CBasicEnemy* badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
			badGuy->Type(CBase::OBJ_ENEMY);
			badGuy->PosX(1700);
			badGuy->PosY(200);
			CObjectManager::GetInstance()->AddObject(badGuy);

			badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
			badGuy->Type(CBase::OBJ_ENEMY);
			badGuy->PosX(1600);
			badGuy->PosY(230);
			CObjectManager::GetInstance()->AddObject(badGuy);


			CBasicEnemy* FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
			FElemental->Type(CBase::OBJ_ENEMY);
			FElemental->PosX(1800);
			FElemental->PosY(200);
			CObjectManager::GetInstance()->AddObject(FElemental);

			FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
			FElemental->Type(CBase::OBJ_ENEMY);
			FElemental->PosX(1800);
			FElemental->PosY(260);
			CObjectManager::GetInstance()->AddObject(FElemental);

			FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
			FElemental->Type(CBase::OBJ_ENEMY);
			FElemental->PosX(1860);
			FElemental->PosY(230);
			CObjectManager::GetInstance()->AddObject(FElemental);

			//////////////////////////////////////////////////////////////////////////

			badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
			badGuy->Type(CBase::OBJ_ENEMY);
			badGuy->PosX(400);
			badGuy->PosY(200);
			CObjectManager::GetInstance()->AddObject(badGuy);

			badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
			badGuy->Type(CBase::OBJ_ENEMY);
			badGuy->PosX(1600);
			badGuy->PosY(900);
			CObjectManager::GetInstance()->AddObject(badGuy);

			badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
			badGuy->Type(CBase::OBJ_ENEMY);
			badGuy->PosX(1700);
			badGuy->PosY(930);
			CObjectManager::GetInstance()->AddObject(badGuy);


			FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
			FElemental->Type(CBase::OBJ_ENEMY);
			FElemental->PosX(1500);
			FElemental->PosY(900);
			CObjectManager::GetInstance()->AddObject(FElemental);

			FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
			FElemental->Type(CBase::OBJ_ENEMY);
			FElemental->PosX(1500);
			FElemental->PosY(960);
			CObjectManager::GetInstance()->AddObject(FElemental);

			FElemental = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Fire Elemental");
			FElemental->Type(CBase::OBJ_ENEMY);
			FElemental->PosX(1560);
			FElemental->PosY(930);
			CObjectManager::GetInstance()->AddObject(FElemental);
		}

		m_nLevel++;

		break;
	case 2:
		{
			CWorldManager::GetInstance()->Load("Resource//Graphics//Level 2.mfl");

			CMarine* alliedMarine = CMovementControl::GetInstance()->Marine();
			CHeavy*  alliedHeavy  = CMovementControl::GetInstance()->Heavy();
			CMedic*  alliedMedic  = CMovementControl::GetInstance()->Medic();
			CScout*  alliedScout  = CMovementControl::GetInstance()->Scout();

			alliedMarine->PosX(50);
			alliedMarine->PosY(50);
			alliedHeavy->PosX(150);
			alliedHeavy->PosY(50);
			alliedScout->PosX(150);
			alliedScout->PosY(150);
			alliedMedic->PosX(50);
			alliedMedic->PosY(150);

			CBasicEnemy* badGuy = (CBasicEnemy*)CUnitFactory::GetInstance()->CreateUnit("Footman");
			badGuy->Type(CBase::OBJ_ENEMY);
			badGuy->PosX(1600);
			badGuy->PosY(230);
			CObjectManager::GetInstance()->AddObject(badGuy);
		}

		m_nLevel++;

		break;
	default:
		break;
	}
}

void CGamePlayState::InitHud()
{
	// Setup GUI
	m_vButtons.push_back(CHUDButton(-76, 645, 2048, 512, "BottomHUD", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/0.png").c_str())));
	m_vButtons.push_back(CHUDButton(270, 706, 256, 256, "UnitPortrait", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/1.png").c_str())));
	m_vButtons.push_back(CHUDButton(274, 852, 256, 32, "PortraitNameLine", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/2.png").c_str())));
	m_vButtons.push_back(CHUDButton(433, 728, 1024, 256, "MiddleHUDOutlines", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/3.png").c_str())));
	m_vButtons.push_back(CHUDButton(1113, 688, 64, 64, "MoveOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/7.png").c_str())));
	m_vButtons.push_back(CHUDButton(1177, 688, 64, 64, "AttackOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/8.png").c_str())));
	m_vButtons.push_back(CHUDButton(1243, 688, 64, 64, "HoldOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/9.png").c_str())));
	m_vButtons.push_back(CHUDButton(1357, 819, 64, 64, "CancelOrder", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str())));
	m_vButtons.push_back(CHUDButton(641, 0, 256, 64, "OverMenuButton", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/13.png").c_str())));
	m_vButtons.push_back(CHUDButton(28, 480, 512, 256, "SpeechBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/14.png").c_str())));
	m_vButtons.push_back(CHUDButton(32, 484, 128, 256, "SpeechSpeaker", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/15.png").c_str())));
	m_vButtons.push_back(CHUDButton(37, 577, 128, 32, "SpeechSpeakerNameLine", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/16.png").c_str())));
	m_vButtons.push_back(CHUDButton(41, 31, 256, 64, "ObjectivesSmallBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/17.png").c_str()), false));


	// Unit Ability Buttons
	// Marine
	m_vButtons.push_back(CHUDButton(1113, 752, 64, 64, "Marine 1", ActivateAbilityOne, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(1177, 752, 64, 64, "Marine 2", ActivateAbilityTwo, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str()), false));
	
	//Heavy
	m_vButtons.push_back(CHUDButton(1113, 752, 64, 64, "Heavy 1", ActivateAbilityOne, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(1177, 752, 64, 64, "Heavy 2", ActivateAbilityTwo, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str()), false));

	//Medic
	m_vButtons.push_back(CHUDButton(1113, 752, 64, 64, "Medic 1", ActivateAbilityOne, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(1177, 752, 64, 64, "Medic 2", ActivateAbilityTwo, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str()), false));

	//Scout
	m_vButtons.push_back(CHUDButton(1113, 752, 64, 64, "Scout 1", ActivateAbilityOne, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(1177, 752, 64, 64, "Scout 2", ActivateAbilityTwo, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/10.png").c_str()), false));



	//////////////////////////////////////////////////////////////////////////
	m_vButtons.push_back(CHUDButton(577, 752, 64, 64, "Item1", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/7.png").c_str()), false));
	CItem* BookOfHaste = CItemFactory::GetInstance()->CreateItem("Book of Haste");
	//////////////////////////////////////////////////////////////////////////

	m_vButtons.push_back(CHUDButton(0, 0, 256, 64, "ToolTipBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/20.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(0, 0, 512, 32, "ObjectivesLargeBG-NoCheck", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/18.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(0, 0, 512, 32, "ObjectivesLargeBG-Check", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/19.png").c_str()), false));
	m_vButtons.push_back(CHUDButton(0, 0, 512, 128, "ToolTipLargeBG", NULL, CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD/21.png").c_str()), false));
	m_vButtonInstances = m_vButtons;

	m_ftTextSmall.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.5f, 0.5f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(255, 255, 255));
	m_ftTextSmall.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_ftTextSmallShadow.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.5f, 0.5f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(0, 0, 0));
	m_ftTextSmallShadow.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_ftTextLarge.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.80f, 0.80f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(255, 255, 255));
	m_ftTextLarge.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_ftTextLargeShadow.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.80f, 0.80f, 2, D3DCOLOR_XRGB(0,0,0), D3DCOLOR_XRGB(0, 0, 0));
	m_ftTextLargeShadow.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
}

void ActivateAbilityOne()
{
	if ((*CMovementControl::GetInstance()->GetSelectedUnits()).size() < 1 || ((CUnit*)(*CMovementControl::GetInstance()->GetSelectedUnits())[0])->Type() != CUnit::OBJ_PLAYER)
	{
		return;
	}
	if((*((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]))->Abilities())[0]->Type() == 0)
	{
		(*((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]))->Abilities())[0]->Activate();
	}
	else if ((*((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]))->Abilities())[0]->Type() == 1)
	{
		CGamePlayState::GetInstance()->SetCommand("Ability1");
		CMovementControl::GetInstance()->SetUnit((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]));
		CMovementControl::GetInstance()->SetPosition(0);
	}
	else if ((*((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]))->Abilities())[0]->Type() == 2)
	{
		CGamePlayState::GetInstance()->SetCommand("Ability2");
		CMovementControl::GetInstance()->SetUnit((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]));
		CMovementControl::GetInstance()->SetPosition(1);
	}
}

void ActivateAbilityTwo()
{
	if ((*CMovementControl::GetInstance()->GetSelectedUnits()).size() < 1 || ((CUnit*)(*CMovementControl::GetInstance()->GetSelectedUnits())[0])->Type() != CUnit::OBJ_PLAYER)
	{
		return;
	}
	if((*((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]))->Abilities())[1]->Type() == 0)
	{
		(*((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]))->Abilities())[1]->Activate();
	}
	else if ((*((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]))->Abilities())[1]->Type() == 1)
	{
		CGamePlayState::GetInstance()->SetCommand("Ability2");
		CMovementControl::GetInstance()->SetUnit((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]));
		CMovementControl::GetInstance()->SetPosition(1);
	}
	else if ((*((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]))->Abilities())[1]->Type() == 2)
	{
		CGamePlayState::GetInstance()->SetCommand("Ability2");
		CMovementControl::GetInstance()->SetUnit((CUnit*)((*CMovementControl::GetInstance()->GetSelectedUnits())[0]));
		CMovementControl::GetInstance()->SetPosition(1);
	}
}