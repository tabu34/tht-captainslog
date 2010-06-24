#include "precompiled_header.h"
#include "CWorldManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

#include <fstream>
using namespace std;

CWorldManager::CWorldManager()
{

}

CWorldManager::~CWorldManager()
{

}

void CWorldManager::Load(string sFileName)
{
	ifstream fin(sFileName.c_str(), ios::in | ios::binary);

	fin >> m_fVersionNumber;
	fin >> m_sFileName;

	m_nTilesetImageID = CSGD_TextureManager::GetInstance()->LoadTexture(m_sFileName.c_str());

	fin >> m_nTilesetWidth;
	fin >> m_nTilesetHeight;

	fin >> m_nWorldWidth;
	fin >> m_nWorldHeight;
	fin >> m_nWorldDepth;

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

				fin >> tempTile.m_nWidth;
				fin >> tempTile.m_nHeight;
				fin >> tempTile.m_nTileNumber;
				fin >> tempTile.m_nTop;
				fin >> tempTile.m_nLeft;

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
				if (tempTile.m_nTileNumber != -1)
				{
					RECT src = {tempTile.m_nTileNumber % (m_nTilesetWidth / tempTile.m_nWidth) * tempTile.m_nWidth,
								tempTile.m_nTileNumber / (m_nTilesetWidth / tempTile.m_nWidth) * tempTile.m_nHeight,
								0, 0};
					src.bottom = src.top + tempTile.m_nHeight;
					src.right = src.left + tempTile.m_nWidth;
					CSGD_TextureManager::GetInstance()->Draw(m_nTilesetImageID, tempTile.m_nLeft, tempTile.m_nTop, 1.0f, 1.0f, &src, 0.0f, 0.0f, 0.0f);
				}
			}
		}
	}
}