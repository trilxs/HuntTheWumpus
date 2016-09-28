#include "AI.h"



AI::AI()
{
	srand(time(NULL));
	// setup input variable
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;

	// set up the virtual-key codes
	left_key = 0x31;
	right_key = 0x32;
	up_key = 0x33;
	down_key = 0x34;
	fire_key = 0x35;

	playing = true;
}


AI::~AI()
{

}

void AI::playAI()
{
	while (playing) {
		Sleep(5000);
		random_choice = (rand() % 5) + 1;
		if (random_choice == 1) pressKey(left_key);
		else if (random_choice == 2) pressKey(right_key);
		else if (random_choice == 3) pressKey(up_key);
		else if (random_choice == 4) pressKey(down_key);
		else  pressKey(fire_key);
	}
	
}

void AI::pressKey(WORD xkey)
{   
	// Press the x key
	ip.ki.wVk = xkey; // virtual-key code for the x key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the x key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}