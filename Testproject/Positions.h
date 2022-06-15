#pragma once
#include <vector>

struct Position {
	int x, y;
};

class Positions
{
public:
	static Positions* getInstance();
	void updateTankPosition(int index, int xCoord, int yCoord);
	Position* tankPosition(int index);
	int getTankSize();

private:
	Positions();
	std::vector<Position> tankPositions;
	static Positions* instance;
	int tankSize;
};

