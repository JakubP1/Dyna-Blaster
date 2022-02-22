
#include "StdAfx.h"
#include "BackBuffer.h"

CBackBuffer::CBackBuffer(void)
{
	m_SizeX = 500;
	m_SizeY = 500;
	m_PosX = 0;
	m_PosY = 0;
}

CBackBuffer::~CBackBuffer(void)
{
	// Unitialize and deallocate resources
	SelectObject(hLocalDC, hOldBmp);
	DeleteDC(hLocalDC);
	DeleteObject(hBitmap);
}

bool CBackBuffer::Create(HDC hWinDC) {

	// Create a device context that is compatible with the window

	hLocalDC = CreateCompatibleDC(hWinDC);
	// Verify that the device context was created
	if (hLocalDC == NULL) {
		MessageBox(NULL, __T("CreateCompatibleDC Failed"), __T("Error"), MB_OK);
		return false;
	}

	hBitmap = CreateCompatibleBitmap(hWinDC, m_SizeX, m_SizeY);
	if (hBitmap == NULL) {
		MessageBox(NULL, __T("CreateCompatibleBitmap Failed"), __T("Error"), MB_OK);
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

void CBackBuffer::Display(HDC dc) {
	// Blit the dc which holds the bitmap onto the window's dc
	BOOL qRetBlit = BitBlt(dc, m_PosX, m_PosY, qBitmap.bmWidth, qBitmap.bmHeight,
		hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit) {
		MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
	}
}

void CBackBuffer::Clear() {

	RECT rect;
	rect.left = rect.top = 0;
	rect.right = m_SizeX;
	rect.bottom = m_SizeY;
	FillRect(hLocalDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
}