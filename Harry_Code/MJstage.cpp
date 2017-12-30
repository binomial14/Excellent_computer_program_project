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
	Print_All();
	if(Now_Player>=0 && Now_Player<human_num){
		Return_T=Play_Human(Now_Player);
	}
	else {
		Return_T=Play_AI(Now_Player);
	}

	while(1){
		if(_MJC.size()==0)break; // No more tiles to draw

		bool check_act=After_Play_Q(Now_Player,Now_Actiontype,
	Now_Actionparameter,Action_T,Return_T);

		if(!check_act){ // no one acts
			Now_Player=(Now_Player+1)%4;
		}
		// here
	}

}

bool MJstage::After_Play_Q(int& Now_Player,int& Now_Actiontype,
	int& Now_Actionparameter,MJtiles* Action_T,MJtiles& Return_T){

	bool change_player=false;
	int _action_list[4];
	_action_list[Now_Player]=-1;
	// Ask each player
	for(int _PID=1;_PID<=3;++_PID){
		// ask other three players
		int Next_P=(Now_Player+_PID)%4;
		if(Next_P>=0 && Next_P<human_num){ // human
			Human_Strategy(Next_P,Now_Player,Return_T,Now_Actiontype,Now_Actionparameter);
			_action_list[Next_P]=Now_Actiontype;
		}
		else { // AI
			(_players[Next_P])->strategy(Now_Player,Return_T,Now_Actiontype,Now_Actionparameter);
			_action_list[Next_P]=Now_Actiontype;
		}
	}
		// See if there's someone who wants to do something
	bool check_act=false;
	// Priority: huother > pong = minggone > eat
	for(int i=0;i<4 && !check_act;++i){
		if(_action_list[i]==7){
			// huother
			(_players[i])->P_huother(Return_T);
			check_act=true;
			Now_Player=i;
			break;
		}
	}
	for(int i=0;i<4 && !check_act;++i){
		if(_action_list[i]==2){
			// pong
			(_players[i])->P_pong(Return_T);
			check_act=true;
			Now_Player=i;
			break;
		}
		else if(_action_list[i]==3){
			// minggone
			(_players[i])->P_minggone(Return_T,_MJC);
			check_act=true;
			Now_Player=i;
			break;
		}
	}
	for(int i=0;i<4 && !check_act;++i){
		if(_action_list[i]==1){
			// eat
			(_players[i])->P_eat(Return_T);
			check_act=true;
			Now_Player=i;
			break;
		}
	}

	return check_act;
}

void MJstage::Human_Strategy(int HU_ID, int position, MJtile t,
	int &actiontype, int &actionparameter){
	// HU_ID:0~3
	// position: who played
	// t: played what
	// actiontype: decide how to act
	cout<<"What do you want to do? ";
	vector<int> do_list; do_list.clear();
	if(position==((HU_ID+4-1)%4) && ((_players[HU_ID])->P_caneat(t))>0){
		// eat=1
		do_list.push_back(1);
	}
	if((_players[HU_ID])->P_canpong(t)){
		// pong=2
		do_list.push_back(2);
	}
	if(position!=((HU_ID+4-1)%4) && (_players[HU_ID])->P_canminggone(t)){
		// minggone=3
		do_list.push_back(3);
	}
	/*if(position!=((HU_ID+4-1)%4) && (_players[HU_ID])->P_canbugone(t)){
		// bugone=5
		do_list.push_back(5);
	}*/
	if((_players[HU_ID])->P_canhu(t)){
		// huother=7
		do_list.push_back(7);
	}
	if(do_list.size()==0){
		actiontype=-1;
		cout<<"Sadly, you cannot do anything.\n";
		return;
	}

	cout<<"Choose the moves you prefer:\n";
				 cout<<"nothing: -1\n";
	for(int i=0;i<do_list.size();++i){
		switch(do_list[i]){
			case 1:  cout<<"eat:      1\n"; break;
			case 2:  cout<<"pong:     2\n"; break;
			case 3:  cout<<"minggone: 3\n"; break;
			//case 4:  cout<<"angone:   4\n"; break;
			//case 5:  cout<<"bugone:   5\n"; break;
			//case 6:  cout<<"applique: 6\n"; break;
			case 7:  cout<<"huother:  7\n"; break;
			//case 8:  cout<<"huown:    8\n"; break;
			default: cout<<"bang!\n";
		}
	}

	cout<<"Enter number: ";
	int _enter_num;
	while(1){
		cin>>_enter_num;
		if(_enter_num==-1)break;
		bool check_num=false;
		for(int i=0;i<do_list.size();++i){
			if(_enter_num==do_list[i]){
				check_num=true;
			}
		}
		if(check_num)break;
		else cout<<"Please enter a valid integer: ";
	}
	actiontype=_enter_num;

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
	
	return _roll_dice; // 1~4
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

void MJstage::give_info(int position, MJtile* ts, int tiles_num){
	for(int i=0;i<4;++i){
		(_players[i])->getinfo(position,ts,tiles_num);
	}
}

void MJstage::Print_All(int _P_ID){

}
