//////////////////////////////////////////////////////////////////////////////////////////////
//	File			:	"CMainMenuState.h"
//
//	Authors			:	Tim Smith, Daniel Makin
//
//	Purpose			:	To define the functionality of the Main Menu game state
//////////////////////////////////////////////////////////////////////////////////////////////
#include "precompiled_header.h"
#include "CMainMenuState.h"

CMainMenuState::CMainMenuState(void)
{

}

CMainMenuState::~CMainMenuState(void)
{

}

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState instance;
	return &instance;
}

void CMainMenuState::Enter(void)
{

}

bool CMainMenuState::Input(void)
{
	return true;
}

void CMainMenuState::Update(float fElapsedTime)
{

}

void CMainMenuState::Render(void)
{

}

void CMainMenuState::Exit(void)
{

}