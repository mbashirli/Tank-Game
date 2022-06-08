#pragma once
#include <windows.h>
#include "Tank.h"
#include <iostream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75

struct tankStartPosition {
	int x, y;
};

class TankRenderer
{
public:
	TankRenderer();
	~TankRenderer();
	tankStartPosition getScreenBufferInfo();
	void goToXY(short x, short y);
	void renderTank();
	void disableConsoleCursor();
	void moveTank();
	void clearTankVertical();
	void clearTankHorizontal();
	void clearTank();
private:
	tankStartPosition currentTankPosition;
	enum tankDirectionPoints { NORTH, SOUTH, EAST, WEST };
	char tankBlock;
	int tankDirection;
};

