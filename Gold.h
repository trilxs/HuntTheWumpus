#pragma once
#include <iostream>

#include "Event.h"
class Gold :
	public Event
{
public:
	Gold();
	~Gold();
	void interact();
};

