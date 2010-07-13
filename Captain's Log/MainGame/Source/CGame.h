#ifndef CGame_h__
#define CGame_h__

#include <string>
#include <vector>
#include "Managers\CCamera.h"
#include "Managers\CCollisionManager.h"
#include "Managers\CObjectManager.h"
#include "Managers\MovementControl.h"
#include "GameObjects\CAnimationManager.h"
#include "SGD Wrappers\CSGD_Direct3D.h"
#include "SGD Wrappers\CSGD_DirectInput.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "States\IGameState.h"
using namespace std;

class CGame
{
	bool					m_bWindowed;
	DWORD					m_dwPreviousTimeStamp;
	DWORD					m_dwTimeStamp;
	float					m_fElapsedTime;
	float					m_fGameTime;
	int						m_nWindowHeight;
	int						m_nWindowWidth;
	vector<IGameState*>		m_vStateStack;
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CObjectManager*			m_pOM;
	CCollisionManager*		m_pCM;
	CCamera*				m_pCAM;
	CAnimationManager*		m_pAM;
	CMovementControl*		m_pMC;

	POINT					m_ptMousePos;

	// Directory Variables /////////////////////
	string					m_strResourcePath;
	string					m_strGraphicsPath;
	string					m_strSoundPath;
	string					m_strFontPath;
	////////////////////////////////////////////

	//Game Options
	int						m_nSFXVolume;
	int						m_nMusicVolume;
	int						m_nVoiceVolume;
	unsigned char			m_arrKeybinds[18];
	////////////////////////////////////////////

	~CGame();
	CGame();
	CGame(CGame&);
	CGame& operator=(CGame&);

	bool			Input();
	void			Render();
	void			Update();


public:


	void			ToggleFullScreen();

	void			SettingsChanged();

	// Accessors
	int				GetScreenHeight(void) {return m_nWindowHeight;}
	int				GetScreenWidth(void) {return m_nWindowWidth;}
	bool			IsWindowed(void) {return m_bWindowed;}
	CCamera*		GetCamera() { return m_pCAM; }

	string			ResourcePath() const { return m_strResourcePath; }
	string			GraphicsPath() const { return m_strGraphicsPath; }
	string			SoundPath() const { return m_strSoundPath; }
	string			FontPath() const { return m_strFontPath; }

	string			GraphicsPath(char * fileName) { return GraphicsPath() + fileName; }
	string			SoundPath(char* fileName) { return SoundPath() + fileName; }
	string			FontPath(char* fileName) { return FontPath() + fileName; }
	//

	void			ChangeState(IGameState* pNewState);
	static CGame*	GetInstance();
	void			Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed);
	bool			Main();
	void			PopState();
	void			PushState(IGameState* pNewState);
	void			Shutdown();


};
#endif // CGame_h__