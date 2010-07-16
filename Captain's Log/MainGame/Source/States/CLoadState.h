

#ifndef CLoadState_h__
#define CLoadState_h__

#include "IGameState.h"
#include "../GameObjects/CBMPFont.h"

typedef struct  
{
	int nProfileSizeInBytes;
	float fGameTime;
	char szLastPlayed[256];
} tProfileHeader;

class CLoadState : public IGameState
{
	int m_nBGImage;
	CBMPFont m_bfFont;
	CBMPFont m_bfWhite;

	bool m_bError;
	float m_fErrorTimer;

	int m_nMouseX;
	int m_nMouseY;
	int m_nMousePrevX;
	int m_nMousePrevY;

	int m_nNumProfiles;
	tProfileHeader *m_pProfiles;

	int m_nCurrentControl;
	int m_nMaxControls;

	CLoadState();
	CLoadState(const CLoadState&);
	~CLoadState();
	CLoadState& operator=(const CLoadState&);

	void LoadProfiles();
	void LoadGame();
	void DeleteProfile();
public:
	static CLoadState* GetInstance();

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();
};
#endif // CLoadState_h__