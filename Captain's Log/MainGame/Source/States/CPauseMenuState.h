#ifndef CPauseMenuState_h__
#define CPauseMenuState_h__

#include "IGameState.h"
#include "..\GameObjects\CBMPFont.h"

//class CBitmapFontEngine;

class CPauseMenuState : public IGameState
{
	CBMPFont	m_bfFont;
	short		m_sCurrentChoice;

	CPauseMenuState(void);
	CPauseMenuState(const CPauseMenuState&);
	CPauseMenuState& operator=(const CPauseMenuState&);
	~CPauseMenuState(void);
public:
	static CPauseMenuState* GetInstance();

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};
#endif // CPauseMenuState_h__
