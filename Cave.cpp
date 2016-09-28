#include "Cave.h"



Cave::Cave()
{
}

Cave::Cave(int size)
{
	setup(size);
}

Cave::~Cave()
{
}

void Cave::setup(int size) {
	this->size = size;
	rooms = new Room*[size];
	for (int i = 0; i < size; i++) rooms[i] = new Room[size];
	createEvents();

	arrows = 3;
	isPlaying = true;
	hasGold = false;
	lose = false;
}

void Cave::createEvents()
{	
	srand(time(NULL));
	player_r = rand() % size;
	player_c = rand() % size; 
	escape_r = player_r;
	escape_c = player_c;
	rooms[player_r][player_c].hasPlayer = true;
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			do {
				bat_r[i] = rand() % size;
				bat_c[i] = rand() % size;
			} while (bat_r[i] == player_r && bat_c[i] == player_c);
		}
		else {
			do {
				bat_r[i] = rand() % size;
				bat_c[i] = rand() % size;
			} while ((bat_r[0] == bat_r[1] && bat_c[0] == bat_c[1]) || (bat_r[i] == player_r && bat_c[i] == player_c));
		}
		rooms[bat_r[i]][bat_c[i]].hasBats = true;
	}
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			do {
				pit_r[i] = rand() % size;
				pit_c[i] = rand() % size;
			} while ((pit_r[i] == player_r && pit_c[i] == player_c) || (pit_r[i] == bat_r[0] && pit_r[i] == bat_c[0]) || (pit_r[i] == bat_r[1] && pit_r[i] == bat_c[1]));
		}
		else {
			do {
				pit_r[i] = rand() % size;
				pit_c[i] = rand() % size;
			} while ((pit_r[i] == player_r && pit_c[i] == player_c) || (pit_r[i] == bat_r[0] && pit_r[i] == bat_c[0]) || (pit_r[i] == bat_r[1] && pit_r[i] == bat_c[1]) || (pit_r[i] == pit_r[0] && pit_c[i] == pit_c[0]));
		}
		rooms[pit_r[i]][pit_c[i]].hasPit = true;
	}
	do {
		gold_r = rand() % size;
		gold_c = rand() % size;
	} while ((gold_r == player_r && gold_c == player_c) || (gold_r == bat_r[0] && gold_c == bat_c[0]) || (gold_r == bat_r[1] && gold_c == bat_c[1]) || (gold_r == pit_r[0] && gold_c == pit_c[0]) || (gold_r == pit_r[1] && gold_c == pit_c[1]));
	rooms[gold_r][gold_c].hasGold = true;
	do {
		wumpus_r = rand() % size;
		wumpus_c = rand() % size;
	} while ((wumpus_r == player_r && wumpus_c == player_c) || (wumpus_r == bat_r[0] && wumpus_c == bat_c[0]) || (wumpus_r == bat_r[1] && wumpus_c == bat_c[1]) || (wumpus_r == pit_r[0] && wumpus_c == pit_c[0]) || (wumpus_r == pit_r[1] && wumpus_c == pit_c[1]) || (wumpus_r == gold_r && wumpus_c == gold_c));
	rooms[wumpus_r][wumpus_c].hasWumpus = true;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			rooms[i][j].whichEvent();
		}
	}
}


void Cave::teleportWumpus()
{
	rooms[wumpus_r][wumpus_c].hasWumpus = false;
	do {
		wumpus_r = rand() %( size-1);
		wumpus_c = rand() % (size-1);
	} while ((wumpus_r == player_r && wumpus_c == player_c) || (wumpus_r == bat_r[0] && wumpus_c == bat_c[0]) || (wumpus_r == bat_r[1] && wumpus_c == bat_c[1]) || (wumpus_r == pit_r[0] && wumpus_c == pit_c[0]) || (wumpus_r == pit_r[1] && wumpus_c == pit_c[1]) || (wumpus_r == gold_r && wumpus_c == gold_c));
	rooms[wumpus_r][wumpus_c].hasWumpus = true;
}

void Cave::teleportPlayer()
{
	std::cout << "You have been teleported by the bats to a random room." << std::endl;
	rooms[player_r][player_c].hasPlayer = false;
	do {
		player_r = rand() % size;
		player_c = rand() % size;
	} while ((player_r == wumpus_r && player_c == wumpus_c) || (player_r == bat_r[0] && player_c == bat_c[0]) || (player_r == bat_r[1] && player_c == bat_c[1]) || (player_r == pit_r[0] && player_c == pit_c[0]) || (player_r == pit_r[1] && player_c == pit_c[1]) || (player_r == gold_r && player_c == gold_c));
	rooms[player_r][player_c].hasPlayer = true;
}

