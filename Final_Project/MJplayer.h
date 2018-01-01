#ifndef MJPLAYER 
#define MJPLAYER 
#include <iostream>
#include "MJhand.h"
using namespace std;
class MJplayer{
public :
	MJplayer();
	MJplayer(int , int/*, MJtile*, int*/);
	~MJplayer();
	int Get_Pos() const;
	int Get_Mon() const;
	void Print_Hand() const;
	void Reset_Hand(MJtile*, int);
	void strategy(int position, MJtile t, int &actiontype, int &actionparameter);
	void getinfo(int position, MJtile* ts, int tiles_num);
	//type: eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6

	int P_total_len() const;
	int P_faceup_len() const;
	void P_set_faceup_len(int f);
	bool P_stage() const;
	void P_set_stage(bool s);
	void P_set_last(const MJtile&); // debug code
	MJtile P_get_last()const;
	
	int P_caneat(const MJtile&);
	bool P_canpong(const MJtile&);
	bool P_canminggone(const MJtile&);
	bool P_canangone(const MJtile&);
	bool P_canbugone(const MJtile&);
	bool P_canhu(const MJtile&);
	
	void P_arrange();
	void P_draw(MJcollection&);
	MJtile P_play(int);
	void P_faceup(int);
	void P_applique(int, MJcollection&);
	void P_initial(MJcollection&);
	
	void P_eat(const MJtile&, int);
	void P_pong(const MJtile&);
	void P_minggone(const MJtile&, MJcollection&);
	void P_angone(int, MJcollection&);
	void P_bugone(int, MJcollection&);
	void P_huother(const MJtile&);
	void P_huown();

private :
	MJhand _hand;
	int _position;//east = 1 ,south = 2 , west = 3 , north = 4 
	// -> 0 , 1 , 2 , 3 (because it's easier to use for comparing (..%4))
	int _money;

};
#endif
