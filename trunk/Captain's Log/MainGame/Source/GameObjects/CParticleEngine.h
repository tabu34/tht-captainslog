#include <vector>
#include "CParticleEmitter.h"
using namespace std;

class CParticleEngine
{
	vector<CParticleEmitter>	m_vEmitters;
public:
	void	CreateNewEmitter(int nImageID, int nHeight, int nWidth, float fPosX, float fPosY);
	void	Update(float fElapsedTime);
	void	Render();
	void	Shutdown();
};