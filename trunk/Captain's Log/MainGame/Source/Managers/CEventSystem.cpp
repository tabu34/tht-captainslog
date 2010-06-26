#include "precompiled_header.h"

#include "CEventSystem.h"


bool CEventSystem::IsAlreadyIn(string eventID, CEventClient* pGameClient)
{
	bool bIsAlreadyRegistered = false;

	pair<multimap<string, CEventClient*>::iterator,
		 multimap<string, CEventClient*>::iterator> range;

	range = m_EventClients.equal_range(eventID);

	for(multimap<string, CEventClient*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		if((*mmIter).second == pGameClient)
		{
			bIsAlreadyRegistered = true;
			break;
		}
	}

	return bIsAlreadyRegistered;
}

void CEventSystem::RegisterEventClient(string EventID, CEventClient* pClient)
{
	if(!pClient || IsAlreadyIn(EventID, pClient))
	{
		return;
	}else
	{
		m_EventClients.insert(make_pair(EventID, pClient));
	}
}

void CEventSystem::UnregisterEventClient(string eventID, CEventClient* pClient)
{
	pair<multimap<string, CEventClient*>::iterator,
		 multimap<string, CEventClient*>::iterator> range;

	range = m_EventClients.equal_range(eventID);

	for(multimap<string, CEventClient*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		if((*mmIter).second == pClient)
		{
			mmIter = m_EventClients.erase(mmIter);
			break;
		}
	}
}

void CEventSystem::UnregisterEventClientAll(CEventClient* pClient)
{
	multimap<string, CEventClient*>::iterator mmIter = m_EventClients.begin();

	while(mmIter !=m_EventClients.end())
	{
		if((*mmIter).second == pClient)
		{
			mmIter = m_EventClients.erase(mmIter);
		}
		else
			mmIter++;
	}
}

void CEventSystem::SendEvents(CGameEvent* pGameEvent)
{
	pair<multimap<string, CEventClient*>::iterator,
		 multimap<string, CEventClient*>::iterator> range;

	range = m_EventClients.equal_range(pGameEvent->GetEventID());

	for(multimap<string, CEventClient*>::iterator mmIter = range.first;
					mmIter != range.second; mmIter++)
	{
		(*mmIter).second->HandleEvent(pGameEvent);
	}
}


void CEventSystem::SendGameEvent(string eventID, void* pData)
{
	CGameEvent newEvent(eventID, pData);

	m_CurrentGameEvents.push_back(newEvent);
}


void CEventSystem::ProcessGameEvents(void)
{
	while(m_CurrentGameEvents.size())
	{
		SendEvents(&m_CurrentGameEvents.front());
		m_CurrentGameEvents.pop_front();
	}
}

void CEventSystem::Clear(void)
{
	m_CurrentGameEvents.clear();
}

void CEventSystem::Shutdown(void)
{
	m_EventClients.clear();
}

