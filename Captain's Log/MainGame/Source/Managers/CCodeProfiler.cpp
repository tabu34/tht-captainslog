#include "CCodeProfiler.h"

CCodeProfiler::~CCodeProfiler()
{

}

CCodeProfiler::CCodeProfiler()
{

}

CCodeProfiler* CCodeProfiler::GetInstance()
{
	static CCodeProfiler instance;
	return &instance;
}

void CCodeProfiler::StartFunction( float fTime, char* szFunctionName )
{

}

void CCodeProfiler::EndFunction( float fTime, char* szFunctionName )
{

}

void CCodeProfiler::Output( char* szFileName )
{

}
