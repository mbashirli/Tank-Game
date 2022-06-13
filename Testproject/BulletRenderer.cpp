#include "BulletRenderer.h"

BulletRenderer::BulletRenderer(TankRenderer* tank) : std::thread(&BulletRenderer::renderBullets, this)
{
	bulletDirection = directionPoints::UP;
	currentBulletPosition.x = 0;
	currentBulletPosition.y = 0;
	this->tank = tank;
}


void BulletRenderer::goToXY(short x, short y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

int  BulletRenderer::getTerminalRightCoordinate()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	int eastCoordinate = csbiInfo.dwSize.X;
	return eastCoordinate;
}

int BulletRenderer::getTerminalDownCoordinate()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	int southCoordinate = csbiInfo.srWindow.Bottom;
	return southCoordinate + 1;
}

void BulletRenderer::addBullet()
{
	bulletDirection = tank->getTankDirection();
	int currentTankPositionX = tank->getCurrentTankPosition().x;
	int currentTankPositionY = tank->getCurrentTankPosition().y;

	if (bulletDirection == directionPoints::UP)
	{
		currentBulletPosition.x = currentTankPositionX + 1;
		currentBulletPosition.y = currentTankPositionY - 3;
		currentBulletPosition.direction = bulletDirection;
		bullets.push_back(currentBulletPosition);
	}
	else if (bulletDirection == directionPoints::DOWN)
	{
		currentBulletPosition.x = currentTankPositionX + 1;
		currentBulletPosition.y = currentTankPositionY + 3;
		currentBulletPosition.direction = bulletDirection;
		bullets.push_back(currentBulletPosition);
	}
	else if (bulletDirection == directionPoints::LEFT)
	{
		currentBulletPosition.x = currentTankPositionX - 3;
		currentBulletPosition.y = currentTankPositionY;
		currentBulletPosition.direction = bulletDirection;
		bullets.push_back(currentBulletPosition);
	}
	else if (bulletDirection == directionPoints::RIGHT)
	{
		currentBulletPosition.x = currentTankPositionX + 4;
		currentBulletPosition.y = currentTankPositionY;
		currentBulletPosition.direction = bulletDirection;
		bullets.push_back(currentBulletPosition);
	}

	currentBulletPosition.endRender = false;
}

void BulletRenderer::renderBullets()
{
	int rightCoordinate = getTerminalRightCoordinate();
	int downCoordinate = getTerminalDownCoordinate();
	while (true)
	{
		for (auto it = bullets.begin(); it != bullets.end(); it++){
			Application::getInstance()->lockCout();
			if (it->direction == directionPoints::UP && !it->endRender)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x, it->y--);
				std::cout << "*";
				if (it->y == -1)
				{
					goToXY(it->x, 0);
					std::cout << " "; 
					it->endRender = true;
				}
			}
			else if (it->direction == directionPoints::DOWN && !it->endRender)
			{
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				goToXY(it->x, it->y++);
				std::cout << "*";
				if (it->y == downCoordinate)
				{
					goToXY(it->x, downCoordinate - 1);
					std::cout << " ";
					it->endRender = true;
				}
			}
			else if (it->direction == directionPoints::RIGHT && !it->endRender)
			{
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x++, it->y);
				std::cout << "*";

				if (it->x == rightCoordinate)
				{
					goToXY(rightCoordinate - 1, it->y);
					std::cout << " ";
					it->endRender = true;
				}
			}
			else if (it->direction == directionPoints::LEFT && !it->endRender)
			{
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				goToXY(it->x--, it->y);
				std::cout << "*";
				if (it->x == -1)
				{
					goToXY(0, it->y);
					std::cout << " ";
					it->endRender = true;
				}
			}
			Application::getInstance()->unlockCout();
	}
		Sleep(30);
	}
	bullets.clear();
}