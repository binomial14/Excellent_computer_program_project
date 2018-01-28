#ifndef MJPLAYER 
#define MJPLAYER 
#include <iostream>
#include <vector>
#include "MJhand.h"
using namespace std;
class MJplayer:public MJhand{
	friend class MJstage;
public:
	MJplayer();
	MJplayer(int , int/*, MJtile*, int*/);
	~MJplayer();
	int Get_Pos() const;
	int Get_Mon() const;
	void Print_Hand();
	void Set_Pos(int);
	//void Reset_Hand(MJtile*, int);
	virtual void strategy(int position, MJtile t, int &actiontype, int &actionparameter);
	virtual void getinfo(int position, vector<MJtile> ts, int tiles_num);
	//type: nothing=0 eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6 hu=7 8=play

protected:
	//MJhand _hand;
	void set_hand(MJtile*);
	int _position;//east = 1 ,south = 2 , west = 3 , north = 4 
	// -> 0 , 1 , 2 , 3 (because it's easier to use for comparing (..%4))
	int _money;

};
#endif
