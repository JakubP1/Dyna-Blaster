#pragma once

#include "Bitmap.h"

class CBackground
{
	
public:
	static CBitmap m_Btm;
	static int m_X;
	static int m_Y;
	static int m_AnimPhase;
	static void LoadData(HDC dc);
	static void Display(HDC dc);
	static void SetAnimePhase(int aPhase);
};

