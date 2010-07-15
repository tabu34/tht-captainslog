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

void CSaveState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("saveScreen.png").c_str());
	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
	m_bfWhite.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFFFFFFFF);
	m_bfWhite.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
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
			m_bfFont.RenderText(m_pProfiles[i].szLastPlayed, 180, 180+(i*25));
			string szTimePlayed;
			szTimePlayed += ((int)m_pProfiles[i].fGameTime)/3600;
			szTimePlayed += ':';
			szTimePlayed += (((int)m_pProfiles[i].fGameTime)%3600)/60;
			szTimePlayed += ':';
			szTimePlayed += (((int)m_pProfiles[i].fGameTime)%3600)%60;
			m_bfFont.RenderText(const_cast<char*>(szTimePlayed.c_str()), 650, 180+(i*25));
		}
	}
	m_bfFont.RenderText("Press <ESC> to Exit", CGame::GetInstance()->GetScreenWidth()/3+100, CGame::GetInstance()->GetScreenHeight()-50);

	CMovementControl::GetInstance()->RenderCursor();
}