#include "precompiled_header.h"
#include "COptionsMenuState.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../CGame.h"
#include "../Managers/MovementControl.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios_base;

COptionsMenuState::COptionsMenuState()
{
	m_nMusicVolume=0;
	m_nSFXVolume = 0;
	m_nVoiceVolume=0;
}

COptionsMenuState::~COptionsMenuState()
{

}

COptionsMenuState* COptionsMenuState::GetInstance()
{
	static COptionsMenuState instance;
	return &instance;
}

void COptionsMenuState::Enter()
{
	m_nBGImageID = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\optionsMenu.png").c_str());
	m_nSliderImageID = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("HUD\\optionsMenuSlider.png").c_str());
	m_pCurrentControl = NULL;

	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.7f, 0.7f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());

	m_bfWhite.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 0.7f, 0.7f, 2, 0xFF000000, 0xFFFFFFFF);
	m_bfWhite.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());

	//add controls to the vector (ALL OF THEM..GAH)
	tMenuControl mcInit;
	SetRect(&mcInit.rArea, 511, 235, 646, 259);
	mcInit.szIdentifier = "fullscreen";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 415, 396, 600, 413);
	mcInit.szIdentifier = "sfxvolume";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 415, 474, 600, 490);
	mcInit.szIdentifier = "voiceovervolume";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 415, 550, 600, 567);
	mcInit.szIdentifier = "musicvolume";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 865, 237, 1045, 260);
	mcInit.szIdentifier = "layout";
	m_vControls.push_back(mcInit);


	//ALL THE FRIGGIN KEYBINDS
	char buffer[128];
	for(int i=0; i<18; i++)
	{
		sprintf_s(buffer, 128, "key%i", i);
		SetRect(&mcInit.rArea, 779, 272+(i*25)+(int)(i*1.5f), 1041, 298+(i*25)+(int)(i*1.5f));
		mcInit.szIdentifier = buffer;
		m_vControls.push_back(mcInit);
	}

	SetRect(&mcInit.rArea, 362, 651, 662, 687);
	mcInit.szIdentifier = "saveexit";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 362, 690, 662, 727);
	mcInit.szIdentifier = "exit";
	m_vControls.push_back(mcInit);
	SetRect(&mcInit.rArea, 362, 730, 662, 767);
	mcInit.szIdentifier = "restoredefaults";
	m_vControls.push_back(mcInit);

	LoadSettings();

}

