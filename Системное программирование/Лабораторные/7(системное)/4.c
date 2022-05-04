#include <windows.h>
#include <stdio.h>
#include "WinMain.c"

VOID UpdateWin(HWND hwnd)
{
	RECT window;  
	GetClientRect(hwnd, &window);
	window.left = 0;
	InvalidateRect(hwnd, &window, 1);
}

VOID UpdateWin1(HWND hwnd,RECT window)
{
	window.left = 0;
	InvalidateRect(hwnd, &window, 1);
}


HBITMAP CopyBitmap(HBITMAP hbmOn) {
    HDC hdcSrc = CreateCompatibleDC(NULL);
    HDC hdcDst = CreateCompatibleDC(NULL);
    HBITMAP hbmNew;
    BITMAP bm, bm1;

    GetObject(hbmOn, sizeof(bm), &bm);
    SelectObject(hdcSrc, hbmOn);
    hbmNew = CreateBitmap( bm.bmWidth, bm.bmHeight, bm.bmPlanes,bm.bmBitsPixel,NULL);
    SelectObject(hdcDst, hbmNew);
    BitBlt(hdcDst, 0, 0, bm.bmWidth, bm.bmHeight, hdcSrc, 0, 0, SRCCOPY);

    DeleteDC(hdcSrc);
    DeleteDC(hdcDst);

    return hbmNew;
}

HBITMAP pic;

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE:
	{
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		HANDLE hMapFile;
        hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,TEXT("kat"));
        HBITMAP pic1 = (HBITMAP) MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS, 0,0,0);
        pic = CopyBitmap(pic1);
        UnmapViewOfFile(pic1);
        CloseHandle(hMapFile);
		UpdateWin(hwnd);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		HDC memDc = CreateCompatibleDC(hdc);
		BITMAP bmp;
		RECT window;
		GetClientRect(hwnd,&window);
		FillRect(hdc, &window, (HBRUSH)(RGB(255,255,255)));
		if(pic != NULL)
		{  
			SelectObject(memDc, pic);
			BitBlt(hdc, 0,50,window.right,window.bottom,memDc,0,0,SRCCOPY);
		} 
		DeleteDC(memDc);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_ERASEBKGND:
	{
		return 0;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}