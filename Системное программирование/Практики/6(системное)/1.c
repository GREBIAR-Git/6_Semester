#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "WinMain.c"
#include "Elements.c"

BOOL moving;
HANDLE hThread;
Coords elips;
BOOL directionTop = FALSE;
int elipsTop = 200;
int elipsBot = 400;
HWND main1;

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
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

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	while(moving)
	{
		if (directionTop)
			elips.point1.y -= 1;
		else
			elips.point1.y += 1;

		if (elips.point1.y == elipsBot)
		{
			directionTop = TRUE;
		}
		else if (elips.point1.y == elipsTop)
		{
			directionTop = FALSE;
		}
		UpdateWin(main1);
		Sleep(3);
	}
    return 0;
}

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: 
	{
		main1 = hwnd;
		moving = FALSE;
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		RECT window;
		GetClientRect(hwnd,&window);
		int widthRec = 200; 
		elips.point1.x = (window.right-widthRec)/2;
		elips.point1.y = 300;
		elips.point2.x = (window.right+widthRec)/2;
		UpdateWin1(hwnd,window);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		DWORD dwThreadId, dwThrdParam = 1;
		if(hThread==NULL)
		{
			hThread = CreateThread(
			NULL,         // атрибуты безопасности по умолчанию
			0,            // размер стека используется по умолчанию
			ThreadFunc,   // функция потока
			&dwThrdParam, // аргумент функции потока
			0,            // флажки создания используются по умолчанию
			&dwThreadId); // возвращает идентификатор потока
			moving = TRUE;
		}
			
		break;
	}
	case WM_RBUTTONDOWN:
	{
		if(hThread!=NULL)
		{
			moving = FALSE;
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle( hThread );
			hThread = NULL;
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		HDC memDc = CreateCompatibleDC(hdc);
		RECT window;
		GetClientRect(hwnd, &window);
		HBITMAP bmp = CreateCompatibleBitmap(hdc, window.right, window.bottom);
		SelectObject(memDc, bmp);
		FillRect(memDc, &window, (HBRUSH)(RGB(255,255,255)));
		
		int widthRec = 200; 
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
		SelectObject(memDc, hPen);

		double interval = (elips.point1.y-100)  /(double)14;
		int count = 0;
		Line(memDc, window.right/2, 100 + count * interval, window.right/2, 100 + (count+1)*interval);
		count++;
		Line(memDc, window.right/2, 100 + count * interval, (window.right+widthRec)/2, 100 + (count+1)*interval);
		for (int i = 0; i < 5; i++)
		{
			count++;
			Line(memDc, (window.right+widthRec)/2, 100 + count * interval,(window.right-widthRec)/2, 100 + (count+1)*interval);
			count++;
			Line(memDc, (window.right-widthRec)/2, 100 + count * interval,(window.right+widthRec)/2, 100 + (count+1)*interval);
		}
		count++;
		Line(memDc, (window.right+widthRec)/2, 100 + count * interval, window.right/2, 100 + (count+1)*interval);
		count++;
		Line(memDc, window.right/2, 100 + count * interval, window.right/2, 100 + (count+1)*interval);

		HBRUSH hBrush = CreateSolidBrush(RGB(0,0,255));
		SelectObject(memDc, hBrush);
		Rectangle(memDc,(window.right-widthRec)/2,0,(window.right+widthRec)/2,100);
		DeleteObject(hBrush);
		
		hBrush = CreateSolidBrush(RGB(255,0,0));
		SelectObject(memDc, hBrush);
		Ellipse(memDc,elips.point1.x,elips.point1.y,elips.point2.x,elips.point1.y+100);
		DeleteObject(hBrush);
		DeleteObject(hPen);

		BitBlt(hdc, 0, 0, window.right, window.bottom, memDc, 0, 0, SRCCOPY);
		DeleteDC(memDc);
		DeleteObject(bmp);
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
