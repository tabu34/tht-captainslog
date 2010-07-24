//gamewin

#ifndef CCreditsState_h__
#define CCreditsState_h__

#include "IGameState.h"

class CCreditsState : public IGameState
{
	int m_nBGImage;

	CCreditsState();
	CCreditsState(const CCreditsState&);
	~CCreditsState();
	CCreditsState& operator=(const CCreditsState&);
public:
	static CCreditsState* GetInstance();

	void Enter();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
	void Exit();
};
#endif // CCreditsState_h__