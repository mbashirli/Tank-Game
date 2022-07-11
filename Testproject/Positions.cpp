#include "Positions.h"

Positions::Positions(){
<<<<<<< Updated upstream
	tankPositions.push_back({0,0,0,0});
	tankPositions.push_back({0,0,0,0});
	tankPositions.push_back({0,0,0,0});
	tankPositions.push_back({});
	tankPositions.push_back({});
	tankPositions.push_back({});
=======
>>>>>>> Stashed changes
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
	if (index < tankPositions.size())
	{
		tankPositions[index] = {xCoord, yCoord, direction};
	}
	else
	{
<<<<<<< Updated upstream
		std::cout<<index;

=======
		tankPositions.push_back({xCoord, yCoord, direction});
>>>>>>> Stashed changes
	}
}

Position* Positions::getTankPosition(int index)
{
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

void Positions::increaseTankAmount()
{
	totalTankAmount++;
}
void Positions::decreaseTankAmount()
{
	totalTankAmount--;
}