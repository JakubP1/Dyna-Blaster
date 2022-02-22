#pragma once
//#include "StdAfx.h"
#include "Bitmap.h"
#include "rectangle.h"


class CBlock: public CRectangle
{
	CBitmap m_Btm;
	int m_AnimPhase;
	int m_MaxAnimPhase;
	DWORD m_TimeFrameInterval; // interval v ms kdy se bude menit animacni faze
	DWORD m_LastTime; // 
	bool m_Burned;

public:
	CBlock(int x, int y);
	
	CBlock();
	void LoadData(HDC dc);
	void Display(HDC dc);
	void Animate();
	void SetY(int y);
	void SetX(int x);
	void SetBurned(bool burned);
	bool GetBurned();
};

