#pragma once
#include <windows.h>
#include <conio.h>
#include <vector>
#include "TankRenderer.h"
#include <thread>
#include <mutex>
struct BulletPosition {
	int x, y, direction;
	bool endRender;
};

class BulletRenderer : public std::thread 
{
public:
	BulletRenderer(TankRenderer* tank);
	void goToXY(short x, short y);
	void renderBullets();
	void addBullet();
	int getTerminalRightCoordinate();
	int getTerminalDownCoordinate();
private:
	TankRenderer* tank;
	std::vector <BulletPosition> bullets;
	enum directionPoints { UP, DOWN, LEFT, RIGHT };
	int bulletDirection;
	BulletPosition currentBulletPosition;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	std::thread mThread;
	std::condition_variable mCV;
	std::mutex mMutex;
};

