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


BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: {
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
		if (drawing)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			HDC memDc = CreateCompatibleDC(hdc);
			RECT rcClientRect;
			GetClientRect(hwnd, &rcClientRect);
			HBITMAP bmp = CreateCompatibleBitmap(hdc, rcClientRect.right, rcClientRect.bottom);
			SelectObject(memDc, bmp);
			FillRect(memDc, &ps.rcPaint, (HBRUSH)(RGB(255,255,255)));

			for (int i = 0; i < countElement+1; i++)
			{
				if (elem[i].typeElement.shape == shapeLine)
				{
					HPEN hPen = CreatePen(PS_SOLID, elem[i].typeElement.size, elem[i].typeElement.colour);
					SelectObject(memDc, hPen);
					Line(memDc, elem[i].coords.point1.x, elem[i].coords.point1.y, elem[i].coords.point2.x, elem[i].coords.point2.y);
					DeleteObject(hPen);
				}
				if (elem[i].typeElement.shape == shapeRectangle)
				{
					HPEN hPen = CreatePen(PS_DASH, elem[i].typeElement.size, elem[i].typeElement.colour);
					SelectObject(memDc, hPen);
					HBRUSH hBrush = CreateHatchBrush(HS_BDIAGONAL, elem[i].typeElement.colour);
					SelectObject(memDc, hBrush);
					Rectangle(memDc, elem[i].coords.point1.x, elem[i].coords.point1.y, elem[i].coords.point2.x, elem[i].coords.point2.y);
					DeleteObject(hBrush);
					DeleteObject(hPen);
				}
				if (elem[i].typeElement.shape == shapeEllipse)
				{
					HBRUSH hBrush = CreateSolidBrush(elem[i].typeElement.colour);
					SelectObject(memDc, hBrush);
					Ellipse(memDc, elem[i].coords.point1.x, elem[i].coords.point1.y, elem[i].coords.point2.x, elem[i].coords.point2.y);
					DeleteObject(hBrush);
				}
			}

			BitBlt(hdc, 0, 0, rcClientRect.right, rcClientRect.bottom, memDc, 0, 0, SRCCOPY);
			DeleteDC(memDc);
			DeleteObject(bmp);

			EndPaint(hwnd, &ps);
		}
		break;
	}
	case WM_ERASEBKGND:
	{
		return 1;
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
			currentElement.shape = shapeEllipse
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
