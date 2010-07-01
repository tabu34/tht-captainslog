// A-Star (spike).cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "A-Star (spike).h"
#define MAX_LOADSTRING 100

//stuff for A*
struct Blocker
{
	struct Point
	{
		int x;
		int y;
		Point(int nX = 0, int nY = 0) {x = nX; y = nY;}
	};
	int m_nNumPoints;
	Point* m_Points;
} arrBlockers[3];


typedef struct
{
	float fX;
	float fY;
} tNode;

const tNode helperNodes[6] = {
	{
		139.0f, 29.0f,
	},
	{
		89.0f, 224.0f,
	},
	{
		124.0f, 125.0f,
	},
	{
		317.0f, 291.0f,
	},
	{
		446.0f, 240.0f,
	},
	{
		434.0f, 156.0f,
	},
};

typedef struct  
{
	tNode* pFrom;
	tNode* pTo;
} tEdge;

typedef struct 
{
	tNode* pNode;
	vector<tNode*> pNeighbors;
} tAdjacency;

struct tAStarNode 
{
	tNode* pNode;

	//used to construct path once search is over
	tAStarNode* pCameFrom;
	size_t nIndexParent;

	//distance from source along optimal path
	float fG;

	//estimate of distance from here to target node (heuristic)
	float fH;
};


struct tLine
{
	tVector2D start;
	tVector2D end;
};

class CPathManager
{
public:
	vector<tNode> m_lstNodeList;

	map<tNode*, tAdjacency> m_mpAdjacencies;
	vector<tLine> m_vLines;
private:
	CPathManager();
	~CPathManager();
	CPathManager(const CPathManager&);
	CPathManager& operator=(const CPathManager&);
public:
	static CPathManager* GetInstance();

