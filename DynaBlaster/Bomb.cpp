#include "StdAfx.h"
#include "Bomb.h"
#include "Bomber.h"


CBomb::CBomb()
{
	m_AnimPhase = 0;
	m_TimeFrameInterval = 200;
	m_MaxAnimPhase = 2;
	m_LastTime = GetTickCount();
}

CBomb::CBomb(int x, int y,int typePar, bool isWalkable, int bTime, int bFire, CBomber* bomber)
{
	m_AnimPhase = 0;
	m_MaxAnimPhase = 2;
	m_TimeFrameInterval = 200;
	m_LastTime = GetTickCount();
	top = y;
	left = x;
	type = typePar;
	walkable = isWalkable;
	m_BombTime = bTime;
	m_FlameSize = bFire;
	m_Player = bomber;
	m_LastTimeBombing = GetTickCount();
	m_ExplosionInterval = 2000;

}

bool CBomb::IsBombExploded()
{
	return m_IsExploded;
}

int CBomb::GetBombFire()
{
	return m_FlameSize;
}

void CBomb::LoadData(HDC dc)
{

	m_Btm.LoadBitmap((char*)"sprites\\bomb.bmp", dc);
	m_Btm.SetAnim(32, 32);
}

void CBomb::Display(HDC dc)
{
	m_Btm.DisplayTransparentAnim(dc, left, top, m_AnimPhase, 0);
}

void CBomb::SetY(int y) {
	top = y;
}

void CBomb::SetX(int x) {
	left = x;
}


void CBomb::SetBombed(bool bombed)
{
	m_IsExploded = bombed;
}

CBitmap* CBomb::GetBitmap()
{
	return &m_Btm;
}

void CBomb::SetBitmap(CBitmap* bmap)
{
	m_Btm = *bmap;
}

void CBomb::Update()
{
	if (GetTickCount() - m_LastTimeBombing > m_ExplosionInterval * m_BombTime) {
		if (!m_IsExploded) {
			m_Player->Explode((left/32), (top/32), m_FlameSize);
				SetBombed(true);
		}
	}
	
}



void CBomb::Animate() {
	if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) { // zmenime animacni fazi jenom pokud uplyne vetsi cas od posledni zmenu nez je nastaveny
		m_AnimPhase++;
		m_LastTime = GetTickCount();
		if (m_AnimPhase > m_MaxAnimPhase) m_AnimPhase = 0; // pokud jsme na konci animacnich fazi, tak se vratme na zacatek
	}
}