#include "TankRenderer.h"


TankRenderer::TankRenderer(int index)
{
	customTank = false;
	isTankActive = true;
	this->player = player;
	currentTankPosition = getScreenBufferInfo();
	currentTankPosition.index = index;
	mapRightCoordinate = GameMap::getInstance()->getMapRightCoordinate();
	mapDownCoordinate = GameMap::getInstance()->getMapDownCoordinate();
	tankBlock = 219;
	setTankActiveColor();
}

TankRenderer::~TankRenderer() {
}

TankRenderer::TankRenderer(int xCoord, int yCoord, int tankDirection, int index, int totalPlayerCount)
{
	mapRightCoordinate = GameMap::getInstance()->getMapRightCoordinate();
	mapDownCoordinate = GameMap::getInstance()->getMapDownCoordinate();

	currentTankPosition.x = xCoord;
	currentTankPosition.y = yCoord;
	currentTankPosition.index = index;

	this->tankDirection = tankDirection;
	this->totalPlayers = totalPlayerCount;
	this->isTankActive = true;
	this->customTank = true;
	this->tankBlock = 219;
}

TankRenderer::TankRenderer()
{
	mapRightCoordinate = GameMap::getInstance()->getMapRightCoordinate();
	mapDownCoordinate = GameMap::getInstance()->getMapDownCoordinate();

	this->isTankActive = true;
	this->customTank = true;
	this->tankBlock = 219;
}

void TankRenderer::setTankPosition(short xCoord, short yCoord, short tankDirection)
{
	currentTankPosition.x = xCoord;
	currentTankPosition.y = yCoord;
	this->tankDirection = tankDirection;
}
void TankRenderer::disableTank()
{
	isTankActive = false;
}

bool TankRenderer::isTankDisabled()
{
	return isTankActive;
}

void TankRenderer::deathAnimation()
{
	while (threadLoop)
	{
		if (!isTankActive)
		{
			setTankInactiveColor();
			renderTank();
			Sleep(100);
			setTankActiveColor();
			renderTank();
			Sleep(100);
			setTankInactiveColor();
			renderTank();
			Sleep(100);
			clearTank();
			//Positions::getInstance()->updateTankPosition(currentTankPosition.index,0,0, directionPoints::UP);
			threadLoop = false;
		}
	}
}

void TankRenderer::setTankActiveColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, tankColor);
}

void TankRenderer::setTankInactiveColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colors::RED);
}

void TankRenderer::setColorBlack()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0);
}

tankPosition TankRenderer::getScreenBufferInfo()
{
	mapRightCoordinate = GameMap::getInstance()->getMapRightCoordinate();
	mapDownCoordinate = GameMap::getInstance()->getMapDownCoordinate();
	tankPosition coordinates{};

	tankColor = colors::BLUE;
	srand(time(NULL));
	tankDirection = rand() % 4;
	coordinates.y = rand() % (mapDownCoordinate - 5);
	coordinates.x = rand() % (mapRightCoordinate - 5);
	return coordinates;

}

