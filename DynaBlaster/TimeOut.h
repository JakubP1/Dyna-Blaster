#pragma once
#include "block.h"
#include "vector"
#include "string"
class CBomber;

class CTimeOut
{

	CBomber* m_Player;
	bool m_Ticking;
	DWORD m_TimeOutInterval; // interval v ms kdy se bude menit animacni faze
	DWORD m_LastTime; // posledni cas, kdy se menila animacni faze
	int m_X;
	int m_Y;
	int m_BombFire;
	std::string m_Action;

public:
	CTimeOut(int x, int y, int bfire, std::string action, CBomber* player);
	void Update();
	void SetTickingFlag(bool flag);

	DWORD GetLastTime();
};

