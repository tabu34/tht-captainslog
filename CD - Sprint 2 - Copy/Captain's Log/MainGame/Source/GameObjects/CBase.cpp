#include "precompiled_header.h"
#include "CBase.h"

RECT CBase::GetCollisionRect()
{
	RECT tempRect;
	tempRect.left=long((int)PosX() - Width() / 2);
	tempRect.top=long((int)PosY() - Height() / 2);
	tempRect.right=tempRect.left+Width();
	tempRect.bottom=tempRect.top+Height();

	return tempRect;
}

void CBase::Update( float fElapsedTime )
{
	PosX( PosX() + VelX() * fElapsedTime );
	PosY( PosY() + VelY() * fElapsedTime );
	return;
}

void CBase::Render()
{

}

void CBase::AddRef()
{

}

void CBase::Release()
{

}
