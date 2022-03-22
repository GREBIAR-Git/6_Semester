#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "WinMain.c"
#include "Elements.c"

#define SizeElement 500
#define shapeLine 1
#define shapeRectangle 2
#define shapeEllipse 3

BOOL drawing; 
TypeElement currentElement;
Element elem[SizeElement];
int countElement;
Display display; 
BOOL move;
BOOL automove;
int margin;
int direction;

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

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: 
	{
		ShowWindow(hwnd, SW_SHOW);
		RECT window;
		GetClientRect(hwnd,&window);
		//HWND hw = CreateWindow("static", "Use keys to change tools:\nQ - Line\nW - Rectangle\nE -  Circle\n\nUse keys to change color:\nS - Red\nD - Green\nF - Blue\nR - White\n\nUse keys to change thickness:\n'I' - Thicker\n'O' - Thinner", WS_VISIBLE | WS_CHILDWINDOW , 0, 0, 250, window.bottom, hwnd, (HMENU)NULL, NULL, NULL);
		currentElement.shape = shapeEllipse;
		display.center.x = 0;
		display.center.y = 0;
		countElement = 0;
		UpdateWin1(hwnd,window);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		RECT window;
		GetClientRect(hwnd,&window);
		elem[countElement].coords.point1.x = LOWORD(lParam);
		elem[countElement].coords.point1.y = HIWORD(lParam);
		elem[countElement].typeElement.shape = currentElement.shape;
		elem[countElement].typeElement.colour = currentElement.colour;
		elem[countElement].typeElement.size = currentElement.size;
		drawing = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		RECT window;
		GetClientRect(hwnd,&window);
		elem[countElement].coords.point2.x = LOWORD(lParam);
		elem[countElement].coords.point2.y = HIWORD(lParam);
		UpdateWin1(hwnd,window);

		if(move && countElement>0)
		{
			int size1,size2;
			size1 = abs(elem[countElement-1].coords.point2.x-elem[countElement-1].coords.point1.x);
			size2 = abs(elem[countElement-1].coords.point2.y-elem[countElement-1].coords.point1.y);
			elem[countElement-1].coords.point1.x = LOWORD(lParam);
			elem[countElement-1].coords.point1.y = HIWORD(lParam);
			elem[countElement-1].coords.point2.x = LOWORD(lParam) + size1;
			elem[countElement-1].coords.point2.y = HIWORD(lParam) + size2;

		}
		break;
	}
	case WM_LBUTTONUP:
	{
		drawing = FALSE;
		if (countElement < SizeElement)
		{
			countElement++;
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
		for (int i = 0; i < countElement+1; i++)
		{
			double x1 = elem[i].coords.point1.x;
			double y1 = elem[i].coords.point1.y;
			double x2 = elem[i].coords.point2.x;
			double y2 = elem[i].coords.point2.y;
			if (elem[i].typeElement.shape == shapeLine)
			{
				HPEN hPen = CreatePen(PS_SOLID, elem[i].typeElement.size, elem[i].typeElement.colour);
				SelectObject(memDc, hPen);
				Line(memDc, x1, y1, x2, y2);
				DeleteObject(hPen);
			}
			else if (elem[i].typeElement.shape == shapeRectangle)
			{
				HPEN hPen = CreatePen(PS_DASH, elem[i].typeElement.size, elem[i].typeElement.colour);
				SelectObject(memDc, hPen);
				HBRUSH hBrush = CreateHatchBrush(HS_BDIAGONAL, elem[i].typeElement.colour);
				SelectObject(memDc, hBrush);
				Rectangle(memDc, x1, y1, x2, y2);
				DeleteObject(hBrush);
				DeleteObject(hPen);
			}
			else if (elem[i].typeElement.shape == shapeEllipse)
			{
				HPEN hPen = CreatePen(PS_SOLID, 5,  RGB(255, 255, 0));
				SelectObject(memDc, hPen);
				
				Rectangle(memDc,  x1, y1, x2, y2);
				DeleteObject(hPen);
				HPEN hPen1 = CreatePen(PS_DASH, 4,  RGB(0, 0, 0));
				SelectObject(memDc, hPen1);
				Line(memDc, x1, y1, x2, y2);
				Line(memDc, x2, y1, x1, y2);
				DeleteObject(hPen1);
				//DeleteObject(hBrush);
			}
		}







		// хорошо бы разбить на функции эту жесть (я про весь PAINT ивент)
		if (automove)
		{
			RECT window;
			GetClientRect(hwnd, &window);
			char str[4];
			sprintf(str,"%d", direction);
			SetWindowText(hwnd,str);			
			margin = 40;
			int step = 3;
			if (direction == 0)
			{
				elem[countElement-1].coords.point1.y-=step;
				elem[countElement-1].coords.point2.y-=step;
				if (elem[countElement-1].coords.point1.y < margin || elem[countElement-1].coords.point2.y < margin)
				{
					direction = 1;
				}
			}
			else if (direction == 1)
			{
				elem[countElement-1].coords.point1.y+=step;
				elem[countElement-1].coords.point2.y+=step;
				elem[countElement-1].coords.point1.x+=step;
				elem[countElement-1].coords.point2.x+=step;
				if (elem[countElement-1].coords.point1.x > window.right/2 + (abs(elem[countElement-1].coords.point2.x -elem[countElement-1].coords.point1.x))/2 || elem[countElement-1].coords.point2.x > window.right /2 + (abs(elem[countElement-1].coords.point2.x -elem[countElement-1].coords.point1.x))/2)
				{
					direction = 2;
				}
			}
			else if (direction == 2)
			{
				elem[countElement-1].coords.point1.y-=step;
				elem[countElement-1].coords.point2.y-=step;
				elem[countElement-1].coords.point1.x+=step;
				elem[countElement-1].coords.point2.x+=step;
				if (elem[countElement-1].coords.point1.x > window.right - margin || elem[countElement-1].coords.point2.x > window.right - margin)
				{
					direction = 3;
				}
			}
			else if (direction == 3)
			{
				elem[countElement-1].coords.point1.y+=step;
				elem[countElement-1].coords.point2.y+=step;
				if (elem[countElement-1].coords.point1.y > window.bottom - margin || elem[countElement-1].coords.point2.y > window.bottom - margin)
				{
					direction = 4;
				}
			}
			else if (direction == 4)
			{
				elem[countElement-1].coords.point1.x-=step;
				elem[countElement-1].coords.point2.x-=step;
				if (elem[countElement-1].coords.point1.x < margin || elem[countElement-1].coords.point2.x < margin)
				{
					direction = 5;
				}
			}
			else if (direction == 5)
			{
				int width = abs(elem[countElement-1].coords.point2.x-elem[countElement-1].coords.point1.x);
				int height = abs(elem[countElement-1].coords.point2.y-elem[countElement-1].coords.point1.y);
				elem[countElement-1].coords.point1.x = margin+1;
				elem[countElement-1].coords.point2.x = margin+1 + width;
				elem[countElement-1].coords.point2.y = window.bottom - margin-1;
				elem[countElement-1].coords.point1.y = elem[countElement-1].coords.point2.y - height;
				
				direction = 0;
			}
			UpdateWin(hwnd);
		}













		
		
		//DrawUI(memDc, window);

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
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case 0x45:
			{
				currentElement.shape = shapeEllipse;
				break;
			}
			case 0x49:
			{
				if (currentElement.size < 228)
				currentElement.size++;
				break;
			}
			case 0x4F:
			{
				if (currentElement.size > 1)
				currentElement.size--;
				break;
			}
			case VK_LEFT:
			{
				display.center.x-=1;
				UpdateWin(hwnd);
				break;
			}
			case VK_RIGHT:
			{
				display.center.x+=1;
				UpdateWin(hwnd);
				break;
			}
			case VK_UP:
			{
				display.center.y+=1;
				UpdateWin(hwnd);
				break;
			}
			case VK_DOWN:
			{
				display.center.y-=1;
				UpdateWin(hwnd);
				break;
			}
			case VK_SPACE:
			{
				move=!move;
				break;
			}
			case VK_CONTROL:
			{
				automove = 1;
				UpdateWin(hwnd);
				
				break;
			}
		}
		break;
	}
	case WM_KEYUP:
	{
		switch(wParam)
		{
			case VK_CONTROL:
			{
				automove = 0;
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
