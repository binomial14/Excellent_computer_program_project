#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "Shuffler.h"
#include "MJplayer.h"

using namespace std;


#ifndef MJSTAGE
#define MJSTAGE

class MJstage{
public:
	MJstage(); // fucking nothing constructor
	MJstage(vector<MJplayer*>&, int, int, int); // MJgame::start() will call this
	~MJstage();

	void Control(int);
	bool After_Play_Q(int&, int&, MJtile*, MJtile&);
	MJtile Play_AI(int,bool&);
	MJtile Play_Human(int,bool&);
	void Human_Strategy(int HU_ID, int position, MJtile t, int &actiontype, int &actionparameter);

	int roll_dice();
	void init_collection();
	void give_info(int, MJtile*, int);

	void Print_All();
	void Print_GOD(); // God's view -> for debugging
	void Show_Result(int);
private:
	vector<MJplayer*> _players;
	//int rounds;
	int valueofpoints;
	int human_num;
	int Now_Player;
	MJcollection _MJC;
};

#endif
