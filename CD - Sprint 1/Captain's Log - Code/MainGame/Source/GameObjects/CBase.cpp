#include "CBase.h"

RECT CBase::GetCollisionRect()
{
	RECT tempRect;
	tempRect.left=long((int)PosX() - Width() / 2);
	tempRect.top=long((int)PosY() - Height());
	tempRect.right=tempRect.left+Width();
	tempRect.bottom=tempRect.top+Height();

	return tempRect;
}

void CBase::Update( float fElapsedTime )
{

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
