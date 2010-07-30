
#ifndef CSaveState_h__
#define CSaveState_h__

#include "IGameState.h"
#include "../GameObjects/CBMPFont.h"
#include "CLoadState.h"

typedef struct 
{
	bool				bBurned;
	bool				bCloaked;
	bool				bInvulnerable;
	bool				bRanged;
	bool				bStunned;
	float				fAttackDamage;
	float				fAttackSpeed;
	float				fMovementSpeed;
	int					fAttackRange;
	int					nArmor;
	int					nCurHealth;
	int					nHealthRegenRate;
	int					nLevel;
	int					nMaxHealth;
	int					nSightRange;
	int					nSubType;
	int					nEnemyClass;
	float				fPosX;
	float				fPosY;
	int					nType;

	int		nItemName[4];
	int		nItemType[4];
	int		nAmountType[4];
	int		nAmountCategory[4];
	float	fAmount[4];
} tUnitSaveInfo;

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

	bool m_bError;
	float m_fErrorTimer;

	CSaveState();
	CSaveState(const CSaveState&);
	~CSaveState();
	CSaveState& operator=(const CSaveState&);

	void LoadProfiles();
public:
	static CSaveState* GetInstance();

	void Save(int nSlot, float fGameTime, tUnitSaveInfo* pData, int numUnits);
	void SaveCurrent(int nSlot);

	void Enter();
	void Exit();
	bool Input();
	void Update(float fElapsedTime);
	void Render();

};
#endif // CSaveState_h__