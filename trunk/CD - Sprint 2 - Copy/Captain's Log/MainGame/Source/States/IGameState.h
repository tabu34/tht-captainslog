#ifndef IGameState_h__
#define IGameState_h__

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

class IGameState
{
public:
	virtual ~IGameState(void)=0 {}

	virtual void Enter(void)=0;
	virtual bool Input(void)=0;
	virtual void Update(float fElapsedTime)=0;
	virtual void Render(void)=0;
	virtual void Exit(void)=0;
};
#endif // IGameState_h__