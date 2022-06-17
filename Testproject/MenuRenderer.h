#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include "Menu.h"
#include <conio.h>
#include "Config.h"
#include <sstream>

#define KEY_UP 72
#define KEY_DOWN 80

struct MenuStartPosition {
	int x, y;
};

class MenuRenderer
{
public:
	MenuRenderer(Menu* _menu);
	MenuStartPosition getScreenBufferInfo();
	void go_to_xy(short x, short y);
	void outCenteredText();
	void render();
	void clearTerminal();
	void showConsoleCursor(bool showFlag);
	void setMenuActiveColor(int menuColor);
	void setTitleActiveColor();
	void setTitleInactiveColor();
	void updateActiveTitleID();
	void updateMenuPosition();
	bool consoleWindowSizeChanged();
	bool menuColorChanged();
	int getActiveTitleID();
private:
	Menu* menu;
	MenuStartPosition menuPosition;
	int activeTitleID;
	int menuColor;
	bool isMenuColorChanged;
};

