#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "LinePro.c"
#include "WinMain.c"
#include "Elements.c"
#include "Menu.c"

#define SizeElement 500
#define shapeLine 1
#define shapeRectangle 2
#define shapeEllipse 3

BOOL drawing; 
TypeElement currentElement;
Element elem[SizeElement];
int countElement;
float zoom;

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}

POINT Zoom(int x,int y,HWND hwnd)
{
	RECT rect;
	GetWindowRect(hwnd,&rect);
	float w = rect.right-rect.left;
	float h = rect.bottom-rect.top; 
	if(zoom!=0)
	{
		if (x<w)
		{
			if(zoom>0)
			{
				x=w/2 - (w/2 - x)/ zoom;
			}
			else
			{
				x=w/2 - (w/2 - x)* (-zoom);
			}
		}
		else
		{
			if(zoom>0)
			{
				x=w/2 + (w/2 - x)*zoom;
			}
			else
			{
				x=w/2 + (w/2 - x)/ (-zoom);
			}
		}
		if(y<h)
		{
			if(zoom>0)
			{
				y=h/2 - (h/2 - y)/zoom;
			}
			else
			{
				y=h/2 - (h/2 - y)*(-zoom);
			}
		}
		else
		{
			if(zoom>0)
			{
				y=h/2 + (h/2 - y)*zoom;
			}
			else
			{
				y=h/2 + (h/2 - y)/(-zoom);
			}
		}
	}
	POINT f; 
	f.x = x;
	f.y = y;
	return f;
}

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: {
		currentElement.shape = shapeLine;
		zoom=1;
		countElement = 0;
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		RECT window;  
		GetClientRect(hwnd, &window);
		HWND hw = CreateWindow("static", "Use keys to change tools:\nQ - Line\nW - Rectangle\nE -  Circle\n\nUse keys to change color:\nS - Red\nD - Green\nF - Blue\nR - White\n\nUse keys to change thickness:\n'I' - Thicker\n'O' - Thinner", WS_VISIBLE | WS_CHILDWINDOW , 0, 0, 250, window.bottom, hwnd, (HMENU)NULL, NULL, NULL);
		ShowWindow(hw, SW_SHOW);
		RECT rcClientRect;
		GetClientRect(hwnd, &rcClientRect);
		rcClientRect.left = 250;
		InvalidateRect(hwnd, &rcClientRect, 1);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		elem[countElement].coords.point1.x = LOWORD(lParam);
		elem[countElement].coords.point1.y = HIWORD(lParam);
		elem[countElement].typeElement.shape = currentElement.shape;
		elem[countElement].typeElement.colour = currentElement.colour;
		elem[countElement].typeElement.size = currentElement.size;
		drawing = TRUE;
		break;
	}
	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		HDC memDc = CreateCompatibleDC(hdc);
		RECT rcClientRect;
		GetClientRect(hwnd, &rcClientRect);
		HBITMAP bmp = CreateCompatibleBitmap(hdc, rcClientRect.right, rcClientRect.bottom);
		SelectObject(memDc, bmp);
		FillRect(memDc, &ps.rcPaint, (HBRUSH)(RGB(255,255,255)));

		Line(memDc,(rcClientRect.right-rcClientRect.left)/2+10,0,(rcClientRect.right-rcClientRect.left)/2+10,(rcClientRect.bottom-rcClientRect.top));

		Line(memDc,0,(rcClientRect.bottom-rcClientRect.top)/2+20,(rcClientRect.right-rcClientRect.left),(rcClientRect.bottom-rcClientRect.top)/2+20);


		for (int i = 0; i < countElement+1; i++)
		{
			RECT rect;
			GetWindowRect(hwnd,&rect);
			int w = rect.right-rect.left;
			int h = rect.bottom-rect.top; 
			POINT center;
			center.x = w/2;
			center.y = h/2;
			int currentW = w/zoom;
			int currentH = h/zoom;
			int left = center.x-currentW/2;
			int right = center.y + currentW/2;
			int top = center.x - currentH/2;
			int bottom = center.y + currentH/2;
			int onePX = 1*zoom;


			/*
			0:0     100:0

			0:100	100:100
			*/

			
			if (elem[i].typeElement.shape == shapeLine)
			{
				HPEN hPen = CreatePen(PS_SOLID, elem[i].typeElement.colour, elem[i].typeElement.colour);
				SelectObject(memDc, hPen);
				int x1 = elem[i].coords.point1.x;
				int y1 = elem[i].coords.point1.y;
				int x2 =  elem[i].coords.point2.x;
				int y2 =  elem[i].coords.point2.y;
				POINT f1 = Zoom(x1,y1,hwnd);
				POINT f2 = Zoom(x2,y2,hwnd);

				Line(memDc, f1.x, f1.y, f2.x, f2.y);
				DeleteObject(hPen);
			}
			if (elem[i].typeElement.shape == shapeRectangle)
			{
				HPEN hPen = CreatePen(PS_DASH, elem[i].typeElement.size, elem[i].typeElement.colour);
				SelectObject(memDc, hPen);
				HBRUSH hBrush = CreateHatchBrush(HS_BDIAGONAL, elem[i].typeElement.colour);
				SelectObject(memDc, hBrush);
				int x1 = elem[i].coords.point1.x;
				int y1 = elem[i].coords.point1.y;
				int x2 =  elem[i].coords.point2.x;
				int y2 =  elem[i].coords.point2.y;
				POINT f1 = Zoom(x1,y1,hwnd);
				POINT f2 = Zoom(x2,y2,hwnd);
				Rectangle(memDc, f1.x, f1.y, f2.x, f2.y);
				DeleteObject(hBrush);
				DeleteObject(hPen);
			}
			if (elem[i].typeElement.shape == shapeEllipse)
			{
				HBRUSH hBrush = CreateSolidBrush(elem[i].typeElement.colour);
				SelectObject(memDc, hBrush);
				int x1 = elem[i].coords.point1.x;
				int y1 = elem[i].coords.point1.y;
				int x2 =  elem[i].coords.point2.x;
				int y2 =  elem[i].coords.point2.y;
				POINT f1 = Zoom(x1,y1,hwnd);
				POINT f2 = Zoom(x2,y2,hwnd);
				Ellipse(memDc,  f1.x, f1.y, f2.x, f2.y);
				DeleteObject(hBrush);
			}
		}
		BitBlt(hdc, 0, 0, rcClientRect.right, rcClientRect.bottom, memDc, 0, 0, SRCCOPY);
		DeleteDC(memDc);
		DeleteObject(bmp);

		EndPaint(hwnd, &ps);
		
		break;
	}
	case WM_ERASEBKGND:
	{
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		elem[countElement].coords.point2.x = LOWORD(lParam);
		elem[countElement].coords.point2.y = HIWORD(lParam);

		RECT rcClientRect;
		GetClientRect(hwnd, &rcClientRect);
		rcClientRect.left = 250;
		InvalidateRect(hwnd, &rcClientRect, 1);

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
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case 0x51:
			{
				currentElement.shape = shapeLine;
				break;
			}
			case 0x57:
			{
				currentElement.shape = shapeRectangle;
				break;
			}
			case 0x45:
			{
				currentElement.shape = shapeEllipse;
				break;
			}
			case 0x53:
			{
				currentElement.colour = RGB(255, 0, 0);
				break;
			}
			case 0x44:
			{
				currentElement.colour = RGB(0, 255, 0);
				break;
			}
			case 0x46:
			{
				currentElement.colour = RGB(0, 0, 255);
				break;
			}
			case 0x52:
			{
				currentElement.colour = RGB(255, 255, 255);
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
				zoom++;
				RECT rcClientRect;
				GetClientRect(hwnd, &rcClientRect);
				rcClientRect.left = 250;
				InvalidateRect(hwnd, &rcClientRect, 1);
				break;
			}
			case VK_RIGHT:
			{
				zoom--;
				RECT rcClientRect;
				GetClientRect(hwnd, &rcClientRect);
				rcClientRect.left = 250;
				InvalidateRect(hwnd, &rcClientRect, 1);
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
