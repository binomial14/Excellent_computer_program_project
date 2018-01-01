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

MJstage::~MJstage(){
	// empty
}

void MJstage::Control(int _FST_Player){
	// _FST_Player -> first player (0~3)
	// This function is to control the whole game

	// type:do nothing=-1, play=0
	// type:eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6
	// type:huother=7 huown=8

	Now_Player=_FST_Player; // Reset Initial Player (0~3)
	// human players' number: 1~human_num (-> 0~human_num-1)
	int Now_Actiontype=0; // Action type
	int Now_Actionparameter=0; // Where are you doing this action
	MJtile Action_T[10];
	MJtile Return_T;

	// Initialize everyone's _hand (arrange and applique)
	(_players[(Now_Player+0)%4])->P_initial(_MJC);
	(_players[(Now_Player+1)%4])->P_initial(_MJC);
	(_players[(Now_Player+2)%4])->P_initial(_MJC);
	(_players[(Now_Player+3)%4])->P_initial(_MJC);

	Print_GOD();
	system("pause");
	system("cls");

	// First Player: draw
	cout<<"Player "<<Now_Player<<" draws a tile.\n\n";
	(_players[Now_Player])->P_draw(_MJC);
	Print_GOD();
	bool check_hu=false;
	if(Now_Player>=0 && Now_Player<human_num){
		Return_T=Play_Human(0,check_hu);
	}
	else {
		Return_T=Play_AI(0,check_hu);
	}
	cout<<"Player "<<Now_Player+1<<" played:\n";
	cout<<Return_T;
	system("pause");
	system("cls");

	//Print_GOD();
	/*cout<<"Player "<<Now_Player+1<<" played:\n";
	cout<<Return_T;*/


	while(1){
		if(_MJC.size()==0)break; // No more tiles to draw

		cout<<"Player "<<Now_Player+1<<" played:\n";
		cout<<Return_T;

		bool check_act=After_Play_Q(Now_Actiontype,
				Now_Actionparameter,Action_T,Return_T);

		system("pause");
		system("cls");
		if(!check_act){ // no one acts
			Now_Player=(Now_Player+1)%4;
			// draw one tile
			(_players[Now_Player])->P_draw(_MJC);
			cout<<"Player "<<Now_Player+1<<" draws a tile.\n\n";
		}
		else { // someone wants to act
			switch(Now_Actiontype){
				case 1: (_players[Now_Player])->P_eat(Return_T,Now_Actionparameter); break;
				case 2: (_players[Now_Player])->P_pong(Return_T); break;
				case 3: (_players[Now_Player])->P_minggone(Return_T,_MJC); break;
				case 7: (_players[Now_Player])->P_huother(Return_T); break;
				default: cout<<"bang!\n";
			}
			cout<<"Player "<<Now_Player+1<<" ";
			switch(Now_Actiontype){
				case 1:  cout<<"eat:      1\n"; break;
				case 2:  cout<<"pong:     2\n"; break;
				case 3:  cout<<"minggone: 3\n"; break;
				case 7:  cout<<"huother:  7\n"; break;
				default: cout<<"bang!\n";
			}
			//Print_GOD();
			if(Now_Actiontype==7){
				Show_Result(0); // huother
				return;
			}
		}

		Print_GOD();
		system("pause");
		system("cls");
		
		// Now_Player needs to act now:
		if(Now_Actiontype==3){ // minggone
			check_act=0;
		}
		bool check_hu=false;
		if(Now_Player>=0 && Now_Player<human_num){
			Return_T=Play_Human(check_act,check_hu);
			system("cls");
		}
		else {
			Return_T=Play_AI(check_act,check_hu);
		}
		
		Print_GOD();
		cout<<"Player "<<Now_Player+1<<" played:\n";
		cout<<Return_T;

		if(check_hu){
			Show_Result(1); // huown
			return;
		}
		system("pause");
		system("cls");
	}

	Show_Result(2); // _MJC empty, no one wins
}