bool COptionsMenuState::Input()
{
	m_nMouseX = CMovementControl::GetInstance()->MousePosX();
	m_nMouseY = CMovementControl::GetInstance()->MousePosY();

	if(m_bBinding)
	{
		UCHAR dikCode = CSGD_DirectInput::GetInstance()->GetDIKCode();
		if(dikCode!=0)
		{
			bool bUnique=true;
			for(int i=0; i<18; i++)
			{
				if(m_arrKeybinds[i]==dikCode && i!=m_nBindIndex)
				{
					bUnique=false;
					break;
				}
			}

			if(bUnique)
			{
				m_bBinding=false;
				m_arrKeybinds[m_nBindIndex]=dikCode;
				return true;
			}
		}
		return true;
	}
	
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->PopState();
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RIGHT))
	{
		if(m_pCurrentControl)
		{
			if(m_pCurrentControl->szIdentifier == "fullscreen")
			{
				m_pCurrentControl = &m_vControls[4];
				m_nBindIndex=-1;
			}
			else if(m_pCurrentControl->szIdentifier == "sfxvolume")
			{
				m_nSFXVolume = (m_nSFXVolume >= 100) ? 100 : m_nSFXVolume+1;
			}
			else if(m_pCurrentControl->szIdentifier == "voiceovervolume")
			{
				m_nVoiceVolume = (m_nVoiceVolume >= 100) ? 100 : m_nVoiceVolume+1;
			}
			else if(m_pCurrentControl->szIdentifier == "musicvolume")
			{
				m_nMusicVolume = (m_nMusicVolume >= 100) ? 100 : m_nMusicVolume+1;
			}
		}
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_LEFT))
	{
		if(m_pCurrentControl)
		{
			if(m_pCurrentControl->szIdentifier == "layout")
			{
				m_pCurrentControl = &m_vControls[0];
				m_nBindIndex=-5;
			}
			else if(m_pCurrentControl->szIdentifier == "sfxvolume")
			{
				m_nSFXVolume = (m_nSFXVolume <=0) ? 0 : m_nSFXVolume-1;
			}
			else if(m_pCurrentControl->szIdentifier == "voiceovervolume")
			{
				m_nVoiceVolume = (m_nVoiceVolume <=0) ? 0 : m_nVoiceVolume-1;
			}
			else if(m_pCurrentControl->szIdentifier == "musicvolume")
			{
				m_nMusicVolume = (m_nMusicVolume <=0) ? 0 : m_nMusicVolume-1;
			}
		}
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_TAB))
	{
		//find index we're at
		unsigned int nCurIndex=-1;
		if(m_pCurrentControl == NULL)
			nCurIndex = -1;
		else
		{
			for(size_t i=0; i<m_vControls.size(); i++)
			{
				if(m_pCurrentControl == &m_vControls[i])
				{
					nCurIndex = i;
					break;
				}
			}
		}

		nCurIndex = (nCurIndex+1<m_vControls.size()) ? nCurIndex+1 : 0;

		m_pCurrentControl = &m_vControls[nCurIndex];
		m_nBindIndex = nCurIndex-5;
	}

	if((m_nMouseX!=m_nMousePrevX || m_nMouseY!=m_nMousePrevY) && !CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
	{
		m_pCurrentControl = NULL;
		for(size_t i=0; i<m_vControls.size(); i++)
		{
			POINT ptMouse = {m_nMouseX, m_nMouseY};
			if(PtInRect(&m_vControls[i].rArea, ptMouse))
			{
				m_pCurrentControl = &m_vControls[i];
				m_nBindIndex = i-5;
				break;
			}
		}
	}

	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN) || CSGD_DirectInput::GetInstance()->MouseButtonPressed(0))
	{
		if(m_pCurrentControl)
		{
			if(m_pCurrentControl->szIdentifier == "saveexit")
			{
				//save options
				CGame::GetInstance()->PopState();
			}
			else if(m_pCurrentControl->szIdentifier == "exit")
			{
				CGame::GetInstance()->PopState();
			}
			else if(m_pCurrentControl->szIdentifier == "fullscreen")
			{
				CGame::GetInstance()->ToggleFullScreen();
			}
			else if(m_pCurrentControl->szIdentifier.substr(0,3)=="key")
			{
				m_bBinding=true;
			}
		}
	}

	if(CSGD_DirectInput::GetInstance()->MouseButtonDown(0))
	{
		if(m_pCurrentControl)
		{
			if(m_pCurrentControl->szIdentifier == "musicvolume")
			{
				m_nMusicVolume = (int)(((float)(m_nMouseX - 415)/185.0f)*100.0f);
				if(m_nMusicVolume>100)
					m_nMusicVolume=100;
				else if(m_nMusicVolume<0)
					m_nMusicVolume=0;
			}
			else if(m_pCurrentControl->szIdentifier == "sfxvolume")
			{
				m_nSFXVolume = (int)(((float)(m_nMouseX - 415)/185.0f)*100.0f);
				if(m_nSFXVolume>100)
					m_nSFXVolume=100;
				else if(m_nSFXVolume<0)
					m_nSFXVolume=0;
			}
			else if(m_pCurrentControl->szIdentifier == "voiceovervolume")
			{
				m_nVoiceVolume = (int)(((float)(m_nMouseX - 415)/185.0f)*100.0f);
				if(m_nVoiceVolume>100)
					m_nVoiceVolume=100;
				else if(m_nVoiceVolume<0)
					m_nVoiceVolume=0;
			}
		}
	}

	m_nMousePrevX = m_nMouseX;
	m_nMousePrevY = m_nMouseY;
	return true;
}

