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
	void updateTankPosition(int xCoord, int yCoord, int direction, int index);
	Position* getTankPosition(int index);
	int getTotalTanks();
	bool getTankStatus(int index);
	void killTank(int index);
	void updateTankAmount(int amount);
	void decreaseTankAmount();
	void setClientIndex(int index);
	int getClientIndex();
	void setPressedKey(short key);
	short getPressedKey();
	void deactiveTank(short index);
private:
	Positions();
	std::vector<Position> tankPositions;
	static Positions* instance;
	short totalTankAmount = 0;
	short clientIndex;
	short pressedKey;
};

