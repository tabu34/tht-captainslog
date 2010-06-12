#include "CAnimationManager.h"

CAnimationManager::~CAnimationManager()
{

}

CAnimationManager::CAnimationManager()
{

}

CAnimationManager* CAnimationManager::GetInstance()
{
	static CAnimationManager instance;
	return &instance;
}

CAnimationManager::tAnimation* CAnimationManager::GetAnimation( int nID )
{
	CAnimationManager::tAnimation placeholder;
	return &placeholder;
}

int CAnimationManager::LoadAnimation( char* szImageID, DWORD dwKeyColor, float fSpeed, bool bIsLooping, int nNumFrames, CAnimation::tFrame* pFrames )
{
	return 0;
}

void CAnimationManager::UnloadAnimation( int nID )
{

}
