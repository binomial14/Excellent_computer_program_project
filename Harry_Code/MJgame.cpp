#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "MJgame.h"
#include "Shuffler.h"

using namespace std;

MJgame::MJgame(){
	cout<<endl;
	cout<<"************************************"<<endl;
	cout<<"******Welcome to Taiwan Mahjong*****"<<endl;
	cout<<"************************************"<<endl;
	cout<<endl; // length=36

	rounds=valueofpoints=_human_num=0;
	_players.clear();
}
MJgame::~MJgame(){
	// empty
}
void MJgame::setting(){
	while(1){
		cout<<"How many human players? ";
		cin>>human_num; // Human players will start from 1
		cout<<"Please enter ROUNDS: ";
		cin>>rounds;
		cout<<"Please enter Value of Points: ";
		cin>>valueofpoints;

		cout<<_human_num<<" human player(s) and "<<4-human_num<<" AI player(s)\n";
		cout<<rounds<<" rounds, value of points: "<<valueofpoints<<endl;

		cout<<"Is this the correct input? [y/n]: ";
		char _str[10];
		cin>>_str;
		if(_str[0]=='y' || _str[0]=='Y')break;
	}

	system("cls"); // clean screen

	// Set players
	for(int i=1;i<=4;++i){
		_players.push_back(new MJplayer(rounds,valueofpoints));
	}
}

void MJgame::start() {
	cout<<"Let's Play!"<<endl;

	MJstage New_Stage=MJstage(_players,rounds,valueofpoints,human_num);
	int _who_first=New_Stage.roll_dice();

	for(int _rnd=1;_rnd<=rounds;++_rnd){ // rounds
		New_Stage.init_collection(); // Initialize collection
		cout<<"Round "<<_rnd<<" !\n";
		New_Stage.Control((_who_first+_rnd-1)%4); // Start Game
	}
}

void MJgame::end() {
	for(int i=0;i<4;++i){
		delete _players[i]; // Not sure if it works
	}
	_players.clear();

	cout << "Game Ended." << endl;
	cout << "Press any button to exit.." << endl;
	cin.get();
}