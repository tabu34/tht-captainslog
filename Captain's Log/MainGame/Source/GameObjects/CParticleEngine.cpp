#include "precompiled_header.h"
#include "CParticleEngine.h"

void CParticleEngine::CreateNewEmitter( int nImageID, int nHeight, int nWidth, float fPosX, float fPosY )
{
	CParticleEmitter emitter;
	emitter.Initialize(nImageID,nHeight,nWidth,fPosX,fPosY,500,200,100);
	m_vEmitters.push_back(emitter);
}

void CParticleEngine::Update( float fElapsedTime )
{
	for(unsigned int i = 0; i<m_vEmitters.size(); ++i)
	{
		m_vEmitters[i].Update(fElapsedTime);
	}
}

void CParticleEngine::Render()
{
	for(unsigned int i = 0; i<m_vEmitters.size(); ++i)
	{
		m_vEmitters[i].Render();
	}
}

void CParticleEngine::Shutdown()
{
	/*for(unsigned int i = 0; i<m_vEmitters.size(); ++i)
	{
		m_vEmitters[i].~CParticleEmitter();
	}
	m_vEmitters.clear();*/
}
