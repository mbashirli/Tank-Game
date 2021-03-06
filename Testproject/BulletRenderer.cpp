#include "BulletRenderer.h"

BulletRenderer::BulletRenderer(TankRenderer* tank)
{
	bulletDirection = directionPoints::UP;
	currentBulletPosition.x = 0;
	currentBulletPosition.y = 0;
	this->tank = tank;
	rightCoordinate = GameMap::getInstance()->getMapRightCoordinate();
	downCoordinate = GameMap::getInstance()->getMapDownCoordinate();
	threadLoop = true;
	bulletColor = colors::RED;
}



void BulletRenderer::setBulletColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bulletColor);
}

void BulletRenderer::goToXY(short x, short y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
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
		currentBulletPosition.index++;
		bullets.push_back(currentBulletPosition);
	}
	else if (bulletDirection == directionPoints::DOWN)
	{
		currentBulletPosition.x = currentTankPositionX + 1;
		currentBulletPosition.y = currentTankPositionY + 3;
		currentBulletPosition.direction = bulletDirection;
		currentBulletPosition.index++;
		bullets.push_back(currentBulletPosition);
	}
	else if (bulletDirection == directionPoints::LEFT)
	{
		currentBulletPosition.x = currentTankPositionX - 3;
		currentBulletPosition.y = currentTankPositionY;
		currentBulletPosition.direction = bulletDirection;
		currentBulletPosition.index++;
		bullets.push_back(currentBulletPosition);
	}
	else if (bulletDirection == directionPoints::RIGHT)
	{
		currentBulletPosition.x = currentTankPositionX + 4;
		currentBulletPosition.y = currentTankPositionY;
		currentBulletPosition.direction = bulletDirection;
		currentBulletPosition.index++;
		bullets.push_back(currentBulletPosition);
	}

	currentBulletPosition.endRender = false;
}

void BulletRenderer::renderBullets()
{
	while (threadLoop)
	{
		for (auto it = bullets.begin(); it != bullets.end(); it++) {
			Application::getInstance()->lockCout();
			setBulletColor();
			if (it->direction == directionPoints::UP && !it->endRender)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x, it->y--);
				std::cout << "*";
				if (it->y == 0)
				{
					goToXY(it->x, 1);
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
				if (it->x == 1)
				{
					goToXY(2, it->y);
					std::cout << " ";
					it->endRender = true;
				}
			}
			checkBulletHit(it);
			Application::getInstance()->unlockCout();
		}
		Sleep(30);
		clearBullets();
	}

	return;
}



void BulletRenderer::checkBulletHit(std::vector<BulletPosition>::iterator it)
{
	if (it->endRender == false)
	{
		checkBullet(it);
	}
}

void BulletRenderer::clearBullets()
{
	if (bullets.size() >= 4)
	{
		if (bullets.begin()->endRender == true)
		{
			auto it = bullets.begin();
			bullets.erase(it);
		}
	}
}

void BulletRenderer::checkBullet(std::vector<BulletPosition>::iterator it)
{
	for (int i = 0; i < Positions::getInstance()->getTotalTanks(); i = i + 1)
	{
		if (Positions::getInstance()->getTankStatus(i) == false) {
			it->endRender = false;
			continue;
		}
		if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::LEFT)
		{

			if (Positions::getInstance()->getTankPosition(i)->x == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y + 1 == it->y)
			{
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y - 1 == it->y)
			{
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}

		}
		else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::RIGHT)
		{

			if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 2 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y + 1 == it->y)
			{
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y - 1 == it->y)
			{
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}

		}
		else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::UP)
		{
			if (Positions::getInstance()->getTankPosition(i)->x + 2 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x == it->x &&
				Positions::getInstance()->getTankPosition(i)->y + 1 == it->y)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y - 1 == it->y)
			{
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
		}
		else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::DOWN)
		{
			if (Positions::getInstance()->getTankPosition(i)->x == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y + 1 == it->y)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x - 1, it->y);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 2 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x, it->y + 1);
				std::cout << " ";
				goToXY(it->x + 1, it->y);
				std::cout << " ";
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
			else if (Positions::getInstance()->getTankPosition(i)->x + 1 == it->x &&
				Positions::getInstance()->getTankPosition(i)->y == it->y)
			{
				goToXY(it->x, it->y - 1);
				std::cout << " ";
				it->endRender = true;
				killTank(i);
			}
		}
	}
}


int BulletRenderer::isTankActive()
{
	for (int i = 0; i < Positions::getInstance()->getTotalTanks(); i = i + 1)
	{
		if (Positions::getInstance()->getTankStatus(i) == false)
		{
			return i;
		}
	}
	return -1;
}

void BulletRenderer::killTank(int index)
{
	Positions::getInstance()->killTank(index);
}

void BulletRenderer::killThread()
{
	threadLoop = false;
}