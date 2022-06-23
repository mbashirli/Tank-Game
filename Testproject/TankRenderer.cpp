#include "TankRenderer.h"


TankRenderer::TankRenderer(int player, int index)
{
	if (player == players::NPC)
	{
		tankColor = colors::BLUE;
	}
	else if (player == players::PRIMARY)
	{
		tankColor = colors::GREEN;
	}
	isTankActive = true;
	this->player = player;
	currentTankPosition = getScreenBufferInfo();
	currentTankPosition.index = index;
	tankBlock = 219;
	threadLoop = true;
	setTankActiveColor();
}

TankRenderer::~TankRenderer() {
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


tankPosition TankRenderer::getScreenBufferInfo()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	tankPosition coordinates{};
	terminalX = csbiInfo.dwSize.X;
	terminalY = csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top;
	if (player == players::PRIMARY)
	{
		tankColor = colors::GREEN;
		tankDirection = directionPoints::UP;
		coordinates.x = terminalX / 2;
		coordinates.y = terminalY / 2;
		return coordinates;
	}
	else if (player == players::NPC)
	{
		tankColor = colors::BLUE;
		srand(time(NULL));
		tankDirection = rand() % 4;
		coordinates.y = rand() % (terminalY - 5);
		coordinates.x = rand() % (terminalX - 5);
		return coordinates;
	}
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
	Positions::getInstance()->updateTankPosition(currentTankPosition.index, currentTankPosition.x, currentTankPosition.y, tankDirection);
}


void TankRenderer::moveTank()
{
	if (_kbhit() && isTankActive)
	{
		int keyPressed = _getch();
		if (keyPressed == KEY_UP)
		{
			if (tankDirection == directionPoints::UP && tankOnPath())
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
			if (tankDirection == directionPoints::DOWN && tankOnPath())
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
			if (tankDirection == directionPoints::LEFT && tankOnPath())
			{
				currentTankPosition.x--;
				clearTankLeft();
				renderTank();
			}
			else
			{
				if (tankDirection == directionPoints::UP)
					clearTankUp();
				else if (tankDirection == directionPoints::DOWN)
					clearTankDown();
				else
					clearTankRight();
				tankDirection = directionPoints::LEFT;
				renderTank();
			}
		}
		else if (keyPressed == KEY_RIGHT)
		{
			if (tankDirection == directionPoints::RIGHT && tankOnPath())
			{
				clearTankRight();
				currentTankPosition.x++;
				renderTank();
			}
			else
			{
				if (tankDirection == directionPoints::UP)
					clearTankUp();
				else if (tankDirection == directionPoints::DOWN)
					clearTankDown();
				else if (tankDirection == directionPoints::LEFT)
					clearTankLeftModified();
				tankDirection = directionPoints::RIGHT;
				renderTank();
			}

		}
	}
	Positions::getInstance()->updateTankPosition(currentTankPosition.index, currentTankPosition.x, currentTankPosition.y, tankDirection);
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
		clearTankLeft();
	}
}

void TankRenderer::disableConsoleCursor()
{

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);

}

void TankRenderer::clearTankUp()
{
	Application::getInstance()->lockCout();
	goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
	std::cout << " ";
	goToXY(currentTankPosition.x, currentTankPosition.y);
	std::cout << "   ";
	Application::getInstance()->unlockCout();
}

void TankRenderer::clearTankDown()
{
	Application::getInstance()->lockCout();
	goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
	std::cout << " ";
	goToXY(currentTankPosition.x, currentTankPosition.y);
	std::cout << "   ";
	Application::getInstance()->unlockCout();
}

void TankRenderer::clearTankLeft()
{
	Application::getInstance()->lockCout();
	goToXY(currentTankPosition.x + 1, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 2, currentTankPosition.y - 1);
	std::cout << " ";
	goToXY(currentTankPosition.x + 2, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 2, currentTankPosition.y + 1);
	std::cout << " ";
	Application::getInstance()->unlockCout();
}