void TankRenderer::goToXY(short x, short y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void TankRenderer::renderTank()
{
	if (isTankActive)
		setTankActiveColor();
	Application::getInstance()->lockCout();
	setTankPosition();
	Sleep(30);
	Application::getInstance()->unlockCout();
	disableConsoleCursor();

}

void TankRenderer::setTankPosition()
{

	if (tankDirection == directionPoints::UP)
	{
		goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
		std::cout << tankBlock;
		goToXY(currentTankPosition.x, currentTankPosition.y);
		std::cout << tankBlock << tankBlock << tankBlock;
	}
	else if (tankDirection == directionPoints::DOWN)
	{
		goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
		std::cout << tankBlock;
		goToXY(currentTankPosition.x, currentTankPosition.y);
		std::cout << tankBlock << tankBlock << tankBlock;

	}
	else if (tankDirection == directionPoints::LEFT)
	{
		goToXY(currentTankPosition.x, currentTankPosition.y);
		std::cout << tankBlock;
		goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
		std::cout << tankBlock;
		goToXY(currentTankPosition.x + 1, currentTankPosition.y);
		std::cout << tankBlock;
		goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
		std::cout << tankBlock;
	}
	else if (tankDirection == directionPoints::RIGHT)
	{
		goToXY(currentTankPosition.x + 2, currentTankPosition.y);
		std::cout << tankBlock;
		goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
		std::cout << tankBlock;
		goToXY(currentTankPosition.x + 1, currentTankPosition.y);
		std::cout << tankBlock;
		goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
		std::cout << tankBlock;
	}

}


void TankRenderer::moveTank(int keyPressed)
{
	if (keyPressed == KEY_UP)
	{
		if (tankDirection == directionPoints::UP && !borderOnPath() && !tankOnPath())
		{
			clearTankUp();
			currentTankPosition.y--;
			renderTank();
		}
		else
		{
			tankDirection = directionPoints::UP;
			clearTankDown();
			renderTank();
		}
	}
	else if (keyPressed == KEY_DOWN)
	{
		if (tankDirection == directionPoints::DOWN && !borderOnPath() && !tankOnPath())
		{
			clearTankDown();
			currentTankPosition.y++;
			renderTank();
		}
		else
		{
			clearTankUp();
			tankDirection = directionPoints::DOWN;
			renderTank();
		}
	}
	else if (keyPressed == KEY_LEFT)
	{
		if (tankDirection == directionPoints::LEFT && !borderOnPath() && !tankOnPath())
		{
			currentTankPosition.x--;
			clearTankLeft();
			renderTank();
		}
		else
		{
			if (tankDirection == directionPoints::UP)
			{
				clearTankUp();
			}
			else if (tankDirection == directionPoints::DOWN)
			{
				clearTankDown();
			}
			else
			{
				clearTankRight();
			}
			tankDirection = directionPoints::LEFT;
			renderTank();
		}
	}
	else if (keyPressed == KEY_RIGHT)
	{
		if (tankDirection == directionPoints::RIGHT && !borderOnPath() && !tankOnPath())
		{
			clearTankRight();
			currentTankPosition.x++;
			renderTank();
		}
		else
		{
			if (tankDirection == directionPoints::UP)
			{
				clearTankUp();
			}
			else if (tankDirection == directionPoints::DOWN)
			{
				clearTankDown();
			}
			else if (tankDirection == directionPoints::LEFT)
			{
				clearTankLeftModified();
			}
			tankDirection = directionPoints::RIGHT;
			renderTank();
		}

	}
}

void TankRenderer::clearTank()
{
	if (tankDirection == directionPoints::UP)
	{
		clearTankUp();
	}
	else if (tankDirection == directionPoints::DOWN)
	{
		clearTankDown();
	}
	else if (tankDirection == directionPoints::RIGHT)
	{
		clearTankRight();
	}
	else if (tankDirection == directionPoints::LEFT)
	{
		clearTankLeftModified();
	}
}

void TankRenderer::disableConsoleCursor()
{

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

}

void TankRenderer::clearTankUp()
{
	Application::getInstance()->lockCout();
	setColorBlack();
	goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
	std::cout << " ";
	goToXY(currentTankPosition.x, currentTankPosition.y);
	std::cout << "   ";
	setTankActiveColor();
	Application::getInstance()->unlockCout();
}

void TankRenderer::clearTankDown()
{
	Application::getInstance()->lockCout();
	setColorBlack();
	goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
	std::cout << " ";
	goToXY(currentTankPosition.x, currentTankPosition.y);
	std::cout << "   ";
	setTankActiveColor();
	Application::getInstance()->unlockCout();
}

void TankRenderer::clearTankLeft()
{
	Application::getInstance()->lockCout();
	setColorBlack();
	goToXY(currentTankPosition.x + 1, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 2, currentTankPosition.y - 1);
	std::cout << " ";
	goToXY(currentTankPosition.x + 2, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 2, currentTankPosition.y + 1);
	std::cout << " ";
	setTankActiveColor();
	Application::getInstance()->unlockCout();
}

void TankRenderer::clearTankLeftModified()
{
	Application::getInstance()->lockCout();
	setColorBlack();
	goToXY(currentTankPosition.x, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
	std::cout << " ";
	setTankActiveColor();
	Application::getInstance()->unlockCout();

}
void TankRenderer::clearTankRight()
{
	Application::getInstance()->lockCout();
	setColorBlack();
	goToXY(currentTankPosition.x + 2, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
	std::cout << " ";
	setTankActiveColor();
	Application::getInstance()->unlockCout();
}
int TankRenderer::getTankDirection()
{
	return tankDirection;
}

tankPosition TankRenderer::getCurrentTankPosition()
{
	return currentTankPosition;
}

bool TankRenderer::tankOnPath()
{
	int tankOnPathX, tankOnPathY;
	int currentTankX, currentTankY;
	for (int i = 0; i < Positions::getInstance()->getTotalTanks(); i = i + 1)
	{
		if (i == currentTankPosition.index || Positions::getInstance()->getTankStatus(i) == false)
			continue;
		tankOnPathX = Positions::getInstance()->getTankPosition(i)->x;
		tankOnPathY = Positions::getInstance()->getTankPosition(i)->y;
		currentTankX = currentTankPosition.x;
		currentTankY = currentTankPosition.y;


		if (tankDirection == directionPoints::UP)
		{
			if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::UP)
			{
				currentTankY += 1;
				if ((currentTankY - 2 == tankOnPathY && currentTankX == tankOnPathX) ||
					(currentTankY - 2 == tankOnPathY && currentTankX + 1 == tankOnPathX) ||
					(currentTankY - 2 == tankOnPathY && currentTankX - 1 == tankOnPathX) ||
					(currentTankY - 1 == tankOnPathY && currentTankX - 2 == tankOnPathX) ||
					(currentTankY - 1 == tankOnPathY && currentTankX + 2 == tankOnPathX))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::DOWN)
			{
				currentTankY -= 1;
				if ((currentTankY - 3 == tankOnPathY && currentTankX == tankOnPathX) ||
					(currentTankY - 2 == tankOnPathY && currentTankX - 1 == tankOnPathX) ||
					(currentTankY - 2 == tankOnPathY && currentTankX + 1 == tankOnPathX) ||
					(currentTankY - 1 == tankOnPathY && currentTankX + 2 == tankOnPathX) ||
					(currentTankY - 1 == tankOnPathY && currentTankX - 2 == tankOnPathX))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::RIGHT)
			{
				if ((currentTankX == tankOnPathX && currentTankY - 3 == tankOnPathY) ||
					(currentTankX - 1 == tankOnPathX && currentTankY - 2 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX && currentTankY - 2 == tankOnPathY) ||
					(currentTankX - 2 == tankOnPathX && currentTankY - 1 == tankOnPathY))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::LEFT)
			{
				if ((currentTankX == tankOnPathX && currentTankY - 3 == tankOnPathY) ||
					(currentTankX - 1 == tankOnPathX && currentTankY - 2 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX && currentTankY - 2 == tankOnPathY) ||
					(currentTankX + 2 == tankOnPathX && currentTankY - 1 == tankOnPathY))
					return true;
			}
		}
		else if (tankDirection == directionPoints::DOWN)
		{
			if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::UP)
			{
				//currentTankY += 1;
				if ((currentTankY + 3 == tankOnPathY && currentTankX == tankOnPathX) ||
					(currentTankY + 2 == tankOnPathY && currentTankX + 1 == tankOnPathX) ||
					(currentTankY + 2 == tankOnPathY && currentTankX - 1 == tankOnPathX) ||
					(currentTankX + 1 == tankOnPathX - 1 && currentTankY + 1 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX + 3 && currentTankY + 1 == tankOnPathY))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::DOWN)
			{
				if ((currentTankY + 2 == tankOnPathY && currentTankX == tankOnPathX) ||
					(currentTankY + 2 == tankOnPathY && currentTankX + 1 == tankOnPathX) ||
					(currentTankY + 2 == tankOnPathY && currentTankX - 1 == tankOnPathX) ||
					(currentTankX + 1 == tankOnPathX - 1 && currentTankY + 1 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX + 3 && currentTankY + 1 == tankOnPathY))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::LEFT)
			{
				if ((currentTankX + 1 == tankOnPathX && currentTankY + 2 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX + 1 && currentTankY + 1 == tankOnPathY - 2) ||
					(currentTankX + 1 == tankOnPathX + 2 && currentTankY + 1 == tankOnPathY - 1) ||
					(currentTankX + 1 == tankOnPathX - 1 && currentTankY + 2 == tankOnPathY + 1))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::RIGHT)
			{
				if ((currentTankX + 1 == tankOnPathX && currentTankY + 2 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX + 1 && currentTankY + 1 == tankOnPathY - 2) ||
					(currentTankX + 1 == tankOnPathX + 2 && currentTankY + 2 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX + 3 && currentTankY + 1 == tankOnPathY))
					return true;
			}

		}
		else if (tankDirection == directionPoints::RIGHT)
		{
			//currentTankX -= 1;
			if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::UP)
			{
				if ((currentTankX + 3 == tankOnPathX && currentTankY == tankOnPathY) ||
					(currentTankX + 2 == tankOnPathX && currentTankY + 1 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX && currentTankY + 2 == tankOnPathY) ||
					(currentTankX + 2 == tankOnPathX && currentTankY - 1 == tankOnPathY))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::DOWN)
			{
				if ((currentTankX + 3 == tankOnPathX && currentTankY == tankOnPathY) ||
					(currentTankX + 2 == tankOnPathX && currentTankY == tankOnPathY - 1) ||
					(currentTankX + 2 == tankOnPathX && currentTankY == tankOnPathY + 1) ||
					(currentTankX + 1 == tankOnPathX && currentTankY == tankOnPathY + 2))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::LEFT)
			{
				if ((currentTankX + 3 == tankOnPathX && currentTankY == tankOnPathY) ||
					(currentTankX + 2 == tankOnPathX && currentTankY - 1 == tankOnPathY) ||
					(currentTankX + 2 == tankOnPathX && currentTankY + 1 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX && currentTankY - 2 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX && currentTankY + 2 == tankOnPathY))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::RIGHT)
			{
				if ((currentTankX + 2 == tankOnPathX && currentTankY == tankOnPathY) ||
					(currentTankX + 2 == tankOnPathX && currentTankY - 1 == tankOnPathY) ||
					(currentTankX + 2 == tankOnPathX && currentTankY + 1 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX && currentTankY - 2 == tankOnPathY) ||
					(currentTankX + 1 == tankOnPathX && currentTankY + 2 == tankOnPathY))
					return true;
			}
		}
		else if (tankDirection == directionPoints::LEFT)
		{
			if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::UP)
			{
				if ((currentTankX - 3 == tankOnPathX && currentTankY == tankOnPathY) ||
					(currentTankX - 2 == tankOnPathX && currentTankY - 1 == tankOnPathY) ||
					(currentTankX - 2 == tankOnPathX && currentTankY + 1 == tankOnPathY) ||
					(currentTankX - 1 == tankOnPathX && currentTankY + 2 == tankOnPathY))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::DOWN)
			{
				if ((currentTankX - 3 == tankOnPathX && currentTankY == tankOnPathY) ||
					(currentTankX - 2 == tankOnPathX && currentTankY - 1 == tankOnPathY) ||
					(currentTankX - 2 == tankOnPathX && currentTankY + 1 == tankOnPathY) ||
					(currentTankX - 1 == tankOnPathX && currentTankY - 2 == tankOnPathY))
					return true;
			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::LEFT)
			{
				currentTankX -= 1;
				if ((currentTankX - 2 == tankOnPathX && currentTankY == tankOnPathY) ||
					(currentTankX - 2 == tankOnPathX && currentTankY + 1 == tankOnPathY) ||
					(currentTankX - 2 == tankOnPathX && currentTankY - 1 == tankOnPathY) ||
					(currentTankX - 1 == tankOnPathX && currentTankY - 2 == tankOnPathY) ||
					(currentTankX - 1 == tankOnPathX && currentTankY + 2 == tankOnPathY))
					return true;

			}
			else if (Positions::getInstance()->getTankPosition(i)->direction == directionPoints::RIGHT)
			{
				
				if ((currentTankX - 3 == tankOnPathX && currentTankY == tankOnPathY) ||
					(currentTankX- 2 == tankOnPathX && currentTankY + 1 == tankOnPathY) ||
					(currentTankX - 2 == tankOnPathX && currentTankY - 1 == tankOnPathY) ||
					(currentTankX - 1 == tankOnPathX && currentTankY + 2 == tankOnPathY) ||
					(currentTankX - 1 == tankOnPathX && currentTankY - 2 == tankOnPathY))
					return true;
			}

		}
	}
	return false;
}


bool TankRenderer::borderOnPath()
{

	if (tankDirection == directionPoints::UP)
	{
		if (currentTankPosition.y - 2 == 0)
			return true;
	}
	else if (tankDirection == directionPoints::DOWN)
	{
		if (currentTankPosition.y == mapDownCoordinate)
			return true;
	}
	else if (tankDirection == directionPoints::LEFT)
	{
		if (currentTankPosition.x - 2 == 0)
			return true;
	}
	else if (tankDirection == directionPoints::RIGHT)
	{
		if (currentTankPosition.x == mapRightCoordinate - 3)
			return true;
	}
	return false;
}