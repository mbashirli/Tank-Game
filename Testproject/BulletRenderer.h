#pragma once
#include <windows.h>
#include <conio.h>
#include <vector>
#include "TankRenderer.h"
#include "Application.h"
#include "Positions.h".
#include "GameMap.h"

#define tankBlock 219

struct BulletPosition {
	int x, y, direction, index = 0;
	bool endRender = false;
};

class BulletRenderer
{
public:
	BulletRenderer(TankRenderer* tank);
	void checkBullet(std::vector<BulletPosition>::iterator it);
	void checkBulletHit(std::vector<BulletPosition>::iterator it);
	void goToXY(short x, short y);
	void clearBullets();
	void renderBullets();
	void setBulletColor();
	void addBullet();
	void killTank(int index);
	void killThread();
	int isTankActive();
private:
	TankRenderer* tank;
	BulletPosition currentBulletPosition;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	std::vector <BulletPosition> bullets;
	enum directionPoints { UP, DOWN, LEFT, RIGHT };
	enum colors { GREEN = 2, RED = 4, BLUE = 1, WHITE = 8 };
	int rightCoordinate;
	int downCoordinate;
	int bulletDirection;
	int bulletColor;
	bool threadLoop;
};

