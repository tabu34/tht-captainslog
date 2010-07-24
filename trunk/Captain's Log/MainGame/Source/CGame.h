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


	int SFXVolume() { return m_nSFXVolume; }
	int MusicVolume() { return m_nMusicVolume; }
	int VoiceVolume() { return m_nVoiceVolume; }

	void SFXVolume(int val) { m_nSFXVolume = val; }
	void MusicVolume(int val) { m_nMusicVolume = val; }
	void VoiceVolume(int val) { m_nVoiceVolume = val; }


	float ElapsedTime() const { return m_fElapsedTime; }

	void			ToggleFullScreen();

	void			SettingsChanged();

	// Accessors
	int				GetScreenHeight(void) {return m_nWindowHeight;}
	int				GetScreenWidth(void) {return m_nWindowWidth;}
	bool			IsWindowed(void) {return m_bWindowed;}
	enum {KEY_UNIT1, KEY_UNIT2, KEY_UNIT3, KEY_UNIT4, KEY_ALLUNIT, KEY_ABILITY1, KEY_ABILITY2, KEY_ABILITY3, KEY_ABILITY4,
	KEY_INV1, KEY_INV2, KEY_INV3, KEY_INV4, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
	unsigned char	KeyBinds(int index_key) {return m_arrKeybinds[index_key];}
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