#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include "Menu.h"
#include <conio.h>
#include "Config.h"

#define KEY_UP 72
#define KEY_DOWN 80

struct MenuStartPosition {
	int x, y;
};


class MenuRenderer
{
public:
	MenuRenderer(Menu* _menu);
	void go_to_xy(short x, short y);
	MenuStartPosition getScreenBufferInfo();
	void outCenteredText();
	void render();
	void clearTerminal();
	void showConsoleCursor(bool showFlag);
	void setMenuActiveColor(std::string menuColor);
	void setTitleActiveColor();
	void setTitleInactiveColor();
	void updateActiveTitleID();
	bool consoleWindowSizeChanged();
	bool menuColorChanged();
	void updateMenuPosition();
	int getActiveTitleID();

private:
	MenuStartPosition menuPosition;
	int activeTitleID;
	int menuColor;
	bool isMenuColorChanged;
	Menu* menu;
};

