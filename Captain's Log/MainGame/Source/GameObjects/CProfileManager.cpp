#include "precompiled_header.h"

#include "CProfileManager.h"

#include <fstream>
using namespace std;

void CProfileManager::AddProfile(string ProfileName, CGameInfo* GameInfo)
{	
	CProfile* newProfileArray = new CProfile[m_nProfiles+1];
	for(int i = 0; i<m_nProfiles;++i)
	{
		newProfileArray[i].SetName(m_cProfileArray[i].GetName());
		newProfileArray[i].SetNumber(i);
		//COPY THE GAME PROGRESS
	}
	newProfileArray[m_nProfiles].SetName(ProfileName);
	newProfileArray[m_nProfiles].SetNumber(m_nProfiles);

	delete[] m_cProfileArray;
	m_cProfileArray = newProfileArray;
	++m_nProfiles;
}

void CProfileManager::LoadProfiles(void)
{
	ifstream in;
	in.open("REsource/SaveFile.txt");
	if(in.is_open())
	{
		delete[] m_cProfileArray;

		int nprofs = 0;

		m_nProfiles = nprofs;
		m_cProfileArray = new CProfile[m_nProfiles];

		in>>nprofs;
		for(int i = 0; i<m_nProfiles;++i)
		{
			if(in.eof())
			{
				break;
			}
			char buffer[120];
			in.getline(buffer,_countof(buffer),'\n');
			AddProfile(buffer);
			/*in.getline(buffer,_countof(buffer), '\n');
			newprofile.SetNumber((int)buffer);*/
			
			//READ GAME PROGRESS
			/*
			in.getline(buffer,_countof(buffer), '\n');

			CGameInfo info;
			info.ReadFromSaveFile(buffer);

			newprofile.SetProgress(info);*/
			
		}
		in.close();
	}
}

void CProfileManager::SaveProfiles(void)
{
	ofstream out;
	out.open("Resource/SaveFile.txt");
	if(out.is_open())
	{
		out<<m_nProfiles<<"\n";
		for(int i = 0; i<m_nProfiles;++i)
		{
			out<<m_cProfileArray[i].GetName()<<"\n";
			//out<<m_cProfileArray[i].GetNumber()<<"\n";
			//SAVE GAME PROGRESS
			//out<<m_vProfiles[i].GetProgress().WriteToSaveFile()<<"\n";
		}
		out.close();
	}
}

void CProfileManager::DeleteProfile(int ProfileNumber)
{
	CProfile* newProfileArray = new CProfile[m_nProfiles-1];
	for(int i = 0; i<m_nProfiles;++i)
	{
		if(i != ProfileNumber)
		{
			newProfileArray[i].SetName(m_cProfileArray[i].GetName());
			newProfileArray[i].SetNumber(i);
			//COPY THE GAME PROGRESS
		}
	}

	delete[] m_cProfileArray;
	m_cProfileArray = newProfileArray;
	--m_nProfiles;
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
	m_nStatus = DISPLAY;
	int m_nSelectedProfile = 0;

	m_cProfileArray = NULL;
	m_nProfiles = 0;

	LoadProfiles();

	AddProfile("Manny");
	AddProfile("Mann");
	AddProfile("Ma");
	DeleteProfile(2);
	SaveProfiles();
	LoadProfiles();
}