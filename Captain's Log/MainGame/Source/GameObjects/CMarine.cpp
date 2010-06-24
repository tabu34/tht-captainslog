#include "precompiled_header.h"
#include "CMarine.h"
#include "..\SGD Wrappers\CSGD_Direct3D.h"
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
}
