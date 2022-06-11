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
	//std::cout << "added bullet " << std::endl;
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
		std::mutex mtx;
		mtx.lock();
		for (auto it = bullets.begin(); it != bullets.end(); it++){
			if (it->direction == directionPoints::UP && !it->endRender)
			{
				//std::cout<<"UP";
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
				//std::cout << "DOWN";
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
				//std::cout << "RIGHT";
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
				//std::cout << "LEFT";
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
			if (it != bullets.begin())
			{
			}
	}
		Sleep(30);
		mtx.unlock();
	}
	bullets.clear();
}