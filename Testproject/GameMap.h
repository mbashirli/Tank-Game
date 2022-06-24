#pragma once
#include <windows.h>
#include <iostream>



struct MapBorders {
	short left, right, up, down;
};
class GameMap
{
public:
	static GameMap* getInstance();
	int getMapRightCoordinate();
	int getMapDownCoordinate();
	void renderMap();
	void setMapBorderColor();
	void goToXY(short x, short y);
private:
	GameMap();
	int mapRightCoordinate;
	int mapDownCoordinate;
	static GameMap* instance;
	char MAP_BLOCK;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
};

