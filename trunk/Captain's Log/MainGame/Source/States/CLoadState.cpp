#include "precompiled_header.h"
#include "CLoadState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../CGame.h"
#include "../States/CGamePlayState.h"
#include "../Managers/MovementControl.h"
#include "CSaveState.h"
#include <fstream>
#include <string>
using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::string;

CLoadState::CLoadState()
{
	m_pProfiles = NULL;
}

CLoadState::~CLoadState()
{

}

CLoadState* CLoadState::GetInstance()
{
	static CLoadState instance;
	return &instance;
}

void CLoadState::LoadProfiles()
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

void CLoadState::DeleteProfile()
{
	//first, load in the entire file.
	ifstream fin;
	string szPath;
	szPath = CGame::GetInstance()->ResourcePath();
	szPath+="Save.bin";
	fin.open(szPath.c_str(), ios_base::in | ios_base::binary);

	tUnitSaveInfo** ppSaveData = NULL;

	if(m_pProfiles)
		delete[] m_pProfiles;
	m_pProfiles=NULL;
	if(fin.fail())
	{
		fin.clear(ios_base::failbit);

		m_nNumProfiles=0;
		m_nCurrentControl=-1;
		return;
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

		ofstream fout;
		fout.open(szPath.c_str(), ios_base::out | ios_base::trunc | ios_base::binary);
		if(fout.is_open() && fout.good())
		{
			int n = m_nNumProfiles-1;
			fout.write((char*)&n, sizeof(int));
			for(int i=0; i<m_nNumProfiles; i++)
			{
				if(i!=m_nCurrentControl)
				{
					fout.write((char*)&m_pProfiles[i], sizeof(tProfileHeader));
					int j=(m_pProfiles[i].nProfileSizeInBytes-sizeof(int))/sizeof(tUnitSaveInfo);
					fout.write((char*)&j, sizeof(int));
					fout.write((char*)ppSaveData[i], m_pProfiles[i].nProfileSizeInBytes - sizeof(int));
				}
			}
			fout.close();
		}

		m_nCurrentControl=-1;
		for(int i=0; i<m_nNumProfiles; i++)
			delete[] ppSaveData[i];

	if(ppSaveData)
		delete[] ppSaveData;

	LoadProfiles();
}

void CLoadState::LoadGame()
{
	int nOffset = 0;
	nOffset+=sizeof(int);
	for(int i=0; i<m_nNumProfiles; i++)
	{
		if(i==m_nCurrentControl)
		{
			nOffset+=sizeof(tProfileHeader);
			break;
		}
		else
		{
			nOffset+=sizeof(tProfileHeader);
			nOffset+=m_pProfiles[i].nProfileSizeInBytes;
		}
	}
	CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
	CGamePlayState::GetInstance()->LoadProfile(nOffset);
}

void CLoadState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("loadScreen.png").c_str());
	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_bfWhite.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFFFFFFFF);
	m_bfWhite.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_fErrorTimer=0.0f;
	m_bError=false;
	m_nCurrentControl=-1;
	LoadProfiles();
}

void CLoadState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage);
}

bool CLoadState::Input()
{
	m_nMouseX = CMovementControl::GetInstance()->MousePosX();
	m_nMouseY = CMovementControl::GetInstance()->MousePosY();
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->PopState();
	}

	//NOTE: 2 methods for exit:
	//1. Escape (pop state and do nothing else)
	//2. Load Game (change to GamePlayState and load game)

	RECT rSelectionBox = {135, 175, 807, 414};
	RECT rLoadButton = {135, 429, 443, 480};
	RECT rDeleteButton = {499, 429, 808, 480};
	POINT ptMouse = {m_nMouseX, m_nMouseY};

	if(CSGD_DirectInput::GetInstance()->MouseButtonPressed(0) && PtInRect(&rSelectionBox, ptMouse))
	{
		int nSelect = (m_nMouseY-180)/25;
		m_nCurrentControl = (nSelect>=0 && nSelect<m_nNumProfiles) ? nSelect : -1;
	}
	if(CSGD_DirectInput::GetInstance()->MouseButtonPressed(0) && PtInRect(&rLoadButton, ptMouse))
	{
		//load here...
		if(m_nCurrentControl==-1)
		{
			m_bError = true;
			m_fErrorTimer = 2.0f;
		}
		else
			LoadGame();
	}
	if(CSGD_DirectInput::GetInstance()->MouseButtonPressed(0) && PtInRect(&rDeleteButton, ptMouse))
	{
		//delete profile here
		if(m_nCurrentControl==-1)
		{
			m_bError = true;
			m_fErrorTimer = 2.0f;
		}
		else
			DeleteProfile();
	}

	m_nMousePrevX = m_nMouseX;
	m_nMousePrevY = m_nMouseY;
	return true;
}

void CLoadState::Update(float fElapsedTime)
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
		if(m_fErrorTimer<=0.0f)
			m_bError=false;
	}
}

void CLoadState::Render()
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
		m_bfFont.RenderText("Error: No Profile Selected", 135, 490);
	}

	m_bfFont.RenderText("Press <ESC> to Exit", CGame::GetInstance()->GetScreenWidth()/3+100, CGame::GetInstance()->GetScreenHeight()-50);

	CMovementControl::GetInstance()->RenderCursor();
}