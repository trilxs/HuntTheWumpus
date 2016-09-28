#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <thread>
#include "Cave.h"
//#include "AI.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    cout <<"ERROR: wrong amount of arguments " << endl;
    cout <<"USAGE: file_name -s # " << endl;
    cout << endl;
  }
  else
  {
    int size = atoi(argv[2]);
    if(size < 4)
    {
      cout <<"ERROR: Caves with less than 4 rooms on one side are not allowed. " << endl;
      cout << endl;
      exit(1);
    }
    else
    {
      cout <<"Size of Cave: " << size << endl;

    }
//	AI bot;
//	thread _run(bot.playAI());
//	if (_run.joinable()) _run.join();
    Cave game(size);
    game.playGame();
  }

  return 0;
}
