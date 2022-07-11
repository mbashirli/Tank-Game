#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>

struct Position {
	int x, y, direction;
	bool isTankActive = true;
};

class Positions
{
public:
	static Positions* getInstance();
	void updateTankPosition(int index, int xCoord, int yCoord, int direction);
	Position* getTankPosition(int index);
	int getTotalTanks();
	bool getTankStatus(int index);
	void killTank(int index);
	void increaseTankAmount();
	void decreaseTankAmount();
private:
	Positions();
	std::vector<Position> tankPositions;
	static Positions* instance;
	int totalTankAmount = 0;
};