	void GenerateMap();
	vector<tNode*> GetPath(float fX1, float fY1, float fX2, float fY2);


};

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

	for(int i=0; i<3; i++)
	{
		counter=0;
		p1 = arrBlockers[i].m_Points[0];

		for(int j=1; j<=arrBlockers[i].m_nNumPoints; j++)
		{
			p2 = arrBlockers[i].m_Points[j%arrBlockers[i].m_nNumPoints];
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
	for(int i=0; i<3; i++)
	{
		vector<tNode> vNodesInShape;
		vNodesInShape.clear();
		lastNode.fX = -1.0f;
		node.fX = -1.0f;
		for(int j=0; j<arrBlockers[i].m_nNumPoints; j++)
		{
			if(node.fX!=-1.0f)
			{
				lastNode = node;
			}
			node.fX = (float)arrBlockers[i].m_Points[j].x;
			node.fY = (float)arrBlockers[i].m_Points[j].y;
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
	for(int i=0; i<6; i++)
	{
		node.fX = helperNodes[i].fX;
		node.fY = helperNodes[i].fY;
		m_lstNodeList.push_back(node);
	}


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



// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
vector<tNode*> vDirections;
POINT theGuy;
POINT target;
POINT startGuy;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ASTARSPIKE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	//CREATE THE BLOCKERS
	arrBlockers[0].m_nNumPoints = 5;
	arrBlockers[1].m_nNumPoints = 4;
	arrBlockers[2].m_nNumPoints = 7;

	arrBlockers[0].m_Points = new Blocker::Point[5]; //rectangle
	arrBlockers[1].m_Points = new Blocker::Point[4]; //triangle
	arrBlockers[2].m_Points = new Blocker::Point[7]; //hexagon

	arrBlockers[0].m_Points[0] = Blocker::Point(20, 20);
	arrBlockers[0].m_Points[1] = Blocker::Point(90, 20);
	arrBlockers[0].m_Points[2] = Blocker::Point(90, 200);
	arrBlockers[0].m_Points[3] = Blocker::Point(20, 200);
	arrBlockers[0].m_Points[4] = Blocker::Point(20, 20);

	arrBlockers[1].m_Points[0] = Blocker::Point(200, 32);
	arrBlockers[1].m_Points[1] = Blocker::Point(425, 226);
	arrBlockers[1].m_Points[2] = Blocker::Point(90, 255);
	arrBlockers[1].m_Points[3] = Blocker::Point(200, 32);

	arrBlockers[2].m_Points[0] = Blocker::Point(590, 187);
	arrBlockers[2].m_Points[1] = Blocker::Point(716, 251);
	arrBlockers[2].m_Points[2] = Blocker::Point(716, 381);
	arrBlockers[2].m_Points[3] = Blocker::Point(593, 446);
	arrBlockers[2].m_Points[4] = Blocker::Point(470, 379);
	arrBlockers[2].m_Points[5] = Blocker::Point(470, 253);
	arrBlockers[2].m_Points[6] = Blocker::Point(590, 187);

	CPathManager* pPM = CPathManager::GetInstance();
	pPM->GenerateMap();

	theGuy.x = 300;
	theGuy.y = 100;
	target.x = 747;
	target.y = 408;

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTARSPIKE));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTARSPIKE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ASTARSPIKE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
   RECT rClient;
   SetRect(&rClient, 0, 0, 1000, 800);
   AdjustWindowRect(&rClient, WS_OVERLAPPEDWINDOW, TRUE);
   int ww = rClient.right - rClient.left;
   int wh = rClient.bottom - rClient.top;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, ww, wh, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }





   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC	hdc = BeginPaint(hWnd, &ps);

	RECT theScreen;
	GetClientRect(hWnd, &theScreen);

	HBRUSH hbrBG = CreateSolidBrush((COLORREF)0xFFFFFF);
	HBRUSH hbrOld;
	FillRect(hdc, &theScreen, hbrBG);
	hbrOld=(HBRUSH)SelectObject(hdc, hbrBG);

	HPEN hpBoard, hpOld, hpPath, hpAdj, hpNode;
	hpBoard=CreatePen(PS_SOLID, 3, 0x000000);
	hpPath = CreatePen(PS_SOLID, 3, 0xFF0000);
	hpAdj = CreatePen(PS_SOLID, 1, 0x00FF00);
	hpNode = CreatePen(PS_SOLID, 2, 0x0000FF);
	hpOld=(HPEN)SelectObject(hdc, hpBoard);

// 	//draw the blockers
// 	for(int i=0; i<3; i++)
// 	{
// 		for(int j=0; j<arrBlockers[i].m_nNumPoints-1; j++)
// 		{
// 			MoveToEx(hdc, arrBlockers[i].m_Points[j].x, arrBlockers[i].m_Points[j].y, NULL);
// 			LineTo(hdc, arrBlockers[i].m_Points[j+1].x, arrBlockers[i].m_Points[j+1].y);
// 		}
// 	}
	//draw lines of collision
	for(size_t i=0; i<CPathManager::GetInstance()->m_vLines.size(); i++)
	{
		MoveToEx(hdc, (int)CPathManager::GetInstance()->m_vLines[i].start.fX,
			(int)CPathManager::GetInstance()->m_vLines[i].start.fY, NULL);
		LineTo(hdc, (int)CPathManager::GetInstance()->m_vLines[i].end.fX,
			(int)CPathManager::GetInstance()->m_vLines[i].end.fY);
	}

	//draw the adjacencies
	SelectObject(hdc, hpAdj);
	for(size_t i=0; i<CPathManager::GetInstance()->m_lstNodeList.size(); i++)
	{
		tNode* pN = &CPathManager::GetInstance()->m_lstNodeList[i];
		for(size_t j=0; j<CPathManager::GetInstance()->m_mpAdjacencies[pN].pNeighbors.size(); j++)
		{
			MoveToEx(hdc, (int)pN->fX, (int)pN->fY, NULL);
			LineTo(hdc, (int)CPathManager::GetInstance()->m_mpAdjacencies[pN].pNeighbors[j]->fX,
				(int)CPathManager::GetInstance()->m_mpAdjacencies[pN].pNeighbors[j]->fY);
		}
	}

	//draw the path
	SelectObject(hdc, hpPath);
	MoveToEx(hdc, startGuy.x, startGuy.y, NULL);
	for(size_t i=0; i<vDirections.size(); i++)
	{
		LineTo(hdc, (int)vDirections[i]->fX, (int)vDirections[i]->fY);
		MoveToEx(hdc, (int)vDirections[i]->fX, (int)vDirections[i]->fY, NULL);	
	}
	if(vDirections.size()>0)
		LineTo(hdc, target.x, target.y);

	//draw the nodes
	SelectObject(hdc, hpNode);
	for(size_t i=0; i<CPathManager::GetInstance()->m_lstNodeList.size(); i++)
	{
		tNode* pNode = &CPathManager::GetInstance()->m_lstNodeList[i];
		MoveToEx(hdc, (int)pNode->fX-7, (int)pNode->fY-7, NULL);
		LineTo(hdc, (int)pNode->fX+7, (int)pNode->fY+7);
		MoveToEx(hdc, (int)pNode->fX+7, (int)pNode->fY-7, NULL);
		LineTo(hdc, (int)pNode->fX-7, (int)pNode->fY+7);
	}
	
	//draw our guy
	SelectObject(hdc, hpBoard);
	MoveToEx(hdc, theGuy.x-3, theGuy.y-3, NULL);
	LineTo(hdc, theGuy.x+3, theGuy.y+3);
	MoveToEx(hdc, theGuy.x-3, theGuy.y+3, NULL);
	LineTo(hdc, theGuy.x+3, theGuy.y-3);

	//draw the target
	MoveToEx(hdc, target.x, target.y-5, NULL);
	LineTo(hdc, target.x, target.y+5);
	MoveToEx(hdc, target.x-5, target.y, NULL);
	LineTo(hdc, target.x+5, target.y);

	SelectObject(hdc, hpOld);
	SelectObject(hdc, hbrOld);
	DeleteObject(hpPath);
	DeleteObject(hpBoard);
	DeleteObject(hbrBG);
	DeleteObject(hpAdj);
	DeleteObject(hpNode);
	EndPaint(hWnd, &ps);
}

