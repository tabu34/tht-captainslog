#ifndef CCodeProfiler_h__
#define CCodeProfiler_h__

#include <vector>
#include <string>
using namespace std;

class CCodeProfiler
{
	vector<string>			strFunctionName;
	vector<vector<float>>	vTimes;

	~CCodeProfiler();
	CCodeProfiler();
	CCodeProfiler(CCodeProfiler&);
	CCodeProfiler& operator=(CCodeProfiler&);

public:
	static CCodeProfiler*	GetInstance();

	void	StartFunction(float fTime, char* szFunctionName);
	void	EndFunction(float fTime, char* szFunctionName);
	void	Output(char* szFileName);

};
#endif // CCodeProfiler_h__