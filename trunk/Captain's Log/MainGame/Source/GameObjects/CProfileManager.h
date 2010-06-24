#pragma once

#include <string>
#include <vector>
using namespace std;

class CGameInfo
{
};

class CProfile
{
	string m_sPlayerName;
	CGameInfo m_cPlayerProgress;
	int m_nPlayerNumber;
public:
	string GetName(void){return m_sPlayerName;}
	void SetName(string Name){m_sPlayerName = Name;}
	
	CGameInfo GetProgress(void){return m_cPlayerProgress;}
	void SetProgress(CGameInfo Progress){m_cPlayerProgress = Progress;}

	int GetNumber(void){return m_nPlayerNumber;}
	void SetNumber(int Number){m_nPlayerNumber = Number;}
};

enum STATUS {DISPLAY = 0, ENTER_NEW, NUM_STATUSES};

class CProfileManager
{
	vector<CProfile> m_vProfiles;

	int m_nSelectedProfile;
	int m_nProfilesToDisplay[10];

	int m_nStatus;

	CProfileManager() {}
	CProfileManager(const CProfileManager&);
	CProfileManager& operator=(const CProfileManager&);
	~CProfileManager() {}

public:
	void Init(void);
	void LoadProfiles(void);
	void SaveProfiles(void);
	void AddProfile(CProfile newProfile);//DONE
	void DeleteProfile(CProfile tobeDeleted);//DONE
	void SelectProfile(CProfile selectedProfile);
	void Update(void);//FINISH THIS
	void Render(void);
};