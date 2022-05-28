#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include "Menu.h"


struct MenuStartPosition {
	int x, y;
};


class MenuRenderer
{
public:
	MenuRenderer();
	~MenuRenderer();
	void go_to_xy(); // based on spX & spY
	void go_to_xy(short x, short y);
	void get_screen_buffer_info();
	void out_centered_text(std::vector <std::string> input);
	void render(Menu* m1);
	void clear_terminal(Menu* m1);
	void ShowConsoleCursor(bool showFlag);
	void ClearScreen();
private:
	MenuStartPosition struct_coordinates;
	short tempX = 0, tempY = 0;
};

