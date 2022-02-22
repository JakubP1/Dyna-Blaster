#pragma once

class CBitmap
{
	HBITMAP hBitmap; // bitmapa v pameti
	HDC hLocalDC; // device context pro lokalni bitmapu
	HBITMAP hOldBmp; // puvodni bitmapa v contextu zarizeni - pouze pro uvolneni pameti
	BITMAP qBitmap; // udaje o nactene bitmape - velikost atd/
	int m_AnimX, m_AnimY; // velikost animacniho ctverce (dlazdice) - pokud se obrazek sklada z dlazdic animaci

public:
	void SetAnim(int width, int height) { m_AnimX = width; m_AnimY = height; }; // nastavime velikost animacni dlazdice
	bool LoadBitmap(LPSTR szFileName, HDC hWinDC);
	void Display(HDC hWinDC, int x, int y);
	void DisplayStrech(HDC hWinDC, int x, int y, int sizex, int sizey); //zobrazime se zmenou velikosti
	void DisplayTransparent(HDC hWinDC, int x, int y, int sizex, int sizey, DWORD transparentcolor = 0); //zobrazime s transparentni barvou, pokud zadna neni specifikovana bude to barva pixelu v levem horni rohu

	void DisplayTransparentAnim(HDC hWinDC, int x, int y, int animphaseX, int animphaseY); //zobrazime pouze zvolenou animacni dlazdici dle indexu animpahsex a animphasey
	void DisplayTransparentAnimScale(HDC hWinDC, int x, int y, int animphaseX, int animphaseY, float scale);
	CBitmap(void);
	~CBitmap(void);
};
