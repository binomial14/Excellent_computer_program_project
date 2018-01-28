#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "MJstage.h"

using namespace std;

const int _wait_time=0;

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
	for(int i=0;i<4;++i){
		_tmp_tiles.push_back(MJtile());
	}
}

MJstage::~MJstage(){
	// empty
}

void MJstage::Control(int _FST_Player){
	// _FST_Player -> first player (0~3)
	// This function is to control the whole game

	// type: nothing=0 eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6 hu=7 play=8


	Now_Player=_FST_Player; // Reset Initial Player (0~3)
	// human players' number: 1~human_num (-> 0~human_num-1)
	int Now_Actiontype=0; // Action type
	int Now_Actionparameter=0; // Where you are doing this action
	MJtile Action_T[10];
	MJtile Return_T;

	const int human_ID=0;
	// When there is only 1 human player, we choose to show only the human's hand.

	// Initialize everyone's _hand (arrange and applique)
	(_players[(Now_Player+0)%4])->initial(_MJC);
	(_players[(Now_Player+1)%4])->initial(_MJC);
	(_players[(Now_Player+2)%4])->initial(_MJC);
	(_players[(Now_Player+3)%4])->initial(_MJC);

	Print_All(human_ID);
	//Print_GOD();
	Pause_time();
	Clean_Screen();

	// First Player: draw
	cout<<"Player "<<Now_Player+1<<" draws a tile.\n\n";
	(_players[Now_Player])->draw(_MJC);

	//Print_GOD();
	Print_All(human_ID);
	Pause_time();
	Clean_Screen();
	
	bool check_hu=false;
	if(Now_Player>=0 && Now_Player<human_num){
		Return_T=Play_Human(0,check_hu);
		Clean_Screen();
	}
	else {
		Return_T=Play_AI(0,check_hu);
	}
	//Print_GOD();
	Print_All(human_ID);

	cout<<"Player "<<Now_Player+1<<" played:\n";
	cout<<Return_T;
	Pause_time();
	Clean_Screen();


	while(1){
		if(_MJC.size()<=16)break; // No more tiles to draw

		/*cout<<"Player "<<Now_Player+1<<" played:\n";
		cout<<Return_T;*/

		bool check_act=After_Play_Q(Now_Actiontype,
				Now_Actionparameter,Action_T,Return_T);

		Pause_time();
		Clean_Screen();
		if(!check_act){ // no one acts
			Now_Player=(Now_Player+1)%4;
			// draw one tile
			(_players[Now_Player])->draw(_MJC);
			cout<<"Player "<<Now_Player+1<<" draws a tile.\n\n";
		}
		else { // someone wants to act
			switch(Now_Actiontype){
				case 1:
					//give_eat(Return_T,Now_Actionparameter);
					give_info(Now_Player,3,
						(_players[Now_Player])->eat(Return_T,Now_Actionparameter));
					break;
				case 2:
					//give_pong(Return_T);
					give_info(Now_Player,3,
						(_players[Now_Player])->pong(Return_T));
					break;
				case 3:
					give_minggone(Return_T);
					give_info(Now_Player,4,
						(_players[Now_Player])->minggone(Return_T,_MJC));
					break;
				case 7:
					(_players[Now_Player])->huother(Return_T);
					break;
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

		//Print_GOD();
		Print_All(human_ID);
		Pause_time();
		Clean_Screen();
		
		// Now_Player needs to act now:
		if(Now_Actiontype==3){ // minggone
			check_act=0;
		}
		bool check_hu=false;
		if(Now_Player>=0 && Now_Player<human_num){
			Return_T=Play_Human(check_act,check_hu);
			Clean_Screen();
		}
		else {
			Return_T=Play_AI(check_act,check_hu);
		}

		if(check_hu){
			Print_All(human_ID);
			Show_Result(1); // huown
			return;
		}
		
		//Print_GOD();
		Print_All(human_ID);
		cout<<"Player "<<Now_Player+1<<" played:\n";
		cout<<Return_T;
		
		Pause_time();
		Clean_Screen();
	}

	Show_Result(2); // _MJC empty, no one wins
}

bool MJstage::After_Play_Q(int& Now_Actiontype,
	int& Now_Actionparameter,MJtile* Action_T,MJtile& Return_T){

	bool change_player=false;
	int _action_list[4];
	int _param_list[4];
	_action_list[Now_Player]=_param_list[Now_Player]=0;
	bool check_act=false;

	// Ask each player
	for(int _PID=1;_PID<=3;++_PID){
		// ask other three players
		int Next_P=(Now_Player+_PID)%4;
		if(Next_P>=0 && Next_P<human_num){ // human
			Human_Strategy(Next_P,Now_Player,Return_T,Now_Actiontype,Now_Actionparameter);
			_action_list[Next_P]=Now_Actiontype;
			_param_list[Next_P]=Now_Actionparameter;
		}
		else { // AI
			Now_Actiontype=Now_Actionparameter=0;
			(_players[Next_P])->strategy(Now_Player+1,Return_T,Now_Actiontype,Now_Actionparameter);
			_action_list[Next_P]=Now_Actiontype;
			_param_list[Next_P]=Now_Actionparameter;
		}
	}
		// See if there's someone who wants to do something
	
	// Priority: huother > pong = minggone > eat
	for(int i=0;i<4 && !check_act;++i){
		int Next_P=(Now_Player+i)%4;
		if(_action_list[Next_P]==7){
			// huother
			//(_players[Next_P])->huother(Return_T);
			Now_Player=Next_P;
			Now_Actiontype=_action_list[Next_P];
			Now_Actionparameter=_param_list[Next_P];
			return true;
		}
	}
	for(int i=0;i<4 && !check_act;++i){
		int Next_P=(Now_Player+i)%4;
		if(_action_list[Next_P]==2){
			// pong
			//(_players[Next_P])->pong(Return_T);
			Now_Player=Next_P;
			Now_Actiontype=_action_list[Next_P];
			Now_Actionparameter=_param_list[Next_P];
			return true;
		}
		else if(_action_list[Next_P]==3){
			// minggone
			//(_players[Next_P])->minggone(Return_T,_MJC);
			Now_Player=Next_P;
			Now_Actiontype=_action_list[Next_P];
			Now_Actionparameter=_param_list[Next_P];
			return true;
		}
	}
	for(int i=0;i<4 && !check_act;++i){
		int Next_P=(Now_Player+i)%4;
		if(_action_list[Next_P]==1){
			// eat
			//(_players[Next_P])->eat(Return_T,Now_Actionparameter);
			Now_Player=Next_P;
			Now_Actiontype=_action_list[Next_P];
			Now_Actionparameter=_param_list[Next_P];
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
	if(position==((HU_ID+4-1)%4) && ((_players[HU_ID])->caneat(t))>0){
		// eat=1
		do_list.push_back(1);
	}
	if((_players[HU_ID])->canpong(t)){
		// pong=2
		do_list.push_back(2);
	}
	if(position!=((HU_ID+4-1)%4) && (_players[HU_ID])->canminggone(t)){
		// minggone=3
		do_list.push_back(3);
	}
	/*if(position!=((HU_ID+4-1)%4) && (_players[HU_ID])->canbugone(t)){
		// bugone=5
		do_list.push_back(5);
	}*/
	if((_players[HU_ID])->canhu(t)){
		// huother=7
		do_list.push_back(7);
	}
	if(do_list.size()==0){
		actiontype=-1;
		cout<<"Sadly, you cannot do anything.\n";
		return;
	}

	Print_Without_Self(0);
	cout<<"==============================================";
	cout<<"==============================================\n";

	cout<<"Your hand: \n";
	(_players[HU_ID])->Print_Hand();

	cout<<"Choose the moves you prefer:\n";
				     cout<<"nothing:  0\n";
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
		if(_enter_num==0)break;
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
		case 0:  cout<<"do nothing\n";  break;
		case 1:  cout<<"eat:      1\n"; break;
		case 2:  cout<<"pong:     2\n"; break;
		case 3:  cout<<"minggone: 3\n"; break;
		case 7:  cout<<"huother:  7\n"; break;
		default: cout<<"bang!\n";
	}
	cout<<endl;

	if(_enter_num==1){ // ask eat type
		int _eat_method=(_players[HU_ID])->caneat(t);
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
	int _Acttype=8,_Actpar=0;
	MJtile tmp;

	if(play_type){
		(_players[Now_Player])->strategy(Now_Player+1,tmp,_Acttype,_Actpar);
		MJtile Return_T=(_players[Now_Player])->play(_Actpar);

		return Return_T;
	}

	while(1){
		_Acttype=8;_Actpar=0;
		(_players[Now_Player])->strategy(Now_Player+1,tmp,_Acttype,_Actpar);
		int last_pos=(_players[Now_Player])->total_len()
					-(_players[Now_Player])->faceup_len()
					+(_players[Now_Player])->stage();
		if(_Acttype==7){
			(_players[Now_Player])->huown();
			if_hu=true;
			return MJtile();
		}
		else if(_Acttype==8){
			MJtile Return_T=(_players[Now_Player])->play(_Actpar);
			return Return_T;
		}
		else if(_Acttype==4){
			//give_angone();
			give_info(Now_Player,4,
				(_players[Now_Player])->angone(last_pos,_MJC));
		}
		else if(_Acttype==5){
			//give_bugone((_players[Now_Player])->get_tile(last_pos));
			give_info(Now_Player,4,
				(_players[Now_Player])->bugone(last_pos,_MJC));
			
		}
	}
}

MJtile MJstage::Play_Human(int play_type,bool &if_hu){

	int _enter_num=0;

	int choose_range=(_players[Now_Player])->total_len()-(_players[Now_Player])->faceup_len()+(_players[Now_Player])->stage();
	
	if(play_type){ // just throw something out
		Print_Play_Hand();
		cout<<"Which tile do you want to play? ";
		// _faceup_len ~ _total_len
		while(1){
			cin>>_enter_num;
			if(1<=_enter_num && choose_range>=_enter_num)break;
			else {
				cout<<"Please enter an integer between "<<1;
				cout<<" and "<<choose_range<<endl;
			}
		}
		return (_players[Now_Player])->play(_enter_num);
	}

	while(1){
		Print_Play_Hand();
		MJtile last_tile=(_players[Now_Player])->get_last();

		cout<<"What do you want to do?\n";
		vector<int> do_list; do_list.clear();

		if((_players[Now_Player])->canangone(last_tile)){
			do_list.push_back(4);
			cout<<"angone:            4\n";
		}
		if((_players[Now_Player])->canbugone(last_tile)){
			do_list.push_back(5);
			cout<<"bugone:            5\n";
		}
		if((_players[Now_Player])->canhu(last_tile)){
			do_list.push_back(7);
			cout<<"huown:             7\n";
		}
			cout<<"Play one tile out: 8\n"; do_list.push_back(8);

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
		if(_enter_num==8){
			cout<<"Which tile do you want to play? ";
			// _faceup_len ~ _total_len
			while(1){
				cin>>_enter_num;
				if(1<=_enter_num && choose_range>=_enter_num)break;
				else {
					cout<<"Please enter an integer between "<<1;
					cout<<" and "<<choose_range<<endl;
				}
			}
			return (_players[Now_Player])->play(_enter_num);
		}
		else if(_enter_num==4){
			//give_angone();
			give_info(Now_Player,4,
				(_players[Now_Player])->angone(choose_range,_MJC));
			cout<<"Angone!\n";
		}
		else if(_enter_num==5){
			//give_bugone((_players[Now_Player])->get_tile(choose_range));
			give_info(Now_Player,4,
				(_players[Now_Player])->bugone(choose_range,_MJC));
			cout<<"Bugone!\n";
		}
		else if(_enter_num==7){
			(_players[Now_Player])->huown();
			if_hu=true;
			cout<<"Huown!\n";
			return MJtile();
		}
	}
}

int MJstage::roll_dice(){
	// set who's first
	srand((unsigned)time(NULL));
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
	
	return _roll_dice-1; // 0~3
}


// ===============Initialization=================
void MJstage::init_collection(){
	MJtile _all_tiles[144];
	Shuffler _SF;

	srand((unsigned)time(NULL));
	int _rand_num=rand()%10+1;
	
	for(int i=0;i<_rand_num;++i){
		_SF.init();
	}

	_SF.fill(_all_tiles); // Fill _all_tiles with randomized tiles
	_MJC=MJcollection(_all_tiles); // Initialize collection

	for(int i=1;i<=4;++i){
		// Initialize each player's _hand;
		(_players[i-1])->set_hand(_all_tiles+(i-1)*16);
		//(_players[i-1])->Print_Hand(); // Debug code
	}
	// After giving each player 16 tiles -> total gave out 16*4=64 tiles
	// New front = 64 (because 0~63 has been given out)
	_MJC.change_front(64);

}

// ===================Giving Information==================
void MJstage::give_info(int position, int tiles_num,  vector<MJtile> vm){
	for(int i=0;i<4;++i){
		if(i==position)continue;
		(_players[i])->getinfo(position+1,vm,tiles_num);
	}
}

void MJstage::give_eat(MJtile t,int e_actionparameter){

	_tmp_tiles[1].setfromId(t.getTileId());
	if(e_actionparameter==1){
		_tmp_tiles[0]=MJtile(t.getTileId()-2*16);
		_tmp_tiles[2]=MJtile(t.getTileId()-1*16);
	}
	else if(e_actionparameter==2){
		_tmp_tiles[0]=MJtile(t.getTileId()-1*16);
		_tmp_tiles[2]=MJtile(t.getTileId()+1*16);
	}
	else{
		_tmp_tiles[0]=MJtile(t.getTileId()+1*16);
		_tmp_tiles[2]=MJtile(t.getTileId()+2*16);
	}
}
void MJstage::give_pong(MJtile t){
	_tmp_tiles[0].setfromId(t.getTileId());
	_tmp_tiles[1].setfromId(t.getTileId());
	_tmp_tiles[2].setfromId(t.getTileId());
}
void MJstage::give_minggone(MJtile t){
	_tmp_tiles[0].setfromId(t.getTileId());
	_tmp_tiles[1].setfromId(t.getTileId());
	_tmp_tiles[2].setfromId(t.getTileId());
	_tmp_tiles[3].setfromId(t.getTileId());
}
void MJstage::give_angone(){
	_tmp_tiles[0]=MJtile();
	_tmp_tiles[1]=MJtile();
	_tmp_tiles[2]=MJtile();
	_tmp_tiles[3]=MJtile();
}
void MJstage::give_bugone(MJtile t){
	_tmp_tiles[0].setfromId(t.getTileId());
	_tmp_tiles[1].setfromId(t.getTileId());
	_tmp_tiles[2].setfromId(t.getTileId());
	_tmp_tiles[3].setfromId(t.getTileId());
}
void MJstage::give_applique(MJtile t){
	_tmp_tiles[0].setfromId(t.getTileId());
}

void MJstage::Print_Without_Self(int _PID){
	
	cout<<"Number of tiles left in collection: "<<_MJC.size()<<".\n\n";
	for(int i=0;i<4;++i){
		if(i==_PID)continue;
		cout<<"Player "<<i+1<<" :\n";
		(_players[i])->showhandtoothers();
		//(_players[i])->Print_Hand();
	}
	
}

void MJstage::Print_Play_Hand(){
	Print_Without_Self(0);
	cout<<"==============================================";
	cout<<"==============================================\n";

	cout<<"Your hand:\n";
	for(int i=0;i<=(_players[Now_Player])->faceup_len();++i){
		cout<<"    ";
	}
	int choose_range=(_players[Now_Player])->total_len()-(_players[Now_Player])->faceup_len()+(_players[Now_Player])->stage();
	for(int i=1;i<choose_range;++i){
		printf(" %2d ",i);
	}
	cout<<"    ";
	printf(" %2d ",choose_range);
	cout<<endl;
	(_players[Now_Player])->Print_Hand();
}

void MJstage::Print_All(int _PID){
	
	cout<<"Number of tiles left in collection: "<<_MJC.size()<<".\n\n";
	for(int i=0;i<4;++i){
		cout<<"Player "<<i+1<<" :\n";
		if(i==_PID && human_num)(_players[i])->Print_Hand();
		else (_players[i])->showhandtoothers();
	}
	
}

void MJstage::Print_GOD(){
	// Print Information
	
	cout<<"Number of tiles left in collection: "<<_MJC.size()<<".\n\n";

	for(int i=0;i<4;++i){
		cout<<"Player "<<i+1<<" :\n";
		(_players[i])->Print_Hand();
	}
}

void MJstage::Show_Result(int end_type){
	_end_type_=end_type;
	if(end_type==0){
		// huother
		cout<<"Player "<<Now_Player+1<<" won this round by HU OTHER!!!\n";
		(_players[Now_Player])->Print_Hand();
	}
	else if(end_type==1){
		// huown
		cout<<"Player "<<Now_Player+1<<" won this round by HU OWN!!!\n";
		(_players[Now_Player])->Print_Hand();
	}
	else if(end_type==2){
		// _MJC empty
		cout<<"Collection is empty...\n";
	}
}

int MJstage::get_win_player()const{
	if(_end_type_==2)return 0;
	return Now_Player+1;
}

void MJstage::Pause_time()const{
	//Sleep(_wait_time);
	//cin.get();

	
	cout<<"-----------------------------------------------------------------------------\n";
	fgetc(stdin);
	
}

void MJstage::Clean_Screen()const{
	//system("cls");
}
