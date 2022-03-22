INT GETLineLength(int x1, int y1, int x2, int y2)
{
	return sqrt(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

POINT CalculateDashCoords(int x1, int y1, int x2, int y2, int dashLength)
{
	float m = (y2-y1)/(float)(x2-x1);
	POINT dash;
	dash.x = round(dashLength * m);
	dash.y = (dash.x-x1)/(float)(x2-x1)*(y2-y1)+y1;
	return dash;
}

BOOL LinePro(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2)
{
	int length = GETLineLength(x1, y1, x2, y2);
	char text[1000];
	itoa(length, text, 10);
	SetWindowText(hwnd, text);
	int dash = 10;
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
		SetWindowText(hwnd, text);
		char text1[1000];
		itoa(second.y, text1, 10);
		SetWindowText(hwnd, strcat(strcat(text,":"),text1));
		first = CalculateDashCoords(second.x, second.y, x2, y2, dash);
		MoveToEx(hdc, first.x, first.y,NULL);
		first = CalculateDashCoords(first.x, first.y, x2, y2, dash);
		MoveToEx(hdc, first.x, first.y,NULL);
	}
}