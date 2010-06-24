#include "precompiled_header.h"

#include "CProfileManager.h"

#include <fstream>
using namespace std;

void CProfileManager::AddProfile(CProfile newProfile)
{
	newProfile.SetNumber(m_vProfiles.size());
	m_vProfiles.push_back(newProfile);
}

void CProfileManager::LoadProfiles(void)
{
	ifstream in;
}

void CProfileManager::SaveProfiles(void)
{
	ofstream out;
}

void CProfileManager::DeleteProfile(CProfile tobeDeleted)
{
	
	{
		vector<CProfile>::iterator Iter;
		int i = 0;
		for(Iter = m_vProfiles.begin(); Iter!= m_vProfiles.end(); ++Iter, ++i)
		{
			if(i == tobeDeleted.GetNumber())
			{				
				m_vProfiles.erase(Iter);
				break;
			}
		}
	}
}

void CProfileManager::Update(void)
{
	switch(m_nStatus)
	{
	case DISPLAY:
	//CODE FOR SELECTING PROFILES AND SELECTING OPTIONS (Create new one, use a profile, delete a profile, exit)
		break;
	case ENTER_NEW:
	//CODE FOR ENTERING A NEW PROFILE
		break;
	};
}
void CProfileManager::Render(void)
{
	switch(m_nStatus)
	{
	case DISPLAY:
	//CODE FOR SELECTING PROFILES AND SELECTING OPTIONS (Create new one, use a profile, delete a profile, exit)
		break;
	case ENTER_NEW:
	//CODE FOR ENTERING A NEW PROFILE
		break;
	};
}

void CProfileManager::Init(void)
{
	LoadProfiles();
	m_nStatus = DISPLAY;
	int m_nSelectedProfile = 0;
	vector<CProfile>::iterator Iter;
	Iter = m_vProfiles.begin();
	for(int i = 0; i<10;++i)
	{
		if(Iter != m_vProfiles.end())
		{
			m_nProfilesToDisplay[i] = i;
			++Iter;
		}else
		{
			m_nProfilesToDisplay[i] = -1;
		}
	}
}