#include <iostream>
#include <cstdio>
//#include <cstdlib>
#include <ctime>
//#include <windows.h>

#include "Shuffler.h"
#include "MJplayer.h"
#include "MJAIplayer.h"

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

	// Initialization
	int roll_dice();
	void init_collection();
	
	// Giving Information
	void give_info(int, int, vector<MJtile>);
	void give_eat(MJtile,int);
	void give_pong(MJtile);
	void give_minggone(MJtile);
	void give_angone();
	void give_bugone(MJtile);
	void give_applique(MJtile);

	void Print_Without_Self(int);
	void Print_Play_Hand();
	void Print_All(int);
	void Print_GOD(); // God's view -> for debugging
	void Show_Result(int);
	void Pause_time()const;
	void Clean_Screen()const;
	int get_win_player()const;
private:
	vector<MJplayer*> _players;
	//int rounds;
	int valueofpoints;
	int human_num;
	int Now_Player;
	MJcollection _MJC;
	vector<MJtile> _tmp_tiles;

	int _end_type_;
};

#endif