void TankRenderer::clearTankLeftModified()
{
	Application::getInstance()->lockCout();
	goToXY(currentTankPosition.x, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
	std::cout << " ";
	Application::getInstance()->unlockCout();

}
void TankRenderer::clearTankRight()
{
	Application::getInstance()->lockCout();
	goToXY(currentTankPosition.x + 2, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y - 1);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y);
	std::cout << " ";
	goToXY(currentTankPosition.x + 1, currentTankPosition.y + 1);
	std::cout << " ";
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
	for (int i = 0; i < Positions::getInstance()->getTankSize(); i = i + 1)
	{
		if (i == currentTankPosition.index)
			continue;
		int tankOnPathX = Positions::getInstance()->tankPosition(i)->x;
		int tankOnPathY = Positions::getInstance()->tankPosition(i)->y;
		if (tankDirection == directionPoints::UP)
		{

			if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::UP)
			{
				if ((currentTankPosition.y - 2 == tankOnPathY && currentTankPosition.x == tankOnPathX) ||
					(currentTankPosition.y - 2 == tankOnPathY && currentTankPosition.x + 1 == tankOnPathX) ||
					(currentTankPosition.y - 2 == tankOnPathY && currentTankPosition.x - 1 == tankOnPathX) ||
					(currentTankPosition.y - 1 == tankOnPathY && currentTankPosition.x - 2 == tankOnPathX) ||
					(currentTankPosition.y - 1 == tankOnPathY && currentTankPosition.x + 2 == tankOnPathX))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::DOWN)
			{
				if ((currentTankPosition.y - 3 == tankOnPathY && currentTankPosition.x == tankOnPathX) ||
					(currentTankPosition.y - 2 == tankOnPathY && currentTankPosition.x - 1 == tankOnPathX) ||
					(currentTankPosition.y - 2 == tankOnPathY && currentTankPosition.x + 1 == tankOnPathX) ||
					(currentTankPosition.y - 1 == tankOnPathY && currentTankPosition.x + 2 == tankOnPathX) ||
					(currentTankPosition.y - 1 == tankOnPathY && currentTankPosition.x - 2 == tankOnPathX))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::RIGHT)
			{
				if ((currentTankPosition.x == tankOnPathX && currentTankPosition.y - 3 == tankOnPathY) ||
					(currentTankPosition.x - 1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y  - 1== tankOnPathY ))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::LEFT)
			{
				if ((currentTankPosition.x == tankOnPathX  && currentTankPosition.y - 3 == tankOnPathY) ||
					(currentTankPosition.x -1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y - 1 == tankOnPathY))
					return false;
			}
		}
		else if (tankDirection == directionPoints::DOWN)
		{
			if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::UP)
			{
				if ((currentTankPosition.y + 3 == tankOnPathY && currentTankPosition.x == tankOnPathX) ||
					(currentTankPosition.y + 2 == tankOnPathY && currentTankPosition.x + 1 == tankOnPathX) ||
					(currentTankPosition.y + 2 == tankOnPathY && currentTankPosition.x - 1 == tankOnPathX) ||
					(currentTankPosition.x + 1 == tankOnPathX - 1 && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX + 3 && currentTankPosition.y + 1 == tankOnPathY))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::DOWN)
			{
				if ((currentTankPosition.y + 2 == tankOnPathY && currentTankPosition.x == tankOnPathX) ||
					(currentTankPosition.y + 2 == tankOnPathY && currentTankPosition.x + 1 == tankOnPathX) ||
					(currentTankPosition.y + 2 == tankOnPathY && currentTankPosition.x - 1 == tankOnPathX) ||
					(currentTankPosition.x + 1 == tankOnPathX - 1 && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX + 3 && currentTankPosition.y + 1 == tankOnPathY))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::LEFT)
			{
				if ((currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y + 2 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX + 1 && currentTankPosition.y + 1 == tankOnPathY - 2) ||
					(currentTankPosition.x + 1 == tankOnPathX + 2 && currentTankPosition.y + 1 == tankOnPathY - 1) ||
					(currentTankPosition.x + 1 == tankOnPathX - 1 && currentTankPosition.y + 2 == tankOnPathY + 1))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::RIGHT)
			{
				if ((currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y + 2 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX + 1 && currentTankPosition.y + 1 == tankOnPathY - 2) ||
					(currentTankPosition.x + 1 == tankOnPathX + 2 && currentTankPosition.y + 2 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX + 3 && currentTankPosition.y + 1 == tankOnPathY))
					return false;
			}

		}
		else if (tankDirection == directionPoints::RIGHT)
		{
			if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::UP)
			{
				if ((currentTankPosition.x + 3 == tankOnPathX && currentTankPosition.y == tankOnPathY) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y + 2 == tankOnPathY) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y - 1 == tankOnPathY))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::DOWN)
			{
				if ((currentTankPosition.x + 3 == tankOnPathX && currentTankPosition.y == tankOnPathY) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y == tankOnPathY - 1) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y == tankOnPathY + 1) ||
					(currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y == tankOnPathY + 2))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::LEFT)
			{
				if ((currentTankPosition.x + 3 == tankOnPathX && currentTankPosition.y == tankOnPathY) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y - 1 == tankOnPathY) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y + 2 == tankOnPathY))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::RIGHT)
			{
				if ((currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y == tankOnPathY) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y - 1 == tankOnPathY) ||
					(currentTankPosition.x + 2 == tankOnPathX && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY) ||
					(currentTankPosition.x + 1 == tankOnPathX && currentTankPosition.y + 2 == tankOnPathY))
					return false;
			}
		}
		else if (tankDirection == directionPoints::LEFT)
		{
			if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::UP)
			{
				if ((currentTankPosition.x - 3 == tankOnPathX && currentTankPosition.y == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y - 1 == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x - 1 == tankOnPathX && currentTankPosition.y + 2 == tankOnPathY))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::DOWN)
			{
				if ((currentTankPosition.x - 3 == tankOnPathX && currentTankPosition.y == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y - 1 == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x - 1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::LEFT)
			{

				if ((currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y - 1 == tankOnPathY) ||
					(currentTankPosition.x - 1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY) ||
					(currentTankPosition.x - 1 == tankOnPathX && currentTankPosition.y + 2 == tankOnPathY))
					return false;
			}
			else if (Positions::getInstance()->tankPosition(i)->direction == directionPoints::RIGHT)
			{
				if ((currentTankPosition.x - 3 == tankOnPathX && currentTankPosition.y == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y + 1 == tankOnPathY) ||
					(currentTankPosition.x - 2 == tankOnPathX && currentTankPosition.y - 1 == tankOnPathY) ||
					(currentTankPosition.x - 1 == tankOnPathX && currentTankPosition.y + 2 == tankOnPathY) ||
					(currentTankPosition.x - 1 == tankOnPathX && currentTankPosition.y - 2 == tankOnPathY))
					return false;
			}

		}
	}
	return true;
}
