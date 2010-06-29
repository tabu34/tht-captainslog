#ifndef CPathManager_h__
#define CPathManager_h__
#include <vector>
#include <map>
#include <queue>
#include <stack>
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

	//distance from source along optimal path
	float fG;

	//estimate of distance from here to target node (heuristic)
	float fH;
};

class CPathManager
{
	vector<tNode> m_lstNodeList;

	map<tNode*, tAdjacency> m_mpAdjacencies;

	CPathManager();
	~CPathManager();
	CPathManager(const CPathManager&);
	CPathManager& operator=(const CPathManager&);
public:
	static CPathManager* GetInstance();

	void GenerateMap();
	vector<tNode*> GetPath(float fX1, float fY1, float fX2, float fY2);


};
#endif // CPathManager_h__