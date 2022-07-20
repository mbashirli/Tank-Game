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
	void setSendBulletTrue();
	void setSendBulletFalse();
	bool getBulletStatus();
	void setBulletCoordinates(short xCoord, short yCoord, short direction);
	Position getBulletCoordinates();
	
private:
	Positions();
	std::vector<Position> tankPositions;
	std::vector<Position> bulletPositions;
	static Positions* instance;
	short totalTankAmount = 0;
	short clientIndex;
	short pressedKey;
	bool bulletStatus = false;

};

