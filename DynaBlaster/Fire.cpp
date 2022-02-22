#include "StdAfx.h"
#include "Fire.h"
#include "Scene.h"

CFire::CFire()
{
	m_AnimPhase = 0;
	m_AnimRow = 0;
	m_TimeFrameInterval = 125;
	m_MaxAnimPhase = 4;
	m_LastTime = GetTickCount();
}

CFire::CFire(int x, int y, int typePar, bool isWalkable)
{
	m_AnimPhase = 0;
	m_AnimRow = 0;
	m_TimeFrameInterval = 125;
	m_MaxAnimPhase = 4;
	m_LastTime = GetTickCount();

	top = y;
	left = x;
	type = typePar;
	walkable = isWalkable;

}

void CFire::LoadData(HDC dc)
{

	m_Btm.LoadBitmap((char*)"sprites\\fire.bmp", dc);
	m_Btm.SetAnim(32, 32);
}

void CFire::Display(HDC dc)
{
	m_Btm.DisplayTransparentAnim(dc, left, top, m_AnimPhase, m_AnimRow);
}

void CFire::Animate() {
	if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) { // zmenime animacni fazi jenom pokud uplyne vetsi cas od posledni zmenu nez je nastaveny
		m_AnimPhase++;
		m_LastTime = GetTickCount();
		if (m_AnimPhase > m_MaxAnimPhase) m_AnimPhase = 0; // pokud jsme na konci animacnich fazi, tak se vratme na zacatek
	}
}

void CFire::SetAnimRow(int animRow)
{
	m_AnimRow = animRow;
}

void CFire::SetY(int y) {
	top = y;
}

void CFire::SetX(int x) {
	left = x;
}

CBitmap* CFire::GetBitmap()
{
	return &m_Btm;
}

void CFire::SetBitmap(CBitmap* bmap)
{
	m_Btm = *bmap;
}