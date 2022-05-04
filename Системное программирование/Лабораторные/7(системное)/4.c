#include <windows.h>
#include <stdio.h>
#include "WinMain.c"

int get(HWND hwnd);

HBITMAP hBmpFile;

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE:
	{
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		get(hwnd);
		
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


int get(HWND hwnd)
{
    HANDLE hBmpMappingFile;
    LPVOID hBmpMapFileAddr;

    RECT rect;
    GetClientRect(hwnd,&rect);

   	hBmpMappingFile = OpenFileMappingA(FILE_MAP_READ, FALSE, TEXT("kat"));
    if (hBmpMappingFile == NULL)
    {
        printf("\tCreateFileMappingA error %d\n", GetLastError());
    }

   	hBmpMapFileAddr = MapViewOfFile(hBmpMappingFile, FILE_MAP_READ, 0, 0, 0);
    if (hBmpMapFileAddr == NULL)
    {
        printf("\tMapViewOfFile error %d\n", GetLastError());
    }

	hBmpFile = (HBITMAP)hBmpMapFileAddr;
	
    BITMAPFILEHEADER *bFileHeader = (BITMAPFILEHEADER*)hBmpMapFileAddr;
    BITMAPINFO *bInfo = (BITMAPINFO*)((char*)hBmpMapFileAddr+14);
    HDC hdc = GetDC(hwnd);
    hBmpFile = CreateDIBitmap(hdc,&(bInfo->bmiHeader), CBM_INIT, (char*)hBmpMapFileAddr+bFileHeader->bfOffBits, bInfo, DIB_PAL_COLORS);
    HDC hMemDC = CreateCompatibleDC(hdc);

    SelectObject(hMemDC,hBmpFile);
    StretchBlt(hdc, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, bInfo->bmiHeader.biWidth, bInfo->bmiHeader.biHeight, SRCCOPY); 
    
    ReleaseDC(hwnd,hdc);
    DeleteDC(hMemDC);
    DeleteObject(hBmpFile);

    return (INT_PTR)TRUE;
}