#include <iostream>
#include "MJhand.h"
#include "MJplayer.h"
using namespace std;

MJplayer::MJplayer(){
	// empty
}
MJplayer::MJplayer(int _init_pos, int _init_money/*, 
	MJtile* _init_tiles, int _init_tiles_len*/){
	_total_len=_faceup_len=_stage=0;
    for (int i=0; i<30; i++) {
        _tiles[i]=MJtile();
        noreveal[i]=0;
    }
	_position=_init_pos;
	_money=_init_money;
	//_hand=MJhand(/*_init_tiles,_init_tiles_len*/);
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
void MJplayer::Set_Pos(int _pos){
	_position=_pos;
}
void MJplayer::Print_Hand(){
	cout<<*(this);
}
void MJplayer::set_hand(MJtile* _init_tiles){
	_faceup_len=0;
    _total_len=16;
    _stage=0;
	for(int i=0;i<16;++i){
		_tiles[i].setfromId(_init_tiles[i].getTileId());
	}
	for(int i=0;i<30;++i){
		noreveal[i]=0;
	}
}
void MJplayer::strategy(int position, MJtile t, 
	int &actiontype, int &actionparameter){
	// do nothing -> brainless AI
	// type: nothing=0 eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6 hu=7 play=8
	// actionparmeter: 
	if(canhu(t) && position==_position){ // huown
		actiontype=7;
		return;
	}
	if(actiontype==8){ // play
		actiontype=8;
		actionparameter=total_len()-faceup_len()+stage();
		return;
	}
	else {
		actiontype=0; // do nothing
		return;
	}
}
void MJplayer::getinfo(int position, vector<MJtile> ts, int tiles_num){
	// tiles_num = how many tiles are involved in this action

}