void TheSequence(HWND hWnd)
{
	vDirections = CPathManager::GetInstance()->GetPath((float)theGuy.x, (float)theGuy.y, (float)target.x, (float)target.y);

	startGuy = theGuy;

	for(size_t i=0; i<vDirections.size(); i++)
	{
// 		if(i == vDirections.size()-1)
// 		{
// 			POINT pEnd;
// 			pEnd.x = (int)vDirections[i]->fX;
// 			pEnd.y = (int)vDirections[i]->fY;
// 			if(PointDistance(theGuy, target) < PointDistance(theGuy, pEnd))
// 			{
// 				Sleep(300);
// 				theGuy.x = target.x;
// 				theGuy.y = target.y;
// 				InvalidateRect(hWnd, NULL, TRUE);
// 				OnPaint(hWnd);
// 				Sleep(200);
// 			}
// 			break;
// 		}

		Sleep(300);
		theGuy.x = (int)vDirections[i]->fX;
		theGuy.y = (int)vDirections[i]->fY;
		InvalidateRect(hWnd, NULL, TRUE);
		OnPaint(hWnd);
		Sleep(200);
	}

	bool bRet=false;
	tVector2D guy = {(float)theGuy.x, (float)theGuy.y};
	tVector2D tar = {(float)target.x, (float)target.y};
	for(size_t i=0; i<CPathManager::GetInstance()->m_vLines.size(); i++)
	{
		if(IntersectLine(guy, tar, CPathManager::GetInstance()->m_vLines[i].start, CPathManager::GetInstance()->m_vLines[i].end))
		{
			bRet=true;
			break;
		}
	}
	if(!bRet && !InsideBlocker(target))
	{
		Sleep(300);
		theGuy.x = target.x;
		theGuy.y = target.y;
		InvalidateRect(hWnd, NULL, TRUE);
		OnPaint(hWnd);
		Sleep(200);
	}
	vDirections.clear();
	InvalidateRect(hWnd, NULL, TRUE);
	OnPaint(hWnd);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		TheSequence(hWnd);
		break;
	case WM_RBUTTONDOWN:
		target.x = LOWORD(lParam);
		target.y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
