#include <windows.h>
#include <stdio.h>
#include <string.h>
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

struct Buffer
{
	char text[20];
	HBITMAP picture;
};

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: 
	{
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		char * text = "Test1";
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
		UpdateWin(hwnd);
		break;
	}
	case WM_RBUTTONUP:
	{
		HBITMAP pic = (HBITMAP)LoadImage(NULL, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HGLOBAL hgBuffer = GlobalAlloc(GMEM_DDESHARE, sizeof(HBITMAP));
		HBITMAP * chBuffer = (HBITMAP*)GlobalLock(hgBuffer);
		*chBuffer = pic;
		if(OpenClipboard(NULL))
		{
			EmptyClipboard();
			SetClipboardData(CF_BITMAP, hgBuffer);
			CloseClipboard();
			GlobalUnlock(hgBuffer);
			UpdateWin(hwnd);
		}
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
		if(OpenClipboard(NULL))
		{
			if(IsClipboardFormatAvailable(CF_BITMAP))
			{
				HBITMAP pic = (HBITMAP) GetClipboardData(CF_BITMAP);
				if(pic != NULL)
				{  
					SelectObject(memDc, pic);
					BitBlt(hdc, 0,50,window.right,window.bottom,memDc,0,0,SRCCOPY);
				} 
			} 
			else if (IsClipboardFormatAvailable(CF_TEXT))
			{
				HGLOBAL hgBuffer = (HGLOBAL) GetClipboardData(CF_TEXT);
				if(hgBuffer != NULL)
				{  
					char * chBuffer = (char *) GlobalLock(hgBuffer);
					TextOut(hdc, 0, 0,  chBuffer, strlen(chBuffer));
					GlobalUnlock(hgBuffer);
				}
			}
			else if (IsClipboardFormatAvailable(3))
			{
				printf("3");
			}
			else if (IsClipboardFormatAvailable(4))
			{
				printf("4");
			}
			else if (IsClipboardFormatAvailable(5))
			{
				printf("5");				
			}
			else if (IsClipboardFormatAvailable(6))
			{
				printf("6");
			}
			else if (IsClipboardFormatAvailable(7))
			{
				printf("7");
			}
			else if (IsClipboardFormatAvailable(8))
			{
				printf("8");
			}
			else if (IsClipboardFormatAvailable(9))
			{
				printf("9");
			}
			else if (IsClipboardFormatAvailable(10))
			{
				printf("10");
			}
			else if (IsClipboardFormatAvailable(11))
			{
				printf("11");
			}
			else if (IsClipboardFormatAvailable(12))
			{
				printf("12");
			}
			else if (IsClipboardFormatAvailable(13))
			{
				printf("13");
			}
			else if (IsClipboardFormatAvailable(14))
			{
				printf("14");
			}
			else if (IsClipboardFormatAvailable(15))
			{
				//DragQueryFiles();
				printf("15");
			}
			else if (IsClipboardFormatAvailable(16))
			{
				printf("16");
			}
			else if (IsClipboardFormatAvailable(17))
			{
				printf("17");
			}
			else if (IsClipboardFormatAvailable(18))
			{
				printf("18");
			}
			else
			{
				printf("19");
			}
			
			CloseClipboard();
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
				if(OpenClipboard(NULL))//открываем буфер обмена
				{
					EmptyClipboard(); //очищаем буфер
					CloseClipboard(); //закрываем буфер обмена
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
