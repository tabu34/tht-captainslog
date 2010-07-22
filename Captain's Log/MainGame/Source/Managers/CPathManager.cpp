#include "precompiled_header.h"
#include "CPathManager.h"
#include "CWorldManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include <math.h>
#include "../States/CLoadLevelState.h"

// Grid squares are x by x (ex. 50 by 50) pixels
#define GRID_SCALE 25

CPathManager::CPathManager()
{

}

CPathManager::~CPathManager()
{

}

// int Check_Tri_Dir(tVector2D P1, tVector2D P2, tVector2D P3)
// {
// 	float test;
// 	test = (((P2.fX - P1.fX)*(P3.fY - P1.fY)) - ((P3.fX-P1.fX)*(P2.fY - P1.fY)));
// 	if(test > 0)
// 		return 1;
// 	if(test < 0)
// 		return -1;
// 	return 0;
// }

bool IntersectLine(tVector2D A1, tVector2D A2, tVector2D B1, tVector2D B2)
{
	// 	//if any of the endpoints are the same, the lines technically aren't intersecting
	// 	if((A1.fX == B1.fX && A1.fY == B1.fY) ||
	// 		(A1.fX == B2.fX && A1.fY == B2.fY) ||
	// 		(A2.fX == B1.fX && A2.fY == B1.fY) ||
	// 		(A2.fX == B2.fX && A2.fY == B2.fY))
	// 		return false;
	// 
	// 	int test1, test2, test3, test4;
	// 	test1 = Check_Tri_Dir(A1, A2, B1);
	// 	test2 = Check_Tri_Dir(A1, A2, B2);
	// 	if(test1 != test2)
	// 	{
	// 		test3 = Check_Tri_Dir(B1, B2, A1);
	// 		test4 = Check_Tri_Dir(B1, B2, A2);
	// 		if(test3 != test4)
	// 			return true;
	// 	}
	// 	return false;

	float d = (A2.fX - A1.fX)*(B2.fY - B1.fY) - (A2.fY - A1.fY)*(B2.fX - B1.fX);
	if(fabs(d)<0.001) return false;
	float AB = ((A1.fY - B1.fY)*(B2.fX - B1.fX)-(A1.fX - B1.fX)*(B2.fY-B1.fY))/d;

	if(AB>0.0f && AB<1.0f)
	{
		float CD = ((A1.fY - B1.fY)*(A2.fX - A1.fX) - (A1.fX - B1.fX)*(A2.fY - A1.fY))/d;
		if(CD>0.0f && CD<1.0f)
			return true;
	}
	return false;
}
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

