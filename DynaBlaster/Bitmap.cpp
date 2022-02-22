#include "StdAfx.h"
#include "Bitmap.h"


CBitmap::CBitmap(void)
{
}

CBitmap::~CBitmap(void)
{
	// Unitialize and deallocate resources
	SelectObject(hLocalDC, hOldBmp);
	DeleteDC(hLocalDC);
	DeleteObject(hBitmap);
}


bool CBitmap::LoadBitmap(LPSTR szFileName, HDC hWinDC)
{
	// Load the bitmap image file

	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);
	// Verify that the image was loaded
	if (hBitmap == NULL) {
		MessageBox(NULL, __T("LoadImage Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Create a device context that is compatible with the window

	hLocalDC = ::CreateCompatibleDC(hWinDC);
	// Verify that the device context was created
	if (hLocalDC == NULL) {
		MessageBox(NULL, __T("CreateCompatibleDC Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Get the bitmap's parameters and verify the get

	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),
		reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn) {
		MessageBox(NULL, __T("GetObject Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Select the loaded bitmap into the device context
	hOldBmp = (HBITMAP)::SelectObject(hLocalDC, hBitmap);
	if (hOldBmp == NULL) {
		MessageBox(NULL, __T("SelectObject Failed"), __T("Error"), MB_OK);
		return false;
	}


	return true;
}

void CBitmap::Display(HDC hWinDC, int x, int y) {

	// Blit the dc which holds the bitmap onto the window's dc
	BOOL qRetBlit = BitBlt(hWinDC, x, y, qBitmap.bmWidth, qBitmap.bmHeight,
		hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit) {
		MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
	}

}


void CBitmap::DisplayStrech(HDC hWinDC, int x, int y, int sizex, int sizey) {

	// Blit the dc which holds the bitmap onto the window's dc	
	BOOL qRetBlit = StretchBlt(hWinDC, x, y, sizex, sizey, hLocalDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, SRCCOPY);

	if (!qRetBlit) {
		MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
	}
}

void CBitmap::DisplayTransparent(HDC hWinDC, int x, int y, int sizex, int sizey, DWORD transparentcolor) {

	// Blit the dc which holds the bitmap onto the window's dc	
	if (transparentcolor == 0) transparentcolor = GetPixel(hLocalDC, 0, 0); // if 0 use leftcorner color as transparent
	BOOL qRetBlit = TransparentBlt(hWinDC, x, y, sizex, sizey, hLocalDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, transparentcolor);
	if (!qRetBlit) {
		MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
	}
}

void CBitmap::DisplayTransparentAnim(HDC hWinDC, int x, int y, int animphaseX, int animphaseY) {

	// Blit the dc which holds the bitmap onto the window's dc	
	DWORD transparentcolor = GetPixel(hLocalDC, 0, 0); // if 0 use leftcorner color as transparent
	BOOL qRetBlit = TransparentBlt(hWinDC, x, y, m_AnimX, m_AnimY, hLocalDC, animphaseX * m_AnimX, animphaseY * m_AnimY, m_AnimX, m_AnimY, transparentcolor);
	if (!qRetBlit) {
		MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
	}
}

void CBitmap::DisplayTransparentAnimScale(HDC hWinDC, int x, int y, int animphaseX, int animphaseY, float scale) {

	// Blit the dc which holds the bitmap onto the window's dc	
	DWORD transparentcolor = GetPixel(hLocalDC, 0, 0); // if 0 use leftcorner color as transparent
	BOOL qRetBlit = TransparentBlt(hWinDC, x, y, m_AnimX * scale, m_AnimY * scale, hLocalDC, animphaseX * m_AnimX, animphaseY * m_AnimY, m_AnimX, m_AnimY, transparentcolor);
	if (!qRetBlit) {
		MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
	}
}

