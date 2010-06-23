#include "precompiled_header.h"
#include "HTable.h"
#include <fstream>

CCodeProfiler::~CCodeProfiler()
{
	delete m_hProfileTable;
}

CCodeProfiler::CCodeProfiler()
{
	m_hProfileTable = new HTable();
	QueryPerformanceFrequency(&m_liPerformanceFrequency);
}

CCodeProfiler* CCodeProfiler::GetInstance()
{
	static CCodeProfiler instance;
	return &instance;
}

void CCodeProfiler::StartFunction( char* szFunctionName )
{
	tFunctionProfile*	tempFunctProfile = NULL;

	int nBucketNumber = m_hProfileTable->find(szFunctionName, &tempFunctProfile);

	if (nBucketNumber == -1)
	{
		tempFunctProfile = new tFunctionProfile();
	}

	LARGE_INTEGER	timer;
	QueryPerformanceCounter(&timer);
	tempFunctProfile->vStartTimes.push_back(timer);

	tempFunctProfile->strFunctionName = szFunctionName;

	if (nBucketNumber == -1)
	{
		m_hProfileTable->insert(szFunctionName, tempFunctProfile);
		delete tempFunctProfile;
	}


}

void CCodeProfiler::EndFunction( char* szFunctionName )
{
	tFunctionProfile*	tempFunctProfile = NULL;

	int nBucketNumber = m_hProfileTable->find(szFunctionName, &tempFunctProfile);

	if (nBucketNumber == -1)
	{
		tempFunctProfile = new tFunctionProfile();
	}

	LARGE_INTEGER	timer;
	QueryPerformanceCounter(&timer);
	tempFunctProfile->vEndTimes.push_back(timer);

	tempFunctProfile->strFunctionName = szFunctionName;

	if (nBucketNumber == -1)
	{
		m_hProfileTable->insert(szFunctionName, tempFunctProfile);
		delete tempFunctProfile;
	}
}

void CCodeProfiler::Output( char* szFileName )
{
	vector<double>	vTimeList;
	double			nTimeMax, nTimeMin, nTimeAverage;
	nTimeMax = nTimeMin = nTimeAverage = 0;

	ofstream	outstream;
	outstream.open(szFileName);

	if (outstream.is_open())
	{
		int nNumBuckets = (int)m_hProfileTable->NumBuckets();
		for (int i = 0; i < nNumBuckets; i++)
		{
			SLList<tFunctionProfile>* tempList = m_hProfileTable->OutputTable() + i;
			SLLIter<tFunctionProfile> tempListIter(*tempList);

			tempListIter.begin();

			while (!tempListIter.end())
			{
				int nNumTimes = min(tempListIter.current().vStartTimes.size(), tempListIter.current().vEndTimes.size());
				vTimeList.clear();

				GenerateTimes(&tempListIter.current(), &vTimeList, nNumTimes);
				MaxTime(&vTimeList, &nTimeMax);
				MinTime(&vTimeList, &nTimeMin);
				AverageTime(&vTimeList, &nTimeAverage);

				tFunctionProfile tempProfile = tempListIter.current();
				outstream << "--------------------------------------------------\n";
				outstream << "Function: ";
				outstream << tempProfile.strFunctionName;
				outstream << endl;
				
				outstream << "Max Time: " << nTimeMax << "\t" << "MinTime: " << nTimeMin << "\t" << "Average Time: " << nTimeAverage << "\n\n";

				outstream << "All Times" << vTimeList.size() << ": ";
				for (unsigned int i = 0; i < vTimeList.size(); i++)
				{
					outstream << vTimeList[i] << ", ";
				}
				outstream << "\n\n";

				++tempListIter;
			}
		}
		outstream.close();
	}
}

void CCodeProfiler::GenerateTimes(tFunctionProfile* tfpFunctionProfile, vector<double>* llCalculatedTimes, int nNumTimes)
{
	double tempTime = 0;
	for (int i = 0; i < nNumTimes; i++)
	{
		tempTime = double(tfpFunctionProfile->vEndTimes[i].QuadPart - tfpFunctionProfile->vStartTimes[i].QuadPart);
		tempTime = tempTime / (double)m_liPerformanceFrequency.QuadPart;
		llCalculatedTimes->push_back(tempTime);
	}
}

void CCodeProfiler::MaxTime(vector<double>* llCalculatedTimes, double* nMaxTime)
{
	*nMaxTime = -1;

	for (unsigned int i = 0; i < llCalculatedTimes->size(); i++)
	{
		if (llCalculatedTimes->operator [](i) > *nMaxTime)
			*nMaxTime = llCalculatedTimes->operator [](i);
	}
}

void CCodeProfiler::MinTime(vector<double>* llCalculatedTimes, double* nMinTime)
{
	*nMinTime = INT_MAX;

	for (unsigned int i = 0; i < llCalculatedTimes->size(); i++)
	{
		if (llCalculatedTimes->operator [](i) < *nMinTime)
			*nMinTime = llCalculatedTimes->operator [](i);
	}
}

void CCodeProfiler::AverageTime(vector<double>* llCalculatedTimes, double* nAverageTime)
{
	*nAverageTime = 0;

	for (unsigned int i = 0; i < llCalculatedTimes->size(); i++)
	{
		*nAverageTime += llCalculatedTimes->operator [](i);
	}

	*nAverageTime = *nAverageTime / llCalculatedTimes->size();
}