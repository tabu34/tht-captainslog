//gamewin

#ifndef CGameWinState_h__
#define CGameWinState_h__

#include "IGameState.h"

class CGameWinState : public IGameState
{
	int m_nBGImage;

	CGameWinState();
	CGameWinState(const CGameWinState&);
	~CGameWinState();
	CGameWinState& operator=(const CGameWinState&);
public:
	static CGameWinState* GetInstance();

	void Enter();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
	void Exit();
};
#endif // CGameWinState_h__