void COptionsMenuState::Update(float fElapsedTime)
{
	if(m_nMouseX < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosX(0);

	if(m_nMouseX > CGame::GetInstance()->GetScreenWidth())
		CSGD_DirectInput::GetInstance()->MouseSetPosX(CGame::GetInstance()->GetScreenWidth());

	if(m_nMouseY < 0)
		CSGD_DirectInput::GetInstance()->MouseSetPosY(0);

	if(m_nMouseY > CGame::GetInstance()->GetScreenHeight())
		CSGD_DirectInput::GetInstance()->MouseSetPosY(CGame::GetInstance()->GetScreenHeight());
}

void DrawHollowRect(const RECT *rDraw, unsigned char ucRed = 255, unsigned char ucGreen = 255, unsigned char ucBlue = 255)
{
	CSGD_Direct3D::GetInstance()->SpriteEnd();

	CSGD_Direct3D::GetInstance()->DrawLine(rDraw->left - 1, rDraw->top - 1, rDraw->right - 1, rDraw->top - 1, ucRed, ucGreen, ucBlue);
	CSGD_Direct3D::GetInstance()->DrawLine(rDraw->right - 1, rDraw->top - 1, rDraw->right - 1, rDraw->bottom - 1, ucRed, ucGreen, ucBlue);
	CSGD_Direct3D::GetInstance()->DrawLine(rDraw->right - 1, rDraw->bottom - 1, rDraw->left - 1, rDraw->bottom - 1, ucRed, ucGreen, ucBlue);
	CSGD_Direct3D::GetInstance()->DrawLine(rDraw->left - 1, rDraw->bottom - 1, rDraw->left - 1, rDraw->top - 1, ucRed, ucGreen, ucBlue);

	CSGD_Direct3D::GetInstance()->SpriteBegin();
}

void CreateKeybindBuffer(char* buffer, char* keybind, unsigned char DIKCode)
{
	struct STRUC_KEY
	{
		UCHAR keyByte;
		char  keyName[30];
	};

	STRUC_KEY MyKey[] = 
	{
		DIK_0, 				"0",
		DIK_1, 				"1",
		DIK_2, 				"2",
		DIK_3, 				"3",
		DIK_4, 				"4",
		DIK_5, 				"5",
		DIK_6, 				"6",
		DIK_7, 				"7",
		DIK_8, 				"8",
		DIK_9, 				"9",
		DIK_A, 				"A",
		DIK_ABNT_C1, 		"ABNT_C1",
		DIK_ABNT_C2, 		"ABNT_C2",
		DIK_ADD, 			"+",
		DIK_APOSTROPHE, 	"'",
		DIK_APPS, 			"APPS",
		DIK_AT, 			"AT",
		DIK_AX, 			"AX",
		DIK_B, 				"B",
		DIK_BACK, 			"BACK",
		DIK_BACKSLASH, 		"\\",
		DIK_C, 				"C",
		DIK_CALCULATOR, 	"CALC",
		DIK_CAPITAL, 		"CAPITAL",
		DIK_COLON, 			":",
		DIK_COMMA, 			",COMMA",
		DIK_CONVERT, 		"CONVERT",
		DIK_D, 				"D",
		DIK_DECIMAL, 		".",
		DIK_DELETE, 		"DEL",
		DIK_DIVIDE, 		"/",
		DIK_DOWN, 			"DN",
		DIK_E, 				"E",
		DIK_END, 			"END",
		DIK_EQUALS, 		"=",
		DIK_ESCAPE, 		"ESC",
		DIK_F, 				"F",
		DIK_F1, 			"F1",
		DIK_F2, 			"F2",
		DIK_F3, 			"F3",
		DIK_F4, 			"F4",
		DIK_F5, 			"F5",
		DIK_F6, 			"F6",
		DIK_F7, 			"F7",
		DIK_F8, 			"F8",
		DIK_F9, 			"F9",
		DIK_F10, 			"F10",
		DIK_F11, 			"F11",
		DIK_F12, 			"F12",
		DIK_F13, 			"F13",
		DIK_F14, 			"F14",
		DIK_F15, 			"F15",
		DIK_G, 				"G",
		DIK_GRAVE, 			"`",
		DIK_H, 				"H",
		DIK_HOME, 			"HOME",
		DIK_I, 				"I",
		DIK_INSERT, 		"INS",
		DIK_J, 				"J",
		DIK_K, 				"K",
		DIK_KANA, 			"KANA",
		DIK_KANJI, 			"KANJI",
		DIK_L, 				"L",
		DIK_LBRACKET, 		"[",
		DIK_LCONTROL, 		"CTRL",
		DIK_LEFT, 			"LEFT",
		DIK_LMENU, 			"LALT",
		DIK_LSHIFT, 		"LSHIFT",
		DIK_LWIN, 			"LWIN",
		DIK_M, 				"M",
		DIK_MAIL, 			"MAIL",
		DIK_MEDIASELECT, 	"MEDIA",
		DIK_MEDIASTOP, 		"STOP",
		DIK_MINUS, 			"-",
		DIK_MULTIPLY, 		"*",
		DIK_MUTE, 			"MUTE",
		DIK_MYCOMPUTER, 	"MYCOMPUTER",
		DIK_N, 				"N",
		DIK_NEXT, 			"NEXT",
		DIK_NEXTTRACK, 		"NEXTTRACK",
		DIK_NOCONVERT, 		"NOCONVERT",
		DIK_NUMLOCK, 		"NUMLOCK",
		DIK_NUMPAD0, 		"NP0",
		DIK_NUMPAD1, 		"NP1",
		DIK_NUMPAD2, 		"NP2",
		DIK_NUMPAD3, 		"NP3",
		DIK_NUMPAD4, 		"NP4",
		DIK_NUMPAD5, 		"NP5",
		DIK_NUMPAD6, 		"NP6",
		DIK_NUMPAD7, 		"NP7",
		DIK_NUMPAD8, 		"NP8",
		DIK_NUMPAD9, 		"NP9",
		DIK_NUMPADCOMMA, 	"NPCOMMA",
		DIK_NUMPADENTER, 	"NPENTER",
		DIK_NUMPADEQUALS, 	"NP=",
		DIK_O, 				"O",
		DIK_OEM_102, 		"OEM_102",
		DIK_P, 				"P",
		DIK_PAUSE, 			"PAUSE",
		DIK_PERIOD, 		".",
		DIK_PLAYPAUSE, 		"PLAYPAUSE",
		DIK_POWER, 			"POWER",
		DIK_PREVTRACK, 		"PREVTRACK",
		DIK_PRIOR, 			"PRIOR",
		DIK_Q, 				"Q",
		DIK_R, 				"R",
		DIK_RBRACKET, 		"]",
		DIK_RCONTROL, 		"RCTRL",
		DIK_RETURN, 		"RETURN",
		DIK_RIGHT, 			"RIGHT",
		DIK_RMENU, 			"RALT",
		DIK_RSHIFT, 		"RSHIFT",
		DIK_RWIN, 			"RWIN",
		DIK_S, 				"S",
		DIK_SCROLL, 		"SCROLL",
		DIK_SEMICOLON, 		";",
		DIK_SLASH, 			"/",
		DIK_SLEEP, 			"SLP",
		DIK_SPACE, 			"[SPACE]",
		DIK_STOP, 			"STOP",
		DIK_SUBTRACT, 		"-",
		DIK_SYSRQ, 			"SYSRQ",
		DIK_T, 				"T",
		DIK_TAB, 			"TAB",
		DIK_U, 				"U",
		DIK_UNDERLINE, 		"_",
		DIK_UNLABELED, 		"UNLABELED",
		DIK_UP, 			"UP",
		DIK_V, 				"V",
		DIK_VOLUMEDOWN, 	"VOLDOWN",
		DIK_VOLUMEUP, 		"VOLUP",
		DIK_W, 				"W",
		DIK_WAKE, 			"WAKE",
		DIK_WEBBACK, 		"WEBBACK",
		DIK_WEBFAVORITES, 	"WEBFAVORITES",
		DIK_WEBFORWARD, 	"WEBFORWARD",
		DIK_WEBHOME, 		"WEBHOME",
		DIK_WEBREFRESH, 	"WEBREFRESH",
		DIK_WEBSEARCH, 		"WEBSEARCH",
		DIK_WEBSTOP, 		"WEBSTOP",
		DIK_X, 				"X",
		DIK_Y, 				"Y",
		DIK_YEN, 			"YEN",
		DIK_Z, 				"Z",
		DIK_LALT,			"LALT",
		DIK_RALT,			"RALT",
	};

	std::string szStuff = keybind;
	bool bfound=false;
	for(int i=0; i<_countof(MyKey); i++)
	{
		if(MyKey[i].keyByte==DIKCode)
		{
			bfound=true;
			szStuff+=MyKey[i].keyName;
			break;
		}
	}

	if(bfound)
		strcpy_s(buffer, 128, szStuff.c_str());
	else
		buffer=NULL;
}

void COptionsMenuState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImageID, 0, 0, 0.75f, 0.75f);

	
	if(m_pCurrentControl)
		DrawHollowRect(&m_pCurrentControl->rArea);

	CSGD_TextureManager::GetInstance()->Draw(m_nSliderImageID, (int)(415.0f + ((float)m_nSFXVolume/100.0f)*185.0f)-3, 396, 0.75f, 0.75f);
	CSGD_TextureManager::GetInstance()->Draw(m_nSliderImageID, (int)(415.0f + ((float)m_nVoiceVolume/100.0f)*185.0f)-3, 474, 0.75f, 0.75f);
	CSGD_TextureManager::GetInstance()->Draw(m_nSliderImageID, (int)(415.0f + ((float)m_nMusicVolume/100.0f)*185.0f)-3, 550, 0.75f, 0.75f);
	
	int j=0;
	for(size_t i=0; i<m_vControls.size(); i++)
	{
		if(m_vControls[i].szIdentifier.substr(0, 3) == "key")
		{
			char buff[128];
			switch(j++)
			{
			case 0:
				CreateKeybindBuffer(buff, "Select Unit 1: ", m_arrKeybinds[0]);
				break;
			case 1:
				CreateKeybindBuffer(buff, "Select Unit 2: ", m_arrKeybinds[1]);
				break;
			case 2:
				CreateKeybindBuffer(buff, "Select Unit 3: ", m_arrKeybinds[2]);
				break;
			case 3:
				CreateKeybindBuffer(buff, "Select Unit 4: ", m_arrKeybinds[3]);
				break;
			case 4:
				CreateKeybindBuffer(buff, "Select All: ", m_arrKeybinds[4]);
				break;
			case 5:
				CreateKeybindBuffer(buff, "Ability 1: ", m_arrKeybinds[5]);
				break;
			case 6:
				CreateKeybindBuffer(buff, "Ability 2: ", m_arrKeybinds[6]);
				break;
			case 7:
				CreateKeybindBuffer(buff, "Ability 3: ", m_arrKeybinds[7]);
				break;
			case 8:
				CreateKeybindBuffer(buff, "Ability 4: ", m_arrKeybinds[8]);
				break;
			case 9:
				CreateKeybindBuffer(buff, "Inventory 1: ", m_arrKeybinds[9]);
				break;
			case 10:
				CreateKeybindBuffer(buff, "Inventory 2: ", m_arrKeybinds[10]);
				break;
			case 11:
				CreateKeybindBuffer(buff, "Inventory 3: ", m_arrKeybinds[11]);
				break;
			case 12:
				CreateKeybindBuffer(buff, "Inventory 4: ", m_arrKeybinds[12]);
				break;
			case 13:
				CreateKeybindBuffer(buff, "Camera Up: ", m_arrKeybinds[13]);
				break;
			case 14:
				CreateKeybindBuffer(buff, "Camera Down: ", m_arrKeybinds[14]);
				break;
			case 15:
				CreateKeybindBuffer(buff, "Camera Left: ", m_arrKeybinds[15]);
				break;
			case 16:
				CreateKeybindBuffer(buff, "Camera Right: ", m_arrKeybinds[16]);
				break;
			}
			if(j-1 == m_nBindIndex && m_bBinding)
				sprintf_s(buff, 128, "Awaiting Keypress...");

			m_bfWhite.RenderText(buff, 780, 273+((j-1)*25)+(int)((j-1)*1.5f));
		}
	}
	
	m_bfFont.RenderText(((CGame::GetInstance()->IsWindowed()) ? "False" : "True"), 511, 235);

	CMovementControl::GetInstance()->RenderCursor();
}

