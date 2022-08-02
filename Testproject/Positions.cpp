#include "Positions.h"

Positions::Positions() {

	bulletPositions.push_back({});
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

void Positions::updateTankPosition(int xCoord, int yCoord, int direction, int index)
{

	if (index < tankPositions.size())
	{
		tankPositions[index] = { xCoord, yCoord, direction, true };
	}
	else
	{
		tankPositions.push_back({ xCoord, yCoord, direction, true });

	}
}

Position* Positions::getTankPosition(int index)
{
	if (index < tankPositions.size())
		return &tankPositions[index];
}

int Positions::getTotalTanks()
{
	return tankPositions.size();
}

void Positions::killTank(int index)
{
	tankPositions[index].isTankActive = false;
}

bool Positions::getTankStatus(int index)
{
	if (index < tankPositions.size())
		return tankPositions[index].isTankActive;
	else
		return true;
}

void Positions::updateTankAmount(int amount)
{
	totalTankAmount = amount;
}
void Positions::decreaseTankAmount()
{
	totalTankAmount--;
}

void Positions::setClientIndex(int index)
{
	clientIndex = index;
}

int Positions::getClientIndex()
{
	return clientIndex;
}

void Positions::setPressedKey(short key)
{
	this->pressedKey = key;
}

short Positions::getPressedKey()
{
	return pressedKey;
}


void Positions::deactiveTank(short index)
{
	tankPositions[index].isTankActive = false;
}

void Positions::setSendBulletTrue()
{
	bulletStatus = true;
}

void Positions::setSendBulletFalse()
{
	bulletStatus = false;
}


bool Positions::getBulletStatus()
{
	return bulletStatus;
}

void Positions::setBulletCoordinates(short x, short y, short direction)
{
	bulletPositions[0].x = x;
	bulletPositions[0].y = y;
	bulletPositions[0].direction = direction;
}

Position Positions::getBulletCoordinates()
{
	return bulletPositions[0];
}