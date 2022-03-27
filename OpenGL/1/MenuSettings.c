int DrawUI(HDC hdc, RECT menuArea);

int DrawUI(HDC hdc, RECT window)
{
    //      settings {
    int marginTop = 0;
    int marginLeft = 0;
    int width = 200;
    BOOL vertical = TRUE;
    int buttonSize = 35;
    //      }

    RECT menuArea;
	menuArea.left = marginLeft;
	menuArea.right = menuArea.left + width;
	menuArea.top = marginTop;
	DrawMenu(hdc, menuArea, vertical, buttonSize, "Menu");
	menu.buttonsLength = 0;
    DrawMenuButton(hdc, "Line");
    DrawMenuButton(hdc, "Rectangle");
    DrawMenuButton(hdc, "Circle");
}
