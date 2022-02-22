#include "StdAfx.h"
#include "TimeOut.h"
#include "Bomber.h"


CTimeOut::CTimeOut(int x, int y, int bfire, std::string action, CBomber* player)
{
	m_LastTime = GetTickCount();
	m_Ticking = false;
	m_Player = player;
	m_X = x;
	m_Y = y;
	m_BombFire = bfire;
	m_Action = action;
}

void CTimeOut::Update()
{
		if (!m_Ticking) {
			m_Player->CheckCollisionWithFire(m_X, m_Y, m_BombFire,m_Action);
			SetTickingFlag(true);
		}
}

void CTimeOut::SetTickingFlag(bool flag)
{
	m_Ticking = flag;
}

DWORD CTimeOut::GetLastTime()
{
	return m_LastTime;
}
