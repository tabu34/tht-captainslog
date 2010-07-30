#include "precompiled_header.h"
#include "CPathManager.h"
#include "CWorldManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include <math.h>
#include "../States/CLoadLevelState.h"
#include "../GameObjects/CBase.h"
// Grid squares are x by x (ex. 50 by 50) pixels
#define GRID_SCALE 50

CPathManager::CPathManager()
{
	openBH =		NULL;
	lstIndex =		NULL;
	cameFrom =		NULL;
	fCost =			NULL;
	gCost =			NULL;
	hCost =			NULL;
	xPos =			NULL;
	yPos =			NULL;
}

CPathManager::~CPathManager()
{
	if(openBH)
	{
		delete[] openBH;
		openBH = NULL;
	}
	if(lstIndex)
	{
		delete lstIndex;
		lstIndex = NULL;
	}
	if(cameFrom)
	{
		delete[] cameFrom;
		cameFrom = NULL;
	}
	if(fCost)
	{
		delete[] fCost;
		fCost = NULL;
	}
	if(gCost)
	{
		delete[] gCost;
		gCost = NULL;
	}
	if(hCost)
	{
		delete[] hCost;
		hCost = NULL;
	}
	if(xPos)
	{
		delete[] xPos;
		xPos = NULL;
	}
	if(yPos)
	{
		delete[] yPos;
		yPos = NULL;
	}
}

bool IntersectLine(tVector2D A1, tVector2D A2, tVector2D B1, tVector2D B2)
{
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
}

bool CPathManager::InsideObject( tNode _node )
{
	vector<CBase*>* _objList = CObjectManager::GetInstance()->GetObjectList();
	RECT nodeRect;
	nodeRect.left = LONG(_node.fX - 20);
	nodeRect.top = LONG(_node.fY - 20);
	nodeRect.right = LONG(nodeRect.left + 40);
	nodeRect.bottom = LONG(nodeRect.top + 40);
	RECT objectRect, result;
	for(unsigned int i = 0; i < _objList->size(); i++)
	{
		objectRect = (*_objList)[i]->GetCollisionRect();
		if(IntersectRect(&result, &objectRect, &nodeRect))
			return true;
	}

	return false;
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
	//tNode node, lastNode;

	// calculate number of grid lines
	int m_nNumGridLinesX = CWorldManager::GetInstance()->WorldWidth() / GRID_SCALE;
	int m_nNumGridLinesY = CWorldManager::GetInstance()->WorldHeight() / GRID_SCALE;

	if(openBH)
	{
		delete[] openBH;
		openBH = NULL;
	}
	if(lstIndex)
	{
		delete lstIndex;
		lstIndex = NULL;
	}
	if(cameFrom)
	{
		delete[] cameFrom;
		cameFrom = NULL;
	}
	if(fCost)
	{
		delete[] fCost;
		fCost = NULL;
	}
	if(gCost)
	{
		delete[] gCost;
		gCost = NULL;
	}
	if(hCost)
	{
		delete[] hCost;
		hCost = NULL;
	}
	if(xPos)
	{
		delete[] xPos;
		xPos = NULL;
	}
	if(yPos)
	{
		delete[] yPos;
		yPos = NULL;
	}

	// Setup the arrays
	openBH =	new int[m_nNumGridLinesX * m_nNumGridLinesY];
	lstIndex =	new int[m_nNumGridLinesX * m_nNumGridLinesY];
	cameFrom =	new int[m_nNumGridLinesX * m_nNumGridLinesY];
	fCost =		new float[m_nNumGridLinesX * m_nNumGridLinesY];		
	gCost =		new float[m_nNumGridLinesX * m_nNumGridLinesY];		
	hCost =		new float[m_nNumGridLinesX * m_nNumGridLinesY];		
	xPos =		new float[m_nNumGridLinesX * m_nNumGridLinesY];		
	yPos =		new float[m_nNumGridLinesX * m_nNumGridLinesY];


	for(int y = 0; y < m_nNumGridLinesY; y++)
	{
		for(int x = 0; x < m_nNumGridLinesX; x++)
		{
			tNode node;
			node.fX = float(x * GRID_SCALE);
 			node.fY = float(y * GRID_SCALE);
			node.checked = false;
 			m_lstNodeList.push_back(node);
 		}
		CLoadLevelState::GetInstance()->SetPercentage(5.0f + (((float)y/ (m_nNumGridLinesY)) * 45.0f));
		CLoadLevelState::GetInstance()->Render();
	}

	for(int x = 0; x < m_nNumGridLinesX; x++)
	{
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
		CLoadLevelState::GetInstance()->SetPercentage(50.0f + (((float)x/ (m_nNumGridLinesX)) * 35.0f));
		CLoadLevelState::GetInstance()->Render();
	}

		// Sort the node list
	sort(m_lstNodeList.begin(), m_lstNodeList.end());

	for(int i = 0; i < CWorldManager::GetInstance()->GetNumBlockers(); i++)
	{
		for(int j = 0; j < CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints - 1; j++)
		{
			tLine newLine;
			newLine.start.fX = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j].x;
			newLine.start.fY = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j].y;
			newLine.end.fX = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j+1].x;
			newLine.end.fY = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[j+1].y;
			m_vLines.push_back(newLine);
		}
		tLine newLine;
		newLine.start.fX = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints - 1].x;
		newLine.start.fY = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[CWorldManager::GetInstance()->GetBlockers()[i].m_nNumPoints - 1].y;
		newLine.end.fX = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[0].x;
		newLine.end.fY = (float)CWorldManager::GetInstance()->GetBlockers()[i].m_Points[0].y;
		m_vLines.push_back(newLine);
		
		CLoadLevelState::GetInstance()->SetPercentage(85.0f + (((float)i/ (CWorldManager::GetInstance()->GetNumBlockers())) * 15.0f));
		CLoadLevelState::GetInstance()->Render();
	}


	
	CLoadLevelState::GetInstance()->SetPercentage(100.0f);
	CLoadLevelState::GetInstance()->Render();
}