bool InsideBlocker(tNode p)
{
	int i, j;
	bool oddNodes = false;

	for(int n=0; n<CWorldManager::GetInstance()->GetNumBlockers(); n++)
	{
		j=CWorldManager::GetInstance()->GetBlockers()[n].m_nNumPoints-1;
		for(i=0; i<CWorldManager::GetInstance()->GetBlockers()[n].m_nNumPoints; i++)
		{
			if((float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].y<(float)p.fY && 
				(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[j].y>=(float)p.fY ||
				(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[j].y<(float)p.fY &&
				(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].y>=(float)p.fY)
			{
				if((float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].x + 
					((float)p.fY - (float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].y)/ 
					((float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[j].y -
					(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].y)*
					((float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[j].x - 
					(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].x)<(float)p.fX)
				{
					oddNodes=!oddNodes;
				}
			}
			j=i;
		}
		if(oddNodes==true)
			return true;
	}
	return false;

}
bool InsideBlocker(POINT p)
{
	int i, j;
	bool oddNodes = false;

	for(int n=0; n<CWorldManager::GetInstance()->GetNumBlockers(); n++)
	{
		j=CWorldManager::GetInstance()->GetBlockers()[n].m_nNumPoints-1;
		for(i=0; i<CWorldManager::GetInstance()->GetBlockers()[n].m_nNumPoints; i++)
		{
			if((float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].y<(float)p.y && 
				(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[j].y>=(float)p.y ||
				(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[j].y<(float)p.y &&
				(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].y>=(float)p.y)
			{
				if((float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].x + 
					((float)p.y - (float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].y)/ 
					((float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[j].y -
					(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].y)*
					((float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[j].x - 
					(float)CWorldManager::GetInstance()->GetBlockers()[n].m_Points[i].x)<(float)p.x)
				{
					oddNodes=!oddNodes;
				}
			}
			j=i;
		}
		if(oddNodes==true)
			return true;
	}
	return false;
// 	int counter=0;
// 	float xInters;
// 	Blocker::Point p1, p2;
// 
// 	for(int i=0; i<CWorldManager::GetInstance()->GetNumBlockers(); i++)
// 	{
// 		counter=0;
// 		p1 = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[0];
// 
// 		for(int j=1; j<=CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints; j++)
// 		{
// 			p2 = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j%CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints];
// 			if(p.y > MIN(p1.y, p2.y))
// 			{
// 				if(p.y <= MAX(p1.y, p2.y))
// 				{
// 					if(p.x <= MAX(p1.x, p2.x))
// 					{
// 						if(p1.y!=p2.y)
// 						{
// 							xInters = float((p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x);
// 							if(p1.x == p2.x || p.x<=xInters)
// 								counter++;
// 						}
// 					}
// 				}
// 			}
// 			p1=p2;
// 		}
// 
// 		if(counter!=0 && counter%2!=0)
// 			return true;
// 
// 	}
// 	return false;
}

bool CPathManager::IsPointInside(POINT p)
{
	return InsideBlocker(p);
}

CPathManager* CPathManager::GetInstance()
{
	static CPathManager instance;
	return &instance;
}

void CPathManager::GenerateMap()
{

	vector<tLine> vLines;
	m_lstNodeList.clear();
	m_mpAdjacencies.clear();
	//step 1:  create all the nodes
	tNode node, lastNode;
	//for(int i=0; i<CWorldManager::GetInstance()->GetNumBlockers(); i++)
	//{
	//	vector<tNode> vNodesInShape;
	//	vNodesInShape.clear();
	//	lastNode.fX = -1.0f;
	//	node.fX = -1.0f;
	//	for(int j=0; j<CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints; j++)
	//	{
	//		if(node.fX!=-1.0f)
	//		{
	//			lastNode = node;
	//		}
	//		node.fX = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j].x;
	//		node.fY = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j].y;
	//		m_lstNodeList.push_back(node);
	//		vNodesInShape.push_back(node);

	//		// 			if(lastNode.fX!=-1.0f)
	//		// 			{
	//		// 				tLine line;
	//		// 				line.start.fX = lastNode.fX;
	//		// 				line.start.fY = lastNode.fY;
	//		// 				line.end.fX = node.fX;
	//		// 				line.end.fY = node.fY;
	//		// 				vLines.push_back(line);
	//		// 				char buff[128];
	//		// 				sprintf_s(buff, 128, "X1: %.2f, Y1: %.2f, X2: %.2f, Y2: %.2f \n", line.start.fX, line.start.fY, line.end.fX, line.end.fY);
	//		// 				OutputDebugString(buff);
	//		// 			}
	//	}
	//	for(size_t k=0; k<vNodesInShape.size(); k++) {
	//		for(size_t j=0; j<vNodesInShape.size(); j++)
	//		{
	//			tLine line;
	//			line.start.fX = vNodesInShape[k].fX;
	//			line.start.fY = vNodesInShape[k].fY;
	//			line.end.fX = vNodesInShape[j].fX;
	//			line.end.fY = vNodesInShape[j].fY;
	//			vLines.push_back(line);
	//		} }

	//	CLoadLevelState::GetInstance()->SetPercentage(5.0f + (((float)i / (CWorldManager::GetInstance()->GetNumBlockers())) * 25.0f));
	//	CLoadLevelState::GetInstance()->Render();
	//}
	//CLoadLevelState::GetInstance()->SetPercentage(30.0f);
	//CLoadLevelState::GetInstance()->Render();
	
	
	//add helper nodes

	// calculate number of grid lines
	int m_nNumGridLinesX = CWorldManager::GetInstance()->WorldWidth() / GRID_SCALE;
	int m_nNumGridLinesY = CWorldManager::GetInstance()->WorldHeight() / GRID_SCALE;

	for(int y = 0; y < m_nNumGridLinesY; y++)
		for(int x = 0; x < m_nNumGridLinesX; x++)
		{
			tNode node;
			node.fX = x * GRID_SCALE;
 			node.fY = y * GRID_SCALE;
 			m_lstNodeList.push_back(node);

			//adj.pNeighbors.push_back(new tNode);
			//adj.pNeighbors.push_back(new tNode);
			//adj.pNeighbors.push_back(new tNode);
			//adj.pNeighbors.push_back(new tNode);
			//adj.pNeighbors.push_back(new tNode);
			//adj.pNeighbors.push_back(new tNode);
			//adj.pNeighbors.push_back(new tNode);
			//adj.pNeighbors.push_back(new tNode);

			//// Node above
			//adj.pNeighbors[0]->fX = x.pNode->fX;
			//adj.pNeighbors[0]->fY = x.pNode->fY - GRID_SCALE;
			//// Node right
			//adj.pNeighbors[1]->fX = x.pNode->fX + GRID_SCALE;
			//adj.pNeighbors[1]->fY = x.pNode->fY;
			//// Node below
			//adj.pNeighbors[2]->fX = x.pNode->fX;
			//adj.pNeighbors[2]->fY = x.pNode->fY + GRID_SCALE;
			//// Node left
			//adj.pNeighbors[3]->fX = x.pNode->fX - GRID_SCALE;
			//adj.pNeighbors[3]->fY = x.pNode->fY;
			//// Node left above
			//adj.pNeighbors[4]->fX = x.pNode->fX - GRID_SCALE;
			//adj.pNeighbors[4]->fY = x.pNode->fY - GRID_SCALE;
			//// Node right above
			//adj.pNeighbors[5]->fX = x.pNode->fX + GRID_SCALE;
			//adj.pNeighbors[5]->fY = x.pNode->fY - GRID_SCALE;
			//// Node below right
			//adj.pNeighbors[6]->fX = x.pNode->fX + GRID_SCALE;
			//adj.pNeighbors[6]->fY = x.pNode->fY + GRID_SCALE;
			//// Node left below
			//adj.pNeighbors[7]->fX = x.pNode->fX - GRID_SCALE;
			//adj.pNeighbors[7]->fY = x.pNode->fY + GRID_SCALE;



 		}

	for(int x = 0; x < m_nNumGridLinesX; x++)
		for(int y = 0; y < m_nNumGridLinesY; y++)
		{
			// Setup adjancies for this node
			tAdjacency adj;
			adj.pNode = &m_lstNodeList[(y * m_nNumGridLinesX) + x];

			if(y-1 >= 0 && x-1 >= 0 && !InsideBlocker( m_lstNodeList[ ((y-1) * m_nNumGridLinesX) + x-1 ] ) )
				adj.pNeighbors.push_back( &(m_lstNodeList[((y-1) * m_nNumGridLinesX) + x-1]));
			if(y-1 >= 0 && x >= 0 && !InsideBlocker( m_lstNodeList[ ((y-1) * m_nNumGridLinesX) + x ] ) )
				adj.pNeighbors.push_back( &(m_lstNodeList[((y-1) * m_nNumGridLinesX) + x]));
			if(y-1 >= 0 && x+1 < m_nNumGridLinesX && !InsideBlocker( m_lstNodeList[ ((y-1) * m_nNumGridLinesX) + x+1 ] ) )
				adj.pNeighbors.push_back( &(m_lstNodeList[((y-1) * m_nNumGridLinesX) + x+1]));
			if(y >= 0 && x-1 >= 0 && !InsideBlocker( m_lstNodeList[ ((y) * m_nNumGridLinesX) + x-1 ] ) )
				adj.pNeighbors.push_back( &(m_lstNodeList[(y * m_nNumGridLinesX) + x-1]));
			if(y >= 0 && x+1 < m_nNumGridLinesX && !InsideBlocker( m_lstNodeList[ ((y) * m_nNumGridLinesX) + x+1 ] ) )
				adj.pNeighbors.push_back( &(m_lstNodeList[(y * m_nNumGridLinesX) + x+1]));
			if(y+1 < m_nNumGridLinesY && x-1 >= 0 && !InsideBlocker( m_lstNodeList[ ((y+1) * m_nNumGridLinesX) + x-1 ] ) )
				adj.pNeighbors.push_back( &(m_lstNodeList[((y+1) * m_nNumGridLinesX) + x-1]));
			if(y+1 < m_nNumGridLinesY && x >= 0 && !InsideBlocker( m_lstNodeList[ ((y+1) * m_nNumGridLinesX) + x ] ) )
				adj.pNeighbors.push_back( &(m_lstNodeList[((y+1) * m_nNumGridLinesX) + x]));
			if(y+1 < m_nNumGridLinesY && x+1 < m_nNumGridLinesX && !InsideBlocker( m_lstNodeList[ ((y+1) * m_nNumGridLinesX) + x+1 ] ) )
				adj.pNeighbors.push_back( &(m_lstNodeList[((y+1) * m_nNumGridLinesX) + x+1]));

			m_mpAdjacencies[adj.pNode] = adj;
		}


	////step 2: set up adjacencies and edges
	//for(size_t i=0; i<m_lstNodeList.size(); i++)
	//{
	//	tAdjacency adjacency;
	//	adjacency.pNode = &m_lstNodeList[i];
	//	for(size_t j=0; j<m_lstNodeList.size(); j++)
	//	{
	//		if(j!=i)
	//		{
	//			//we have two different nodes, create a line between them and check for intersection
	//			tLine nodePath;
	//			nodePath.start.fX = m_lstNodeList[i].fX;
	//			nodePath.start.fY = m_lstNodeList[i].fY;
	//			nodePath.end.fX = m_lstNodeList[j].fX;
	//			nodePath.end.fY = m_lstNodeList[j].fY;

	//			//now, check this line against all others
	//			bool bIntersect=false;
	//			for(size_t k=0; k<vLines.size(); k++)
	//			{
	//				if(IntersectLine(nodePath.start, nodePath.end, vLines[k].start, vLines[k].end))
	//				{
	//					bIntersect=true;
	//					break;
	//				}
	//			}

	//			if(!bIntersect)
	//			{
	//				adjacency.pNeighbors.push_back(&m_lstNodeList[j]);
	//			}
	//		}
	//	}
	//	m_mpAdjacencies[adjacency.pNode] = adjacency;
		//CLoadLevelState::GetInstance()->SetPercentage(30.0f + (((float)i / (m_lstNodeList.size())) * 70.0f));
		//CLoadLevelState::GetInstance()->Render();

		for(int i = 0; i < CWorldManager::GetInstance()->GetNumBlockers(); i++)
		{
			for(int j = 0; j < CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints - 1; j++)
			{
				tLine newLine;
				newLine.start.fX = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j].x;
				newLine.start.fY = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j].y;
				newLine.end.fX = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j+1].x;
				newLine.end.fY = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j+1].y;
				m_vLines.push_back(newLine);
			}
			tLine newLine;
			newLine.start.fX = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints - 1].x;
			newLine.start.fY = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints - 1].y;
			newLine.end.fX = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[0].x;
			newLine.end.fY = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[0].y;
			m_vLines.push_back(newLine);
		}


	
	CLoadLevelState::GetInstance()->SetPercentage(100.0f);
	CLoadLevelState::GetInstance()->Render();
}

inline float ManhattanDistance(tNode& source, tNode& target)
{
	return fabs(source.fX - target.fX) + fabs(source.fY - target.fY);
}

inline int PointDistance(POINT p1, POINT p2)
{
	return (int)sqrt(static_cast<double>((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y)));
}

bool CPathManager::CheckPath(float fX1, float fY1, float fX2, float fY2)
{
	//check path to see if A* is necessary
	//Return false if there is an obstruction
	bool bRet=true;
	tVector2D pos = {fX1, fY1};
	tVector2D dst = {fX2, fY2};
	for(size_t i=0; i<m_vLines.size(); i++)
	{
		if(IntersectLine(pos, dst, m_vLines[i].start, m_vLines[i].end))
		{
			bRet=false;
			break;
		}
	}
	return bRet;
}

vector<tNode*> CPathManager::GetPath(float fX1, float fY1, float fX2, float fY2)
{
	//THIS is A*

	vector<tNode*> vRet;
	vector<tAStarNode> vNodePool;

	map<tNode*, tAStarNode> openSet;
	queue<tAStarNode> pQueue;
	map<tNode*, tAStarNode> closeSet;

	tAStarNode start;
	tAStarNode goal;
	start.pNode=NULL;
	goal.pNode=NULL;

	//calculate nearest node to start and goal
	{
		//tVector2D pos = {fX1, fY1};
		//tVector2D dst;
		//float minDist = 10000.0f;
		//float fTemp;
		//for(int i = 0; i < m_lstNodeList.size(); i++)
		//{
		//	dst.fX = m_lstNodeList[i].fX;
		//	dst.fY = m_lstNodeList[i].fY;
		//	fTemp = Vector2DLength(dst - pos);

		//	bool bRet=false;
		//	for(size_t j=0; j<m_vLines.size(); j++)
		//	{
		//		if(IntersectLine(pos, dst, m_vLines[j].start, m_vLines[j].end))
		//		{
		//			bRet = true;
		//			break;
		//		}
		//	}

		//	if(!bRet && fTemp < minDist)
		//	{
		//		minDist = fTemp;
		//		start.pNode = &m_lstNodeList[i];
		//	}
		//}
		
		int closestDistance = 10000;
		int closestNode;
		int tilePosX = (fX1 / GRID_SCALE);
		int tilePosY = (fY1 / GRID_SCALE);

		POINT startPt;
		startPt.x = fX1;
		startPt.y = fY1;

		POINT tileEdges[4];
		// Top left
		tileEdges[0].x = tilePosX * GRID_SCALE;
		tileEdges[0].y = tilePosY * GRID_SCALE;
		// Top right
		tileEdges[1].x = tilePosX * GRID_SCALE + GRID_SCALE;
		tileEdges[1].y = tilePosY * GRID_SCALE;
		// Bottom left
		tileEdges[2].x = tilePosX * GRID_SCALE;
		tileEdges[2].y = tilePosY * GRID_SCALE + GRID_SCALE;
		// Bottom right
		tileEdges[3].x = tilePosX * GRID_SCALE + GRID_SCALE;
		tileEdges[3].y = tilePosY * GRID_SCALE + GRID_SCALE;

		for(int i = 0; i < 4; i++)
		{
			if(PointDistance(startPt, tileEdges[i]) < closestDistance)
			{
				closestDistance = PointDistance(startPt, tileEdges[i]);
				closestNode = i;
			}
		}
		
		for(int i = 0; i < m_lstNodeList.size(); i++)
			if(m_lstNodeList[i].fX == tileEdges[closestNode].x && m_lstNodeList[i].fY == tileEdges[closestNode].y)
			{
				start.pNode = &m_lstNodeList[i];
				break;
			}
		
	}
	{
		//tVector2D pos = {fX2, fY2};
		//tVector2D dst;
		//float minDist = 1000.0f;
		//float fTemp;
		//for(size_t i=0; i<m_lstNodeList.size(); i++)
		//{
		//	dst.fX = m_lstNodeList[i].fX;
		//	dst.fY = m_lstNodeList[i].fY;
		//	fTemp = Vector2DLength(dst - pos);
		//	if(fTemp < minDist)
		//	{
		//		minDist = fTemp;
		//		goal.pNode = &m_lstNodeList[i];
		//	}
		//}

		int closestDistance = 10000;
		int closestNode;
		int tilePosX = (fX2 / GRID_SCALE);
		int tilePosY = (fY2 / GRID_SCALE);

		POINT endPt;
		endPt.x = fX2;
		endPt.y = fY2;

		POINT tileEdges[4];
		// Top left
		tileEdges[0].x = tilePosX * GRID_SCALE;
		tileEdges[0].y = tilePosY * GRID_SCALE;
		// Top right
		tileEdges[1].x = tilePosX * GRID_SCALE + GRID_SCALE;
		tileEdges[1].y = tilePosY * GRID_SCALE;
		// Bottom left
		tileEdges[2].x = tilePosX * GRID_SCALE;
		tileEdges[2].y = tilePosY * GRID_SCALE + GRID_SCALE;
		// Bottom right
		tileEdges[3].x = tilePosX * GRID_SCALE + GRID_SCALE;
		tileEdges[3].y = tilePosY * GRID_SCALE + GRID_SCALE;

		for(int i = 0; i < 4; i++)
		{
			if(PointDistance(endPt, tileEdges[i]) < closestDistance)
			{
				closestDistance = PointDistance(endPt, tileEdges[i]);
				closestNode = i;
			}
		}

		for(int i = 0; i < m_lstNodeList.size(); i++)
			if(m_lstNodeList[i].fX == tileEdges[closestNode].x && m_lstNodeList[i].fY == tileEdges[closestNode].y)
			{
				goal.pNode = &m_lstNodeList[i];
				break;
			}
	}

	if(!start.pNode)
		return vector<tNode*>();

	if(goal.pNode == start.pNode)
		return vector<tNode*>();

	start.pCameFrom = NULL;
	start.nIndexParent = -1;
	start.fG = 0.0f;
	start.fH = ManhattanDistance(*start.pNode, *goal.pNode);

	openSet[start.pNode] = start;
	pQueue.push(start);

	bool bFoundGoal = false;
	while(openSet.size() > 0)
	{
		tAStarNode x = pQueue.front();
		vNodePool.push_back(x);
		pQueue.pop();
		openSet.erase(x.pNode);
		if(x.pNode == goal.pNode)
		{
			//path exists
			goal = x;
			bFoundGoal = true;
			break;
		}
		else
		{
			closeSet[x.pNode] = x;
			tAdjacency adj;
			adj = m_mpAdjacencies[x.pNode];

			for(size_t i=0; i<adj.pNeighbors.size(); i++)
			{
				POINT curNode;
				curNode.x = adj.pNeighbors[i]->fX;
				curNode.y = adj.pNeighbors[i]->fY;

				if(x.pNode->fX == adj.pNeighbors[i]->fX && x.pNode->fY == adj.pNeighbors[i]->fY)
					continue;

				if(closeSet.find(adj.pNeighbors[i]) == closeSet.end())
				{
					POINT cur, prev;
					cur.x = adj.pNeighbors[i]->fX;
					cur.y = adj.pNeighbors[i]->fY;
					prev.x = vNodePool.back().pNode->fX;
					prev.y = vNodePool.back().pNode->fY;

					float f = x.fG + ManhattanDistance(*adj.pNeighbors[i], *x.pNode);
					if(openSet.find(adj.pNeighbors[i]) == openSet.end())
					{
						tAStarNode n;
						n.pNode = adj.pNeighbors[i];
						n.pCameFrom = &vNodePool.back();
						n.nIndexParent = vNodePool.size()-1;
						n.fG = PointDistance(cur,prev);
						n.fH = ManhattanDistance(*adj.pNeighbors[i], *goal.pNode);
						openSet[n.pNode] = n;
						pQueue.push(n);
					}
					else if(f < openSet[adj.pNeighbors[i]].fG)
					{
						openSet[adj.pNeighbors[i]].pCameFrom = &vNodePool.back();
						openSet[adj.pNeighbors[i]].nIndexParent = vNodePool.size()-1;
						openSet[adj.pNeighbors[i]].fG = PointDistance(cur,prev);
						openSet[adj.pNeighbors[i]].fH = ManhattanDistance(*adj.pNeighbors[i], *goal.pNode);
					}
				}
			}
		}
	}

	if(bFoundGoal)
	{
		stack<tNode*> stk;
		stk.push(goal.pNode);
		tAStarNode pParent = vNodePool[goal.nIndexParent];
		while(pParent.nIndexParent < vNodePool.size())
		{
			stk.push(pParent.pNode);
			pParent = vNodePool[pParent.nIndexParent];
			if(pParent.pCameFrom == NULL)
			{
				stk.push(pParent.pNode);
				break;
			}
		}

		while(stk.size() > 0)
		{
			vRet.push_back(stk.top());
			stk.pop();
		}
		return vRet;
	}
	return vector<tNode*>();
}