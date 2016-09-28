#pragma once
#include <iostream>
#include "Event.h"

class Wumpus :
	public Event
{
public:
	Wumpus();
	~Wumpus();
	void interact();
};

