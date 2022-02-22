#pragma once
#include "Bitmap.h"
#include "rectangle.h"


class CBomber;

class CBomb: public CRectangle
{
	CBitmap m_Btm;
	int m_AnimPhase;
	int m_MaxAnimPhase;
	DWORD m_TimeFrameInterval; // interval v ms kdy se bude menit animacni faze
	DWORD m_ExplosionInterval;
	DWORD m_LastTime; // posledni cas, kdy se menila animacni faze
	DWORD m_LastTimeBombing;
	int m_FlameSize;
	int m_BombTime;
	bool m_IsExploded;

	CBomber* m_Player;


public:
	CBomb();
	CBomb(int x, int y,int type, bool walkable, int bombTime, int bombFire, CBomber* bomber);

	bool IsBombExploded();
	int GetBombFire();

	void LoadData(HDC dc);
	void Display(HDC dc);
	void Animate();

	void SetY(int y);
	void SetX(int x);

	void SetBombed(bool bombed);
	void Update();
	
	void SetBitmap(CBitmap *bmap);
	CBitmap* GetBitmap();
};


