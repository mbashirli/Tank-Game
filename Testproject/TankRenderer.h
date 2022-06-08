#pragma once
#include <windows.h>
#include "Tank.h"
#include <iostream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_SPACE 32

struct startPosition {
	int x, y;

};

class TankRenderer
{
public:
	TankRenderer();
	~TankRenderer();
	startPosition getScreenBufferInfo();
	void goToXY(short x, short y);
	void renderTank();
	void setTankPosition();
	void disableConsoleCursor();
	void moveTank();
	void clearTankVertical();
	void clearTankHorizontal();
	void renderBullet();

	int getTerminalEastCoordinate();
	int getTerminalSouthCoordinate();
private:
	startPosition currentTankPosition;
	startPosition currentBulletPosition;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	enum directionPoints { UP, DOWN, LEFT, RIGHT };
	char tankBlock;
	int tankDirection;
	int bulletDirection;
};

