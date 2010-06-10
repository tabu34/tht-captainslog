#ifndef CBMPFont_h__
#define CBMPFont_h__

#include <vector>
#include <Windows.h>
using namespace std;

class CBMPFont
{
	vector<RECT>	m_vLetterRects;
	int				m_nImageID;
	float			m_fScaleX;
	float			m_fScaleY;
	int				m_nKerning;

public:
	void	SetUp(char* szFileName, float fScaleX, float fScaleY, int nKerning);
	void	RenderText(char* szString);
	void	AddLetter(char* szLetter, RECT rRectangle);
};
#endif // CBMPFont_h__