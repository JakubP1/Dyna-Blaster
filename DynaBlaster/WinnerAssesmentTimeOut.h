#pragma once
#include <vector>

class CWinnerAssesmentTimeOut
{
	bool m_Ticking;
	DWORD m_LastTime;


public:
	CWinnerAssesmentTimeOut();
	void Update();
	void SetTickingFlag(bool flag);
	DWORD GetLastTime();
};

