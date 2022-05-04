#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "WinMain.c"

void HyperCopy(char ** here, char ** fromHere)
{
	free(*here);
	*here = (char *)calloc('\0', strlen(*fromHere) * sizeof(char));
	memcpy(*here, *fromHere, strlen(*fromHere) * sizeof(char));
	return;
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

HBITMAP pic;
char * text;

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE:
	{
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if(OpenClipboard(NULL))
		{
			if(IsClipboardFormatAvailable(CF_BITMAP))
			{
				HBITMAP picTmp = (HBITMAP) GetClipboardData(CF_BITMAP); // надо скопировать именно а то теряется потом
				pic = CopyBitmap(picTmp);
				
				text = NULL;
			} 
			else if (IsClipboardFormatAvailable(CF_TEXT))
			{
				HGLOBAL hgBuffer = (HGLOBAL) GetClipboardData(CF_TEXT);
				if(hgBuffer != NULL)
				{  
					char * chBuffer = (char *) GlobalLock(hgBuffer);
					HyperCopy(&text, &chBuffer);
					GlobalUnlock(hgBuffer);
					pic = NULL;
				}
			}
			CloseClipboard();
		}
		UpdateWin(hwnd);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		if(pic != NULL)
		{  
			if(OpenClipboard(NULL))
			{
				EmptyClipboard();
				SetClipboardData(CF_BITMAP, pic);
				CloseClipboard();
			}
		}
		else if(text != NULL)
		{  
			HGLOBAL hgBuffer= GlobalAlloc(GMEM_DDESHARE, strlen(text)+1);
			char * chBuffer= (char*)GlobalLock(hgBuffer);
			strcpy(chBuffer, text);
			if(OpenClipboard(NULL))
			{
				EmptyClipboard();
				SetClipboardData(CF_TEXT, hgBuffer);
				CloseClipboard();
				GlobalUnlock(hgBuffer);
			}
		}
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
		else if(text != NULL)
		{  
			TextOut(hdc, 0, 0,  text, strlen(text));
		}
		DeleteDC(memDc);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_ERASEBKGND:
	{
		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case VK_LEFT:
			{
				if(OpenClipboard(NULL))
				{
					EmptyClipboard();
					CloseClipboard();
					UpdateWin(hwnd);
				}
				break;
			}
			case VK_RIGHT:
			{
				UpdateWin(hwnd);
				break;
			}
		}
		break;
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
