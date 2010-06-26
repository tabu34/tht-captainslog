#ifndef CWorldManager_h__
#define CWorldManager_h__

struct Tile 
{
	int m_nWidth;
	int m_nHeight;
	int m_nTileNumber;
	int m_nTop;
	int m_nLeft;
};

struct Object
{
	int m_nTop;
	int m_nLeft;
	int m_nID;
};

struct Blocker
{
	struct Point
	{
		int x;
		int y;
	};
	Point* m_Points;
};

class CWorldManager
{
private:

	float m_fVersionNumber;

	char* m_szFileName;
	int m_nTilesetImageID;
	int m_nTilesetWidth;
	int m_nTilesetHeight;

	Tile*** m_World;
	Object* m_Objects;
	Blocker* m_Blockers;

	int m_nWorldHeight;
	int m_nWorldWidth;
	int m_nWorldDepth;



	CWorldManager();
	~CWorldManager();
	CWorldManager(CWorldManager&);
	CWorldManager& operator=(CWorldManager&);

public:
	static CWorldManager* GetInstance();

	void Load(string sFileName);
	void Render();
};

#endif