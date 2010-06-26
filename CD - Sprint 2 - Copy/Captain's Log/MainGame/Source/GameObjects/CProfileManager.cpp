#include "precompiled_header.h"

#include "CProfileManager.h"

#include "..\SGD Wrappers\CSGD_Direct3D.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "CBMPFont.h"

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
	in.open("Resource/SaveFile.txt");
	if(in.is_open())
	{
		if(m_cProfileArray!=NULL)
		{
			delete[] m_cProfileArray;
		}

		
		char buffer[120] = {0};
		
		int nprofs = 0;

		in>>nprofs;

		in.getline((char*)&buffer,_countof(buffer),'\n');

		for(int i = 0; i<nprofs;++i)
		{
			if(in.eof())
			{
				break;
			}
			in.getline((char*)&buffer,_countof(buffer),'\n');
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
		if(i<ProfileNumber-1)
		{
			newProfileArray[i].SetName(m_cProfileArray[i].GetName());
			newProfileArray[i].SetNumber(i);
			//COPY GAME PROGRESSS
		}else if(i>ProfileNumber-1)
		{
			newProfileArray[i-1].SetName(m_cProfileArray[i].GetName());
			newProfileArray[i-1].SetNumber(i-1);
			//COPY GAME PROGRESSS
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
	//CODE FOR SELECTING PROFILES AND SELECTING OPTIONS (Create new one, use a profile, delete a profile, exit)
	case DISPLAY:
		{
			CSGD_DirectInput *pDI = CSGD_DirectInput::GetInstance();
			if(pDI->KeyPressed(DIK_DOWN))
			{
				++m_nSelectedProfile;
			}
			if(pDI->KeyPressed(DIK_UP))
			{
				--m_nSelectedProfile;
			}
			if(pDI->KeyPressed(DIK_RSHIFT))
			{
				if(m_nSelectedProfile == m_nProfiles)
				{
					m_nStatus = ENTER_NEW;
				}else
				{
					m_nExpandSelector = 0;
					m_nStatus = EXPAND;
				}
			}

			if(m_nSelectedProfile>m_nProfiles)
			{
				m_nSelectedProfile = 0;
			}else if(m_nSelectedProfile<0)
			{
				m_nSelectedProfile = m_nProfiles;
			}
		}
		break;
	case ENTER_NEW:	//CODE FOR ENTERING A NEW PROFILE
		{
			CSGD_DirectInput *pDI = CSGD_DirectInput::GetInstance();

			if(pDI->KeyPressed(DIK_RSHIFT))
			{
				if(m_szNewProfName.size()>2)
				{
					AddProfile(m_szNewProfName);
				}
				m_szNewProfName.clear();
				m_nStatus = DISPLAY;
			}
			char keyPressed;
			keyPressed = pDI->CheckBufferedKeysEx();
			if (keyPressed != 0)
			{
				if(isalnum(keyPressed))
				{
					m_szNewProfName+=keyPressed;
				}
			}
			if(pDI->KeyPressed(DIK_BACKSPACE))
			{
				if(m_szNewProfName.size()>0)
				{
					m_szNewProfName.erase(m_szNewProfName.end()-1);
				}
			}
		}
		break;
	case EXPAND:
		{
			CSGD_DirectInput *pDI = CSGD_DirectInput::GetInstance();

			if(pDI->KeyPressed(DIK_BACKSPACE))
			{
				m_nStatus = DISPLAY;
			}

			if(pDI->KeyPressed(DIK_RIGHT))
			{
				++m_nExpandSelector;
			}
			if(pDI->KeyPressed(DIK_LEFT))
			{
				--m_nExpandSelector;
			}

			if(m_nExpandSelector>1)
			{
				m_nExpandSelector = 0;
			}else if(m_nExpandSelector<0)
			{
				m_nExpandSelector = 1;
			}

			if(pDI->KeyPressed(DIK_RSHIFT))
			{
				if(m_nExpandSelector == 0)
				{
					//CODE TO CONTINUE THE SAVE GAME
				}else if(m_nExpandSelector == 1)
				{
					DeleteProfile(m_nSelectedProfile+1);
					m_nStatus = DISPLAY;
				}
			}
		}
		break;
	};
}
void CProfileManager::Render(void)
{
	switch(m_nStatus)
	{
	case DISPLAY:
		{
			int i = 0;
	//CODE FOR SELECTING PROFILES AND SELECTING OPTIONS (Create new one, use a profile, delete a profile, exit)

			for(; i<m_nProfiles;++i)
			{
				if(i != m_nSelectedProfile)
				{
					m_cBMPFont.RenderText((char*)m_cProfileArray[i].GetName().c_str(),300,200+(25*i));
				}else
				{
					m_cBMPFont.RenderText((char*)m_cProfileArray[i].GetName().c_str(),250,200+(25*i));
				}
			}
			if(i != m_nSelectedProfile)
			{
				m_cBMPFont.RenderText("Enter new profile",300,200+(25*i));
			}else
			{
				m_cBMPFont.RenderText("Enter new profile",250,200+(25*i));
			}
		}
		break;
	case ENTER_NEW:	//CODE FOR ENTERING A NEW PROFILE
		{
			m_cBMPFont.RenderText("Enter profile name:   (at least 3 characters)",250,200);
			string NameDisplay = "-";
			NameDisplay += m_szNewProfName;
			m_cBMPFont.RenderText((char*)NameDisplay.c_str(),300,250);
		}
		break;
	case EXPAND:
		{
			m_cBMPFont.RenderText((char*)m_cProfileArray[m_nSelectedProfile].GetName().c_str(),250,200);
			if(m_nExpandSelector == 0)
			{
				m_cBMPFont.RenderText("Continue Game",300,250);
				m_cBMPFont.RenderText("Delete Profile",450,300);
			}else if(m_nExpandSelector == 1)
			{
				m_cBMPFont.RenderText("Delete Profile",300,250);
				m_cBMPFont.RenderText("Continue Game",450,300);
			}
		}
		break;
	};
}

void CProfileManager::Init(void)
{
	m_nStatus = DISPLAY;
	int m_nSelectedProfile = 0;

	m_cProfileArray = NULL;
	m_nProfiles = 0;

	m_cBMPFont.Initialize("Resource/Fonts/Font - Orbitron.bmp",1.0f,1.0f,1);
	m_cBMPFont.LoadLetterRects("Resource/Fonts/FontData.txt");

	m_nDisplayOffset = 0;

	m_cProfileArray;

	m_nExpandSelector = 0;

	//m_szNewProfName = '\0';

	LoadProfiles();

	/*
	AddProfile("Manny");
	AddProfile("Mann");
	AddProfile("Ma");
	DeleteProfile(2);
	SaveProfiles();
	//LoadProfiles();*/
}