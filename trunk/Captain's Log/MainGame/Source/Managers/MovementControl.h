#ifndef CMovementControl_h__
#define CMovementControl_h__

class CBase;
class CEventSystem;
class CCamera;
class CMarine;
class CMedic;
class CHeavy;
class CScout;
class CUnit;
#include <vector>
using namespace std;

#include <windows.h>
#include "..\SGD Wrappers\CSGD_DirectInput.h"

class CMovementControl
{
	vector<CBase*>*		m_vObjectList;
	vector<CBase*>*		m_vSelected;
	CEventSystem*		m_esEventSystem;
	CSGD_DirectInput*	m_DI;
	CCamera*			m_cCAM;

	// Unit selection variables
	bool				m_bDragging;
	POINT				m_ptStart;

	// Cursor variables
	int					m_nCursorImageID;

	//	references to the four player units (for individual unit selection via keyboard)
	CMarine*			m_pMarine;
	CHeavy*				m_pHeavy;
	CScout*				m_pScout;
	CMedic*				m_pMedic;

	//	reference to the unit that you are selecting an ability for
	CUnit*				m_pUnitAbilitySelection;

	//	ID of the ability in the unit's vector of abilities
	int					m_nUnitAbilityPosition;

	CMovementControl(void) {};
	~CMovementControl(void) {};
	CMovementControl(CMovementControl&) {};
	CMovementControl& operator=(CMovementControl&) {};
public:
	int		MousePosX()	{ return CSGD_DirectInput::GetInstance()->MouseGetPosX(); }
	int		MousePosY()	{ return CSGD_DirectInput::GetInstance()->MouseGetPosY(); }

	static CMovementControl* GetInstance();
	vector<CBase*>* GetSelectedUnits(){return m_vSelected;}
	void Init();
	void Input();
	void CheckDragRect();
	void RenderDragRect();
	void RenderCursor();
	void Shutdown();
	void UpdateCamera(float fElapsedTime);
	void SetPlayerUnits(CMarine* pMarine, CHeavy* pHeavy, CScout* pScout, CMedic* pMedic) { m_pMarine = pMarine; m_pHeavy=pHeavy; m_pScout=pScout; m_pMedic=pMedic;}

	void SetUnit(CUnit* val) { m_pUnitAbilitySelection = val; }
	void SetPosition(int val) { m_nUnitAbilityPosition = val; }
};

#endif
