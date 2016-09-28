#pragma once
#include <iostream>
#include "Event.h"
#include "Wumpus.h"
#include "Bats.h"
#include "Pit.h"
#include "Gold.h"

class Room
{
public:
	Room();
	~Room();
	void whichEvent();

	Wumpus wumpus;
	Bats bats;
	Pit pit;
	Gold gold;

	bool hasBats;
	bool hasWumpus;
	bool hasGold;
	bool hasPit;
	bool hasPlayer;

	Event* virEvent;
};

