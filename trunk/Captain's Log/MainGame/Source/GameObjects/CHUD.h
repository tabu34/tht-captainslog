#ifndef CHUD_h__
#define CHUD_h__

#include "..\Managers\CCamera.h"
#include <string>
#include "CBMPFont.h"
using namespace std;

class CHUD
{
	int				m_nHUDImageID;
	int				m_nMarkerImageID;
	int**			m_nCharacterHealth;
	string			m_strDialogue;
	CBMPFont		m_cFont;

public:
	void	Setup(int* nC1Health, int* nC2Health, int* nC3Health, int* nC4Health);
	void	Update(float fElapsedTime);
	void	Render();

};
#endif // CHUD_h__