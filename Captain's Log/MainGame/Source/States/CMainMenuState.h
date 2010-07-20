//////////////////////////////////////////////////////////////////////////////////////////////
//	File			:	"CMainMenuState.h"
//
//	Authors			:	Tim Smith, Daniel Makin
//
//	Purpose			:	To describe the functionality of the Main Menu game state
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MENUGAMESTATE_H_
#define _MENUGAMESTATE_H_

#include "IGameState.h"
#include "..\GameObjects\CBMPFont.h"

class CMainMenuState : public IGameState
{
	CBMPFont	m_bfFont;
	int			m_nMenuMusic;
	short		m_sCurrentChoice;

	int m_nMenuBG;
	int	m_nMenuCur[6];

	int m_nMouseX;
	int m_nMouseY;
	int m_nMousePrevX;
	int m_nMousePrevY;

	CMainMenuState(void);
	CMainMenuState(const CMainMenuState&);
	CMainMenuState& operator=(const CMainMenuState&);
	~CMainMenuState(void);
public:
	static CMainMenuState* GetInstance();

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};

#endif