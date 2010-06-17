#ifndef CBMPFont_h__
#define CBMPFont_h__

#include <vector>
#include <Windows.h>
using namespace std;

class CBMPFont
{
	RECT			m_rLetterRects[256];
	int				m_nStartChar;
	int				m_nImageID;
	float			m_fScaleX;
	float			m_fScaleY;
	int				m_nKerning;
	DWORD			m_dwFontColor;

public:

	void	Initialize(const char* szFileName, float fScaleX, float fScaleY, int nKerning, DWORD dwKeyColor = 0, DWORD dwFontColor = -1);
	void	SetUp(float fScaleX, float fScaleY, int nKerning, DWORD dwFontColor = -1);
	void	RenderText(char* szString, int nPosX, int nPosY);
	void	LoadLetterRects(const char* szFileName);
};
#endif // CBMPFont_h__