bool MJstage::After_Play_Q(int& Now_Actiontype,
	int& Now_Actionparameter,MJtile* Action_T,MJtile& Return_T){

	bool change_player=false;
	int _action_list[4];
	_action_list[Now_Player]=-1;
	bool check_act=false;

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
	
	// Priority: huother > pong = minggone > eat
	for(int i=0;i<4 && !check_act;++i){
		int Next_P=(Now_Player+i)%4;
		if(_action_list[Next_P]==7){
			// huother
			//(_players[Next_P])->P_huother(Return_T);
			Now_Player=Next_P;
			Now_Actiontype=_action_list[Next_P];
			return true;
		}
	}
	for(int i=0;i<4 && !check_act;++i){
		int Next_P=(Now_Player+i)%4;
		if(_action_list[Next_P]==2){
			// pong
			//(_players[Next_P])->P_pong(Return_T);
			Now_Player=Next_P;
			Now_Actiontype=_action_list[Next_P];
			return true;
		}
		else if(_action_list[Next_P]==3){
			// minggone
			//(_players[Next_P])->P_minggone(Return_T,_MJC);
			Now_Player=Next_P;
			Now_Actiontype=_action_list[Next_P];
			return true;
		}
	}
	for(int i=0;i<4 && !check_act;++i){
		int Next_P=(Now_Player+i)%4;
		if(_action_list[Next_P]==1){
			// eat
			//(_players[Next_P])->P_eat(Return_T,Now_Actionparameter);
			Now_Player=Next_P;
			Now_Actiontype=_action_list[Next_P];
			return true;
		}
	}

	return false;
}

void MJstage::Human_Strategy(int HU_ID, int position, MJtile t,
	int &actiontype, int &actionparameter){
	// HU_ID:0~3
	// position: who played
	// t: played what
	// actiontype: decide how to act

	if(HU_ID==position){
		actiontype=-1;
		//cout<<"Sadly, you cannot do anything.\n";
		return;
	}

	cout<<"What do you want to do? \n";

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

	cout<<"Your hand: \n";
	(_players[HU_ID])->Print_Hand();

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

	cout<<"You chose to ";
	switch(_enter_num){
		case -1: cout<<"do nothing\n";  break;
		case 1:  cout<<"eat:      1\n"; break;
		case 2:  cout<<"pong:     2\n"; break;
		case 3:  cout<<"minggone: 3\n"; break;
		case 7:  cout<<"huother:  7\n"; break;
		default: cout<<"bang!\n";
	}
	cout<<endl;

	if(_enter_num==1){ // ask eat type
		int _eat_method=(_players[HU_ID])->P_caneat(t);
		if(_eat_method==1 || _eat_method==2 || _eat_method==4){
			actionparameter=_eat_method;
			return;
		}
		cout<<"Which type of EAT do you want?\n";
		if(t.rank()>=3)
			cout<<"type 1: "<<t.rank()-2<<t.rank()-1<<t.rank()<<endl;
		if(t.rank()>=2 && t.rank()<=8)
			cout<<"type 2: "<<t.rank()-1<<t.rank()<<t.rank()+1<<endl;
		if(t.rank()<=7)
			cout<<"type 4: "<<t.rank()<<t.rank()+1<<t.rank()+2<<endl;

		while(1){
			cin>>_enter_num;
			if((_enter_num & _eat_method) && _enter_num<=4 && _enter_num!=3)
				break;
			else cout<<"Please enter a valid integer: ";
		}
		actionparameter=_enter_num;

		cout<<"\nYou chose to eat:\n";
		if(_enter_num==1)
			cout<<"type 1: "<<t.rank()-2<<t.rank()-1<<t.rank()<<endl;
		else if(_enter_num==2)
			cout<<"type 2: "<<t.rank()-1<<t.rank()<<t.rank()+1<<endl;
		else if(_enter_num==4)
			cout<<"type 4: "<<t.rank()<<t.rank()+1<<t.rank()+2<<endl;
		cout<<endl;
	}
}

MJtile MJstage::Play_AI(int play_type,bool &if_hu){
	// play_type : 0->drew a tile (possible to huown), 1->impossible to huown
	int _Acttype=0,_Actpar=0;
	MJtile tmp;
	(_players[Now_Player])->strategy(Now_Player,tmp,_Acttype,_Actpar);
	if(!play_type && _Acttype==8){
		(_players[Now_Player])->P_huown();
		return MJtile();
	}
	 
	MJtile Return_T=(_players[Now_Player])->P_play(_Actpar-(_players[Now_Player])->P_faceup_len()+1);
	/*cout<<"Player "<<Now_Player+1<<" played :\n";
	cout<<Return_T;*/
	return Return_T;
}

