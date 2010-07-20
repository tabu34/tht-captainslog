#ifndef _LOADLEVELSTATE_H_
#define _LOADLEVELSTATE_H_

#include "IGameState.h"
#include "..\GameObjects\CBMPFont.h"

class CLoadLevelState : public IGameState
{
	int			m_nMenuBG;
	int			m_nLoadBar;
	int			m_nLevelNum;
	float		m_fPercentage;
	CBMPFont	m_ftText;

	CLoadLevelState(void);
	CLoadLevelState(const CLoadLevelState&);
	CLoadLevelState& operator=(const CLoadLevelState&);
	~CLoadLevelState(void);
public:
	static CLoadLevelState* GetInstance();
	void SetLoadLevel(int _nLevelNum) { m_nLevelNum = _nLevelNum; }
	void SetPercentage(float _fPercentage) { m_fPercentage = _fPercentage; }
	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Load(void);
	void Render(void);
	void Exit(void);
};

#endif