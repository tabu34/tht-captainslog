#include "precompiled_header.h"
#include "CParticleEngine.h"

#include <fstream>
using namespace std;

void CParticleEngine::CreateNewEmitter( int nImageID, int nWidth, int nHeight, float fPosX, float fPosY, int nNumParticles, int nMinPartLife, int nMaxPartLife)
{
	CParticleEmitter emitter;
	emitter.Initialize(nImageID,nWidth,nHeight,(int)fPosX,(int)fPosY,nNumParticles,nMaxPartLife,nMinPartLife);
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

bool CParticleEngine::CreateEmitterFromFile(int nImageID, string sFileName, float fPosX, float fPosY)
{
	CParticleEmitter emitter;

	ifstream in;
	in.open(sFileName.c_str(), ios_base::in||ios_base::binary );
	if(in.is_open())
	{
		int MinLife = 0, MaxLife = 0, EmitterWidth = 0, EmitterHeight = 0, nParticles = 0, AlphaValue = 0, initialForceX = 0, initialForceY = 0,
			BlendModeSource = 0, BlendModeDest = 0, minPartWidth = 0, minPartHeight = 0, maxPartWidth = 0, maxPartHeight = 0, nGravity = 0,
			GravitySourceX = 0, GravitySourceY = 0, RandomSpread = 0, blue = 255, green = 255, red = 255;

		in.read((char*)&MinLife,sizeof(int));
		in.read((char*)&MaxLife,sizeof(int));

		in.read((char*)&EmitterWidth,sizeof(int));
		in.read((char*)&EmitterHeight,sizeof(int));

		in.read((char*)&nParticles,sizeof(int));

		in.read((char*)&AlphaValue,sizeof(int));

		in.read((char*)&initialForceX,sizeof(int));
		in.read((char*)&initialForceY,sizeof(int));

		in.read((char*)&BlendModeSource,sizeof(int));
		in.read((char*)&BlendModeDest,sizeof(int));

		in.read((char*)&minPartWidth,sizeof(int));
		in.read((char*)&minPartHeight,sizeof(int));
		in.read((char*)&maxPartWidth,sizeof(int));
		in.read((char*)&maxPartHeight,sizeof(int));

		in.read((char*)&nGravity,sizeof(int));
		in.read((char*)&GravitySourceX,sizeof(int));
		in.read((char*)&GravitySourceY,sizeof(int));

		in.read((char*)&RandomSpread,sizeof(int));

		in.read((char*)&blue,sizeof(int));
		in.read((char*)&green,sizeof(int));
		in.read((char*)&red,sizeof(int));

		in.close();

		emitter.Initialize(nImageID,EmitterWidth,EmitterHeight,(int)fPosX,(int)fPosY,nParticles,MinLife,MaxLife,AlphaValue,initialForceX,initialForceY,BlendModeSource,BlendModeDest,
			minPartWidth,minPartHeight,maxPartWidth,maxPartHeight,nGravity,GravitySourceX,GravitySourceY,RandomSpread,red,green,blue);

		m_vEmitters.push_back(emitter);

		return true;
	}
	return false;
}