#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include "Menu.h"
#include <conio.h>

#define UP 72
#define DOWN 80
#define ENTER 13

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
	void updateMenuPosition();
	int getActiveTitleID();

private:
	MenuStartPosition menuPosition;
	int activeTitleID;
	int menuColor;
	Menu* menu;
};

