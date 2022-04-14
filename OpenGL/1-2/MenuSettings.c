int DrawUI(HDC hdc, RECT menuArea);

int DrawUI(HDC hdc, RECT window)
{
    DrawDebug(hdc, window);

    //      settings {
    int marginTop = 0;
    int width = 200;
    int height = 700;
    int marginLeft = window.right - width;
    BOOL vertical = TRUE;
    int buttonSize = 35;
    //      }

    RECT menuArea;
	menuArea.left = marginLeft;
	menuArea.right = menuArea.left + width;
	menuArea.top = marginTop;
    menuArea.bottom = window.bottom;
	DrawMenu(hdc, menuArea, vertical, buttonSize, "Menu");
	menu.buttonsLength = 0;
    DrawMenuButton(hdc, "Line");
    DrawMenuButton(hdc, "Rectangle");
    DrawMenuButton(hdc, "Circle");
    DrawMenuButton(hdc, "Red");
    DrawMenuButton(hdc, "Green");
    DrawMenuButton(hdc, "Blue");
    DrawMenuButton(hdc, "White");
    DrawMenuButton(hdc, "Size+");
    DrawMenuButton(hdc, "Size-");
    DrawMenuButton(hdc, "Zoom in");
    DrawMenuButton(hdc, "Zoom out");
    DrawMenuButton(hdc, "Left");
    DrawMenuButton(hdc, "Right");
    DrawMenuButton(hdc, "Up");
    DrawMenuButton(hdc, "Down");
}