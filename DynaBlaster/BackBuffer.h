#pragma once

class CBackBuffer
{
	HBITMAP hBitmap; // oblast pameti kde je snimek
	HDC hLocalDC; // device context pro snimek
	HBITMAP hOldBmp;
	BITMAP qBitmap; // rozmery a atributy sminku
	int m_SizeX; // velikost snimku
	int m_SizeY;
	int m_PosX; // aktualni pozice vzhledem k oknu nebo obrazovce (obvykle 0,0)
	int m_PosY;

public:
	void SetSize(int x, int y) { m_SizeX = x; m_SizeY = y; }; // rozmer snimku v pameti v pixelech (mel by odpoviat velikosti obrazovky nebo okna)
	bool Create(HDC hWinDC);
	void Display(HDC dc);
	void Clear(); // smazani bilou barvou, lze nahradit prekopirovanim pozadi z bitmapy (obrazku na pozadi)
	HDC GetDC() { return(hLocalDC); };
	CBackBuffer(void);
	~CBackBuffer(void);
};