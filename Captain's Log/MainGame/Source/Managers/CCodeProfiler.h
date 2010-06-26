#ifndef CCodeProfiler_h__
#define CCodeProfiler_h__

#include <vector>
#include <string>
#include <windows.h>
using namespace std;

class HTable;

class CCodeProfiler
{
public:
	struct tFunctionProfile 
	{
		string					strFunctionName;
		vector<LARGE_INTEGER>	vStartTimes;
		vector<LARGE_INTEGER>	vEndTimes;
	};

private:
	HTable*		m_hProfileTable;

	LARGE_INTEGER	m_liPerformanceFrequency;

	~CCodeProfiler();
	CCodeProfiler();
	CCodeProfiler(CCodeProfiler&);
	CCodeProfiler& operator=(CCodeProfiler&);

public:
	static CCodeProfiler*	GetInstance();

	void	StartFunction(char* szFunctionName);
	void	EndFunction(char* szFunctionName);
	void	Output(char* szFileName);
	void	GenerateTimes(tFunctionProfile* tfpFunctionProfile, vector<double>* llCalculatedTimes, int nNumTimes);
	void	MaxTime(vector<double>* llCalculatedTimes, double* nMaxTime);
	void	MinTime(vector<double>* llCalculatedTimes, double* nMinTime);
	void	AverageTime(vector<double>* llCalculatedTimes, double* nAverageTime);
};
#endif // CCodeProfiler_h__