MJtile MJstage::Play_Human(int play_type,bool &if_hu){
	// 
	cout<<"Your hand:\n";
	(_players[Now_Player])->Print_Hand();

	int _enter_num=0;

	if(play_type){ // just throw something out
		cout<<"Which tile do you want to play? ";
		// needs to be clear for user to choose
		// Add code here!
		// _faceup_len ~ _total_len
		while(1){
			cin>>_enter_num;
			if(1<=_enter_num &&
				(_players[Now_Player])->P_total_len()-(_players[Now_Player])->P_faceup_len()+(_players[Now_Player])->P_stage()>=_enter_num)break;
			else {
				cout<<"Please enter an integer between "<<1;
				cout<<" and "<<(_players[Now_Player])->P_total_len()-(_players[Now_Player])->P_faceup_len()+(_players[Now_Player])->P_stage()<<endl;
			}
		}
		return (_players[Now_Player])->P_play(_enter_num);
	}

	while(1){
		MJtile last_tile=(_players[Now_Player])->P_get_last();

		cout<<"What do you want to do?\n";
		vector<int> do_list; do_list.clear();
			cout<<"Play one tile out: 0\n"; do_list.push_back(0);
		if((_players[Now_Player])->P_canangone(last_tile)){
			do_list.push_back(4);
			cout<<"angone:            4\n";
		}
		if((_players[Now_Player])->P_canbugone(last_tile)){
			do_list.push_back(5);
			cout<<"bugone:            5\n";
		}
		if((_players[Now_Player])->P_canhu(last_tile)){
			do_list.push_back(8);
			cout<<"huown:             8\n";
		}
		cout<<"Which move do you want to do now? ";

		while(1){
			cin>>_enter_num;
			bool check_num=false;
			for(int i=0;i<do_list.size();++i){
				if(_enter_num==do_list[i]){
					check_num=true;
					break;
				}
			}
			if(check_num)break;
			else {
				cout<<"Please enter a valid integer\n";
			}
		}
		if(_enter_num==0){
			cout<<"Which tile do you want to play? ";
			// needs to be clear for user to choose
			// Add code here!
			// _faceup_len ~ _total_len
			while(1){
				cin>>_enter_num;
				if(1<=_enter_num &&
					(_players[Now_Player])->P_total_len()-(_players[Now_Player])->P_faceup_len()+(_players[Now_Player])->P_stage()>=_enter_num)break;
				else {
					cout<<"Please enter an integer between "<<1;
					cout<<" and "<<(_players[Now_Player])->P_total_len()-(_players[Now_Player])->P_faceup_len()+(_players[Now_Player])->P_stage()<<endl;
				}
			}
			return (_players[Now_Player])->P_play(_enter_num);
		}
		else if(_enter_num==4){
			(_players[Now_Player])->P_angone((_players[Now_Player])->P_total_len()-(_players[Now_Player])->P_faceup_len(),_MJC);
			cout<<"Angone!\n";
		}
		else if(_enter_num==5){
			(_players[Now_Player])->P_bugone((_players[Now_Player])->P_total_len()-(_players[Now_Player])->P_faceup_len(),_MJC);
			cout<<"Bugone!\n";
		}
		else if(_enter_num==8){
			(_players[Now_Player])->P_huown();
			if_hu=true;
			cout<<"Huown!\n";
			return MJtile();
		}
	}
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
	
	return _roll_dice-1; // 1~4
}

void MJstage::init_collection(){
	MJtile _all_tiles[144];
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

void MJstage::Print_All(){
	for(int i=0;i<4;++i){
		cout<<"Player "<<i+1<<" :\n";
		(_players[i])->Print_Hand();
	}
}

void MJstage::Print_GOD(){
	// Print Information
	cout<<"Collection length: "<<_MJC.size()<<endl;

	for(int i=0;i<4;++i){
		cout<<"Player "<<i+1<<" :\n";
		(_players[i])->Print_Hand();
	}
}

void MJstage::Show_Result(int end_type){
	if(end_type==0){
		// huother
		cout<<"Player "<<Now_Player+1<<" won this round by HU OTHER!!!\n";
	}
	else if(end_type==1){
		// huown
		cout<<"Player "<<Now_Player+1<<" won this round by HU OWN!!!\n";
	}
	else if(end_type==2){
		// _MJC empty
		cout<<"Collection is empty...\n";
	}
}
