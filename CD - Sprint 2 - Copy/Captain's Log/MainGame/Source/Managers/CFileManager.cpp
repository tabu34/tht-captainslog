#include "precompiled_header.h"
#include "CFileManager.h"

#include <fstream>
using namespace std;

CFileManager::CFileManager()
{

}

CFileManager::~CFileManager()
{

}

CFileManager* CFileManager::GetInstance()
{
	static CFileManager instance;
	return &instance;
}

void CFileManager::LoadBitmapFont( tFontFileStruct* tFileStruct )
{
	ifstream	fin;

	fin.open(tFileStruct->szFilePath);

	if (fin.good())
	{
		fin >> tFileStruct->nImageWidth;
		fin >> tFileStruct->nImageHeight;
		fin >> tFileStruct->nCellWidth;
		fin >> tFileStruct->nCellHeight;
		fin >> tFileStruct->nStartChar;
		fin >> tFileStruct->nFontHeight;
		
		for (int i = 0; i < 256; i++)
			fin >> tFileStruct->pCharWidths[i];
		
		fin.close();
	}
}
