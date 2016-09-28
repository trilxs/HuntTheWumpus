#pragma once
#include <iostream>
#include "Event.h"

class Bats :
	public Event
{
public:
	Bats();
	~Bats();
	void interact();
};

