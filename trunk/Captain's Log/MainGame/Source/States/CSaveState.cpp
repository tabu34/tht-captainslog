#include "precompiled_header.h"
#include "CSaveState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../CGame.h"
#include "../States/CGamePlayState.h"
#include "../Managers/MovementControl.h"
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::string;


CSaveState::CSaveState()
{
	m_pProfiles=NULL;
}

CSaveState::~CSaveState()
{

}

CSaveState* CSaveState::GetInstance()
{
	static CSaveState instance;
	return &instance;
}

void CSaveState::LoadProfiles()
{
	ifstream fin;
	string szPath;
	szPath = CGame::GetInstance()->ResourcePath();
	szPath+="Save.bin";
	fin.open(szPath.c_str(), ios_base::in | ios_base::binary);

	if(m_pProfiles)
		delete[] m_pProfiles;
	m_pProfiles=NULL;

	if(fin.fail())
	{
		fin.clear(ios_base::failbit);
		m_nNumProfiles=0;
	}
	else if(fin.is_open() && fin.good())
	{
		fin.read((char*)&m_nNumProfiles, sizeof(int));
		m_pProfiles = new tProfileHeader[m_nNumProfiles];
		for(int i=0; i<m_nNumProfiles; i++)
		{
			fin.read((char*)&m_pProfiles[i], sizeof(tProfileHeader));
			fin.seekg(m_pProfiles[i].nProfileSizeInBytes+fin.tellg());
		}
		fin.close();
	}
}

