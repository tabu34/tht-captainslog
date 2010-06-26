// Unit Test -- Code Profiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "..\MainGame\Source\Managers\CCodeProfiler.h"
#include <iostream>
using namespace std;

void Yield5()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	Sleep(5000);
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void Yield10()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	Sleep(10000);
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void Yield20()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	Sleep(20000);
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void Yield40()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	Sleep(40000);
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void AFunction()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	int i = 1+1;
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void BFunction()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	int i = 1-1;
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void CFunction()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	int i = 1*1;
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void DFunction()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	int i = 1/1;
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void HFunction()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	AFunction();
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void GFunction()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	AFunction();
	HFunction();
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}

void FFunction()
{
	cout << __FUNCTION__ << endl;
	CCodeProfiler::GetInstance()->StartFunction(__FUNCTION__);
	AFunction();
	GFunction();
	CCodeProfiler::GetInstance()->EndFunction(__FUNCTION__);
}


int _tmain(int argc, _TCHAR* argv[])
{
	int iterations = 5;
	for (int i = 0; i < iterations; i++)
	{
		cout << "Iteration: " << i << " of " << iterations << endl;
		AFunction();
		BFunction();
		CFunction();
		DFunction();
		FFunction();
		cout << endl;
	}

	CCodeProfiler::GetInstance()->Output("testOutput -- 6-22-2010_16-13.txt");
	return 0;
}