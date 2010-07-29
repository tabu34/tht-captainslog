//how to play...

#ifndef CHelpState_h__
#define CHelpState_h__

#include "IGameState.h"

class CHelpState : public IGameState
{
	int curPage;
	int m_nBGImage[2];

	CHelpState();
	CHelpState(const CHelpState&);
	~CHelpState();
	CHelpState& operator=(const CHelpState&);
public:
	static CHelpState* GetInstance();

	void Enter();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
	void Exit();
};
#endif // CHelpState_h__