#include <windows.h>
#include <stdio.h>
#include "WinMain.c"

int put();

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
		put(hwnd);
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

int put(HWND hwnd)
{
    HANDLE hBmpMappingFile;
    LPVOID hBmpMapFileAddr;

    hBmpFile = CreateFileA("0.bmp", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if ((int)hBmpFile == (int)INVALID_HANDLE_VALUE)
    {
        printf("\tCreateFileA error %d\n", GetLastError());
    }

    RECT rect;
    GetClientRect(hwnd,&rect);

   	hBmpMappingFile = CreateFileMappingA(hBmpFile, NULL, PAGE_READONLY, 0, 0, TEXT("kat"));
    if (hBmpMappingFile == NULL)
    {
        printf("\tCreateFileMappingA error %d\n", GetLastError());
    }
    else if ((int)hBmpMappingFile == (int)ERROR_ALREADY_EXISTS)
    {
        printf("\tCreateFileMappingA already exists\n");
    }

   	hBmpMapFileAddr = MapViewOfFile(hBmpMappingFile, FILE_MAP_READ, 0, 0, 0);
    if (hBmpMapFileAddr == NULL)
    {
        printf("\tMapViewOfFile error %d\n", GetLastError());
    }

    return (INT_PTR)TRUE;
}