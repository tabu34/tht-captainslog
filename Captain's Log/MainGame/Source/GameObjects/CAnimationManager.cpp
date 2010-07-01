#include "precompiled_header.h"
#include "CAnimationManager.h"
#include <fstream>
using namespace std;

#include "..\SGD Wrappers\CSGD_TextureManager.h"

CAnimationManager::~CAnimationManager()
{

}

CAnimationManager::CAnimationManager()
{

}

void CAnimationManager::Shutdown()
{
	for(unsigned int i = 0; i < m_Animations.size(); i++)
	{
		m_Animations[i].anAnimation.Shutdown();
	}

	m_Animations.clear();
}

CAnimationManager* CAnimationManager::GetInstance()
{
	static CAnimationManager instance;
	return &instance;
}

CAnimationManager::tAnimation* CAnimationManager::GetAnimation( int nID )
{
	return &(m_Animations[nID]);
}

CAnimationManager::tAnimation* CAnimationManager::GetAnimation( char * _name )
{
	for(unsigned int i = 0; i < m_Animations.size(); i++)
	{
		if(strcmp(m_Animations[i].anAnimation.GetName(), _name) == 0)
			return &m_Animations[i];
	}

	return 0;
}

int CAnimationManager::GetAnimationID(char* _name)
{
	for(unsigned int i = 0; i < m_Animations.size(); i++)
	{
		if(strcmp(m_Animations[i].anAnimation.GetName(), _name) == 0)
			return i;
	}

	return 0;
}

int CAnimationManager::LoadAnimation( char* szAnimationName, char* szImageID, DWORD dwKeyColor, float fSpeed, bool bIsLooping, int nNumFrames, CAnimation::tFrame* pFrames )
{
	CAnimation *newAnimation = new CAnimation();
	newAnimation->Init(szAnimationName, szImageID, dwKeyColor, fSpeed, bIsLooping, nNumFrames, pFrames);
	tAnimation newTAnimation;
	newTAnimation.anAnimation = *newAnimation;
	m_Animations.push_back(newTAnimation);
	return m_Animations.size() - 1;
}

bool CAnimationManager::LoadAnimationsFromFile(char* szFilename, DWORD dwKeyColor)
{
	ifstream in(szFilename, ios::in | ios::binary);
	if(in.is_open())
	{
		vector<tAnimation> newAnimations;

		int numAnimations, numFrames;
		numAnimations = 0;
		numFrames = 0;

		in.read( (char*) &numAnimations, sizeof(int));

		for(int i = 0; i < numAnimations; i++)
		{
			tAnimation newTAnimation;
			bool isLooping;
			in.read( (char*) &isLooping, sizeof(bool));
			in.read( (char*) &newTAnimation.szFilename, 100);
			char name[100];
			in.read( (char*) &name, 100);
			in.read( (char*) &numFrames, sizeof(int));
			CAnimation::tFrame* frames = new CAnimation::tFrame[numFrames];
			for(int f = 0; f < numFrames; f++)
			{
				CAnimation::tFrame newFrame;
				in.read( (char*) &newFrame.rFrame.left, sizeof(int));
				in.read( (char*) &newFrame.rFrame.top, sizeof(int));
				in.read( (char*) &newFrame.rFrame.right, sizeof(int));
				in.read( (char*) &newFrame.rFrame.bottom, sizeof(int));
				newFrame.rFrame.right += newFrame.rFrame.left;
				newFrame.rFrame.bottom += newFrame.rFrame.top;
				in.read( (char*) &newFrame.ptAnchor.x, sizeof(int));
				in.read( (char*) &newFrame.ptAnchor.y, sizeof(int));
				in.read( (char*) &newFrame.cFrame.left, sizeof(int));
				in.read( (char*) &newFrame.cFrame.top, sizeof(int));
				in.read( (char*) &newFrame.cFrame.right, sizeof(int));
				in.read( (char*) &newFrame.cFrame.bottom, sizeof(int));
				in.read( (char*) &newFrame.fDuration, sizeof(float));
				newFrame.cFrame.right += newFrame.cFrame.left;
				newFrame.cFrame.bottom += newFrame.cFrame.top;
				in.read( (char*) &newFrame.szTrigger, 100);
				frames[f] = newFrame;
			}
			
			newTAnimation.anAnimation.Init(name,
				newTAnimation.szFilename,
				dwKeyColor,
				1.0f,
				isLooping,
				numFrames,
				frames);

			newAnimations.push_back(newTAnimation);

			delete[] frames;
		}

		for(unsigned int i = 0; i < newAnimations.size(); i++)
		{
			m_Animations.push_back(newAnimations[i]);
		}

		return true;
	}

	return false;
}

void CAnimationManager::UnloadAnimation( int nID )
{
	m_Animations[nID].anAnimation.Shutdown();
	delete &(m_Animations[nID].anAnimation);
	m_Animations.erase( m_Animations.begin() + nID );
}