void Cave::playGame()
{
	std::cout << "Welcome to Hunt the Wumpus!\n";
	arrowDecision = false;
	while (isPlaying)
	{
		if (!arrowDecision) system("clear");
		arrowDecision = false;
		std::cout << "Arrow count: " << arrows << std::endl;
		checkPlayerParameters();
		checkPlayerPosition();
		if (isPlaying) {
			std::cout << "Current position: ( " << player_r << ", " << player_c << " )\n";
			
			goodMove = false;
			while (!goodMove) {
				std::cout << "Do you want to move left (1), right (2), up (3), down (4), for fire an arrow (5)?\nInput: "; std::cin >> move;
				if (move == 5) {
					arrowDecision = true;
					isPlaying = fireArrow();
					goodMove = true;
				}
				else goodMove = movePlayer(move);
			}
		}
		if (arrows == 0) {
			std::cout << "You have run out of arrows!\n";
			lose = true;
			isPlaying = false;
		}
		//check to see if lose or win
		if (player_r == escape_r && player_c == escape_c && hasGold) isPlaying = false;
	}
	if ((isPlaying == false && hasGold == false) || ((isPlaying == false && hasGold == true && lose == true))) std::cout << "You have died!\n";
	else std::cout << "You have won!\n";
	deleteRooms();
	repeat();
}

