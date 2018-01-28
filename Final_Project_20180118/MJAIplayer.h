#ifndef MJAIPLAYER
#define MJAIPLAYER

#include "MJplayer.h"
//#include <cstdlib>
#include <cmath>
using namespace std;

class MJAIplayer: public MJplayer{
public:
	MJAIplayer(int , int);

	virtual void strategy(int position, MJtile t, int &actiontype, int &actionparameter);
	virtual void getinfo(int position, vector<MJtile> ts, int tiles_num);
	//type: nothing=0 eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6 hu=7 8=play
	
	int strategy_play();

	inline double miss_tile_chances(int,int);
	inline double miss_tile_chances_2(int,int,int);
	inline double value_function(int); // Most Important Part!!!!!!!
	inline double Find_Da(int,int,double);
	inline double Find_UnDa(int,double);
	inline double Find_Single(int);

	void reset_my_count();
	void ts_cal();

	void Print_Get()const;

private:
	void set_hand(MJtile*);

	// remember past moves and used tiles
	int count_used_pos[5][5][10];
	// position 1~4, suit 1~4, rank 1~9
	int count_tile[5][10];
	int count_my_tile[5][10];
	int count_my_tile_old[5][10];

	// For value function
	int _ts[5][10]; // suit:1~4, rank: 1~9

	double dconst; // how good is a dahzi
	double sconst; // how good is a single
};

#endif