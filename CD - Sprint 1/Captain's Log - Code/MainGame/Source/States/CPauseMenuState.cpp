#include "CPauseMenuState.h"

CPauseMenuState::CPauseMenuState(void)
{
}

CPauseMenuState::~CPauseMenuState(void)
{
}

CPauseMenuState* CPauseMenuState::GetInstance()
{
	static CPauseMenuState instance;
	return &instance;
}

void CPauseMenuState::Enter(void)
{

}

bool CPauseMenuState::Input(void)
{
	return true;
}

void CPauseMenuState::Update(float fElapsedTime)
{

}

void CPauseMenuState::Render(void)
{

}

void CPauseMenuState::Exit(void)
{

}