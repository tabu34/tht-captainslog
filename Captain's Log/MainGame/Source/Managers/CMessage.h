
#pragma once


class CBaseMessage
{
private:
	int	m_msgID;

public:
	CBaseMessage(int msgID)
	{
		m_msgID = msgID;
	}

	virtual ~CBaseMessage(void) {}

	int GetMsgID(void)	{ return m_msgID; }
};

///////////////////////////////////////////////////////
//ADD ALL MESSAGES HERE
///////////////////////////////////////////////////////