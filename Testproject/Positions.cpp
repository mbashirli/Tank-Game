#include "Positions.h"

Positions::Positions(){
	
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
		tankPositions[index] = {xCoord, yCoord, direction};
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
	return tankPositions[index].isTankActive;
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