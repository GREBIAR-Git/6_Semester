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
BOOL zooming;

POINT p1;

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
	PointD center;
	center.x = (window.right-window.left)/2.0;
	center.y = (window.bottom-window.top)/2.0;
	PointD inZoom;
	inZoom.x=center.x + (center.x + display.center.x - x)*display.zoom.x;
	inZoom.y=center.y + (center.y + display.center.y - y)*display.zoom.y;
	return inZoom;
}

PointD ZoomReverce(double x,double y,RECT window)
{
	PointD center;
	center.x = (window.right-window.left)/2.0;
	center.y = (window.bottom-window.top)/2.0;
	PointD inZoom;
	inZoom.x=center.x + (center.x + display.center.x*display.zoom.x - x)/(display.zoom.x);
	inZoom.y=center.y + (center.y + display.center.y*display.zoom.y - y)/(display.zoom.y);
	return inZoom;
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

VOID ZoomRectangle(RECT window,int x1, int y1, int x2, int y2)
{
	if(fabs(x1-x2)!=0&&fabs(y1-y2)!=0)
	{
		PointD f1 = ZoomReverce(x1,y1,window);
		PointD f2 = ZoomReverce(x2,y2,window);
		display.zoom.x = fabs(display.zoom.x)*(fabs((window.right-window.left)/fabs(x1-x2)));
		display.zoom.y = fabs(display.zoom.y)*(fabs((window.bottom-window.top)/fabs(y1-y2)));
		double min = min(f1.x,f2.x);
		display.center.x=((min-window.right/2.0)+fabs(f1.x-f2.x)/2);
		min = min(f1.y,f2.y);
		display.center.y=(min-window.bottom/2.0)+fabs(f1.y-f2.y)/2;
	}
}

VOID DrawAxes(HDC memDc,RECT window)
{
	double w = window.right-window.left;
	double h = window.bottom-window.top;
	PointD point = Zoom(w/2,0,window);
	HPEN hPen = CreatePen(PS_DASH,2,RGB(0, 0, 0));
	SelectObject(memDc, hPen);
	Line(memDc, point.x, 0, point.x, h);
	point = Zoom(0,h/2,window);
	Line(memDc,0, point.y, w, point.y);
	DeleteObject(hPen);
}

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: 
	{
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		RECT window;
		GetClientRect(hwnd,&window);
		currentElement.shape = shapeLine;
		display.zoom.x=1;
		display.zoom.y=1;
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
		break;
	}
	case WM_LBUTTONUP:
	{
		drawing = FALSE;

		if (countElement < SizeElement - 1) 
			countElement++;

		break;
	}
	case WM_RBUTTONDOWN:
	{
		zooming = TRUE;
		p1.x = LOWORD(lParam);
		p1.y = HIWORD(lParam);
		break;
	}
	case WM_RBUTTONUP:
	{
		if (zooming)
		{
			zooming = FALSE;
			RECT window;  
			GetClientRect(hwnd, &window);
			ZoomRectangle(window, p1.x, p1.y, LOWORD(lParam), HIWORD(lParam));
			UpdateWin(hwnd);
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
		if(zooming)
		{
			double x1 = elem[countElement].coords.point2.x;
			double y1 = elem[countElement].coords.point2.y;
			PointD f1 = Zoom(x1,y1,window);
			HPEN hPen = CreatePen(PS_DASH,3,RGB(255, 0, 0));
			SelectObject(memDc, hPen);
			Rectangle(memDc, p1.x, p1.y, f1.x, f1.y);
			DeleteObject(hPen);
		}
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
		GetClientRect(hwnd, &window);
		char str[4];
		sprintf(str,"Zx-%lf; Zy-%lf; Cx-%lf; Cy-%lf;clientWin; X-%lu;Y-%lu;",display.zoom.x,display.zoom.y,display.center.x,display.center.y,window.right,window.bottom);
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
			case VK_DELETE:
			{
				display.zoom.x*=1.1;
				UpdateWin(hwnd);
				break;
			}
			case VK_INSERT:
			{
				display.zoom.x/=1.1;;
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
