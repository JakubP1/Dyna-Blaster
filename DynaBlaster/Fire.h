#pragma once

#include "bitmap.h"
#include "rectangle.h"

class CScene;

class CFire: public CRectangle
{
	CBitmap m_Btm;
	int m_AnimPhase;
	int m_AnimRow; // cislo radku v bitmape pro animacni fazi
	int m_MaxAnimPhase;
	int m_Direction; // smer, kterym se drak pohybuje

	DWORD m_TimeFrameInterval; // interval v ms kdy se bude menit animacni faze
	DWORD m_LastTime; // posledni cas, kdy se menila animacni faze

public:

	enum FireType {

		FIRE_TYPE_1 = 10,
		FIRE_TYPE_2,
		FIRE_TYPE_3,
		FIRE_TYPE_4,
		FIRE_TYPE_5,
		FIRE_TYPE_6,
		FIRE_TYPE_7
	};
	
public:
	CFire(int x, int y, int type, bool walkable);
	CFire();
	void LoadData(HDC dc);
	void Display(HDC dc);
	void Animate();
	void SetAnimRow(int animRow);
	void SetY(int y);
	void SetX(int x);
	void SetBitmap(CBitmap* bmap);
	CBitmap* GetBitmap();
};

