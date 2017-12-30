#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "MJstage.h"

using namespace std;


MJstage::MJstage(){
	valueofpoints=0;
	_players.clear();
}

MJstage::MJstage(vector<MJplayer*> &_init_players,int _rounds,int _valofpt,int _init_human_num){
	
	//rounds=_rounds;
	valueofpoints=_valofpt;
	human_num=_init_human_num;

	for(int i=0;i<_init_players.size();++i){
		_players.push_back(_init_players[i]);
	}
}

void MJstage::Control(int _FST_Player){
	// _FST_Player -> first player (0~3)
	// This function is to control the whole game

	// type:eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6
	// type:huother=7 huown=8

	int Now_Player=_FST_Player; // Remembers who's playing now (0~3)
	// human players' number: 1~human_num (-> 0~human_num-1)
	int Now_Actiontype=0; // Action type
	int Now_Actionparameter=0; // Where are you doing this action
	MJtiles Action_T[10];
	MJtiles Return_T;

	// Initialize everyone's _hand (arrange and applique)
	(_players[(Now_Player+0)%4])->P_initial(_MJC);
	(_players[(Now_Player+1)%4])->P_initial(_MJC);
	(_players[(Now_Player+2)%4])->P_initial(_MJC);
	(_players[(Now_Player+3)%4])->P_initial(_MJC);

	// First Player: draw
	(_players[Now_Player])->P_draw(_MJC);
	Print_
	if(Now_Player>=0 && Now_Player<human_num){
		Return_T=Play_Human(Now_Player);
	}
	else {
		Return_T=Play_AI(Now_Player);
	}

	/*for(int i=0;i<4;++i){
		(_players[i])->getinfo(Now_Player,);
	}*/


	while(1){
		if(_MJC.size()==0)break; // No more tiles to draw

		(_players[Now_Player])->P_draw(_MJC);

		MJtiles _PLAY_TILE=
	}

}

MJtiles MJstage::Play_AI(int _P_ID){
	// _P_ID: player ID

}

MJtiles MJstage::Play_Human(int _P_ID){
	// _P_ID: player ID

}

int MJstage::roll_dice(){
	// set who's first
	int _roll_dice=rand()%4+1;
	//east = 1 ,south = 2 , west = 3 , north = 4
	cout<<"After rolling the dice, the first player will be ";
	switch(_roll_dice){
		case 1:  cout<<"east  1"; break;
		case 2:  cout<<"south 2"; break;
		case 3:  cout<<"west  3"; break;
		case 4:  cout<<"north 4"; break;
		default: cout<<"bang!";
	}
	puts("");
	
	return _roll_dice;
}

void MJstage::init_collection(){
	MJtiles _all_tiles[144];
	Shuffler _SF;
	_SF.init();
	_SF.fill(_all_tiles); // Fill _all_tiles with randomized tiles
	_MJC=MJcollection(_all_tiles); // Initialize collection

	for(int i=1;i<=4;++i){
		// Initialize each player's _hand;
		(_players[i-1])->Reset_Hand(_all_tiles+(i-1)*16,16);
		(_players[i-1])->Print_Hand(); // Debug code
	}
	// After giving each player 16 tiles -> total gave out 16*4=64 tiles
	// New front = 64 (because 0~63 has been given out)
	_MJC.change_front(64);

}

void MJstage::Print_All(int _P_ID){
	
}