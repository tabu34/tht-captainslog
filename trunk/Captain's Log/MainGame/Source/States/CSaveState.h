
#ifndef CSaveState_h__
#define CSaveState_h__

#include "IGameState.h"
#include "../GameObjects/CBMPFont.h"
#include "CLoadState.h"

class CSaveState : public IGameState
{
	int m_nBGImage;
	CBMPFont m_bfFont;
	CBMPFont m_bfWhite;

	int m_nMouseX;
	int m_nMouseY;
	int m_nMousePrevX;
	int m_nMousePrevY;

	int m_nNumProfiles;
	tProfileHeader *m_pProfiles;

	int m_nCurrentControl;
	int m_nMaxControls;

	CSaveState();
	CSaveState(const CSaveState&);
	~CSaveState();
	CSaveState& operator=(const CSaveState&);

	void LoadProfiles();
public:
	static CSaveState* GetInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();

};
#endif // CSaveState_h__