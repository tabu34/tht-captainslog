#pragma once

#include "CMessage.h"
#include <queue>
using std::queue;


typedef void (*MESSAGEPROC)(CBaseMessage*);

class CMessageSystem
{
private:
	queue<CBaseMessage*>	m_MsgQueue;
	MESSAGEPROC	m_pfnMsgProc;	

	CMessageSystem() { m_pfnMsgProc = NULL;	}
	CMessageSystem(const CMessageSystem&);
	CMessageSystem& operator=(const CMessageSystem&);
	~CMessageSystem() {}

public:
	
	static CMessageSystem* GetInstance(void)
	{
		static CMessageSystem instance;
		return &instance;
	}
	int GetNumberOfMessages(void)
	{
		return (int)m_MsgQueue.size();
	}
	void InitMessageSystem(MESSAGEPROC pfnMsgProc);
	void SendMessage(CBaseMessage* pMsg);
	void ProcessMessages(void);
	void Clear(void);
	void Shutdown(void);
};