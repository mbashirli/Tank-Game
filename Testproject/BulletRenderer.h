#pragma once
#include <windows.h>
#include <conio.h>
#include <vector>
#include "TankRenderer.h"
#include <thread>
#include <mutex>
#include "Application.h"
#include "Positions.h".

#define tankBlock 219

struct BulletPosition {
	int x, y, direction, index = -1;
	bool endRender;
};

class BulletRenderer : public std::thread 
{
public:
	BulletRenderer(TankRenderer* tank);
	void goToXY(short x, short y);
	void renderBullets();
	void addBullet();
	void checkBulletHit(std::vector<BulletPosition>::iterator it);
	int getTerminalRightCoordinate();
	int getTerminalDownCoordinate();
private:
	TankRenderer* tank;
	std::vector <BulletPosition> bullets;
	enum directionPoints { UP, DOWN, LEFT, RIGHT };
	int bulletDirection;
	BulletPosition currentBulletPosition;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
};

