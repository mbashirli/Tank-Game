#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Application.h"
#include "GameMap.h"
#include "Positions.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_SPACE 32

struct tankPosition {
	int x, y, index;
};

class TankRenderer
{
public:
	TankRenderer( int index);
	TankRenderer();
	~TankRenderer();
	tankPosition getScreenBufferInfo();
	tankPosition getCurrentTankPosition();
	void goToXY(short x, short y);
	void renderTank();
	void renderCustomTank(short xCoord, short yCoord, short directionPoint);
	void clearCustomTank(short xCoord, short yCoord, short directionPoint);
	void setTankPosition();
	void disableConsoleCursor();
	void moveTank();
	void disableTank();
	void clearTank();
	void clearTankUp();
	void clearTankDown();
	void clearTankRight();
	void clearTankLeft();
	void clearTankLeftModified();
	void deathAnimation();
	void setTankActiveColor();
	void setTankInactiveColor();
	bool tankOnPath();
	bool borderOnPath();
	int getTankDirection();
	bool isTankDisabled();
private:
	tankPosition currentTankPosition;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	enum directionPoints { UP, DOWN, LEFT, RIGHT };
	enum colors {GREEN = 2, RED = 4, BLUE = 1};
	char tankBlock;
	int tankDirection;
	int bulletDirection;
	int player;
	int tankColor;
	int mapRightCoordinate, mapDownCoordinate;
	bool isTankActive;
	bool threadLoop;
};

