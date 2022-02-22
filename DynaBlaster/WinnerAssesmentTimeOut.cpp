#include "StdAfx.h"
#include "WinnerAssesmentTimeOut.h"

void CWinnerAssesmentTimeOut::Update()
{
	if (!m_Ticking) {
			SetTickingFlag(true);
	}
}


void CWinnerAssesmentTimeOut::SetTickingFlag(bool flag)
{
	m_Ticking = flag;
}

DWORD CWinnerAssesmentTimeOut::GetLastTime()
{
	return m_LastTime;
}

CWinnerAssesmentTimeOut::CWinnerAssesmentTimeOut() {
	m_LastTime = GetTickCount();
	m_Ticking = false;
}
