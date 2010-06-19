#include "CCodeProfiler.h"
#include "HTable.h"

CCodeProfiler::~CCodeProfiler()
{
	delete m_hProfileTable;
}

CCodeProfiler::CCodeProfiler()
{
	m_hProfileTable = new HTable;
}

CCodeProfiler* CCodeProfiler::GetInstance()
{
	static CCodeProfiler instance;
	return &instance;
}

void CCodeProfiler::StartFunction( char* szFunctionName )
{
	tFunctionProfile	tempFunctProfile;
	tempFunctProfile.strFunctionName = szFunctionName;

	int nBucketNumber = m_hProfileTable->find(&tempFunctProfile);
	if (nBucketNumber == -1)
	{
		m_hProfileTable->insert(tempFunctProfile);
	}

	


}

void CCodeProfiler::EndFunction( char* szFunctionName )
{

}

void CCodeProfiler::Output( char* szFileName )
{

}

