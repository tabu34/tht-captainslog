#ifndef CAnimationManager_h__
#define CAnimationManager_h__

#include "CAnimation.h"

class CAnimationManager
{
public:
	struct tAnimation
	{
		char		szFilename[100];
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
	tAnimation*		GetAnimation(char* _name);
	int				LoadAnimation(char* szAnimationName, char* szImageID, DWORD dwKeyColor, float fSpeed, bool bIsLooping, int nNumFrames, CAnimation::tFrame* pFrames);
	bool			LoadAnimationsFromFile(char* szFilename);
	void			UnloadAnimation(int nID);
	void			Shutdown();

};
#endif // CAnimationManager_h__