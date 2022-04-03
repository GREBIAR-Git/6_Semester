#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "WinMain.c"
#include "Elements.c"
#include "MenuTools.c"
#include "MenuSettings.c"

#define SizeElement 500
#define shapeLine 1
#define shapeRectangle 2
#define shapeEllipse 3


BOOL drawing; 
TypeElement currentElement;
Element elem[SizeElement];
int countElement;
Display display;

#include "ButtonEvents.c"

void RotateElements()
{
	Element first = elem[0];
	for (int i = 0; i < SizeElement; i++)
	{
		elem[i] = elem[i + 1];
	}
	elem[0] = first;
}

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}

PointD Zoom(double x,double y,RECT window)
{
	double w = window.right-window.left;
	double h = window.bottom-window.top;
	PointD center;
	center.x = w/2;
	center.y = h/2;
	PointD coordInZoom;
	if(display.zoom>=1)
	{
		coordInZoom.x=center.x - (center.x + display.center.x - x)/display.zoom;
		coordInZoom.y=center.y - (center.y + display.center.y - y)/display.zoom;
	}
	else if(display.zoom<=-1) 
	{
		coordInZoom.x=center.x + (center.x + display.center.x - x)*display.zoom;
		coordInZoom.y=center.y + (center.y + display.center.y - y)*display.zoom;
	} 
	else
	{
		coordInZoom.x = x;
		coordInZoom.y = y;
	}
	return coordInZoom;
}

int MenuButtonPressed(HWND hwnd)
{
	POINT cursorCoords;
	GetCursorPos(&cursorCoords);
	ScreenToClient(hwnd, &cursorCoords);

	if (CursorInsideArea(menu.buttons[0].area, cursorCoords))
	{
		ButtonLine();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[1].area, cursorCoords))
	{
		ButtonRect();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[2].area, cursorCoords))
	{
		ButtonEllipse();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[3].area, cursorCoords))
	{
		ButtonRed();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[4].area, cursorCoords))
	{
		ButtonGreen();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[5].area, cursorCoords))
	{
		ButtonBlue();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[6].area, cursorCoords))
	{
		ButtonWhite();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[7].area, cursorCoords))
	{
		ButtonSizePlus();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[8].area, cursorCoords))
	{
		ButtonSizeMinus();
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[9].area, cursorCoords))
	{
		ButtonZoomIn(hwnd);
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[10].area, cursorCoords))
	{
		ButtonZoomOut(hwnd);
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[11].area, cursorCoords))
	{
		ButtonLeft(hwnd);
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[12].area, cursorCoords))
	{
		ButtonRight(hwnd);
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[13].area, cursorCoords))
	{
		ButtonUp(hwnd);
		return 1;
	}
	else if (CursorInsideArea(menu.buttons[14].area, cursorCoords))
	{
		ButtonDown(hwnd);
		return 1;
	}
	else
	{
		return 0;
	}
}

