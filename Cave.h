#pragma once
#include "Room.h"
#include <iostream>
#include <cstdlib>

class Cave
{
public:  
	Cave();
	Cave(int);
	~Cave();
	Room** rooms;

	void playGame();

private:
	bool isPlaying;
	bool goodMove;
	bool hasGold;
	int size;
	int arrows;
	int player_c;
	int player_r;
	int bat_c[2];
	int bat_r[2];
	int pit_c[2];
	int pit_r[2];
	int wumpus_c;
	int wumpus_r;
	int gold_c;
	int gold_r;
	int escape_c;
	int escape_r;
	int move;

	bool lose;
	bool arrowDecision;
	bool movePlayer(int);
	void checkPlayerParameters();
	void checkPlayerPosition();
	void debugPrintCave();
	void createEvents();
	void teleportWumpus();
	void teleportPlayer();
	void repeat();
	void setup(int);
	void deleteRooms();
	bool fireArrow();
};

