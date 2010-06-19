#ifndef CCodeProfiler_h__
#define CCodeProfiler_h__

#include <vector>
#include <string>
using namespace std;

class HTable;

class CCodeProfiler
{
public:
	struct tFunctionProfile 
	{
		string			strFunctionName;
		vector<float>	vStartTimes;
		vector<float>	vEndTimes;
	};

private:
	HTable*		m_hProfileTable;


	~CCodeProfiler();
	CCodeProfiler();
	CCodeProfiler(CCodeProfiler&);
	CCodeProfiler& operator=(CCodeProfiler&);

public:
	static CCodeProfiler*	GetInstance();

	void	StartFunction(char* szFunctionName);
	void	EndFunction(char* szFunctionName);
	void	Output(char* szFileName);
};
#endif // CCodeProfiler_h__