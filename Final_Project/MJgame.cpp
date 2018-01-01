#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "MJgame.h"

using namespace std;

MJgame::MJgame(){
	cout<<endl;
	cout<<"*******************************************"<<endl;
	cout<<"*********Welcome to Taiwan Mahjong*********"<<endl;
	cout<<"*******************************************"<<endl;
	cout<<endl; // length=42

	//cout<<"This program was built by:"<<endl;
	cout<<"NTUEE 2017 Nov - 2018 Jan"<<endl;
	cout<<"Harry Chang, Leo Wu, and Yen-Yen Teng"<<endl;
	cout<<endl;
	cout<<"If there's any problem, please tell us~"<<endl;
	cout<<endl;
	system("pause");
	cout<<endl;

	rounds=valueofpoints=human_num=0;
	_players.clear();
}
MJgame::~MJgame(){
	// empty
}
void MJgame::setting(){
	while(1){
		cout<<"How many human players? ";
		cin>>human_num; // Human players will start from 1
		while(human_num>4 || human_num<0){
			cout<<"Please enter an integer from 0 to 4: ";
			cin>>human_num;
		}
		cout<<"Please enter ROUNDS: ";
		cin>>rounds;
		cout<<"Please enter Value of Points: ";
		cin>>valueofpoints;

		cout<<human_num<<" human player(s) and "<<4-human_num<<" AI player(s)\n";
		cout<<rounds<<" rounds, value of points: "<<valueofpoints<<endl;

		cout<<"Is this the correct input? [y/n]: ";
		char _str[10];
		cin>>_str;
		if(_str[0]=='y' || _str[0]=='Y')break;
	}

	system("cls"); // clean screen

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
	system("pause");
	system("cls");
	// Set players
	for(int i=1;i<=4;++i){
		_players.push_back(new MJplayer(i-1,valueofpoints));
	}
}

void MJgame::start() {
	cout<<"Let's Play!"<<endl;

	MJstage New_Stage=MJstage(_players,rounds,valueofpoints,human_num);
	int _who_first=New_Stage.roll_dice();

	for(int _rnd=1;_rnd<=rounds;++_rnd){ // rounds
		New_Stage.init_collection(); // Initialize collection
		cout<<"Round "<<_rnd<<" !\n";
		cout<<"===============================\n\n";
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
