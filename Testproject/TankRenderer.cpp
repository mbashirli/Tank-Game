#include "TankRenderer.h"

TankRenderer::TankRenderer() {
	currentTankPosition = getScreenBufferInfo();
	tankDirection = directionPoints::UP;
	bulletDirection = directionPoints::UP;
	tankBlock = 219;
}
TankRenderer::~TankRenderer() {}

tankPosition TankRenderer::getScreenBufferInfo()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	tankPosition coordinates;
	coordinates.x = csbiInfo.dwSize.X / 2;
	coordinates.y = (csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top) / 2;
	return coordinates;
}

void TankRenderer::goToXY(short x, short y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void TankRenderer::renderTank()
{
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
		goToXY(currentTankPosition.x, currentTankPosition.y - 1);
		std::cout << " " << tankBlock;
		goToXY(currentTankPosition.x, currentTankPosition.y);
		std::cout << tankBlock << tankBlock << tankBlock;
	}
	else if (tankDirection == directionPoints::DOWN)
	{
		goToXY(currentTankPosition.x, currentTankPosition.y + 1);
		std::cout << " " << tankBlock;
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

void TankRenderer::moveTank()
{
	if (_kbhit())
	{
		int keyPressed = _getch();
		if (keyPressed == KEY_UP)
		{
			if (tankDirection == directionPoints::UP)
			{
				clearTankVertical();
				currentTankPosition.y--;
				renderTank();
			}
			else
			{
				tankDirection = directionPoints::UP;
				clearTankVertical();
				renderTank();
			}
		}
		else if (keyPressed == KEY_DOWN)
		{
			if (tankDirection == directionPoints::DOWN)
			{
				clearTankVertical();
				currentTankPosition.y++;
				renderTank();
			}
			else
			{
				clearTankVertical();
				tankDirection = directionPoints::DOWN;
				renderTank();
			}
		}
		else if (keyPressed == KEY_LEFT)
		{
			if (tankDirection == directionPoints::LEFT)
			{
				currentTankPosition.x--;
				clearTankHorizontal();
				renderTank();
			}
			else
			{
				clearTankHorizontal();
				tankDirection = directionPoints::LEFT;
				renderTank();
			}
		}
		else if (keyPressed == KEY_RIGHT)
		{
			if (tankDirection == directionPoints::RIGHT)
			{
				clearTankHorizontal();
				currentTankPosition.x++;
				renderTank();
			}
			else
			{
				clearTankHorizontal();
				tankDirection = directionPoints::RIGHT;
				renderTank();
			}
		}
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

void TankRenderer::clearTankHorizontal()
{
	Application::getInstance()->lockCout();
	for (int i = -1; i < 4; i = i + 1)
	{
		goToXY(currentTankPosition.x - 1, currentTankPosition.y + i);
		std::cout << "   ";
		std::cout << "   ";
	}
	Application::getInstance()->unlockCout();
}

void TankRenderer::clearTankVertical()
{
	Application::getInstance()->lockCout();
	for (int i = 0; i < 4; i = i + 1)
	{
		goToXY(currentTankPosition.x, currentTankPosition.y + i);
		std::cout << "   ";
		goToXY(currentTankPosition.x, currentTankPosition.y - i);
		std::cout << "   ";
	}
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