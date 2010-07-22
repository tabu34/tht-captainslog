#include "precompiled_header.h"
#include "CWorldManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../CGame.h"
#include "CPathManager.h"
#include "../States/CLoadLevelState.h"
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
		CLoadLevelState::GetInstance()->SetPercentage((l / (m_nWorldDepth)) * 5.0f);
		CLoadLevelState::GetInstance()->Render();
	}
	CLoadLevelState::GetInstance()->SetPercentage(5.0f);
	CLoadLevelState::GetInstance()->Render();

	int numHelperNodes;
	fin.read((char*)&numHelperNodes, sizeof(int));

	for (int b = 0; b < numHelperNodes; b++)
	{
		POINT tempPoint;
		fin.read((char*)&tempPoint.x, sizeof(int));
		fin.read((char*)&tempPoint.y, sizeof(int));
		m_HelperNodes.push_back(tempPoint);
	}
	
	
	fin.read((char*)&m_nNumBlockers, sizeof(int));
	
	m_Blockers = new Blocker[m_nNumBlockers];
	
	for (int b = 0; b < m_nNumBlockers; b++)
	{
		fin.read((char*)&m_Blockers[b].m_nNumPoints, sizeof(int));

		m_Blockers[b].m_Points = new Blocker::Point[m_Blockers[b].m_nNumPoints];

		for (int p = 0; p < m_Blockers[b].m_nNumPoints; p++)
		{
			fin.read((char*)&m_Blockers[b].m_Points[p].x, sizeof(int));
			fin.read((char*)&m_Blockers[b].m_Points[p].y, sizeof(int));
		}
	}


	fin.close();

	//DEBUG::  hard-coded blocker to test pathing
// 	m_nNumBlockers=1;
// 	m_Blockers = new Blocker;
// 	m_Blockers->m_nNumPoints=5;
// 	m_Blockers->m_Points = new Blocker::Point[5];
// 	m_Blockers->m_Points[0].x = 516;
// 	m_Blockers->m_Points[0].y = 325;
// 	m_Blockers->m_Points[1].x = 910;
// 	m_Blockers->m_Points[1].y = 325;
// 	m_Blockers->m_Points[2].x = 910;
// 	m_Blockers->m_Points[2].y = 550;
// 	m_Blockers->m_Points[3].x = 516;
// 	m_Blockers->m_Points[3].y = 550;
// 	m_Blockers->m_Points[4].x = 516;
// 	m_Blockers->m_Points[4].y = 325;


	//create pathing
	CPathManager::GetInstance()->GenerateMap();
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
						src.left += tempTile.m_nTileNumber % (m_nTilesetWidth);
						src.top += tempTile.m_nTileNumber / (m_nTilesetWidth);
						src.bottom = src.top + tempTile.m_nHeight;
						src.right = src.left + tempTile.m_nWidth;
						CSGD_TextureManager::GetInstance()->Draw(m_nTilesetImageID, tempTile.m_nLeft - (int)CGame::GetInstance()->GetCamera()->GetX(), tempTile.m_nTop - (int)CGame::GetInstance()->GetCamera()->GetY(), 1.0f, 1.0f, &src, 0.0f, 0.0f, 0.0f);
					}
				}
			}
		}
	}
}