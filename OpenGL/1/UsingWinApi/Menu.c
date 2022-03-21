struct area
{
	POINT topLeft;
	POINT botRight;
};

struct button
{
	char title[100];
	struct area area;
};

struct menu
{
	char title[100];
	struct area area;
	struct button buttons[100];
	BOOL vertical;
	int buttonSize;
	int buttonsLength;
};

struct menu menu;

int CursorInside(RECT area, POINT cursorCoords);
int DrawArea(HDC hdc, RECT area);
int DrawMenu(HDC hdc, RECT menuArea, BOOL vertical, int buttonSize, char title[100]);
int DrawMenuButton(HDC hdc, char title[100]);

struct area RectToArea(RECT rect);

int CursorInside(RECT area, POINT cursorCoords)
{
	if (cursorCoords.x > area.left && cursorCoords.x < area.right && cursorCoords.y < area.bottom && cursorCoords.y > area.top)
	{
		return TRUE;
	}
	return FALSE;
}

int DrawArea(HDC hdc, RECT area)
{
	COLORREF colorBorder = RGB(0,0,0);
	COLORREF colorFill = RGB(100,100,100);

	HPEN hPen = CreatePen(PS_SOLID, 1, colorBorder);
	SelectObject(hdc, hPen);
	HBRUSH hBrush = CreateSolidBrush(colorFill);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, area.left, area.top, area.right, area.bottom);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

int DrawMenu(HDC hdc, RECT menuArea, BOOL vertical, int buttonSize, char title[100])
{
	strcpy(menu.title, title);
	
	DrawArea(hdc, menuArea);
	menu.area = RectToArea(menuArea);
	menu.vertical = vertical;
	menu.buttonSize = buttonSize;
}

int DrawMenuButton(HDC hdc, char title[100])
{
	strcpy(menu.buttons[menu.buttonsLength].title,title);

	int margin = 5;

	RECT buttonArea;
	if (menu.vertical)
	{
		buttonArea.left = menu.area.topLeft.x + margin;
		buttonArea.right = menu.area.botRight.x - margin;
		buttonArea.top = menu.buttonsLength * (menu.buttonSize + 2 * margin) + margin;
		buttonArea.bottom = buttonArea.top + menu.buttonSize;
	}
	else
	{
		buttonArea.top = menu.area.topLeft.y + margin;
		buttonArea.bottom = menu.area.botRight.y - margin;
		buttonArea.left = menu.buttonsLength * (menu.buttonSize + 2 * margin) + margin;
		buttonArea.right = buttonArea.left + menu.buttonSize;
	}
	DrawArea(hdc, buttonArea);
	menu.buttons[menu.buttonsLength].area = RectToArea(buttonArea);
	menu.buttonsLength ++;
}

struct area RectToArea(RECT rect)
{
	struct area area;
	area.topLeft.x = rect.left;
	area.topLeft.y = rect.top;
	area.botRight.x = rect.right;
	area.botRight.y = rect.bottom;
}

int DrawUI(HDC hdc)
{
	RECT menuArea;
	menuArea.left = 500;
	meunArea.right = 700;
	menuArea.top = 10;
	menuArea.bottom = 900;
	DrawMenu(memDc, menuArea, TRUE, 35, "Menu");
}