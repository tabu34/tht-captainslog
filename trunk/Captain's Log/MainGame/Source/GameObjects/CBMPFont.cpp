#include "CBMPFont.h"
#include <fstream>
#include "..\Managers\CFileManager.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
using namespace std;

void CBMPFont::Initialize( const char* szFileName, float fScaleX, float fScaleY, int nKerning, DWORD dwKeyColor, DWORD dwFontColor)
{
	m_nImageID = CSGD_TextureManager::GetInstance()->LoadTexture(szFileName, dwKeyColor);
	SetUp(fScaleX, fScaleY, nKerning, dwFontColor);
}

void CBMPFont::SetUp( float fScaleX, float fScaleY, int nKerning, DWORD dwFontColor)
{
	m_fScaleX = fScaleX;
	m_fScaleY = fScaleY;
	m_nKerning = nKerning;
	m_dwFontColor = dwFontColor;
}

void CBMPFont::RenderText( char* szString, int nPosX, int nPosY )
{
	for (unsigned int i = 0; i < strlen(szString); i++)
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nPosX, nPosY, m_fScaleX, m_fScaleY, &(m_rLetterRects[szString[i]]), 0, 0, 0, m_dwFontColor);
		nPosX = nPosX + m_nKerning + m_rLetterRects[szString[i]].right - m_rLetterRects[szString[i]].left;
	}
}

void CBMPFont::LoadLetterRects( const char* szFileName )
{
	CFileManager::tFontFileStruct fftFileStruct;

	fftFileStruct.szFilePath = new char[strlen(szFileName) + 1];
	strcpy_s(fftFileStruct.szFilePath, strlen(szFileName) + 1, szFileName);

	CFileManager::GetInstance()->LoadBitmapFont(&fftFileStruct);

	short nNumCols = fftFileStruct.nImageWidth / fftFileStruct.nCellWidth;

	m_nStartChar = fftFileStruct.nStartChar;

	for (int i = m_nStartChar; i < 256; i++)
	{
		m_rLetterRects[i].top = fftFileStruct.nCellHeight * ((i-m_nStartChar) / nNumCols);
		m_rLetterRects[i].bottom = m_rLetterRects[i].top + fftFileStruct.nCellHeight;
		m_rLetterRects[i].left = fftFileStruct.nCellWidth * ((i-m_nStartChar) % nNumCols);
		m_rLetterRects[i].right = m_rLetterRects[i].left + fftFileStruct.pCharWidths[i];
	}


	delete[] fftFileStruct.szFilePath;
}
