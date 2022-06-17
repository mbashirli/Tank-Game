#pragma once
#include <vector>

struct Position {
	int x, y, direction;
	bool isTankActive;
};

class Positions
{
public:
	static Positions* getInstance();
	void updateTankPosition(int index, int xCoord, int yCoord, int direction);
	Position* tankPosition(int index);
	int getTankSize();
	bool getTankStatus(int index);
	void killTank(int index);

private:
	Positions();
	std::vector<Position> tankPositions;
	static Positions* instance;
	int tankSize;
};

