#ifndef CMovementControl_h__
#define CMovementControl_h__

class CBase;
class CEventSystem;
class CSGD_DirectInput;
class CCamera;
#include <vector>
using namespace std;

#include <windows.h>

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
	POINT				m_pCursorLocation;

	CMovementControl(void) {};
	~CMovementControl(void) {};
	CMovementControl(CMovementControl&) {};
	CMovementControl& operator=(CMovementControl&) {};
public:
	int		MousePosX()	{ return m_pCursorLocation.x; }
	int		MousePosY()	{ return m_pCursorLocation.y; }

	static CMovementControl* GetInstance();
	void Init();
	void Input();
	void CheckDragRect();
	void RenderDragRect();
	void RenderCursor();
	void Shutdown();
};

#endif
