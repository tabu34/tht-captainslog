//Splash screen...

#ifndef CSplashState_h__
#define CSplashState_h__

#include "IGameState.h"
#include "..\GameObjects\CBMPFont.h"

class CSplashState : public IGameState
{
	CBMPFont m_bfFont;

	int m_nBGImage;

	CSplashState();
	CSplashState(const CSplashState&);
	~CSplashState();
	CSplashState& operator=(const CSplashState&);
public:
	static CSplashState* GetInstance();

	void Enter();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
	void Exit();

};
#endif // CSplashState_h__