#ifndef CAnimation_h__
#define CAnimation_h__

#include <Windows.h>
#include <vector>
using namespace std;

class CAnimation
{
public:
	struct tFrame 
	{
		RECT	rFrame;
		POINT	ptAnchor;
		float	fDuration;
	};

private:
	vector<tFrame>	m_vFrames;
	int				m_nImageID;
	unsigned int	m_nCurFrame;
	float			m_fTimeWaited;
	float			m_fSpeed;
	bool			m_bIsPlaying;
	bool			m_bIsLooping;

	void Reset();

public:
	CAnimation();
	~CAnimation();

	RECT GetCollisionRect(bool bIsFlipped);

	unsigned int CurFrame() const { return m_nCurFrame; }
	void CurFrame(unsigned int val) { m_nCurFrame = val; }

	void Update(float fElapsedTime);
	void Render(int nPosX, int nPosY, bool bIsFlipped = false, float fScale = 1, DWORD dwColor = -1);

	void Init(char* szImageID, DWORD dwKeyColor, float fSpeed, bool bIsLooping, int nNumFrames, tFrame* pFrames);
	void Shutdown();

	bool IsPlaying() const { return m_bIsPlaying; }

	void Play()
	{
		Reset();
		m_bIsPlaying = true;
	}
	void Stop()	{ m_bIsPlaying = false; }
	void Pause()	{ m_bIsPlaying = true; }

};
#endif // CAnimation_h__