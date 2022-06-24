#include "GameMap.h"

GameMap* GameMap::instance;

GameMap* GameMap::getInstance()
{
	if (instance == nullptr)
		instance = new GameMap();
	return instance;
}

int GameMap::getMapDownCoordinate()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	return csbiInfo.srWindow.Bottom - 2;
}

int GameMap::getMapRightCoordinate()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	return  csbiInfo.dwSize.X - 2;

}

void GameMap::setMapBorderColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 9);
}

void GameMap::renderMap()
{
	setMapBorderColor();
	for (int i = 0; i < mapRightCoordinate; i = i + 1)
	{
		goToXY(i, 0);
		std::cout << MAP_BLOCK;
	}
	for (int i = 0; i < mapDownCoordinate; i = i + 1)
	{
		goToXY(0, i);
		std::cout << MAP_BLOCK<<MAP_BLOCK;
	}
	for (int i = 0; i < mapRightCoordinate; i = i + 1)
	{
		goToXY(i, mapDownCoordinate);
		std::cout << MAP_BLOCK;
	}
	for (int i = 0; i < mapDownCoordinate; i = i + 1)
	{
		goToXY(mapRightCoordinate-2, i);
		std::cout << MAP_BLOCK << MAP_BLOCK;
	}
}

void GameMap::goToXY(short x, short y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

GameMap::GameMap()
{
	mapRightCoordinate = getMapRightCoordinate() + 2;
	mapDownCoordinate = getMapDownCoordinate() + 2;
	MAP_BLOCK = 219;
}