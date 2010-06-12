#ifndef CAnimationManager_h__
#define CAnimationManager_h__

#include "CAnimation.h"

class CAnimationManager
{
public:
	struct tAnimation
	{
		char*		szFilename;
		int			nRefs;
		CAnimation	anAnimation;
	};

private:
	vector<tAnimation>	m_Animations;

	~CAnimationManager();
	CAnimationManager();
	CAnimationManager(CAnimationManager&);
	CAnimationManager& operator=(CAnimationManager&);

public:
	static CAnimationManager*	GetInstance();

	tAnimation*		GetAnimation(int nID);
	int				LoadAnimation(char* szImageID, DWORD dwKeyColor, float fSpeed, bool bIsLooping, int nNumFrames, CAnimation::tFrame* pFrames);
	void			UnloadAnimation(int nID);

};
#endif // CAnimationManager_h__