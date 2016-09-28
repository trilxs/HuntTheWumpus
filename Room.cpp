#include "Room.h"



Room::Room()
{
	hasWumpus = false;
	hasBats = false;
	hasGold = false;
	hasPit = false;
	hasPlayer = false;
}


Room::~Room()
{
}

void Room::whichEvent()
{
	if (hasWumpus) virEvent = &wumpus;
	else if (hasGold) virEvent = &gold;
	else if (hasBats) virEvent = &bats;
	else virEvent = &pit;
}