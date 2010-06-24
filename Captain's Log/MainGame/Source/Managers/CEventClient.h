#pragma once


class CEventClient
{
public:
	CEventClient(void);
	~CEventClient(void);

	//EVENT HANDLER
	virtual void HandleEvent(CGameEvent* pEvent) = 0;
};
