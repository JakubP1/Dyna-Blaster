#pragma once
#include "Bitmap.h"
#include "rectangle.h"

class CBoost : public CRectangle
{
	CBitmap m_Btm;
	int m_AnimPhase;
	int m_MaxAnimPhase;
	//DWORD m_TimeFrameInterval; // interval v ms kdy se bude menit animacni faze
	//DWORD m_LastTime; // posledni cas, kdy se menila animacni faze

	int m_Special;
public:
	static enum SpecialType {
		BOMB = 0,
		FIRE	
	};


	void LoadData(HDC dc);
	void Display(HDC dc);
	int GetSpecial();
	CBoost();
	CBoost(int x, int y, int type, bool walkable, int special);
	void SetAnimPhase(int animPhase);
	void SetY(int y);
	void SetX(int x);

	void SetBitmap(CBitmap* bmap);
	CBitmap* GetBitmap();
};

