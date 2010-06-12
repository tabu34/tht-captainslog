#ifndef IBaseInterface_h__
#define IBaseInterface_h__

class IBaseInterface
{
public:
	virtual ~IBaseInterface(void) = 0 {}

	virtual void Update(float fElapsedTime) = 0;
	virtual void Render(void) = 0;

	virtual void AddRef(void) = 0;
	virtual void Release(void) = 0;
};
#endif // IBaseInterface_h__