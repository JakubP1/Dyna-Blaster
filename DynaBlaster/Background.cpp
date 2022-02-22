#include "StdAfx.h"
#include "Background.h"


int CBackground::m_X;;
int CBackground::m_Y;;
int CBackground::m_AnimPhase = 0;
CBitmap CBackground::m_Btm;

void CBackground::LoadData(HDC dc)
{
	m_Btm.LoadBitmap((char*)"sprites\\background_b.bmp", dc);
	m_Btm.SetAnim(736, 544);
}

void CBackground::Display(HDC dc)
{
	m_X = 0;
	m_Y = 0;
	m_Btm.DisplayTransparentAnim(dc,m_X,m_Y, m_AnimPhase,0);
}

void CBackground::SetAnimePhase(int aPhase) {
	m_AnimPhase = aPhase;
}
