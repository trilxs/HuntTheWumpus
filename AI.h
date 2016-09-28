#pragma once
#include "windows.h"
#include <cstdlib>
#include <iostream>

class AI:
{
public:
	AI();
	~AI();

	int random_choice;

	WORD left_key;
	WORD right_key;
	WORD up_key;
	WORD down_key;
	WORD fire_key;

	void pressKey(WORD);
	void playAI();
};

