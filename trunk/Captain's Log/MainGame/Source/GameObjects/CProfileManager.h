#pragma once

#include <string>
#include <vector>
using namespace std;

#include "CBMPFont.h"

class CGameInfo
{
public:
	string WriteToSaveFile(void)
	{
		string info;
		return info;
	}
	void ReadFromSaveFile(string Read)
	{
		string info = Read;
	}
};

class CProfile
{
	string m_sPlayerName;
	CGameInfo m_cPlayerProgress;
	int m_nPlayerNumber;
public:

	CProfile()
	{
		m_sPlayerName = "null";
		m_nPlayerNumber = 0;
	}

	string GetName(void){return m_sPlayerName;}
	void SetName(string Name){m_sPlayerName = Name;}
	
	CGameInfo GetProgress(void){return m_cPlayerProgress;}
	void SetProgress(CGameInfo Progress){m_cPlayerProgress = Progress;}

	int GetNumber(void){return m_nPlayerNumber;}
	void SetNumber(int Number){m_nPlayerNumber = Number;}

};

enum STATUS {DISPLAY = 0, ENTER_NEW, EXPAND, NUM_STATUSES};

class CProfileManager
{
	CProfile* m_cProfileArray;
	int m_nProfiles;

	int m_nSelectedProfile;
	int m_nDisplayOffset;

	int m_nStatus;

	string m_szNewProfName;

	int m_nExpandSelector;

	CBMPFont m_cBMPFont;

	CProfileManager() {}
	CProfileManager(const CProfileManager&);
	CProfileManager& operator=(const CProfileManager&);
	~CProfileManager() {}

public: 
	void Init(void);
	void LoadProfiles(void);
	void SaveProfiles(void);
	void AddProfile(string ProfileName, CGameInfo* GameInfo = NULL);//DONE
	void DeleteProfile(int ProfileNumber);//DONE
	void SelectProfile(int ProfileNumber);
	void Update(void);//FINISH THIS
	void Render(void);

	void Shutdown(void)
	{
		SaveProfiles();
	}

	static CProfileManager* GetInstance(void)
	{
		static CProfileManager instance;
		return &instance;
	}
};