#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
int shape; BOOL drawing; COLORREF colour; int size;
#define N 500
INT GETLineLength(int x1, int y1, int x2, int y2);
typedef struct COORDINATESS
{
	POINT point1;
	POINT point2;
}COORDS;
typedef struct ELEMENTS
{
	COORDS coords;
	int shape;
	COLORREF colour;
	int size;
}ELEMENT;
ELEMENT elem[N];

int schetchik;

PAINTSTRUCT ps;
HPEN hPen;
HBRUSH hBrush;
BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}

POINT CalculateDashCoords(int x1, int y1, int x2, int y2, int dashLength)
{
	float m = (y2-y1)/(float)(x2-x1);
	POINT dash;
	dash.x = round(dashLength * m);
	dash.y = (dash.x-x1)/(float)(x2-x1)*(y2-y1)+y1;
	return dash;
}


BOOL Rectangle1(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}

BOOL LinePro(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2)
{
	int length = GETLineLength(x1, y1, x2, y2);
	int dash = 5;
	POINT first;
	POINT second;
	first.x = x1;
	first.y = y1;
	MoveToEx(hdc, x1, y1, NULL);
	for (int i=0;i<length;i+=dash*2)
	{
		second = CalculateDashCoords(first.x, first.y, x2, y2, dash);
		LineTo(hdc, second.x, second.y);

		char text[1000];
		itoa(second.x, text, 10);
		//SetWindowText(hwnd, text);
		char text1[1000];
		itoa(second.y, text1, 10);
		SetWindowText(hwnd, strcat(strcat(text,":"),text1));
		first = CalculateDashCoords(second.x, second.y, x2, y2, dash);
		MoveToEx(hdc, first.x, first.y,NULL);
	}
}



INT GETLineLength(int x1, int y1, int x2, int y2)
{
	return sqrt(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

LRESULT CALLBACK WndPrc(HWND hw, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_MOUSEMOVE:
		break;
	case WM_PAINT:
		break;
	}
	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: {
		schetchik = 0;
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		RECT window;  GetClientRect(hwnd, &window);
		HWND hw = CreateWindow("static", "Use keys to change tools:\nQ - Line\nW - Rectangle\nE -  Circle\n\nUse keys to change color:\nS - Red\nD - Green\nF - Blue\nR - White\n\nUse keys to change thickness:\n'I' - Thicker\n'O' - Thinner", WS_VISIBLE | WS_CHILDWINDOW , 0, 0, 250, window.bottom, hwnd, (HMENU)NULL, NULL, NULL);
		ShowWindow(hw, SW_SHOW);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		elem[schetchik].coords.point1.x = LOWORD(lParam);
		elem[schetchik].coords.point1.y = HIWORD(lParam);
		elem[schetchik].shape = shape;
		elem[schetchik].colour = colour;
		elem[schetchik].size = size;
		drawing = TRUE;
		break;
	}
	case WM_PAINT:
	{
		if (drawing)
		{
			HDC hdc = BeginPaint(hwnd, &ps);
			HDC memDc = CreateCompatibleDC(hdc);
			RECT rcClientRect;
			GetClientRect(hwnd, &rcClientRect);
			HBITMAP bmp = CreateCompatibleBitmap(hdc, rcClientRect.right, rcClientRect.bottom);
			SelectObject(memDc, bmp);
			FillRect(memDc, &ps.rcPaint, (HBRUSH)(RGB(255,255,255)));

			for (int i = 0; i < schetchik+1; i++)
			{
				if (elem[i].shape == 5)
				{
					hPen = CreatePen(PS_SOLID, elem[i].size, elem[i].colour);
					SelectObject(memDc, hPen);
					LinePro(hwnd, memDc, elem[i].coords.point1.x, elem[i].coords.point1.y, elem[i].coords.point2.x, elem[i].coords.point2.y);
					//Line(memDc, elem[i].coords.point1.x, elem[i].coords.point1.y, elem[i].coords.point2.x, elem[i].coords.point2.y);
					DeleteObject(hPen);
				}
				if (elem[i].shape == 10)
				{
					hBrush = CreateSolidBrush(elem[i].colour);
					SelectObject(memDc, hBrush);

					Rectangle(memDc, elem[i].coords.point1.x, elem[i].coords.point1.y, elem[i].coords.point2.x, elem[i].coords.point2.y);
					DeleteObject(hBrush);
				}
				if (elem[i].shape == 15)
				{
					hBrush = CreateSolidBrush(elem[i].colour);
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
		elem[schetchik].coords.point2.x = LOWORD(lParam);
		elem[schetchik].coords.point2.y = HIWORD(lParam);

		RECT rcClientRect;
		GetClientRect(hwnd, &rcClientRect);
		rcClientRect.left = 250;
		InvalidateRect(hwnd, &rcClientRect, 1);

		break;
	}
	case WM_LBUTTONUP:
	{
		drawing = FALSE;
		if (schetchik < N)
		{
			schetchik++;
		}
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 0x51:
		{
			shape = 5;
			break;
		}
		case 0x57:
		{
			shape = 10;
			break;
		}
		case 0x45:
		{
			shape = 15;
			break;
		}
		case 0x53:
		{
			colour = RGB(255, 0, 0);
			break;
		}
		case 0x44:
		{
			colour = RGB(0, 255, 0);
			break;
		}
		case 0x46:
		{
			colour = RGB(0, 0, 255);
			break;
		}
		case 0x52:
		{
			colour = RGB(255, 255, 255);
			break;
		}
		case 0x49:
		{
			if (size < 228)
			size++;
			break;
		}
		case 0x4F:
		{
			if (size > 1)
			size--;
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




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;


	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);


	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Lab4", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		720,
		NULL, NULL, hInstance, NULL);

	
	//CreateWindow("button", "2222", WS_VISIBLE | WS_CHILD, 500, 200, 200, 20, hwnd, NULL, NULL, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}


	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
