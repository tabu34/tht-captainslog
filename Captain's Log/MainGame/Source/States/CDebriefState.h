//Splash screen...

#ifndef CDebriefState_h__
#define CDebriefState_h__

#include "IGameState.h"
#include "..\GameObjects\CBMPFont.h"

class CDebriefState : public IGameState
{
	CBMPFont m_bfFont;

	int m_nBGImage;

	CDebriefState();
	CDebriefState(const CDebriefState&);
	~CDebriefState();
	CDebriefState& operator=(const CDebriefState&);
public:
	static CDebriefState* GetInstance();

	void Enter();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
	void Exit();

};
#endif // CDebriefState_h__