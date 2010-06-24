#include "precompiled_header.h"
#include "CMarine.h"
#include "..\SGD Wrappers\CSGD_Direct3D.h"

CMarine::CMarine()
{
	Type(OBJ_PLAYER);
}

void CMarine::Update( float fElapsedTime )
{
	CUnit::Update(fElapsedTime);
}

void CMarine::Initialize()
{

}

void CMarine::Render()
{
	if(!Selected())
 		CSGD_Direct3D::GetInstance()->DrawRect(GetCollisionRect(), 255, 0, 0);
	else
		CSGD_Direct3D::GetInstance()->DrawRect(GetCollisionRect(), 255, 255, 255);

	RECT dragRect;
	SetRect(&dragRect, (int)PosX(), (int)PosY(), (int)PosX() + Width(), (int)PosY() + Height());

	CSGD_Direct3D::GetInstance()->DrawLine(dragRect.left, dragRect.top, dragRect.right, dragRect.top, 0, 255, 0);
	CSGD_Direct3D::GetInstance()->DrawLine(dragRect.right, dragRect.top, dragRect.right, dragRect.bottom, 0, 255, 0);
	CSGD_Direct3D::GetInstance()->DrawLine(dragRect.right, dragRect.bottom, dragRect.left, dragRect.bottom, 0, 255, 0);
	CSGD_Direct3D::GetInstance()->DrawLine(dragRect.left, dragRect.bottom, dragRect.left, dragRect.top, 0, 255, 0);
}
