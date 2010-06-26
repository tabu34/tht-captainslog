#pragma once

#include <string>
using std::string;

class CGameEvent
{
private:

	string			m_sEventID;
	void*			m_pParam;


public:

	CGameEvent(string eventID, void* pParam = NULL)
	{
		m_sEventID = eventID;
		m_pParam  = pParam;
	}

	~CGameEvent() {}

	inline string  GetEventID(void)	{	return m_sEventID; }
	inline void*	GetParam(void)		{	return m_pParam; }
};
