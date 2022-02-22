#include "StdAfx.h"
#include "Block.h"

CBlock::CBlock(int x, int y) {
	top = y;
	left = x;
	m_AnimPhase = 0;
	m_TimeFrameInterval = 150;
	m_MaxAnimPhase = 6;
	m_LastTime = GetTickCount();
}

CBlock::CBlock() {
	m_AnimPhase = 0;
	m_TimeFrameInterval = 150;
	m_MaxAnimPhase = 6;
	m_LastTime = GetTickCount();
}



void CBlock::LoadData(HDC dc)
{

	m_Btm.LoadBitmap((char*)"sprites\\block.bmp", dc);
	m_Btm.SetAnim(32, 32);
}

void CBlock::Display(HDC dc)
{
	m_Btm.DisplayTransparentAnim(dc, left, top, m_AnimPhase, 0);
}

void CBlock::Animate()
{
	if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) { // zmenime animacni fazi jenom pokud uplyne vetsi cas od posledni zmenu nez je nastaveny
		m_AnimPhase++;
		m_LastTime = GetTickCount();
		if (m_AnimPhase > m_MaxAnimPhase) m_AnimPhase = 0; // pokud jsme na konci animacnich fazi, tak se vratme na zacatek
	}
}
void CBlock::SetY(int y) {
	top = y;
}

void CBlock::SetX(int x) {
	left = x;
}
void CBlock::SetBurned(bool burned)
{
	m_Burned = burned;
}

bool CBlock::GetBurned()
{
	return m_Burned;
}
