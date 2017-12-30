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
	int After_Play_Q();
	MJtiles Play_AI(int, int);
	MJtiles Play_Human(int, int);
	void Human_Strategy(int HU_ID, int position, MJtile t, int &actiontype, int &actionparameter);

	int roll_dice();
	void init_collection();
	void give_info(int, MJtile*, int);

	void Print_All(int);
	void Print_GOD(); // God's view -> for debugging
	void Show_Result();
private:
	vector<MJplayer*> _players;
	//int rounds;
	int valueofpoints;
	int human_num;
	MJcollection _MJC;
};

#endif
