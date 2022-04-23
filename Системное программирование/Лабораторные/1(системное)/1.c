#include <windows.h>
#include <stdio.h>

HWND hwndMain;

typedef struct OurThread
{
	HANDLE hThread;
	HBITMAP bitMap;
	int StatesImage;
}OURTHREAD;

OURTHREAD thread[3];

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void RegClass(WNDPROC Proc,LPCTSTR szName)
{
  WNDCLASSA wcl;
  memset(&wcl, 0, sizeof(WNDCLASS));
  wcl.lpszClassName = szName;
  wcl.lpfnWndProc = Proc;
  wcl.hbrBackground = (HBRUSH)(COLOR_WINDOW + 23);
  wcl.hIcon = LoadIcon(NULL,IDI_ASTERISK);
  wcl.hCursor = LoadCursor(NULL,IDC_ARROW);
  RegisterClassA(&wcl);
}

DWORD WINAPI ThreadOneProc(LPVOID lpParam)
{
	while(TRUE)
	{
		Sleep(200);
		switch(thread[0].StatesImage){
		case 0:

		thread[0].bitMap = (HBITMAP)LoadImage(NULL, "a2\\0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
		case 1:
		thread[0].bitMap = (HBITMAP)LoadImage(NULL, "a2\\1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
		} 
		thread[0].StatesImage++;
		if(thread[0].StatesImage == 2)
		thread[0].StatesImage = 0;
		InvalidateRect(hwndMain,NULL,0);
	}
	ExitThread(0);
	return 0;
}

DWORD WINAPI ThreadTwoProc(LPVOID lpParam)
{
	while(TRUE)
	{
		Sleep(200);
		switch(thread[1].StatesImage){
		case 0:
		thread[1].bitMap = (HBITMAP)LoadImage(NULL, "a2\\0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
		case 1:
		thread[1].bitMap = (HBITMAP)LoadImage(NULL, "a2\\1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
		} 
		thread[1].StatesImage++;
		if(thread[1].StatesImage == 2)
		thread[1].StatesImage = 0;
		InvalidateRect(hwndMain,NULL,0);
	}
	return 0;
}

DWORD WINAPI ThreadThreeProc(LPVOID lpParam)
{
	while(TRUE)
	{
		Sleep(200);
		switch(thread[2].StatesImage){
		thread[2].bitMap = (HBITMAP)LoadImage(NULL, "a2\\0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
		case 1:
		thread[2].bitMap = (HBITMAP)LoadImage(NULL, "a2\\1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
		} 
		thread[2].StatesImage++;
		if(thread[2].StatesImage == 2)
		thread[2].StatesImage = 0;
		InvalidateRect(hwndMain,NULL,0);
	}
	return 0;
}

DWORD WINAPI WindowMain(LPVOID lpParam)
{
	RegClass(FrameWndProc,"MainWin");
	HWND hwnd = CreateWindow("MainWin", "Main Window", WS_OVERLAPPEDWINDOW, 40, 40, 1100, 720, NULL, NULL, NULL, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int main()
{
	HANDLE threadM =  CreateThread( NULL, 0, WindowMain,NULL,CREATE_ALWAYS,NULL);
	thread[0].hThread = CreateThread( NULL, 0, ThreadOneProc,NULL,CREATE_SUSPENDED,NULL);
	thread[1].hThread = CreateThread( NULL, 0, ThreadTwoProc,NULL,CREATE_SUSPENDED,NULL);
	thread[2].hThread = CreateThread( NULL, 0, ThreadThreeProc,NULL,CREATE_SUSPENDED,NULL);
	int menuItem, menuItem2;
	while(TRUE)
	{
		printf("\nmenu:");
		scanf("%d",&menuItem);
		if(menuItem==0)
		{
			printf("\nthread:");
			scanf("%d",&menuItem2);
			CONTEXT ct; 
			GetThreadContext(thread[menuItem2].hThread, &ct);
			printf("%lu",ct.ContextFlags);
		}
		else if(menuItem==1)
		{
			printf("\nthread:");
			scanf("%d",&menuItem2);

			printf("\npriority level:");
			int priority;
			scanf("%d",&priority);
			SetThreadPriority(thread[menuItem2].hThread,priority);

		}
		else if(menuItem==2)
		{
			printf("\nthread:");
			scanf("%d",&menuItem2);
			printf("\n0-Resume, 1-suspend, 2-finish:");
			int stage;
			scanf("%d",&stage);
			if(stage==0)
			{
				ResumeThread(thread[menuItem2].hThread);
			}
			else if(stage == 1)
			{
				SuspendThread(thread[menuItem2].hThread);
			}
			else
			{
				TerminateThread(thread[menuItem2].hThread,0);
			}
		}
		else if(menuItem==3)
		{
			printf("\nthread:");
			scanf("%d",&menuItem2);
			FILETIME creationTime,exitTime,kernelTime,userTime;
			GetThreadTimes(thread[menuItem2].hThread,&creationTime, &exitTime,&kernelTime,&userTime); 
			SYSTEMTIME stUTC,stLocal;
			FileTimeToSystemTime(&creationTime, &stUTC); 
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal); 
			printf("Time of creation of thread %d: %02d/%02d/%d %02d:%02d:%02d\r\n\n", menuItem2+1, stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
			FileTimeToSystemTime(&exitTime, &stUTC); 
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal); 
			printf("Time of finished of thread %d: %02d/%02d/%d %02d:%02d:%02d\r\n\n", menuItem2+1, stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
		}
	}
}


LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE: 
	{
		hwndMain = hwnd;
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		RECT window, groupBox;
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
		BITMAP bmp;
		RECT window;
		GetClientRect(hwnd,&window);
		if(thread[0].bitMap!=NULL)
		{
			GetObject(thread[0].bitMap,sizeof(bmp),&bmp);
			SelectObject(memDc,thread[0].bitMap);
			BitBlt(hdc, 0,0,window.right/2,window.bottom,memDc,0,0,SRCCOPY);
		}
		if(thread[1].bitMap!=NULL)
		{
			GetObject(thread[1].bitMap,sizeof(bmp),&bmp);
			SelectObject(memDc,thread[1].bitMap);
			BitBlt(hdc, window.right/2,0,window.right/2,window.bottom/2,memDc,0,0,SRCCOPY);
		}
		if(thread[2].bitMap!=NULL)
		{
			GetObject(thread[2].bitMap,sizeof(bmp),&bmp);
			SelectObject(memDc,thread[2].bitMap);
			BitBlt(hdc, window.right/2,window.bottom/2,window.right/2,window.bottom/2,memDc,0,0,SRCCOPY);
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
