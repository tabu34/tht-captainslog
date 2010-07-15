#ifndef CGameOverState_h__
#define CGameOverState_h__

#include "IGameState.h"
#include "..\GameObjects\CBMPFont.h"

class CGameOverState : public IGameState
{
	CBMPFont m_bfFont;

	int m_nBGImage;

	CGameOverState();
	CGameOverState(const CGameOverState&);
	~CGameOverState();
	CGameOverState& operator=(const CGameOverState&);
public:
	static CGameOverState* GetInstance();

	void Enter();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
	void Exit();

};
#endif // CGameOverState_h__