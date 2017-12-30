#include <iostream>
#include "MJhand.h"
#include "MJplayer.h"
using namespace std;

MJplayer::MJplayer(){
	// empty
}
MJplayer::MJplayer(int _init_pos, int _init_money/*, 
	MJtile* _init_tiles, int _init_tiles_len*/){

	_position=_init_pos;
	_money=_init_money;
	_hand=MJhand(/*_init_tiles,_init_tiles_len*/);
	// remember to change MJhand.cpp -> setfromId

}
MJplayer::~MJplayer(){
	// empty
}
int MJplayer::Get_Pos() const{
	return _position;
}
int MJplayer::Get_Mon() const{
	return _money;
}
void MJplayer::Print_Hand() const{
	cout<<_hand;
}
void MJplayer::Reset_Hand(MJtile* _init_tiles, int _init_tiles_len){
	_hand=MJhand(_init_tiles,_init_tiles_len);
}
void MJplayer::strategy(int position, MJtile t, 
	int &actiontype, int &actionparameter){
	// do nothing -> brainless AI
	actiontype=0;
	actionparameter=_hand.total_len()-1+_hand.stage();
}
void MJplayer::getinfo(int position, MJtile* ts, int tiles_num){
	// fucking empty
}
//type: eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6


// Hand Functions

int MJplayer::P_total_len() const             {return _hand.total_len();}
int MJplayer::P_faceup_len() const            {return _hand.faceup_len();}
void MJplayer::P_set_faceup_len(int f)        {_hand.set_faceup_len(f);}
bool MJplayer::P_stage() const                {return _hand.stage();}
void MJplayer::P_set_stage(bool s)            {_hand.set_stage(s);}
void MJplayer::P_set_last(const MJtile& _t)   {_hand.set_last(_t);}
	
int MJplayer::P_caneat(const MJtile& _t)      {return _hand.caneat(_t);}
bool MJplayer::P_canpong(const MJtile& _t)    {return _hand.canpong(_t);}
bool MJplayer::P_canminggone(const MJtile& _t){return _hand.canminggone(_t);}
bool MJplayer::P_canangone(const MJtile& _t)  {return _hand.canangone(_t);}
bool MJplayer::P_canbugone(const MJtile& _t)  {return _hand.canbugone(_t);}
bool MJplayer::P_canhu(const MJtile& _t)      {return _hand.canhu(_t);}
	
void MJplayer::P_arrange()                    {_hand.arrange();}
void MJplayer::P_draw(MJcollection& _MJ_COL)  {_hand.draw(_MJ_COL);}
MJtile MJplayer::P_play(int _PL_ID)           {return _hand.play(_PL_ID);}
void MJplayer::P_faceup(int _FU_ID)           {_hand.faceup(_FU_ID);}
void MJplayer::P_applique(int _APP_ID, MJcollection& _MJ_COL)
{_hand.applique(_APP_ID,_MJ_COL);}
void MJplayer::P_initial(MJcollection& _MJ_COL){_hand.initial(_MJ_COL);}
	
void MJplayer::P_eat(const MJtile& _t, int _ID){_hand.eat(_t,ID);}
void MJplayer::P_pong(const MJtile& _t)        {_hand.pong(_t);}
void MJplayer::P_minggone(const MJtile& _t, MJcollection& _MJ_COL)
{_hand.minggone(_t,_MJ_COL);}
void MJplayer::P_angone(int _ID, MJcollection& _MJ_COL)
{_hand.angone(_ID,_MJ_COL);}
void MJplayer::P_bugone(int _ID, MJcollection& _MJ_COL)
{_hand.bugone(_ID,_MJ_COL);}
void MJplayer::P_huother(const MJtile& _t)     {_hand.huother(_t);}
void MJplayer::P_huown()                       {_hand.huown();}