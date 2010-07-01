#ifndef COptionsMenuState_h__
#define COptionsMenuState_h__


#include "../GameObjects/CBMPFont.h"
#include "IGameState.h"

class CBitmapFontEngine;

class COptionsMenuState : public IGameState
{
	CBMPFont m_bfFont;

	int m_nBGImageID;
	int m_nSliderImageID;

	COptionsMenuState();
	~COptionsMenuState();
	COptionsMenuState(const COptionsMenuState&);
	COptionsMenuState& operator=(const COptionsMenuState&);
public:
	static COptionsMenuState* GetInstance();

	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
};
#endif // COptionsMenuState_h__