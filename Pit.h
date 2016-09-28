#pragma once
#include <iostream>
#include "Event.h"
class Pit :
	public Event
{
public:
	Pit();
	~Pit();
	void interact();
};

