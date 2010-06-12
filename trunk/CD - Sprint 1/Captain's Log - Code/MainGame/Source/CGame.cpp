#include "CGame.h"
#include "States\CGamePlayState.h"
#include "States\CMainMenuState.h"
#include "States\CTestState.h"

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
	m_pCAM					= NULL;
}

CGame::CGame()
{

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

	// Initialize singletons
	m_pD3D->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed, true);
	m_pTM->InitTextureManager(m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite());
	m_pDI->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE);

	//	Store initial program variables
	m_nWindowHeight=nScreenHeight;
	m_nWindowWidth=nScreenWidth;
	m_bWindowed=bIsWindowed;

	m_strResourcePath	= "resource/";
	m_strGraphicsPath	= ResourcePath() + "Graphics/";
	m_strSoundPath		= ResourcePath() + "Sound/";
	m_strFontPath		= ResourcePath() + "Fonts/";


	CGamePlayState::GetInstance();
	ChangeState(CTestState::GetInstance());
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

	if (m_pCAM)
	{
		m_pCAM = NULL;
	}

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
	m_pCAM				= NULL;
}