void CSaveState::SaveCurrent(int nSlot)
{
	vector<tUnitSaveInfo> vToSave;
	vector<CBase*>*	vGame = CObjectManager::GetInstance()->GetObjectList();

	tUnitSaveInfo temp;
	CUnit* pCurUnit;

	pCurUnit = (CUnit*)CMovementControl::GetInstance()->Marine();
	temp.bBurned = pCurUnit->Burned();
	temp.bCloaked = pCurUnit->Cloaked();
	temp.bInvulnerable = pCurUnit->Invulnerable();
	temp.bRanged = pCurUnit->Ranged();
	temp.bStunned = pCurUnit->Stunned();
	temp.fAttackDamage = pCurUnit->AttackDamage();
	temp.fAttackRange = pCurUnit->AttackRange();
	temp.fAttackSpeed = pCurUnit->AttackSpeed();
	temp.fMovementSpeed = pCurUnit->MovementSpeed();
	temp.fPosX = pCurUnit->PosX();
	temp.fPosY = pCurUnit->PosY();
	temp.nArmor = pCurUnit->Armor();
	temp.nCurHealth = pCurUnit->CurHealth();
	temp.nHealthRegenRate = pCurUnit->HealthRegenRate();
	temp.nLevel = pCurUnit->Level();
	temp.nMaxHealth = pCurUnit->MaxHealth();
	temp.nSightRange = pCurUnit->SightRange();
	temp.nSubType = pCurUnit->SubType();
	temp.nType = pCurUnit->Type();
	vToSave.push_back(temp);

	pCurUnit = (CUnit*)CMovementControl::GetInstance()->Heavy();
	temp.bBurned = pCurUnit->Burned();
	temp.bCloaked = pCurUnit->Cloaked();
	temp.bInvulnerable = pCurUnit->Invulnerable();
	temp.bRanged = pCurUnit->Ranged();
	temp.bStunned = pCurUnit->Stunned();
	temp.fAttackDamage = pCurUnit->AttackDamage();
	temp.fAttackRange = pCurUnit->AttackRange();
	temp.fAttackSpeed = pCurUnit->AttackSpeed();
	temp.fMovementSpeed = pCurUnit->MovementSpeed();
	temp.fPosX = pCurUnit->PosX();
	temp.fPosY = pCurUnit->PosY();
	temp.nArmor = pCurUnit->Armor();
	temp.nCurHealth = pCurUnit->CurHealth();
	temp.nHealthRegenRate = pCurUnit->HealthRegenRate();
	temp.nLevel = pCurUnit->Level();
	temp.nMaxHealth = pCurUnit->MaxHealth();
	temp.nSightRange = pCurUnit->SightRange();
	temp.nSubType = pCurUnit->SubType();
	temp.nType = pCurUnit->Type();
	vToSave.push_back(temp);

	pCurUnit = (CUnit*)CMovementControl::GetInstance()->Medic();
	temp.bBurned = pCurUnit->Burned();
	temp.bCloaked = pCurUnit->Cloaked();
	temp.bInvulnerable = pCurUnit->Invulnerable();
	temp.bRanged = pCurUnit->Ranged();
	temp.bStunned = pCurUnit->Stunned();
	temp.fAttackDamage = pCurUnit->AttackDamage();
	temp.fAttackRange = pCurUnit->AttackRange();
	temp.fAttackSpeed = pCurUnit->AttackSpeed();
	temp.fMovementSpeed = pCurUnit->MovementSpeed();
	temp.fPosX = pCurUnit->PosX();
	temp.fPosY = pCurUnit->PosY();
	temp.nArmor = pCurUnit->Armor();
	temp.nCurHealth = pCurUnit->CurHealth();
	temp.nHealthRegenRate = pCurUnit->HealthRegenRate();
	temp.nLevel = pCurUnit->Level();
	temp.nMaxHealth = pCurUnit->MaxHealth();
	temp.nSightRange = pCurUnit->SightRange();
	temp.nSubType = pCurUnit->SubType();
	temp.nType = pCurUnit->Type();
	vToSave.push_back(temp);

	pCurUnit = (CUnit*)CMovementControl::GetInstance()->Scout();
	temp.bBurned = pCurUnit->Burned();
	temp.bCloaked = pCurUnit->Cloaked();
	temp.bInvulnerable = pCurUnit->Invulnerable();
	temp.bRanged = pCurUnit->Ranged();
	temp.bStunned = pCurUnit->Stunned();
	temp.fAttackDamage = pCurUnit->AttackDamage();
	temp.fAttackRange = pCurUnit->AttackRange();
	temp.fAttackSpeed = pCurUnit->AttackSpeed();
	temp.fMovementSpeed = pCurUnit->MovementSpeed();
	temp.fPosX = pCurUnit->PosX();
	temp.fPosY = pCurUnit->PosY();
	temp.nArmor = pCurUnit->Armor();
	temp.nCurHealth = pCurUnit->CurHealth();
	temp.nHealthRegenRate = pCurUnit->HealthRegenRate();
	temp.nLevel = pCurUnit->Level();
	temp.nMaxHealth = pCurUnit->MaxHealth();
	temp.nSightRange = pCurUnit->SightRange();
	temp.nSubType = pCurUnit->SubType();
	temp.nType = pCurUnit->Type();
	vToSave.push_back(temp);

	for(size_t i=0; i<vGame->size(); i++)
	{
		pCurUnit = ((CUnit*)(*vGame)[i]);
		if(pCurUnit!= (CUnit*)CMovementControl::GetInstance()->Marine() &&
			pCurUnit != (CUnit*)CMovementControl::GetInstance()->Heavy() &&
			pCurUnit != (CUnit*)CMovementControl::GetInstance()->Medic() &&
			pCurUnit != (CUnit*)CMovementControl::GetInstance()->Scout())
		{
			temp.bBurned = pCurUnit->Burned();
			temp.bCloaked = pCurUnit->Cloaked();
			temp.bInvulnerable = pCurUnit->Invulnerable();
			temp.bRanged = pCurUnit->Ranged();
			temp.bStunned = pCurUnit->Stunned();
			temp.fAttackDamage = pCurUnit->AttackDamage();
			temp.fAttackRange = pCurUnit->AttackRange();
			temp.fAttackSpeed = pCurUnit->AttackSpeed();
			temp.fMovementSpeed = pCurUnit->MovementSpeed();
			temp.fPosX = pCurUnit->PosX();
			temp.fPosY = pCurUnit->PosY();
			temp.nArmor = pCurUnit->Armor();
			temp.nCurHealth = pCurUnit->CurHealth();
			temp.nHealthRegenRate = pCurUnit->HealthRegenRate();
			temp.nLevel = pCurUnit->Level();
			temp.nMaxHealth = pCurUnit->MaxHealth();
			temp.nSightRange = pCurUnit->SightRange();
			temp.nSubType = pCurUnit->SubType();
			temp.nType = pCurUnit->Type();
			vToSave.push_back(temp);
		}
	}

	tUnitSaveInfo* pData = new tUnitSaveInfo[vToSave.size()];

	
	for(size_t i=0; i<vToSave.size(); i++)
	{
		pData[i] = vToSave[i];	
	}

	Save(nSlot, CGamePlayState::GetInstance()->GetTime(), pData, (int)vToSave.size());

	delete[] pData;

}

