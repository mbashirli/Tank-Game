#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Application.h"
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
	TankRenderer(int player, int index);
	~TankRenderer();
	tankPosition getScreenBufferInfo();
	tankPosition getCurrentTankPosition();
	void goToXY(short x, short y);
	void renderTank();
	void setTankPosition();
	void disableConsoleCursor();
	void moveTank();
	void disableTank();
	void clearTankVertical();
	void clearTankHorizontal();
	void clearTankUp();
	void clearTankDown();
	void clearTankRight();
	void clearTankLeft();
	void deathAnimation();
	void setTankActiveColor();
	void setTankInactiveColor();
	bool onPath();
	int getTankDirection();
	bool isTankDisabled();
private:
	tankPosition currentTankPosition;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	enum directionPoints { UP, DOWN, LEFT, RIGHT };
	enum players { PRIMARY, SECONDARY, NPC };
	enum colors {GREEN = 2, RED = 4, BLUE = 1};
	char tankBlock;
	int tankDirection;
	int bulletDirection;
	int player;
	int tankColor;
	int terminalX, terminalY;
	bool isTankActive;
	bool threadLoop;
};

