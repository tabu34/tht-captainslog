#pragma once

enum eMsgTypes { MSG_NULL, MSG_DESTROY_UNIT };

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
class CUnit;

class CUnitDeathMessage : public CBaseMessage
{
private:
	CUnit* m_pUnit;
public:
	CUnitDeathMessage(CUnit* pUnit) : CBaseMessage(MSG_DESTROY_UNIT)
	{
		m_pUnit = pUnit;
	}

	CUnit* GetUnit() { return m_pUnit; }
};