void COptionsMenuState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImageID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSliderImageID);
}

//SETTINGS FILE FORMAT:
//windowed bool
//sfx vol
//voice vol
//music vol
//18x unsigned char keybinds

void COptionsMenuState::LoadSettings()
{
	ifstream fin;
	std::string szPath = CGame::GetInstance()->ResourcePath();
	szPath+="Settings.bin";
	fin.open(szPath.c_str(), ios_base::in | ios_base::binary);
	if(fin.fail())
	{
		fin.clear(ios_base::failbit);
		MessageBox(0, "Configuration file not found.  Creating new one with defaults.", "Error: Missing File", MB_OK);
		m_bWindowed=true;
		m_nSFXVolume=50;
		m_nVoiceVolume=50;
		m_nMusicVolume=50;
		m_arrKeybinds[0]=DIK_1;
		m_arrKeybinds[1]=DIK_2;
		m_arrKeybinds[2]=DIK_3;
		m_arrKeybinds[3]=DIK_4;
		m_arrKeybinds[4]=DIK_5;
		m_arrKeybinds[5]=DIK_Q;
		m_arrKeybinds[6]=DIK_W;
		m_arrKeybinds[7]=DIK_E;
		m_arrKeybinds[8]=DIK_R;
		m_arrKeybinds[9]=DIK_A;
		m_arrKeybinds[10]=DIK_S;
		m_arrKeybinds[11]=DIK_D;
		m_arrKeybinds[12]=DIK_F;
		m_arrKeybinds[13]=DIK_UP;
		m_arrKeybinds[14]=DIK_DOWN;
		m_arrKeybinds[15]=DIK_LEFT;
		m_arrKeybinds[16]=DIK_RIGHT;
		SaveSettings();
		return;
	}
	else if(fin.is_open() && fin.good())
	{
		fin.read((char*)&m_bWindowed, sizeof(bool));
		fin.read((char*)&m_nSFXVolume, sizeof(int));
		fin.read((char*)&m_nVoiceVolume, sizeof(int));
		fin.read((char*)&m_nMusicVolume, sizeof(int));

		for(int i=0; i<18; i++)
		{
			fin.read((char*)&m_arrKeybinds[i], sizeof(unsigned char));
		}
		fin.close();
	}
}

void COptionsMenuState::SaveSettings()
{
	ofstream fout;
	std::string szPath = CGame::GetInstance()->ResourcePath();
	szPath+="Settings.bin";
	fout.open(szPath.c_str(), ios_base::out | ios_base::binary);

	if(fout.is_open() && fout.good())
	{
		fout.write((char*)&m_bWindowed, sizeof(bool));
		fout.write((char*)&m_nSFXVolume, sizeof(int));
		fout.write((char*)&m_nVoiceVolume, sizeof(int));
		fout.write((char*)&m_nMusicVolume, sizeof(int));

		for(int i=0; i<18; i++)
		{
			fout.write((char*)&m_arrKeybinds[i], sizeof(unsigned char));
		}
		fout.close();
	}
}

