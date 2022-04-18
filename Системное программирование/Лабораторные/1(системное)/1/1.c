#include <windows.h>
#include "WinMain.c"

VOID UpdateWin(HWND hwnd)
{
	RECT window;  
	GetClientRect(hwnd, &window);
	InvalidateRect(hwnd, &window, 1);
}

VOID UpdateWin1(HWND hwnd,RECT window)
{
	InvalidateRect(hwnd, &window, 1);
}

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: 
	{
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		RECT window, groupBox;
		GetClientRect(hwnd, &window);
		HWND ta = CreateWindow("BUTTON", "Time allocation", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,0, 0, window.right/2, window.bottom*2/3,hwnd, 0, NULL, 0);
		GetClientRect(ta, &groupBox);
		CreateWindow("STATIC","Thread 1",WS_VISIBLE | WS_CHILD,0,groupBox.bottom/7,groupBox.right,groupBox.bottom/7,ta,(HMENU)3,NULL,NULL);
		CreateWindow("SCROLLBAR","Thread 1",WS_VISIBLE | WS_CHILD,0,groupBox.bottom*2/7,groupBox.right,groupBox.bottom/7,ta,(HMENU)3,NULL,NULL);
		CreateWindow("STATIC","Thread 2",WS_VISIBLE | WS_CHILD,0,groupBox.bottom*3/7,groupBox.right,groupBox.bottom/7,ta,(HMENU)3,NULL,NULL);
		CreateWindow("SCROLLBAR","Thread 1",WS_VISIBLE | WS_CHILD,0,groupBox.bottom*4/7,groupBox.right,groupBox.bottom/7,ta,(HMENU)3,NULL,NULL);
		CreateWindow("STATIC","Thread 3",WS_VISIBLE | WS_CHILD,0,groupBox.bottom*5/7,groupBox.right,groupBox.bottom/7,ta,(HMENU)3,NULL,NULL);
		CreateWindow("SCROLLBAR","Thread 1",WS_VISIBLE | WS_CHILD,0,groupBox.bottom*6/7,groupBox.right,groupBox.bottom/7,ta,(HMENU)3,NULL,NULL);
		int lastGB = groupBox.right;
		HWND ta1 = CreateWindow("BUTTON", "Time allocation", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,0, 0, window.right/2, window.bottom*2/3,hwnd, 0, NULL, 0);
		
		GetClientRect(ta1, &groupBox);
		CreateWindow("STATIC","Thread 1",WS_VISIBLE | WS_CHILD,lastGB,groupBox.bottom/7,groupBox.right,groupBox.bottom/7,ta1,(HMENU)3,NULL,NULL);
		CreateWindow("STATIC","Thread 1",WS_VISIBLE | WS_CHILD,lastGB,groupBox.bottom*2/7,groupBox.right,groupBox.bottom/7,ta1,(HMENU)3,NULL,NULL);
		CreateWindow("STATIC","Thread 2",WS_VISIBLE | WS_CHILD,lastGB,groupBox.bottom*3/7,groupBox.right,groupBox.bottom/7,ta1,(HMENU)3,NULL,NULL);
		CreateWindow("STATIC","Thread 1",WS_VISIBLE | WS_CHILD,lastGB,groupBox.bottom*4/7,groupBox.right,groupBox.bottom/7,ta1,(HMENU)3,NULL,NULL);
		CreateWindow("STATIC","Thread 3",WS_VISIBLE | WS_CHILD,lastGB,groupBox.bottom*5/7,groupBox.right,groupBox.bottom/7,ta1,(HMENU)3,NULL,NULL);
		CreateWindow("STATIC","Thread 1",WS_VISIBLE | WS_CHILD,lastGB,groupBox.bottom*6/7,groupBox.right,groupBox.bottom/7,ta1,(HMENU)3,NULL,NULL);

		CreateWindow("BUTTON", "Thread operation", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,window.right/2, 0, window.right/4, window.bottom*2/3,hwnd, 0, NULL, 0);
		CreateWindow("BUTTON", "CONTEXT", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,window.right/4+window.right/2, 0, window.right/4, window.bottom,hwnd, 0, NULL, 0);
		CreateWindow("BUTTON", "Thread priority", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,0, window.bottom*2/3, window.right/2, window.bottom,hwnd, 0, NULL, 0);
		CreateWindow("BUTTON", "Info about thread", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,window.right/2, window.bottom*2/3, window.right/4, window.bottom,hwnd, 0, NULL, 0);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		break;
	}
	case WM_MOUSEMOVE:
	{
		break;
	}
	case WM_LBUTTONUP:
	{
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
		break;
	}
	case WM_KEYUP:
	{
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
