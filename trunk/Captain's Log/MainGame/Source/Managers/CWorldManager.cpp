#include "precompiled_header.h"
#include "CWorldManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../CGame.h"

#include <fstream>
using namespace std;

CWorldManager::CWorldManager()
{

}

CWorldManager::~CWorldManager()
{
	for (int l = 0; l < m_nWorldDepth; l++)
	{
		for (int i = 0; i < m_nWorldWidth; i++)
		{
			delete[] m_World[l][i];
		}
		delete[] m_World[l];
	}
	delete[] m_World;
}

CWorldManager* CWorldManager::GetInstance()
{
	static CWorldManager instance;
	return &instance;
}

void CWorldManager::Load(string sFileName)
{
	ifstream fin(sFileName.c_str(), ios::in | ios::binary);

	fin.read((char*)&m_fVersionNumber, sizeof(float));

	int nFileNameSize = 0;
	fin.read((char*)&nFileNameSize, sizeof(int));

	m_szFileName = new char[nFileNameSize];
	fin.read((char*)m_szFileName, nFileNameSize);
	m_szFileName[nFileNameSize] = '\0';

	m_nTilesetImageID = CSGD_TextureManager::GetInstance()->LoadTexture(m_szFileName);

	fin.read((char*)&m_nTilesetHeight, sizeof(int));
	fin.read((char*)&m_nTilesetWidth, sizeof(int));

	fin.read((char*)&m_nWorldWidth, sizeof(int));
	fin.read((char*)&m_nWorldHeight, sizeof(int));
	fin.read((char*)&m_nWorldDepth, sizeof(int));

	m_World = new Tile**[m_nWorldDepth];

	for (int l = 0; l < m_nWorldDepth; l++)
	{
		m_World[l] = new Tile*[m_nWorldWidth];
		for (int i = 0; i < m_nWorldWidth; i++)
		{
			m_World[l][i] = new Tile[m_nWorldHeight];
			for (int j = 0; j < m_nWorldHeight; j++)
			{
				Tile tempTile;

				fin.read((char*)&tempTile.m_nWidth, sizeof(int));
				fin.read((char*)&tempTile.m_nHeight, sizeof(int));
				fin.read((char*)&tempTile.m_nTileNumber, sizeof(int));
				fin.read((char*)&tempTile.m_nTop, sizeof(int));
				fin.read((char*)&tempTile.m_nLeft, sizeof(int));

				m_World[l][i][j] = tempTile;
			}
		}
	}

	fin.close();
}

void CWorldManager::Render()
{
	for (int l = 0; l < m_nWorldDepth; l++)
	{
		for (int i = 0; i < m_nWorldWidth; i++)
		{
			for (int j = 0; j < m_nWorldHeight; j++)
			{
				Tile tempTile = m_World[l][i][j];
				RECT cameraRect = CGame::GetInstance()->GetCamera()->GetCollisionRect();
				if (tempTile.m_nLeft + tempTile.m_nWidth >= cameraRect.left && tempTile.m_nLeft <= cameraRect.right
					&& tempTile.m_nTop + tempTile.m_nHeight >= cameraRect.top && tempTile.m_nTop <= cameraRect.bottom)
				{
					if (tempTile.m_nTileNumber != -1)
					{
						RECT src = {tempTile.m_nTileNumber % (m_nTilesetWidth) * tempTile.m_nWidth,
							tempTile.m_nTileNumber / (m_nTilesetWidth) * tempTile.m_nHeight,
							0, 0};
						src.bottom = src.top + tempTile.m_nHeight;
						src.right = src.left + tempTile.m_nWidth;
						CSGD_TextureManager::GetInstance()->Draw(m_nTilesetImageID, tempTile.m_nLeft - (int)CGame::GetInstance()->GetCamera()->GetX(), tempTile.m_nTop - (int)CGame::GetInstance()->GetCamera()->GetY(), 1.0f, 1.0f, &src, 0.0f, 0.0f, 0.0f);
					}
				}
			}
		}
	}
}