#ifndef CCamera_h__
#define CCamera_h__

#include "..\GameObjects\CBase.h"

class CCamera : public CBase
{
public:
	void	Render();
	void	Update(float fElapsedTime);
	void	Render(CBase* pObject);
};
#endif // CCamera_h__