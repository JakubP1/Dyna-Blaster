#include "StdAfx.h"
#include "Boost.h"

void CBoost::LoadData(HDC dc)
{

	m_Btm.LoadBitmap((char*)"sprites\\boost.bmp", dc);
	m_Btm.SetAnim(32, 32);
}

void CBoost::Display(HDC dc)
{
	m_Btm.DisplayTransparentAnim(dc, left, top, m_AnimPhase, 0);
}

int CBoost::GetSpecial()
{
	return m_Special;
}

CBoost::CBoost()
{
}

CBoost::CBoost(int x, int y,int typePar, bool isWalkable, int special)
{
	top = y;
	left = x;
	type = typePar;
	walkable = isWalkable;
	m_Special = special;
}

void CBoost::SetAnimPhase(int animPhase)
{
	m_AnimPhase = animPhase;
}

void CBoost::SetY(int y) {
	top = y;
}

void CBoost::SetX(int x) {
	left = x;
}

void CBoost::SetBitmap(CBitmap* bmap)
{
	m_Btm = *bmap;
}

CBitmap* CBoost::GetBitmap()
{
	return &m_Btm;
}
