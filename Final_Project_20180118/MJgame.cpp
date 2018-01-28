#include "MJgame.h"

using namespace std;

const int _wait_time=3000;

MJgame::MJgame(){
	//MJanimation ANM;

	//ANM.Opening();

	cout<<endl;
	cout<<"*******************************************"<<endl;
	cout<<"*********Welcome to Taiwan Mahjong*********"<<endl;
	cout<<"*******************************************"<<endl;
	cout<<endl;
	// length=42

	//cout<<"This program was built by:"<<endl;
	cout<<"NTUEE"<<endl;
	cout<<"Harry Chang, Leo Wu, and Yen-Yen Teng"<<endl;
	cout<<"2017 Nov - 2018 Jan"<<endl;
	cout<<endl;
	cout<<"If there's any problem, please tell us~"<<endl;
	cout<<endl;
	//system("pause");
	//Sleep(_wait_time);
	/*Pause_time();
	cout<<endl;*/

	rounds=valueofpoints=human_num=0;
	_players.clear();

	for(int i=0;i<5;++i){
		count_win[i]=0;
	}
}
MJgame::~MJgame(){
	// empty
}
void MJgame::setting(){
	while(1){
		cout<<"How many human players? (0 or 1) ";
		cin>>human_num; // Human players will start from 1
		while(human_num>1 || human_num<0){
			cout<<"Please enter 0 or 1: ";
			cin>>human_num;
		}
		cout<<"Please enter ROUNDS: ";
		cin>>rounds;
		while(rounds<=0){
			cout<<"Please enter an integer larger than 0: ";
			cin>>rounds;
		}
		cout<<"Please enter Value of Points: ";
		cin>>valueofpoints;

		cout<<"\n\n";

		cout<<"  "<<human_num<<" human player(s)\n";
		cout<<"  "<<4-human_num<<" AI player(s)\n";
		cout<<"  "<<rounds<<" round(s)\n";
		cout<<"  "<<"Value of points: "<<valueofpoints<<endl;
		cout<<endl;

		cout<<"Is this the correct input? [y/n]: ";
		char _str[10];
		cin>>_str;
		if(_str[0]=='y' || _str[0]=='Y')break;
	}

	//system("cls"); // clean screen

	cout<<"Player 1 East:  "; if(human_num>=1)cout<<"human";else cout<<"AI";
	cout<<endl;
	cout<<"Player 2 South: "; if(human_num>=2)cout<<"human";else cout<<"AI";
	cout<<endl;
	cout<<"Player 3 West:  "; if(human_num>=3)cout<<"human";else cout<<"AI";
	cout<<endl;
	cout<<"Player 4 North: "; if(human_num==4)cout<<"human";else cout<<"AI";
	cout<<"\n\n";

	cout<<"Moves: \n";
	cout<<"0: nothing\n1: eat\n2: pong\n3: minggone\n4: angone\n5: bugone\n6: applique\n7: hu\n8: play\n\n";
	Pause_time();
	Clean_Screen();
	// Set players
	for(int i=1;i<=4;++i){
		if(i==1 && human_num>0)_players.push_back(new MJplayer(i,valueofpoints));
		else _players.push_back(new MJAIplayer(i,valueofpoints));
	}
}

void MJgame::start() {
	cout<<"Let's Play!"<<endl;

	MJstage New_Stage=MJstage(_players,rounds,valueofpoints,human_num);
	int _who_first=New_Stage.roll_dice();

	for(int _rnd=1;_rnd<=rounds;++_rnd){ // rounds
		New_Stage.init_collection(); // Initialize collection
		cout<<"\n\n";
		cout<<"Round "<<_rnd<<" !\n";
		cout<<"===========================================================\n\n";
		New_Stage.Control((_who_first+_rnd-1)%4); // Start Game
		count_win[New_Stage.get_win_player()]++;

		cout<<"===========================================================\n\n";
		cout<<"End of round "<<_rnd<<" !\n\n";
		Pause_time();
		Clean_Screen();
	}
}

void MJgame::end() {
	for(int i=0;i<4;++i){
		delete _players[i]; // Not sure if it works
	}
	_players.clear();

	cout<<"Total Result:\n";
	for(int i=1;i<=4;++i){
		cout<<"Player "<<i<<" won "<<count_win[i]<<" rounds!!\n";
	}
	cout<<endl;

	cout<<"===========================\n\n";
	cout<<"Game Ended.\n\n";
	cout<<"Thanks for playing Taiwan Mahjong!!!!\n\n";
	cout<<"Press any button to exit.." << endl;
	Pause_time();
}

void MJgame::Pause_time()const{
	//Sleep(_wait_time);
	//cin.get();
	fgetc(stdin);
}

void MJgame::Clean_Screen()const{
	//system("cls");
}
