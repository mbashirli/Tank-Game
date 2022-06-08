#include "TankRenderer.h"

TankRenderer::TankRenderer() {
	currentTankPosition = getScreenBufferInfo();
	tankDirection = tankDirectionPoints::NORTH;
	tankBlock = 219;
}
TankRenderer::~TankRenderer() {}

tankStartPosition TankRenderer::getScreenBufferInfo()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	tankStartPosition coordinates;
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
	if (tankDirection == tankDirectionPoints::NORTH)
	{
		goToXY(currentTankPosition.x, currentTankPosition.y - 1);
		std::cout << " " << tankBlock;
		goToXY(currentTankPosition.x, currentTankPosition.y);
		std::cout << tankBlock << tankBlock << tankBlock;

	}
	else if (tankDirection == tankDirectionPoints::SOUTH)
	{
		goToXY(currentTankPosition.x, currentTankPosition.y + 1);
		std::cout << " " << tankBlock;
		goToXY(currentTankPosition.x, currentTankPosition.y);
		std::cout << tankBlock << tankBlock << tankBlock;
	}
	else if (tankDirection == tankDirectionPoints::EAST)
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
	else if (tankDirection == tankDirectionPoints::WEST)
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
	disableConsoleCursor();
}

void TankRenderer::moveTank()
{
	if (_kbhit())
	{
		int keyPressed = _getch();
		if (keyPressed == KEY_UP)
		{
			if (tankDirection == tankDirectionPoints::NORTH)
			{
				clearTankVertical();
				currentTankPosition.y--;
				renderTank();
			}
			else
			{
				tankDirection = tankDirectionPoints::NORTH;
				clearTankVertical();
				renderTank();
			}
		}
		else if (keyPressed == KEY_DOWN)
		{
			if (tankDirection == tankDirectionPoints::SOUTH)
			{
				clearTankVertical();
				currentTankPosition.y++;
				renderTank();
			}
			else
			{
				clearTankVertical();
				tankDirection = tankDirectionPoints::SOUTH;
				renderTank();
			}
		}
		else if (keyPressed == KEY_LEFT)
		{
			if (tankDirection == tankDirectionPoints::EAST)
			{
				currentTankPosition.x--;
				clearTankHorizontal();
				renderTank();
			}
			else
			{
				clearTankHorizontal();
				tankDirection = tankDirectionPoints::EAST;
				renderTank();
			}
		}
		else if (keyPressed == KEY_RIGHT)
		{
			if (tankDirection == tankDirectionPoints::WEST)
			{
				clearTankHorizontal();
				currentTankPosition.x++;
				renderTank();
			}
			else
			{
				clearTankHorizontal();
				tankDirection = tankDirectionPoints::WEST;
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
	for (int i = -1; i < 4; i = i + 1)
	{
		goToXY(currentTankPosition.x - 1, currentTankPosition.y + i);
		std::cout << "   ";
		std::cout << "   ";
	}
}

void TankRenderer::clearTankVertical()
{
	for (int i = 0; i < 4; i = i + 1)
	{
		goToXY(currentTankPosition.x, currentTankPosition.y + i);
		std::cout << "   ";
		goToXY(currentTankPosition.x, currentTankPosition.y - i);
		std::cout << "   ";
	}
}