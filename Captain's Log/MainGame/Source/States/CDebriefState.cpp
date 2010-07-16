#include "precompiled_header.h"
#include "..\CGame.h"
#include "CDebriefState.h"
#include "..\SGD Wrappers\CSGD_TextureManager.h"
#include "..\SGD Wrappers\CSGD_DirectInput.h"
#include "..\Managers\MovementControl.h"
#include "..\Managers\CObjectManager.h"

CDebriefState::CDebriefState()
{

}

CDebriefState::~CDebriefState()
{

}

CDebriefState* CDebriefState::GetInstance()
{
	static CDebriefState instance;
	return &instance;
}

void CDebriefState::Enter()
{
	m_nBGImage = CSGD_TextureManager::GetInstance()->LoadTexture(CGame::GetInstance()->GraphicsPath("debrief.png").c_str());
	m_bfFont.Initialize(CGame::GetInstance()->FontPath("Font - Orbitron.bmp").c_str(), 1.0f, 1.0f, 2, 0xFF000000, 0xFF00CC00);
	m_bfFont.LoadLetterRects(CGame::GetInstance()->FontPath("FontData.txt").c_str());
}

void CDebriefState::Exit()
{
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nBGImage);
}

bool CDebriefState::Input()
{
	if(CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN))
	{
		CGame::GetInstance()->PopState();
	}
	return true;
}

void CDebriefState::Update(float fElapsedTime)
{

}

void CDebriefState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(m_nBGImage, 0, 0, 0.75f, 0.75f);

	//figure out who's alive
	bool bMarine = false, bHeavy=false, bMedic=false, bScout=false;
	for(size_t i=0; i<CObjectManager::GetInstance()->GetObjectList()->size(); i++)
	{
		CUnit* pUnit = ((CUnit*)(*CObjectManager::GetInstance()->GetInstance()->GetObjectList())[i]);
		if((CUnit*)CMovementControl::GetInstance()->Marine() == pUnit)
			bMarine=true;
		else if((CUnit*)CMovementControl::GetInstance()->Heavy() == pUnit)
			bHeavy=true;
		else if((CUnit*)CMovementControl::GetInstance()->Medic() == pUnit)
			bMedic=true;
		else if((CUnit*)CMovementControl::GetInstance()->Scout() == pUnit)
			bScout=true;
	}

	m_bfFont.RenderText("Unit Status", CGame::GetInstance()->GetScreenWidth()/3+100, 200);

	m_bfFont.RenderText(((bMarine) ? "Marine: Okay" : "Marine: Down"), CGame::GetInstance()->GetScreenWidth()/3+100, 230);
	m_bfFont.RenderText(((bHeavy) ? "Heavy: Okay" : "Heavy: Down"), CGame::GetInstance()->GetScreenWidth()/3+100, 255);
	m_bfFont.RenderText(((bMedic) ? "Medic: Okay" : "Medic: Down"), CGame::GetInstance()->GetScreenWidth()/3+100, 280);
	m_bfFont.RenderText(((bScout) ? "Scout: Okay" : "Scout: Down"), CGame::GetInstance()->GetScreenWidth()/3+100, 305);

	m_bfFont.RenderText("Press <ENTER> to Continue...", CGame::GetInstance()->GetScreenWidth()/3+30, CGame::GetInstance()->GetScreenHeight()/2+300);
}