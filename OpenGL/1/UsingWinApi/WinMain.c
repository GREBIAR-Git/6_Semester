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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	RegClass(FrameWndProc,"MainWin");
	HWND hwnd = CreateWindow("MainWin", "Main Window", WS_OVERLAPPEDWINDOW, 40, 40, 1100, 720, NULL, NULL, NULL, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}