void CSaveState::Save(int nSlot, float fGameTime, tUnitSaveInfo* pData, int numUnits)
{
	//first, load in the entire file.
	ifstream fin;
	string szPath;
	szPath = CGame::GetInstance()->ResourcePath();
	szPath+="Save.bin";
	fin.open(szPath.c_str(), ios_base::in | ios_base::binary);

	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char *szTime = asctime(timeinfo);

	tUnitSaveInfo** ppSaveData = NULL;

	if(m_pProfiles)
		delete[] m_pProfiles;
	m_pProfiles=NULL;

	if(fin.fail())
	{
		fin.clear(ios_base::failbit);

		m_nNumProfiles=0;
		nSlot=0;
	}
	else if(fin.is_open() && fin.good())
	{
		fin.read((char*)&m_nNumProfiles, sizeof(int));
		ppSaveData = new tUnitSaveInfo*[m_nNumProfiles];
		m_pProfiles = new tProfileHeader[m_nNumProfiles];
		for(int i=0; i<m_nNumProfiles; i++)
		{
			int nNumUnits;
			fin.read((char*)&m_pProfiles[i], sizeof(tProfileHeader));
			fin.read((char*)&nNumUnits, sizeof(int));
			ppSaveData[i] = new tUnitSaveInfo[nNumUnits];
			fin.read((char*)ppSaveData[i], sizeof(tUnitSaveInfo)*nNumUnits);
		}
		fin.close();
	}

	if(nSlot>m_nNumProfiles)
		nSlot=m_nNumProfiles;

	if(nSlot>=0 && nSlot<m_nNumProfiles) //replacing an existing profile
	{
		delete[] ppSaveData[nSlot];

		ppSaveData[nSlot] = new tUnitSaveInfo[numUnits];
		memcpy(ppSaveData[nSlot], pData, numUnits*sizeof(tUnitSaveInfo));
		m_pProfiles[nSlot].fGameTime = fGameTime;
		m_pProfiles[nSlot].nProfileSizeInBytes = numUnits*sizeof(tUnitSaveInfo)+sizeof(int);
		strcpy_s(m_pProfiles[nSlot].szLastPlayed, 256, szTime);

		ofstream fout;
		fout.open(szPath.c_str(), ios_base::out | ios_base::trunc | ios_base::binary);
		if(fout.is_open() && fout.good())
		{
			fout.write((char*)&m_nNumProfiles, sizeof(int));
			for(int i=0; i<m_nNumProfiles; i++)
			{
				fout.write((char*)&m_pProfiles[i], sizeof(tProfileHeader));
				int j=(m_pProfiles[i].nProfileSizeInBytes-sizeof(int))/sizeof(tUnitSaveInfo);
				fout.write((char*)&j, sizeof(int));
				fout.write((char*)ppSaveData[i], m_pProfiles[i].nProfileSizeInBytes - sizeof(int));
			}
			fout.close();
		}

		for(int i=0; i<m_nNumProfiles; i++)
			delete[] ppSaveData[i];
	}
	else //add a new profile
	{
		ofstream fout;
		fout.open(szPath.c_str(), ios_base::out | ios_base::trunc | ios_base::binary);
		m_nNumProfiles+=1;
		if(fout.is_open() && fout.good())
		{
			fout.write((char*)&m_nNumProfiles, sizeof(int));
			for(int i=0; i<m_nNumProfiles; i++)
			{
				if(i==m_nNumProfiles-1)
				{
					tProfileHeader pH;
					pH.fGameTime = fGameTime;
					pH.nProfileSizeInBytes = numUnits*sizeof(tUnitSaveInfo)+sizeof(int);
					strcpy_s(pH.szLastPlayed, 256, szTime);

					fout.write((char*)&pH, sizeof(tProfileHeader));
					int j=(pH.nProfileSizeInBytes-sizeof(int))/sizeof(tUnitSaveInfo);
					fout.write((char*)&j, sizeof(int));
					fout.write((char*)pData, pH.nProfileSizeInBytes - sizeof(int));
				}
				else
				{
					fout.write((char*)&m_pProfiles[i], sizeof(tProfileHeader));
					int j=(m_pProfiles[i].nProfileSizeInBytes-sizeof(int))/sizeof(tUnitSaveInfo);
					fout.write((char*)&j, sizeof(int));
					fout.write((char*)ppSaveData[i], m_pProfiles[i].nProfileSizeInBytes - sizeof(int));
				}
			}
			fout.close();
		}
		for(int i=0; i<m_nNumProfiles-1; i++)
			delete[] ppSaveData[i];
	}

	if(ppSaveData)
		delete[] ppSaveData;

	LoadProfiles();


}

