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

bool IntersectLine(tVector2D A1, tVector2D A2, tVector2D B1, tVector2D B2)
{
	tVector2D E = A2-A1;
	tVector2D F = B2-B1;
	tVector2D P = {-E.fY, E.fX};

	float h = (DotProduct((A1 - B1), P) / DotProduct(F, P));

	return (h>0.0f && h<1.0f) ? true : false;
}

CPathManager* CPathManager::GetInstance()
{
	static CPathManager instance;
	return &instance;
}

void CPathManager::GenerateMap()
{
	struct tLine
	{
		tVector2D start;
		tVector2D end;
	};
	vector<tLine> vLines;
	//step 1:  create all the nodes
	tNode node, lastNode;
	for(int i=0; i<CWorldManager::GetInstance()->m_nNumBlockers; i++)
	{
		lastNode.fX = -1.0f;
		node.fX = -1.0f;
		for(int j=0; j<CWorldManager::GetInstance()->m_Blockers[i].m_nNumPoints; j++)
		{
			if(node.fX!=-1.0f)
			{
				if(lastNode.fX!=-1.0f)
				{
					tLine line;
					line.start.fX = lastNode.fX;
					line.start.fY = lastNode.fY;
					line.end.fX = node.fX;
					line.end.fY = node.fY;
					vLines.push_back(line);
				}
				lastNode = node;
			}
			node.fX = (float)CWorldManager::GetInstance()->m_Blockers[i].m_Points[j].x;
			node.fY = (float)CWorldManager::GetInstance()->m_Blockers[i].m_Points[j].y;
			m_lstNodeList.push_back(node);
		}
	}

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

vector<tNode*> CPathManager::GetPath(float fX1, float fY1, float fX2, float fY2)
{
	//THIS is A*

	vector<tNode*> vRet;

	map<tNode*, tAStarNode> openSet;
	queue<tAStarNode> pQueue;
	map<tNode*, tAStarNode> closeSet;
	
	tAStarNode start;
	tAStarNode goal;

	//calculate nearest node to start and goal
	{
		tVector2D pos = {fX1, fY1};
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

	start.pCameFrom = NULL;
	start.fG = 0.0f;
	start.fH = ManhattanDistance(*start.pNode, *goal.pNode);

	openSet[start.pNode] = start;
	pQueue.push(start);

	bool bFoundGoal = false;
	while(openSet.size() > 0)
	{
		tAStarNode x = pQueue.front();
		pQueue.pop();
		openSet.erase(x.pNode);
		if(x.pNode == goal.pNode)
		{
			//path exists
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
				if(closeSet.find(adj.pNeighbors[i]) == closeSet.end())
				{
					float g = x.fG + ManhattanDistance(*adj.pNeighbors[i], *x.pNode);

					if(openSet.find(adj.pNeighbors[i]) == openSet.end())
					{
						tAStarNode n;
						n.pNode = adj.pNeighbors[i];
						n.pCameFrom = &x;
						n.fG = g;
						openSet[n.pNode] = n;
						pQueue.push(n);
					}
					else if(g < openSet[adj.pNeighbors[i]].fG)
					{
						openSet[adj.pNeighbors[i]].pCameFrom = &x;
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
		tAStarNode* pParent = goal.pCameFrom;
		while(pParent != NULL)
		{
			stk.push(pParent->pNode);
			pParent = pParent->pCameFrom;
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