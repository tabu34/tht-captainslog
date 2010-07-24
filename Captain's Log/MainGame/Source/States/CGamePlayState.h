//////////////////////////////////////////////////////////////////////////////////////////////
//	File			:	"CGamePlayState.h"
//
//	Authors			:	Tim Smith, Daniel Makin
//
//	Purpose			:	To describe the functionality of the Game Play game state
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _THEGAMEPLAYGAMESTATE_H_
#define _THEGAMEPLAYGAMESTATE_H_

#include "IGameState.h"
#include "..\Managers\CMessageSystem.h"
#include "..\GameObjects\CParticleEmitter.h"
#include "..\GameObjects\CBMPFont.h"
#include "..\GameObjects\CPlayerUnit.h"
#include "..\GameObjects\CItem.h"
#include <vector>
#include <string>
using namespace std;

class CHUDButton
{
	POINT	m_pLocation;
	SIZE	m_sSize;
	string	m_szName;
	void	(*actionFunction)();
	int		m_nTextureID;
	bool	m_bVisible;
public:

	CHUDButton(int _x, int _y, int _w, int _h, string _szName, void(*_val)(),  int _nTexture, bool _vis = true)
	{
		m_pLocation.x = _x;
		m_pLocation.y = _y;
		m_sSize.cx = _w;
		m_sSize.cy = _h;
		m_szName = _szName;
		actionFunction = _val;
		m_nTextureID = _nTexture;
		m_bVisible = _vis;
	}

	void Activate()
	{
		if(actionFunction != NULL)
			(*actionFunction)();
	}

	// Accessors 
	POINT	Point()			{ return m_pLocation;	}
	SIZE	Size()			{ return m_sSize;		}
	string	Name()			{ return m_szName;		}
	void *	ActionFunction(){ return actionFunction;}
	int		TextureID()		{ return m_nTextureID;	}
	bool	Visible()		{ return m_bVisible;	}

	RECT GetCollisionRect()	{ 
		RECT output; 
		output.left = m_pLocation.x;
		output.top = m_pLocation.y;
		output.right = output.left + m_sSize.cx;
		output.bottom = output.top + m_sSize.cy;
		return output;
	}

	// Mutators
	void	Point(POINT _val)	{ m_pLocation = _val;	}
	void	Point(int _x, int _y)	{ m_pLocation.x = _x;	m_pLocation.y = _y;}
	void	Size(SIZE _val)		{ m_sSize = _val;		}
	void	Name(string _val)	{ m_szName = _val;		}
	void	ActionFunction( void(*_val)()) { actionFunction = _val; }
	void	TextureID(int _val)	{ m_nTextureID = _val;	}
	void	Visible(bool _val)	{ m_bVisible = _val;	}

};


class CGamePlayState : public IGameState
{
	CPlayerUnit*		m_pPlayerArray[4];
	int					m_nLevel;
	int					m_nScore;
	int					m_nBG;
	int					m_nMiniMap;
	int					m_nGunshotSound;
	int					m_nSelectionCircle;
	int					m_nToolTipOffsetY;
	int					m_nBGMusic;
	
	// Interface Elements
	CBMPFont			m_ftTextSmall;
	CBMPFont			m_ftTextSmallShadow;
	CBMPFont			m_ftTextLarge;
	CBMPFont			m_ftTextLargeShadow;
	vector<CHUDButton>	m_vButtons;
	vector<CHUDButton>	m_vButtonInstances;

	// Timed Speech
	float				m_nCurCount;
	string				m_szSpeechText;

	float				m_fTotalGameTime;
	int					m_nKills;

	// Tooltip
	string				m_szTooltipText;

	// Communication between HUD and movement control
	string				m_szSelectedCommand;

	//cheats
	string				m_szCheatBuffer;
	bool				m_bGodMode;
	bool				m_bNoCooldown;
	bool				m_bEnteringCheat;

	// Particles
	CParticleEmitter	m_peEmitter;
	int					m_nParticleImageID;

	CGamePlayState(void);
	CGamePlayState(const CGamePlayState&);
	CGamePlayState& operator=(const CGamePlayState&);
	~CGamePlayState(void);
public:
	static CGamePlayState* GetInstance();

	static void MessageProc(CBaseMessage* pMSG);

	int NextLevel() { return ++m_nLevel; }
	void SetLevel(int _lvl) { m_nLevel = _lvl; }

	// HUD Functions
	vector<CHUDButton> GetButtons() { return m_vButtons; }
	int  FindButton(string _name);
	void RenderSmallShadowText(char* _text, int _x, int _y);
	void RenderLargeShadowText(char* _text, int _x, int _y);
	string CurrentCommand(){return m_szSelectedCommand;}
	void ClearCommand(){m_szSelectedCommand="";}
	void SetCommand(string val) { m_szSelectedCommand = val; }
	void RenderMiniMap();
	void InitHud();
	bool CheckButtonInput();
	int GetSelectionCircleID() { return m_nSelectionCircle; }
	
	void CheckCheats();

	void LoadProfile(int nOffsetInBytes);
	float GetTime(){return m_fTotalGameTime;}

	//cheats
	bool GodMode(){return m_bGodMode;}
	bool NoCooldown(){return m_bNoCooldown;}

	int Kills(){return m_nKills;}
	void Kills(int nKills){m_nKills=nKills;}

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void RenderHUD(void);
	void Exit(void);

	void LoadNextLevel();

	int GunshotSoundID() { return m_nGunshotSound; }
};

#endif