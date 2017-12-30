#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "MJhand.h"
#include "Shuffler.h"

using namespace std;


#ifndef MJSTAGE
#define MJSTAGE

class MJstage{
public:
	MJstage(); // fucking nothing constructor
	MJstage(vector<MJplayer*>&, int, int, int); // MJgame::start() will call this
	~MJstage();

	void Control(int);
	MJtiles Play_AI(int);
	MJtiles Play_Human(int);

	int roll_dice();
	void init_collection();

	void Print_All(int);
private:
	vector<MJplayer*> _players;
	//int rounds;
	int valueofpoints;
	int human_num;
	MJcollection _MJC;
};

#endif