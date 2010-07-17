#include "precompiled_header.h"
#include "CGame.h"
#include "States\CGamePlayState.h"
#include "States\CMainMenuState.h"
#include "States\CSplashState.h"
#include "States\CTestState.h"
#include "Managers\MovementControl.h"
#include "GameObjects\CAnimationManager.h"
#include <fstream>
#include "GameObjects\CItemFactory.h"
#include "SGD Wrappers\CSGD_FModManager.h"
using std::ifstream;
using std::ios_base;

CGame::~CGame()
{
	m_bWindowed				= false;
	m_dwPreviousTimeStamp	= 0;
	m_dwTimeStamp			= 0;
	m_fElapsedTime			= 0.0f;
	m_fGameTime				= 0.0f;
	m_nWindowHeight			= -1;
	m_nWindowWidth			= -1;

	m_pD3D					= NULL;
	m_pDI					= NULL;
	m_pTM					= NULL;
	m_pOM					= NULL;
	m_pCM					= NULL;
}

CGame::CGame()
{
	CItemFactory::GetInstance();
}

bool CGame::Input()
{
	m_pDI->ReadDevices(); //	usually called ONCE a frame

	if(m_pDI->KeyDown(DIK_RMENU) || m_pDI->KeyDown(DIK_LMENU))
	{
		if (m_pDI->KeyPressed(DIK_RETURN))
		{
			ToggleFullScreen();
			return true;
		}
	}

	if (m_vStateStack[m_vStateStack.size() - 1])
		return m_vStateStack[m_vStateStack.size() - 1]->Input();

	return true;
}

void CGame::Render()
{
	m_pD3D->Clear(0,0,0);
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();

	for (unsigned int i = 0; i < m_vStateStack.size(); i++)
	{
		if (m_vStateStack[i])
			m_vStateStack[i]->Render();
	}

	//////////////////////////////////////////////////////////////////////////
	char* buffer = new char[100];
	sprintf_s(buffer, 100, "mouse x: %d; y: %d", CMovementControl::GetInstance()->MousePosX(), CMovementControl::GetInstance()->MousePosY());
	m_pD3D->DrawText(buffer, 10, 300, 255, 255, 255);
	delete[] buffer;
	//////////////////////////////////////////////////////////////////////////

	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();
	m_pD3D->Present();
}

void CGame::Update()
{
	m_fGameTime += m_fElapsedTime;

	if (m_vStateStack[m_vStateStack.size() - 1])
		m_vStateStack[m_vStateStack.size() - 1]->Update(m_fElapsedTime);

}

void CGame::ToggleFullScreen()
{
	m_bWindowed=!m_bWindowed;
	m_pD3D->ChangeDisplayParam(m_nWindowWidth, m_nWindowHeight, m_bWindowed);
	ShowCursor(FALSE);
}

void CGame::SettingsChanged()
{
	//reload keybinds and settings and make changes here
	ifstream fin;
	std::string szPath = ResourcePath()+"Settings.bin";
	fin.open(szPath.c_str(), ios_base::binary | ios_base::in);

	if(fin.fail())
	{
		fin.clear(ios_base::failbit);
		m_bWindowed=true;
		m_nSFXVolume=50;
		m_nVoiceVolume=50;
		m_nMusicVolume=50;
		m_arrKeybinds[0]=DIK_1;
		m_arrKeybinds[1]=DIK_2;
		m_arrKeybinds[2]=DIK_3;
		m_arrKeybinds[3]=DIK_4;
		m_arrKeybinds[4]=DIK_5;
		m_arrKeybinds[5]=DIK_Q;
		m_arrKeybinds[6]=DIK_W;
		m_arrKeybinds[7]=DIK_E;
		m_arrKeybinds[8]=DIK_R;
		m_arrKeybinds[9]=DIK_A;
		m_arrKeybinds[10]=DIK_S;
		m_arrKeybinds[11]=DIK_D;
		m_arrKeybinds[12]=DIK_F;
		m_arrKeybinds[13]=DIK_UP;
		m_arrKeybinds[14]=DIK_DOWN;
		m_arrKeybinds[15]=DIK_LEFT;
		m_arrKeybinds[16]=DIK_RIGHT;
		m_bWindowed=false;
		ToggleFullScreen();
	}
	else if(fin.is_open() && fin.good())
	{
		fin.read((char*)&m_bWindowed, sizeof(bool));
		fin.read((char*)&m_nSFXVolume, sizeof(int));
		fin.read((char*)&m_nVoiceVolume, sizeof(int));
		fin.read((char*)&m_nMusicVolume, sizeof(int));

		for(int i=0; i<18; i++)
		{
			fin.read((char*)&m_arrKeybinds[i], sizeof(unsigned char));
		}
		m_bWindowed=!m_bWindowed;
		ToggleFullScreen();
		fin.close();
	}
}

