#ifndef COptionsMenuState_h__
#define COptionsMenuState_h__

#include <windows.h>
#include <vector>
#include <string>
#include "../GameObjects/CBMPFont.h"
#include "IGameState.h"
using std::vector;
using std::string;

class CBitmapFontEngine;

class COptionsMenuState : public IGameState
{
	typedef struct 
	{
		RECT rArea;
		string szIdentifier;
	} tMenuControl;

	CBMPFont m_bfFont;
	CBMPFont m_bfWhite;

	vector<tMenuControl> m_vControls;

	tMenuControl* m_pCurrentControl;

	int m_nBGImageID;
	int m_nSliderImageID;

	int m_nMouseX;
	int m_nMouseY;
	int m_nMousePrevX;
	int m_nMousePrevY;

	//actual game options
	int m_nMusicVolume;
	int m_nSFXVolume;
	int m_nVoiceVolume;
	unsigned char m_arrKeybinds[18];
	bool m_bWindowed;
	bool m_bPrevWindowed;

	int m_nSoundChangedID;

	bool m_bBinding;
	int m_nBindIndex;
	int m_nCurIndex;

	struct tKeyTimer 
	{
		float m_fKeyRepeatTimer;
		float m_fKeyRepeatRate;

		bool m_bKeyRepeat;
		float m_fFirstKeyRepeatTimer;
		float m_fFirstKeyRepeatRate;

		tKeyTimer()
		{
			m_fKeyRepeatTimer		= 0.0f;
			m_fKeyRepeatRate		= 0.15f;
			m_bKeyRepeat			= false;
			m_fFirstKeyRepeatTimer	= 0.0f;
			m_fFirstKeyRepeatRate	= 0.5f;
		}
	};

	tKeyTimer ktUpDownTimer;
	tKeyTimer ktLeftRightTimer;

	bool m_bError;
	float m_fErrorTimer;

	COptionsMenuState();
	~COptionsMenuState();
	COptionsMenuState(const COptionsMenuState&);
	COptionsMenuState& operator=(const COptionsMenuState&);

	void LoadSettings();
	void SaveSettings();
public:
	static COptionsMenuState* GetInstance();

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};
#endif // COptionsMenuState_h__