inline float ManhattanDistance(tNode* source, tNode* target)
{
	return fabs(source->fX - target->fX) + fabs(source->fY - target->fY);
}

inline int PointDistance(POINT p1, POINT p2)
{
	return (int)((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
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

//tAStarNode* reconstructPath(tAStarNode* curNode)
//{
//	if(curNode->pCameFrom != NULL) {
//		tAStarNode * p = reconstructPath(curNode->pCameFrom); tVector2D pVec, curNodeVec; pVec.fX = p->pNode->fX; pVec.fY = p->pNode->fY; curNodeVec.fX = curNode->pNode->fX; curNodeVec.fY = curNode->pNode->fY;
//		return (p + curNode); }
//	else
//		return curNode;
//}

//bool CPathManager::NodeChecked(tNode * _node)
//{
//	// binary search and find the index of the start
//	int begin = 0, end = _vec->size()-1, mid = -1;
//
//	while (begin <= end) {
//		mid = (begin + end) / 2;
//		if (_node->fY * 9001 + _node->fX > yPos[(*_vec)[mid]] * 9001 + xPos[(*_vec)[mid]]) 
//			begin = mid + 1;
//		else if (_node->fY * 9001 + _node->fX < yPos[(*_vec)[mid]] * 9001 + xPos[(*_vec)[mid]]) 
//			end = mid - 1;
//		else
//			return true;
//	}
//
//	return false;
//}

bool CPathManager::NodeInBH(int _num, int* _arr, tNode * _node)
{
	// check if the _node is in the _vec
	for(int i = 1; i <= _num; i++)
	{
		if(xPos[(_arr)[i]] == _node->fX && yPos[(_arr)[i]] == _node->fY)
			return true;
	}
	return false;
}

tNode * GetNodeInVec(vector<tNode>* _vec, tNode * _node)
{
	for(unsigned int i = 0; i < _vec->size(); i++)
	{
		if(&(*_vec)[i] == _node)
			return &(*_vec)[i];
	}
	return NULL;
}

int CPathManager::GetNodeIndexInVec(vector<tNode>* _vec, tNode * _node)
{
	// binary search and find the index of the start
	int begin = 0, end = _vec->size()-1, mid = -1;

	while (begin <= end) {
		mid = (begin + end) / 2;
		if ((*_node) > (*_vec)[mid]) 
			begin = mid + 1;
		else if ((*_node) < (*_vec)[mid]) 
			end = mid - 1;
		else
			return mid;
	}
	return -1;
}

void AddNodeToSortedList( vector<int>* _vec, int _newVal )
{
	for(int i = _vec->size()-1; i >= 0; i--)
	{
		if((*_vec)[i] < _newVal)
		{
			_vec->insert(_vec->begin() + ++i, _newVal);
			return;
		}
	}

	_vec->insert(_vec->begin(), _newVal);
}


vector<tNode*> CPathManager::GetPath(float fX1, float fY1, float fX2, float fY2)
{
	//THIS is A*

	for(unsigned int i = 0; i < m_lstNodeList.size(); i++)
	{
		m_lstNodeList[i].checked = false;
		//if(InsideObject( m_lstNodeList[i] ) && ((m_lstNodeList[i].fX != fX1 && m_lstNodeList[i].fY != fY1) && (m_lstNodeList[i].fX != fX2 && m_lstNodeList[i].fY != fY2)))
		//		m_lstNodeList[i].blocked = true;
		//	else
		//		m_lstNodeList[i].blocked = false;
	}

	//vector<int> closedList;			// Closed cells
	int start;						// Start node
	int goal;						// Goal node
	bool foundGoal = false;
	int curNodeIndex;					
	int squaresChecked = 0;
	int numberOfOpenListItems = 0;

	// calculate number of grid lines
	int m_nNumGridLinesX = CWorldManager::GetInstance()->WorldWidth() / GRID_SCALE;
	int m_nNumGridLinesY = CWorldManager::GetInstance()->WorldHeight() / GRID_SCALE;

	// Figure out our starting and ending cells

	POINT startPt;
	startPt.x = (LONG)fX1;
	startPt.y = (LONG)fY1;

	POINT endPt;
	endPt.x = (LONG)fX2;
	endPt.y = (LONG)fY2;
	if(InsideBlocker(endPt))
		return vector<tNode*>();

	//calculate nearest node to start and goal
	{
		int closestDistance = 10000;
		int closestNode;
		int tilePosX = int(fX1 / GRID_SCALE);
		int tilePosY = int(fY1 / GRID_SCALE);

		tNode tileEdges[4];
		// Top left
		tileEdges[0].fX = (float)(tilePosX * GRID_SCALE);
		tileEdges[0].fY = (float)(tilePosY * GRID_SCALE);
		// Top right
		tileEdges[1].fX = (float)(tilePosX * GRID_SCALE + GRID_SCALE);
		tileEdges[1].fY = (float)(tilePosY * GRID_SCALE);
		// Bottom left
		tileEdges[2].fX = (float)(tilePosX * GRID_SCALE);
		tileEdges[2].fY = (float)(tilePosY * GRID_SCALE + GRID_SCALE);
		// Bottom right
		tileEdges[3].fX = (float)(tilePosX * GRID_SCALE + GRID_SCALE);
		tileEdges[3].fY = (float)(tilePosY * GRID_SCALE + GRID_SCALE);

		for(int i = 0; i < 4; i++)
		{
			POINT pt;
			pt.x = (LONG)tileEdges[i].fX;
			pt.y = (LONG)tileEdges[i].fY;
			if(PointDistance(startPt, pt) < closestDistance)
			{
				closestDistance = PointDistance(startPt, pt);
				closestNode = i;
			}
		}
		
		// binary search and find the index of the start
		int begin = 0, end = m_lstNodeList.size(), mid = -1;

		while (begin <= end) {
		   mid = (begin + end) / 2;
		   if (tileEdges[closestNode] > m_lstNodeList[mid]) 
			   begin = mid + 1;
		   else if (tileEdges[closestNode] < m_lstNodeList[mid]) 
			   end = mid - 1;
		   else
			   break;
		}

		start = mid;
		m_lstNodeList[start].blocked = false;
	}

	
	{
		int closestDistance = 10000;
		int closestNode;
		int tilePosX = int(fX2 / GRID_SCALE);
		int tilePosY = int(fY2 / GRID_SCALE);

		tNode tileEdges[4];
		// Top left
		tileEdges[0].fX = (float)(tilePosX * GRID_SCALE);
		tileEdges[0].fY = (float)(tilePosY * GRID_SCALE);
		// Top right
		tileEdges[1].fX = (float)(tilePosX * GRID_SCALE + GRID_SCALE);
		tileEdges[1].fY = (float)(tilePosY * GRID_SCALE);
		// Bottom left
		tileEdges[2].fX = (float)(tilePosX * GRID_SCALE);
		tileEdges[2].fY = (float)(tilePosY * GRID_SCALE + GRID_SCALE);
		// Bottom right
		tileEdges[3].fX = (float)(tilePosX * GRID_SCALE + GRID_SCALE);
		tileEdges[3].fY = (float)(tilePosY * GRID_SCALE + GRID_SCALE);

		for(int i = 0; i < 4; i++)
		{
			POINT pt;
			pt.x = (LONG)tileEdges[i].fX;
			pt.y = (LONG)tileEdges[i].fY;
			if(PointDistance(endPt, pt) < closestDistance)
			{
				closestDistance = PointDistance(endPt, pt);
				closestNode = i;
			}
		}

		// binary search and find the index of the start
		int begin = 0, end = m_lstNodeList.size(), mid = -1;

		while (begin <= end) {
		   mid = (begin + end) / 2;
		   if (tileEdges[closestNode] > m_lstNodeList[mid]) 
			   begin = mid + 1;
		   else if (tileEdges[closestNode] < m_lstNodeList[mid]) 
			   end = mid - 1;
		   else
			   break;
		}

	   goal = mid;
	   m_lstNodeList[goal].blocked = false;
	}
	// END Figure out our starting and ending cells


	// Add the starting node to the open list
	fCost[1] = 0.0f;
	gCost[1] = 0.0f;
	hCost[1] = ManhattanDistance(&m_lstNodeList[start], &m_lstNodeList[goal]);
	xPos[1] = m_lstNodeList[start].fX;
	yPos[1] = m_lstNodeList[start].fY;
	cameFrom[1] = 0;
	lstIndex[1] = start;
	squaresChecked = 1;
	numberOfOpenListItems = 1;
	openBH[squaresChecked] = squaresChecked;
	m_lstNodeList[start].checked = true;

	// Repeat while there are tiles to consider
	while( numberOfOpenListItems > 0 )
	{
		// curNodeIndex will equal the cell#ID with the lowest F cost in the openBH
		curNodeIndex = openBH[1];

		// remove it from the openBH and add it to the closed list
		{
			//AddNodeToSortedList(&closedList, openBH[1] );
			m_lstNodeList[lstIndex[openBH[1]]].checked = true;
			openBH[1] = openBH[numberOfOpenListItems];	// move the last item in the list to the front
			numberOfOpenListItems = numberOfOpenListItems - 1;
			
			int v = 1;
			int u;

			while(true)
			{
				u = v;
				if(2*u+1 <= numberOfOpenListItems) // if both children exist
				{
					if(fCost[openBH[u]] >= fCost[openBH[2*u]]) { v = 2 * u; }
					if(fCost[openBH[v]] >= fCost[openBH[2*u+1]]) { v = 2 * u + 1;}
				}
				else if (2*u <= numberOfOpenListItems)
				{
					if (fCost[openBH[u]] >= fCost[openBH[2*u]]) { v = 2 * u; }
				}

				if (u != v)
				{
					//int temp = openList[u];
					//openList[u] = openList[v];
					//openList[v] = temp;
					swap(openBH[u], openBH[v]);
				}
				else
					break;
			}
			 
		}
		// END remove it from the openBH and move it to the closed list

		// if this square is the goal we have found the path
		if(lstIndex[curNodeIndex] == goal)
		{
			//goal = curNode;
			foundGoal = true;
			break;
		}

		// POINT structure representing the current square's pt
		POINT curNodePt;
		curNodePt.x = (LONG)xPos[curNodeIndex];
		curNodePt.y = (LONG)yPos[curNodeIndex];

		

		vector<tNode*>* adjNeighbors = &m_mpAdjacencies[&m_lstNodeList[lstIndex[curNodeIndex]]].pNeighbors;
		// loop through each of this cell's adgancies
		for(unsigned int adj = 0; adj < adjNeighbors->size(); adj++)
		{
			POINT adjPt;
			adjPt.x = (LONG)(*adjNeighbors)[adj]->fX;
			adjPt.y = (LONG)(*adjNeighbors)[adj]->fY;

			if((*adjNeighbors)[adj]->checked == true || (*adjNeighbors)[adj]->blocked == true)
				continue;

			// if it's not in the open list add it
			if(!NodeInBH(numberOfOpenListItems, openBH, (*adjNeighbors)[adj]))
			{
				squaresChecked++;
				numberOfOpenListItems++;
				openBH[numberOfOpenListItems] = squaresChecked;

				cameFrom[squaresChecked] = curNodeIndex;
				gCost[squaresChecked] = gCost[curNodeIndex] + PointDistance(adjPt, curNodePt);
				hCost[squaresChecked] = ManhattanDistance((*adjNeighbors)[adj], &m_lstNodeList[goal]);
				fCost[squaresChecked] = gCost[squaresChecked] + hCost[squaresChecked];
				xPos[squaresChecked] = (*adjNeighbors)[adj]->fX;
				yPos[squaresChecked] = (*adjNeighbors)[adj]->fY;
				lstIndex[squaresChecked] = GetNodeIndexInVec(&m_lstNodeList, (*adjNeighbors)[adj]);
				
				//put it in the right place
				{
					int m = numberOfOpenListItems;
					while(m != 1)
					{
						if(fCost[openBH[m]] <= fCost[openBH[m/2]])
						{
							swap(openBH[m], openBH[m/2]);
							m = m / 2;
						} else
							break;
					}
				}
			} else {
				// we are in the open list, we are checking to see if this path is better
				int adjNode = GetNodeIndexInVec(&m_lstNodeList, (*adjNeighbors)[adj] );
				
				int i = 0;
				for(; i < numberOfOpenListItems; i++)
				{
					if(xPos[i] == xPos[adjNode] && yPos[i] == yPos[adjNode])
						break;
				}

				if(gCost[i] > (gCost[curNodeIndex] + PointDistance(adjPt, curNodePt)))
				{
					// This node is a better path
					gCost[i]= gCost[curNodeIndex] + PointDistance(adjPt, curNodePt);
					fCost[i] = gCost[i] + hCost[i];
					cameFrom[i] = curNodeIndex;

					//put it in the right place
					{
						int m = i;
						while(m != 1)
						{
							if(fCost[openBH[m]] <= fCost[openBH[m/2]])
							{
								swap(openBH[m], openBH[m/2]);
								m = m/2;
							} else
								break;
						}
					}
				}
			}
		}
	}

	if(foundGoal)
	{
		// we have found the goal!
		vector<tNode*> vReturn;
		int indexNode;
		indexNode = curNodeIndex;

		while(cameFrom[indexNode] != NULL)
		{

			vReturn.insert( vReturn.begin(), &m_lstNodeList[lstIndex[indexNode]] );
			indexNode = cameFrom[indexNode];
		}
		
		return vReturn;
	} else {
		// goal not reachable! there is no path!
		return vector<tNode*>();
	}
}



















	//POINT startPt;
	//startPt.x = (LONG)fX1;
	//startPt.y = (LONG)fY1;

	//POINT endPt;
	//endPt.x = (LONG)fX2;
	//endPt.y = (LONG)fY2;
	//if(InsideBlocker(endPt))
	//	return vector<tNode*>();

	//vector<tNode*> vRet;
	//vector<tAStarNode> vNodePool;

	//map<tNode*, tAStarNode> openSet;
	//queue<tAStarNode> pQueue;
	//map<tNode*, tAStarNode> closeSet;

	//tAStarNode start;
	//tAStarNode goal;
	//start.pNode=NULL;
	//goal.pNode=NULL;

	////calculate nearest node to start and goal
	//{
	//	//tVector2D pos = {fX1, fY1};
	//	//tVector2D dst;
	//	//float minDist = 10000.0f;
	//	//float fTemp;
	//	//for(int i = 0; i < m_lstNodeList.size(); i++)
	//	//{
	//	//	dst.fX = m_lstNodeList[i].fX;
	//	//	dst.fY = m_lstNodeList[i].fY;
	//	//	fTemp = Vector2DLength(dst - pos);

	//	//	bool bRet=false;
	//	//	for(size_t j=0; j<m_vLines.size(); j++)
	//	//	{
	//	//		if(IntersectLine(pos, dst, m_vLines[j].start, m_vLines[j].end))
	//	//		{
	//	//			bRet = true;
	//	//			break;
	//	//		}
	//	//	}

	//	//	if(!bRet && fTemp < minDist)
	//	//	{
	//	//		minDist = fTemp;
	//	//		start.pNode = &m_lstNodeList[i];
	//	//	}
	//	//}
	//	
	//	int closestDistance = 10000;
	//	int closestNode;
	//	int tilePosX = int(fX1 / GRID_SCALE);
	//	int tilePosY = int(fY1 / GRID_SCALE);



	//	POINT tileEdges[4];
	//	// Top left
	//	tileEdges[0].x = tilePosX * GRID_SCALE;
	//	tileEdges[0].y = tilePosY * GRID_SCALE;
	//	// Top right
	//	tileEdges[1].x = tilePosX * GRID_SCALE + GRID_SCALE;
	//	tileEdges[1].y = tilePosY * GRID_SCALE;
	//	// Bottom left
	//	tileEdges[2].x = tilePosX * GRID_SCALE;
	//	tileEdges[2].y = tilePosY * GRID_SCALE + GRID_SCALE;
	//	// Bottom right
	//	tileEdges[3].x = tilePosX * GRID_SCALE + GRID_SCALE;
	//	tileEdges[3].y = tilePosY * GRID_SCALE + GRID_SCALE;

	//	for(int i = 0; i < 4; i++)
	//	{
	//		if(PointDistance(startPt, tileEdges[i]) < closestDistance)
	//		{
	//			closestDistance = PointDistance(startPt, tileEdges[i]);
	//			closestNode = i;
	//		}
	//	}
	//	
	//	for(unsigned int i = 0; i < m_lstNodeList.size(); i++)
	//		if(m_lstNodeList[i].fX == tileEdges[closestNode].x && m_lstNodeList[i].fY == tileEdges[closestNode].y)
	//		{
	//			start.pNode = &m_lstNodeList[i];
	//			break;
	//		}
	//	
	//}
	//{
	//	//tVector2D pos = {fX2, fY2};
	//	//tVector2D dst;
	//	//float minDist = 1000.0f;
	//	//float fTemp;
	//	//for(size_t i=0; i<m_lstNodeList.size(); i++)
	//	//{
	//	//	dst.fX = m_lstNodeList[i].fX;
	//	//	dst.fY = m_lstNodeList[i].fY;
	//	//	fTemp = Vector2DLength(dst - pos);
	//	//	if(fTemp < minDist)
	//	//	{
	//	//		minDist = fTemp;
	//	//		goal.pNode = &m_lstNodeList[i];
	//	//	}
	//	//}

	//	int closestDistance = 10000;
	//	int closestNode;
	//	int tilePosX = int(fX2 / GRID_SCALE);
	//	int tilePosY = int(fY2 / GRID_SCALE);



	//	POINT tileEdges[4];
	//	// Top left
	//	tileEdges[0].x = tilePosX * GRID_SCALE;
	//	tileEdges[0].y = tilePosY * GRID_SCALE;
	//	// Top right
	//	tileEdges[1].x = tilePosX * GRID_SCALE + GRID_SCALE;
	//	tileEdges[1].y = tilePosY * GRID_SCALE;
	//	// Bottom left
	//	tileEdges[2].x = tilePosX * GRID_SCALE;
	//	tileEdges[2].y = tilePosY * GRID_SCALE + GRID_SCALE;
	//	// Bottom right
	//	tileEdges[3].x = tilePosX * GRID_SCALE + GRID_SCALE;
	//	tileEdges[3].y = tilePosY * GRID_SCALE + GRID_SCALE;

	//	for(int i = 0; i < 4; i++)
	//	{
	//		if(PointDistance(endPt, tileEdges[i]) < closestDistance)
	//		{
	//			closestDistance = PointDistance(endPt, tileEdges[i]);
	//			closestNode = i;
	//		}
	//	}

	//	for(unsigned int i = 0; i < m_lstNodeList.size(); i++)
	//		if(m_lstNodeList[i].fX == tileEdges[closestNode].x && m_lstNodeList[i].fY == tileEdges[closestNode].y)
	//		{
	//			goal.pNode = &m_lstNodeList[i];
	//			break;
	//		}
	//}

	//if(!start.pNode)
	//	return vector<tNode*>();

	//if(goal.pNode == start.pNode)
	//	return vector<tNode*>();

	//start.pCameFrom = NULL;
	//start.nIndexParent = -1;
	//start.fG = 0.0f;
	//start.fH = ManhattanDistance(*start.pNode, *goal.pNode);

	//openSet[start.pNode] = start;
	//pQueue.push(start);

	//bool bFoundGoal = false;
	//while(openSet.size() > 0)
	//{
	//	tAStarNode x = pQueue.front();
	//	vNodePool.push_back(x);
	//	pQueue.pop();
	//	openSet.erase(x.pNode);
	//	if(x.pNode == goal.pNode)
	//	{
	//		//path exists
	//		goal = x;
	//		bFoundGoal = true;
	//		break;
	//	}
	//	else
	//	{
	//		closeSet[x.pNode] = x;
	//		tAdjacency adj;
	//		adj = m_mpAdjacencies[x.pNode];

	//		for(size_t i=0; i<adj.pNeighbors.size(); i++)
	//		{
	//			POINT curNode;
	//			curNode.x = (LONG)adj.pNeighbors[i]->fX;
	//			curNode.y = (LONG)adj.pNeighbors[i]->fY;

	//			//if(x.pNode->fX == adj.pNeighbors[i]->fX && x.pNode->fY == adj.pNeighbors[i]->fY)
	//			//	continue;

	//			if(closeSet.find(adj.pNeighbors[i]) == closeSet.end())
	//			{
	//				POINT cur, prev;
	//				cur.x = (LONG)adj.pNeighbors[i]->fX;
	//				cur.y = (LONG)adj.pNeighbors[i]->fY;
	//				prev.x = (LONG)x.pNode->fX;
	//				prev.y = (LONG)x.pNode->fY;

	//				float g = x.fG + PointDistance(cur, prev);

	//				bool tentativeIsBetter;
	//				if(openSet.find(adj.pNeighbors[i]) == openSet.end())
	//				{
	//					// If not in openset
	//					tAStarNode n;
	//					n.pNode = adj.pNeighbors[i];
	//					n.pCameFrom = &x;
	//					n.nIndexParent = vNodePool.size()-1;
	//					n.fG = g;
	//					n.fH = ManhattanDistance(*adj.pNeighbors[i], *goal.pNode);
	//					n.fF = g + ManhattanDistance(*adj.pNeighbors[i], *goal.pNode);
	//					openSet[n.pNode] = n;
	//					pQueue.push(n);
	//					tentativeIsBetter = true;
	//				}
	//				else if(g < openSet[adj.pNeighbors[i]].fG)
	//				{
	//					tentativeIsBetter = true;
	//				} else {
	//					tentativeIsBetter = false;
	//				}

	//				if(tentativeIsBetter)
	//				{
	//					openSet[adj.pNeighbors[i]].pCameFrom = &x;
	//					openSet[adj.pNeighbors[i]].fG = g;
	//					openSet[adj.pNeighbors[i]].fH = ManhattanDistance(*adj.pNeighbors[i], *goal.pNode);
	//					openSet[adj.pNeighbors[i]].fF = g + ManhattanDistance(*adj.pNeighbors[i], *goal.pNode);
	//				}
	//							
	//			}
	//		}
	//	}
	//}

	//if(bFoundGoal)
	//{
	//	stack<tNode*> stk;
	//	stk.push(goal.pNode);
	//	tAStarNode pParent = vNodePool[goal.nIndexParent];
	//	while(pParent.nIndexParent < vNodePool.size())
	//	{
	//		stk.push(pParent.pNode);
	//		pParent = vNodePool[pParent.nIndexParent];
	//		if(pParent.pCameFrom == NULL)
	//		{
	//			stk.push(pParent.pNode);
	//			break;
	//		}
	//	}

	//	while(stk.size() > 0)
	//	{
	//		vRet.push_back(stk.top());
	//		stk.pop();
	//	}
	//	return vRet;
	//}
	//return vector<tNode*>();
//}