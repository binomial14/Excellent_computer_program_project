/****************************************************************************** 
   FileName  [MJgame.h]
   Author    [HsuehYa Huang]
   Synopsis  [define a game] 
******************************************************************************/ 
#ifndef MJGAME
#define MJGAME 

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

//#include "MJplayer.h"
#include "MJstage.h"
#include "MJanimation.h"

using namespace std;

class MJgame{
	friend ostream& operator << (ostream&, const MJhand&);
public:
	MJgame();
	~MJgame();
	
	void start();
	void setting();
	void end();

	void Pause_time()const;
	void Clean_Screen()const;
private:
	vector<MJplayer*> _players;
	int rounds;
	int valueofpoints;
	int human_num;

	int count_win[5];
};
#endif
