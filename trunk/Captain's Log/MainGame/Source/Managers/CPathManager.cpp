#include "precompiled_header.h"
#include "CPathManager.h"
#include "CWorldManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include <math.h>

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
bool InsideBlocker(POINT p)
{
	int counter=0;
	float xInters;
	Blocker::Point p1, p2;

	for(int i=0; i<CWorldManager::GetInstance()->GetNumBlockers(); i++)
	{
		counter=0;
		p1 = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[0];

		for(int j=1; j<=CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints; j++)
		{
			p2 = CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j%CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints];
			if(p.y > MIN(p1.y, p2.y))
			{
				if(p.y <= MAX(p1.y, p2.y))
				{
					if(p.x <= MAX(p1.x, p2.x))
					{
						if(p1.y!=p2.y)
						{
							xInters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
							if(p1.x == p2.x || p.x<=xInters)
								counter++;
						}
					}
				}
			}
			p1=p2;
		}

		if(counter!=0 && counter%2!=0)
			return true;

	}
	return false;
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
	for(int i=0; i<CWorldManager::GetInstance()->GetNumBlockers(); i++)
	{
		vector<tNode> vNodesInShape;
		vNodesInShape.clear();
		lastNode.fX = -1.0f;
		node.fX = -1.0f;
		for(int j=0; j<CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints; j++)
		{
			if(node.fX!=-1.0f)
			{
				lastNode = node;
			}
			node.fX = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j].x;
			node.fY = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j].y;
			m_lstNodeList.push_back(node);
			vNodesInShape.push_back(node);

			// 			if(lastNode.fX!=-1.0f)
			// 			{
			// 				tLine line;
			// 				line.start.fX = lastNode.fX;
			// 				line.start.fY = lastNode.fY;
			// 				line.end.fX = node.fX;
			// 				line.end.fY = node.fY;
			// 				vLines.push_back(line);
			// 				char buff[128];
			// 				sprintf_s(buff, 128, "X1: %.2f, Y1: %.2f, X2: %.2f, Y2: %.2f \n", line.start.fX, line.start.fY, line.end.fX, line.end.fY);
			// 				OutputDebugString(buff);
			// 			}
		}
		for(size_t i=0; i<vNodesInShape.size(); i++)
			for(size_t j=0; j<vNodesInShape.size(); j++)
			{
				tLine line;
				line.start.fX = vNodesInShape[i].fX;
				line.start.fY = vNodesInShape[i].fY;
				line.end.fX = vNodesInShape[j].fX;
				line.end.fY = vNodesInShape[j].fY;
				vLines.push_back(line);
			}
	}
	//add helper nodes
// 	for(int i=0; i<6; i++)
// 	{
// 		node.fX = helperNodes[i].fX;
// 		node.fY = helperNodes[i].fY;
// 		m_lstNodeList.push_back(node);
// 	}


	m_vLines = vLines;

	//step 2: set up adjacencies and edges
	for(size_t i=0; i<m_lstNodeList.size(); i++)
	{
		tAdjacency adjacency;
		adjacency.pNode = &m_lstNodeList[i];
		for(size_t j=0; j<m_lstNodeList.size(); j++)
		{
			if(j!=i)
			{
				//we have two different nodes, create a line between them and check for intersection
				tLine nodePath;
				nodePath.start.fX = m_lstNodeList[i].fX;
				nodePath.start.fY = m_lstNodeList[i].fY;
				nodePath.end.fX = m_lstNodeList[j].fX;
				nodePath.end.fY = m_lstNodeList[j].fY;

				//now, check this line against all others
				bool bIntersect=false;
				for(size_t k=0; k<vLines.size(); k++)
				{
					if(IntersectLine(nodePath.start, nodePath.end, vLines[k].start, vLines[k].end))
					{
						bIntersect=true;
						break;
					}
				}

				if(!bIntersect)
				{
					adjacency.pNeighbors.push_back(&m_lstNodeList[j]);
				}
			}
		}
		m_mpAdjacencies[adjacency.pNode] = adjacency;	
	}
}

inline float ManhattanDistance(tNode& source, tNode& target)
{
	return fabs(source.fX - target.fX) + fabs(source.fY - target.fY);
}

inline int PointDistance(POINT p1, POINT p2)
{
	return (int)sqrt(static_cast<double>((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y)));
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
		tVector2D pos = {fX1, fY1};
		tVector2D dst;
		float minDist = 10000.0f;
		float fTemp;
		for(size_t i=0; i<m_lstNodeList.size(); i++)
		{
			dst.fX = m_lstNodeList[i].fX;
			dst.fY = m_lstNodeList[i].fY;
			fTemp = Vector2DLength(dst - pos);

			bool bRet=false;
			for(size_t j=0; j<m_vLines.size(); j++)
			{
				if(IntersectLine(pos, dst, m_vLines[j].start, m_vLines[j].end))
				{
					bRet = true;
					break;
				}
			}

			if(!bRet && fTemp < minDist)
			{
				minDist = fTemp;
				start.pNode = &m_lstNodeList[i];
			}
		}
	}
	{

		tVector2D pos = {fX2, fY2};
		tVector2D dst;
		float minDist = 1000.0f;
		float fTemp;
		for(size_t i=0; i<m_lstNodeList.size(); i++)
		{
			dst.fX = m_lstNodeList[i].fX;
			dst.fY = m_lstNodeList[i].fY;
			fTemp = Vector2DLength(dst - pos);
			if(fTemp < minDist)
			{
				minDist = fTemp;
				goal.pNode = &m_lstNodeList[i];
			}
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
				if(x.pNode->fX == adj.pNeighbors[i]->fX && x.pNode->fY == adj.pNeighbors[i]->fY)
					continue;
				if(closeSet.find(adj.pNeighbors[i]) == closeSet.end())
				{
					float g = x.fG + ManhattanDistance(*adj.pNeighbors[i], *x.pNode);

					if(openSet.find(adj.pNeighbors[i]) == openSet.end())
					{
						tAStarNode n;
						n.pNode = adj.pNeighbors[i];
						n.pCameFrom = &vNodePool.back();
						n.nIndexParent = vNodePool.size()-1;
						n.fG = g;
						n.fH = ManhattanDistance(*adj.pNeighbors[i], *goal.pNode);
						openSet[n.pNode] = n;
						pQueue.push(n);
					}
					else if(g < openSet[adj.pNeighbors[i]].fG)
					{
						openSet[adj.pNeighbors[i]].pCameFrom = &vNodePool.back();
						openSet[adj.pNeighbors[i]].nIndexParent = vNodePool.size()-1;
						openSet[adj.pNeighbors[i]].fG = g;
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