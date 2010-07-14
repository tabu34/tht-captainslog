#ifndef CPathManager_h__
#define CPathManager_h__
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include "..\SGD Wrappers\SGD_Math.h"
using std::stack;
using std::queue;
using std::map;
using std::pair;
using std::multimap;
using std::vector;
typedef struct
{
	float fX;
	float fY;
} tNode;
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
	bool CheckPath(float fX1, float fY1, float fX2, float fY2);
	bool IsPointInside(POINT p);


};
#endif // CPathManager_h__