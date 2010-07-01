#ifndef COptionsMenuState_h__
#define COptionsMenuState_h__

#include <windows.h>
#include <vector>
#include <string>
#include "../GameObjects/CBMPFont.h"
#include "IGameState.h"
using std::vector;
using std::string;

class CBitmapFontEngine;

class COptionsMenuState : public IGameState
{
	typedef struct 
	{
		RECT rArea;
		string szIdentifier;
	} tMenuControl;

	CBMPFont m_bfFont;

	vector<tMenuControl> m_vControls;

	tMenuControl* m_pCurrentControl;

	int m_nBGImageID;
	int m_nSliderImageID;

	int m_nMouseX;
	int m_nMouseY;
	int m_nMousePrevX;
	int m_nMousePrevY;

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