#ifndef CFileManager_h__
#define CFileManager_h__

class CFileManager
{
public:
	struct tFontFileStruct 
	{
		char*	szFilePath;
		short	nImageWidth;
		short	nImageHeight;
		short	nCellWidth;
		short	nCellHeight;
		short	nStartChar;
		short	nFontHeight;
		short	pCharWidths[256];
	};

private:
	CFileManager();
	~CFileManager();
	CFileManager(CFileManager&);
	CFileManager& operator=(CFileManager&);

public:
	static CFileManager* GetInstance();

	void LoadBitmapFont(tFontFileStruct* tFileStruct);
};
#endif // CFileManager_h__