void CGame::ChangeState( IGameState* pNewState )
{
	for (unsigned int i = 0; i < m_vStateStack.size(); i++)
	{
		m_vStateStack[i]->Exit();
	}

	m_vStateStack.clear();

	PushState(pNewState);
}

CGame* CGame::GetInstance()
{
	static CGame instance;
	return &instance;
}

void CGame::Initialize( HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed )
{
	// Get pointers to singletons
	m_pD3D	= CSGD_Direct3D::GetInstance();
	m_pDI	= CSGD_DirectInput::GetInstance();
	m_pTM	= CSGD_TextureManager::GetInstance();
	m_pCM	= CCollisionManager::GetInstance();
	m_pOM	= CObjectManager::GetInstance();
	m_pAM	= CAnimationManager::GetInstance();
 	m_pMC   = CMovementControl::GetInstance();

	// Initialize singletons
	m_pD3D->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed, true);
	m_pTM->InitTextureManager(m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite());
	m_pDI->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE, DI_MOUSE);
	m_pCAM = new CCamera();
	m_pMC->Init();

	CSGD_FModManager::GetInstance()->InitFModManager(hWnd);

	//	Store initial program variables
	m_nWindowHeight=nScreenHeight;
	m_nWindowWidth=nScreenWidth;
	m_bWindowed=bIsWindowed;

	m_strResourcePath	= "resource/";
	m_strGraphicsPath	= ResourcePath() + "Graphics/";
	m_strSoundPath		= ResourcePath() + "Sound/";
	m_strFontPath		= ResourcePath() + "Fonts/";


	CGamePlayState::GetInstance();
	ChangeState(CMainMenuState::GetInstance());
	PushState(CSplashState::GetInstance());

	SettingsChanged();
}

bool CGame::Main()
{	
	DWORD dwStartTimeStamp = GetTickCount();
	m_fElapsedTime = (float)(dwStartTimeStamp - m_dwPreviousTimeStamp) / 1000.0f;
	m_dwPreviousTimeStamp = dwStartTimeStamp;

	//	3 steps a game does during execution:
	//		1. Input
	if(Input()==false)
		return false;
	//		2. Update
	Update();
	//		3. Draw
	Render();

	return true;
}

void CGame::PopState()
{
	if (m_vStateStack[m_vStateStack.size() - 1])
		m_vStateStack[m_vStateStack.size() - 1]->Exit();

	m_vStateStack.pop_back();
}

void CGame::PushState( IGameState* pNewState )
{
	m_vStateStack.push_back(pNewState);

	if (m_vStateStack[m_vStateStack.size() - 1])
		m_vStateStack[m_vStateStack.size() - 1]->Enter();
}

void CGame::Shutdown()
{
	ChangeState(NULL);

	if (m_pCM)
	{
		m_pCM = NULL;
	}

	if (m_pOM)
	{
		m_pOM = NULL;
	}

	if (m_pTM)
	{
		m_pTM->ShutdownTextureManager();
		m_pTM = NULL;
	}

	if (m_pDI)
	{
		m_pDI->ShutdownDirectInput();
		m_pDI = NULL;
	}

	if (m_pD3D)
	{
		m_pD3D->ShutdownDirect3D();
		m_pD3D = NULL;
	}
	m_pD3D				= NULL;
	m_pDI				= NULL;
	m_pTM				= NULL;
	m_pOM				= NULL;
	m_pCM				= NULL;

	CCodeProfiler::GetInstance()->Output("codeprofiler test --");
}