bool Cave::fireArrow()
{
	int direction, rand1, rand2;
	bool hitWumpus, escapedWumpus, arrowHit;
	arrowHit = false;
	rand1 = rand() % 2;
	rand2 = rand() % 4;
	if (rand == 0) hitWumpus == true; else hitWumpus == false;
	if (rand2 == 0) escapedWumpus = false; else escapedWumpus = true;
	std::cout << "Where would you like to shoot? Left (1), right (2), up (3), down (4)\nInput: "; std::cin >> direction;
	system("clear");
	if (direction == 1) {
		for (int i = 0; i < 3 && (player_c - i) > 0; i++) { if (rooms[player_r][player_c - i].hasWumpus) {
				if (hitWumpus) {
					std::cout << "You have killed the Wumpus!\n";
					rooms[wumpus_r][wumpus_c].hasWumpus = false;
					arrowHit = true;
				}
				else {
					if (escapedWumpus) {
						std::cout << "You missed and the Wumpus has escaped to another room!\n";
						teleportWumpus();
					}
					else {
						std::cout << "You missed... The Wumpus has appeared and eaten you!\n";
						lose = true;
						return false;
					}
				}
			}
		}
	}
	else if (direction == 2) {
		for (int i = 0; i < 3 && (player_c + i) < size-1; i++) { if (rooms[player_r][player_c + i].hasWumpus) {
				if (hitWumpus) {
					std::cout << "You have killed the Wumpus!\n";
					rooms[wumpus_r][wumpus_c].hasWumpus = false;
					arrowHit = true;
				}
				else {
					if (escapedWumpus) {
						std::cout << "You missed and the Wumpus has escaped to another room!\n";
						teleportWumpus();
					}
					else {
						std::cout << "You missed... The Wumpus has appeared and eaten you!\n";
						lose = true;
						return false;
					}
				}
			}
		}
	}
	else if (direction == 3) {
		for (int i = 0; i < 3 && (player_r - i) > 0; i++) { if (rooms[player_r- i][player_c].hasWumpus) {
				if (hitWumpus) {
					std::cout << "You have killed the Wumpus!\n";
					rooms[wumpus_r][wumpus_c].hasWumpus = false;
					arrowHit = true;
				}
				else {
					if (escapedWumpus) {
						std::cout << "You missed and the Wumpus has escaped to another room!\n";
						teleportWumpus();
					}
					else {
						std::cout << "You missed... The Wumpus has appeared and eaten you!\n";
						lose = true;
						return false;
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < 3 && (player_r + i) <(size-1); i++) { if (rooms[player_r+i][player_c].hasWumpus) {
				if (hitWumpus) {
					std::cout << "You have killed the Wumpus!\n";
					rooms[wumpus_r][wumpus_c].hasWumpus = false;
					arrowHit = true;
				}
				else {
					if (escapedWumpus) {
						std::cout << "You missed and the Wumpus has escaped to another room!\n";
						teleportWumpus();
					}
					else {
						std::cout << "You missed... The Wumpus has appeared and eaten you!\n";
						lose = true;
						return false;
					}
				}
			}
		}
	}
	arrows--;
	if (!arrowHit) std::cout << "Nothing was hit.\n";
	
	return true;
}

bool Cave::movePlayer(int move)
{
	if (move == 3 && player_r != 0) {
		rooms[player_r][player_c].hasPlayer = false;
		player_r--;
		rooms[player_r][player_c].hasPlayer = true;
		return true;
	}
	else if (move == 4 && player_r != (size - 1)) {
		rooms[player_r][player_c].hasPlayer = false;
		player_r++;
		rooms[player_r][player_c].hasPlayer = true;
		return true;
	}
	else if (move == 2 && player_c != (size - 1)) {
		rooms[player_r][player_c].hasPlayer = false;
		player_c++;
		rooms[player_r][player_c].hasPlayer = true;
		return true;
	}
	else if (move == 1 && player_c != (0)) {
		rooms[player_r][player_c].hasPlayer = false;
		player_c--;
		rooms[player_r][player_c].hasPlayer = true;
		return true;
	}
	else {
		system("clear");
		std::cout << "You cannot move there.\n";
		return false;
	}
}


void Cave::checkPlayerParameters()
{
	if (((player_r + 1) == wumpus_r && (player_c) == wumpus_c) || ((player_r - 1) == wumpus_r && (player_c) == wumpus_c)|| ((player_c + 1) == wumpus_c && (player_r) == wumpus_r)|| ((player_c - 1) == wumpus_c && player_r == wumpus_r)) if (rooms[wumpus_r][wumpus_c].hasWumpus) std::cout << "You smell a terrible stench.\n";
	for (int i = 0; i < 2; i ++) if (((player_r + 1) == bat_r[i] && (player_c) == bat_c[i]) || ((player_r - 1) == bat_r[i] && (player_c) == bat_c[i]) || ((player_c + 1) == bat_c[i] && (player_r) == bat_r[i]) || ((player_c - 1) == bat_c[i] && player_r == bat_r[i])) std::cout << "You hear wings flapping.\n";
	for (int i = 0; i < 2; i ++) if (((player_r + 1) == pit_r[i] && (player_c) == pit_c[i]) || ((player_r - 1) == pit_r[i] && (player_c) == pit_c[i]) || ((player_c + 1) == pit_c[i] && (player_r) == pit_r[i]) || ((player_c - 1) == pit_c[i] && player_r == pit_r[i])) std::cout << "You feel a breeze.\n";
	if (((player_r + 1) == gold_r && (player_c) == gold_c) || ((player_r - 1) == gold_r && (player_c) == gold_c) || ((player_c + 1) == gold_c && (player_r) == gold_r) || ((player_c - 1) == gold_c && player_r == gold_r)) if (rooms[gold_r][gold_c].hasGold) std::cout << "You see a glimmer nearby.\n";
}

void Cave::checkPlayerPosition()
{
	if (player_r == wumpus_r && player_c == wumpus_c) {
		rooms[wumpus_r][wumpus_c].virEvent->interact();
		lose = true;
		isPlaying = false;
	}
	else if (player_r == gold_r && player_c == gold_c) {
		rooms[gold_r][gold_c].virEvent->interact();
		hasGold = true;
		rooms[gold_r][gold_c].hasGold = false;
	}
	for (int i = 0; i < 2; i++) if (player_r == bat_r[i] && player_c == bat_c[i]) {
		rooms[bat_r[i]][bat_c[i]].virEvent->interact();
		teleportPlayer();
	}
	for (int i = 0; i < 2; i++) if (player_r == pit_r[i] && player_c == pit_c[i]) {
		rooms[pit_r[i]][pit_c[i]].virEvent->interact();
		isPlaying = false;
	}
}

void Cave::deleteRooms()
{
	for (int i = 0; i < size; i++) delete[] rooms[i]; delete[] rooms;
}

void Cave::repeat()
{
	int redo;
	std::cout << "Do you want to play again? (1 = yes, 0 = no)\n";
	std::cin >> redo;
	if (redo == 1) {
		int choice;
		std::cout << "Same size? (1 = yes, 0 = no)\n";
		std::cin >> choice;
		if (choice == 1) {
			setup(size);
			playGame();
		}
		else {
			int new_size;
			std::cout << "What size?\n";
			std::cin >> new_size;
			setup(new_size);
			playGame();
		}
	}
	else {
		return;
	}
}