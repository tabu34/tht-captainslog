#pragma once

#include<list>
#include<map>
using std::list;
using std::multimap;
using std::pair;

#include "CGameEvent.h"
#include "CEventClient.h"

class CEventSystem
{
	multimap<string, CEventClient*> m_EventClients;

	list<CGameEvent> m_CurrentGameEvents;

	void SendEvents(CGameEvent* pGameEvent);

	bool IsAlreadyIn(string eventID, CEventClient* pGameClient);

	CEventSystem() {}
	CEventSystem(const CEventSystem&);
	CEventSystem& operator=(const CEventSystem&);
	~CEventSystem() {}

public:
	static CEventSystem* GetInstance(void)
	{
		static CEventSystem instance;
		return &instance;
	}

	void RegisterEventClient(string eventID, CEventClient* pClient);

	void UnregisterEventClient(string eventID, CEventClient* pClient);

	void UnregisterEventClientAll(CEventClient* pClient);

	void SendGameEvent(string eventID, void* pData = NULL);

	void ProcessGameEvents(void);

	void Clear(void);

	void Shutdown(void);



};