void CSaveState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("saveScreen.png").c_str());
	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_bfWhite.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFFFFFFFF);
	m_bfWhite.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_nCurrentControl=-1;
	m_fErrorTimer=0.0f;
	m_bError=false;
	LoadProfiles();
}

void CSaveState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage);
}

bool CSaveState::Input()
{
	m_nMouseX = CMovementControl::GetInstance()->MousePosX();
	m_nMouseY = CMovementControl::GetInstance()->MousePosY();
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->PopState();
	}

	RECT rSaveButton = {135, 428, 445, 481};
	RECT rSelectionBox = {135, 175, 807, 414};
	POINT ptMouse = {m_nMouseX, m_nMouseY};
	if(CSGD_DirectInput::GetInstance()->MouseButtonPressed(0) && PtInRect(&rSelectionBox, ptMouse))
	{
		int nSelect = (m_nMouseY-180)/25;
		m_nCurrentControl = (nSelect>=0 && nSelect<m_nNumProfiles) ? nSelect : -1;
	}
	if(CSGD_DirectInput::GetInstance()->MouseButtonPressed(0) && PtInRect(&rSaveButton, ptMouse))
	{
		if(m_nCurrentControl == -1)
		{
			if(m_nNumProfiles==8)
			{
				m_bError=true;
				m_fErrorTimer=2.0f;
			}
			else
				SaveCurrent(m_nNumProfiles);
		}
		else
			SaveCurrent(m_nCurrentControl);
	}

	m_nMousePrevX = m_nMouseX;
	m_nMousePrevY = m_nMouseY;
	return true;
}

void CSaveState::Update(float fElapsedTime)
{
	if(m_nMouseX < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosX(0);

	if(m_nMouseX > CGame::GetInstance()->GetScreenWidth())
		CSGD_DirectInput::GetInstance()->MouseSetPosX(CGame::GetInstance()->GetScreenWidth());

	if(m_nMouseY < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosY(0);

	if(m_nMouseY > CGame::GetInstance()->GetScreenHeight())
		CSGD_DirectInput::GetInstance()->MouseSetPosY(CGame::GetInstance()->GetScreenHeight());

	if(m_bError)
	{
		m_fErrorTimer-=fElapsedTime;
		if(m_fErrorTimer<=0)
			m_bError=false;
	}
}

void CSaveState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImage, 0, 0, 0.75f, 0.75f);
	if(m_nNumProfiles==0)
	{
		m_bfFont.RenderText("No Profiles Found", 300, 180);
	}
	else
	{
		for(int i=0; i<m_nNumProfiles; i++)
		{
			if(i==m_nCurrentControl)
				m_bfWhite.RenderText(m_pProfiles[i].szLastPlayed, 180, 180+(i*25));
			else
				m_bfFont.RenderText(m_pProfiles[i].szLastPlayed, 180, 180+(i*25));
			char buffer[128];
			sprintf_s(buffer, 128, "%i:%i:%i",
				((int)m_pProfiles[i].fGameTime)/3600,
				(((int)m_pProfiles[i].fGameTime)%3600)/60,
				((((int)m_pProfiles[i].fGameTime)%3600)%60));
			if(i==m_nCurrentControl)
				m_bfWhite.RenderText(buffer, 650, 180+(i*25));
			else
				m_bfFont.RenderText(buffer, 650, 180+(i*25));
		}
	}

	if(m_bError)
	{
		m_bfFont.RenderText("Error: Can't save more\nthan 8 profiles.", 135, 490);
	}

	m_bfFont.RenderText("Press <ESC> to Exit", CGame::GetInstance()->GetScreenWidth()/3+100, CGame::GetInstance()->GetScreenHeight()-50);

	CMovementControl::GetInstance()->RenderCursor();
}