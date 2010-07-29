#include <vector>
#include "CParticleEmitter.h"
using namespace std;

class CParticleEngine
{
	vector<CParticleEmitter>	m_vEmitters;

public:
	void	CreateNewEmitter(int nImageID, int nHeight, int nWidth, float fPosX, float fPosY, int nNumParticles, int nMaxPartLife, int nMinPartLife);
	void	Update(float fElapsedTime);
	void	Render();
	void	Shutdown();

	vector<CParticleEmitter>* Emitters() { return &m_vEmitters; }

	bool	CreateEmitterFromFile(int nImageID, string sFileName, float fPosX, float fPosY);
};