PointD ZoomReverce(double x,double y,RECT window)
{
	double w = (window.right-window.left);
	double h = (window.bottom-window.top);
	PointD center;
	center.x = w/2;
	center.y = h/2;
	PointD coordInZoom;
	if(display.zoom>=1)
	{
		coordInZoom.x=center.x - (center.x - display.center.x/display.zoom - x)*(display.zoom);
		coordInZoom.y=center.y - (center.y - display.center.y/display.zoom - y)*(display.zoom);
	}
	else if(display.zoom<=-1)
	{
		coordInZoom.x=center.x + (center.x + display.center.x*display.zoom - x)/(display.zoom);
		coordInZoom.y=center.y + (center.y + display.center.y*display.zoom - y)/(display.zoom);
	}
	else
	{
		coordInZoom.x = x;
		coordInZoom.y = y;
	}
	return coordInZoom;
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

VOID DrawAxes(HDC memDc,RECT window)
{
	FillRect(memDc, &window, (HBRUSH)(RGB(255,255,255)));
	double w = window.right-window.left;
	double h = window.bottom-window.top;
	PointD point = Zoom(w/2,0,window);
	Line(memDc, point.x, 0, point.x, h);
	point = Zoom(0,h/2,window);
	Line(memDc,0, point.y, w, point.y);
}

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: 
	{
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		RECT window;
		GetClientRect(hwnd,&window);
		//HWND hw = CreateWindow("static", "Use keys to change tools:\nQ - Line\nW - Rectangle\nE -  Circle\n\nUse keys to change color:\nS - Red\nD - Green\nF - Blue\nR - White\n\nUse keys to change thickness:\n'I' - Thicker\n'O' - Thinner", WS_VISIBLE | WS_CHILDWINDOW , 0, 0, 250, window.bottom, hwnd, (HMENU)NULL, NULL, NULL);
		currentElement.shape = shapeLine;
		display.zoom=1;
		display.center.x = 0;
		display.center.y = 0;
		countElement = 0;
		UpdateWin1(hwnd,window);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (!MenuButtonPressed(hwnd))
		{
			if (countElement >= SizeElement - 1)
			{
				countElement--;
				RotateElements();
			}
			RECT window;
			GetClientRect(hwnd,&window);
			PointD firstPoint = ZoomReverce(LOWORD(lParam), HIWORD(lParam), window);
			elem[countElement].coords.point1 = firstPoint;
			elem[countElement].typeElement.shape = currentElement.shape;
			elem[countElement].typeElement.colour = currentElement.colour;
			elem[countElement].typeElement.size = currentElement.size;
			drawing = TRUE;
		}

		break;
	}
	case WM_MOUSEMOVE:
	{
		RECT window;
		GetClientRect(hwnd,&window);
		PointD secondPoint = ZoomReverce(LOWORD(lParam), HIWORD(lParam), window);
		elem[countElement].coords.point2 = secondPoint;
		UpdateWin1(hwnd,window);

		double w = window.right-window.left;
		double h = window.bottom-window.top;
		PointD point = Zoom(w/2,0,window);
		char str[100],str1[100],str2[100],str3[100];
		
		sprintf(str2,"%lf",point.x);
		point = Zoom(0,h/2,window);
		sprintf(str3,"%lf",point.y);				

		sprintf(str,"%lf",secondPoint.x);
		sprintf(str1,"%lf",secondPoint.y);
		strcat(str," : ");
		strcat(str,str1);
		strcat(str," ; ");
		strcat(str,str2);
		strcat(str," : ");
		strcat(str,str3);
		//SetWindowText(hwnd,str);
		break;
	}
	case WM_LBUTTONUP:
	{
		drawing = FALSE;

		if (countElement < SizeElement - 1) countElement++;

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
		DrawAxes(memDc, window);
		for (int i = 0; i < countElement+1; i++)
		{
			double x1 = elem[i].coords.point1.x;
			double y1 = elem[i].coords.point1.y;
			double x2 = elem[i].coords.point2.x;
			double y2 = elem[i].coords.point2.y;
			PointD f1 = Zoom(x1,y1,window);
			PointD f2 = Zoom(x2,y2,window);
			if (elem[i].typeElement.shape == shapeLine)
			{
				HPEN hPen = CreatePen(PS_SOLID, elem[i].typeElement.size, elem[i].typeElement.colour);
				SelectObject(memDc, hPen);
				Line(memDc, f1.x, f1.y, f2.x, f2.y);
				DeleteObject(hPen);
			}
			else if (elem[i].typeElement.shape == shapeRectangle)
			{
				HPEN hPen = CreatePen(PS_DASH, elem[i].typeElement.size, elem[i].typeElement.colour);
				SelectObject(memDc, hPen);
				HBRUSH hBrush = CreateHatchBrush(HS_BDIAGONAL, elem[i].typeElement.colour);
				SelectObject(memDc, hBrush);
				Rectangle(memDc, f1.x, f1.y, f2.x, f2.y);
				DeleteObject(hBrush);
				DeleteObject(hPen);
			}
			else if (elem[i].typeElement.shape == shapeEllipse)
			{
				HBRUSH hBrush = CreateSolidBrush(elem[i].typeElement.colour);
				SelectObject(memDc, hBrush);
				Ellipse(memDc,  f1.x, f1.y, f2.x, f2.y);
				DeleteObject(hBrush);
			}
		}

		char str[4];
		sprintf(str,"%d",countElement);
		SetWindowText(hwnd, str);
		
		DrawUI(memDc, window);

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
			case VK_OEM_PLUS:
			{
				ButtonZoomIn(hwnd);
				break;
			}
			case VK_OEM_MINUS:
			{
				ButtonZoomOut(hwnd);
				break;
			}
			case VK_LEFT:
			{
				ButtonLeft(hwnd);
				break;
			}
			case VK_RIGHT:
			{
				ButtonRight(hwnd);
				break;
			}
			case VK_UP:
			{
				ButtonUp(hwnd);
				break;
			}
			case VK_DOWN:
			{
				ButtonDown(hwnd);
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
