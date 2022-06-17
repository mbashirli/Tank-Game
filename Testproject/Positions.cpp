#include "Positions.h"
#include <iostream>

Positions::Positions(){
	tankPositions.push_back({});
	tankPositions.push_back({});
	tankSize = 0;
}
Positions* Positions::instance;

Positions* Positions::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Positions();
	}
	return instance;
}

void Positions::updateTankPosition(int index, int xCoord, int yCoord, int direction)
{
	if (tankPositions[index].x == 0 && tankPositions[index].y == 0)
	{
		tankPositions[index] = { xCoord, yCoord, direction, true };
		tankSize += 1;
	}
	else
	{
		tankPositions[index] = { xCoord, yCoord, direction };
	}
}

Position* Positions::tankPosition(int index)
{
	return &tankPositions[index];
}

int Positions::getTankSize()
{
	return tankSize;
}

void Positions::killTank(int index)
{
	tankPositions[index].isTankActive = false;
}

bool Positions::getTankStatus(int index)
{
	return tankPositions[index].isTankActive;
}