#include "precompiled_header.h"
#include "CMarine.h"
#include "..\SGD Wrappers\CSGD_Direct3D.h"
#include "CAnimationManager.h"

CMarine::CMarine()
{
	Type(OBJ_PLAYER);
	PosX(50);
	PosY(50);
	VelX(0);
	VelY(0);
	Width(120);
	Height(140);
	CurHealth(10);
	MaxHealth(10);
	AttackSpeed(1);
	AttackDamage(4);
	AttackTimer(0);
	AttackRange(250);
	

	if(CAnimationManager::GetInstance()->GetAnimation("MarineIdle"))
		CAnimationManager::GetInstance()->GetAnimation("MarineIdle")->anAnimation.Play();
	m_nCurFrame = 0;
}

void CMarine::Update( float fElapsedTime )
{
	if(CAnimationManager::GetInstance()->GetAnimation("MarineIdle"))
		CAnimationManager::GetInstance()->GetAnimation("MarineIdle")->anAnimation.Update(fElapsedTime);
	CUnit::Update(fElapsedTime);
}

void CMarine::Initialize()
{

}

void CMarine::Render()
{
	CUnit::Render();
	if(CAnimationManager::GetInstance()->GetAnimation("MarineIdle"))
	{
		bool flipped = false;
		if(VelX() == 0.0f && VelY() < 0.0f)
		{
			m_nCurFrame = 0;
		} else if(VelX() > 0.0f && VelY() < 0.0f)
		{
			m_nCurFrame = 1;
		} else if(VelX() > 0.0f && VelY() == 0.0f)
		{
			m_nCurFrame = 4;
		} else if(VelX() > 0.0f && VelY() > 0.0f)
		{
			m_nCurFrame = 6;
		} else if(VelX() == 0.0f && VelY() > 0.0f)
		{
			m_nCurFrame = 8;
		} else if(VelX() < 0.0f && VelY() < 0.0f)
		{
			flipped = true;
			m_nCurFrame = 1;
		} else if(VelX() < 0.0f && VelY() == 0.0f)
		{
			flipped = true;
			m_nCurFrame = 4;
		} else if(VelX() < 0.0f && VelY() > 0.0f)
		{
			flipped = true;
			m_nCurFrame = 6;
		}

		CAnimationManager::GetInstance()->GetAnimation("MarineIdle")->anAnimation.CurFrame(m_nCurFrame);
		CAnimationManager::GetInstance()->GetAnimation("MarineIdle")->anAnimation.Render(int(PosX() - CGame::GetInstance()->GetCamera()->GetX()), int(PosY() - CGame::GetInstance()->GetCamera()->GetY()), flipped, 2.0f);
	} else {
		CSGD_Direct3D::GetInstance()->DrawRect(GetCollisionRect(), 255, 255, 255);
	}

}
