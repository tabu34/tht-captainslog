//////////////////////////////////////////////////////////////////////////////////////////////
//	File			:	"CGamePlayState.h"
//
//	Authors			:	Tim Smith, Daniel Makin
//
//	Purpose			:	To describe the functionality of the Game Play game state
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _THEGAMEPLAYGAMESTATE_H_
#define _THEGAMEPLAYGAMESTATE_H_

#include "IGameState.h"
#include "..\GameObjects\CPlayerUnit.h"
#include <vector>
#include "..\GameObjects\CItem.h"
using namespace std;

class CGamePlayState : public IGameState
{
	CPlayerUnit*	m_pPlayerArray;
	int				m_nLevel;
	int				m_nScore;

	CGamePlayState(void);
	CGamePlayState(const CGamePlayState&);
	CGamePlayState& operator=(const CGamePlayState&);
	~CGamePlayState(void);
public:
	static CGamePlayState* GetInstance();

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};

#endif