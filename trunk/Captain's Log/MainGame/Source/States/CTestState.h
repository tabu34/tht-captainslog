#ifndef CTestState_h__
#define CTestState_h__


#include "IGameState.h"
#include "..\GameObjects\CBMPFont.h"
#include "..\GameObjects\CMarine.h"
#include "..\Managers\CMessageSystem.h"

class CTestState : public IGameState
{
	CMarine		Marine1, Marine2;
	CMarine		temporaryBlocker;
	CMarine		testEnemy;
	int			m_nBackgroundID;
	CBMPFont	testFont;

	CTestState(void);
	CTestState(const CTestState&);
	CTestState& operator=(const CTestState&);
	~CTestState(void);
public:
	static CTestState* GetInstance();

	static void MessageProc(CBaseMessage* pMSG);

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};
#endif // CTestState_h__