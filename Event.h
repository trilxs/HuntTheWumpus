#pragma once
class Event
{
public:
	Event();
	~Event();
	virtual void interact() = 0;
};

