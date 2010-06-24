#include "precompiled_header.h"

#include "CMessageSystem.h"

void CMessageSystem::InitMessageSystem(MESSAGEPROC pfnMsgProc)
{
	if (!pfnMsgProc)	return;

	m_pfnMsgProc = pfnMsgProc;
}

void CMessageSystem::SendMessage(CBaseMessage* pMsg)
{
	if (!pMsg)	return;

	m_MsgQueue.push(pMsg);
}

void CMessageSystem::ProcessMessages(void)
{
	if(!m_pfnMsgProc)	return;

	while(!m_MsgQueue.empty())
	{
		m_pfnMsgProc(m_MsgQueue.front());
		delete m_MsgQueue.front();		
		m_MsgQueue.pop();				
	}
}

void CMessageSystem::Clear(void)
{
	while(!m_MsgQueue.empty())
	{
		delete m_MsgQueue.front();
		m_MsgQueue.pop();
	}
}

void CMessageSystem::Shutdown(void)
{
	Clear();
	m_pfnMsgProc = NULL;
}