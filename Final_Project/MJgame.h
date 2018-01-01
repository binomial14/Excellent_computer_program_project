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

using namespace std;

class MJgame{
	friend ostream& operator << (ostream&, const MJhand&);
public:
	MJgame();
	~MJgame();
	
	void start();
	void setting();
	void end();
private:
	vector<MJplayer*> _players;
	int rounds;
	int valueofpoints;
	int human_num;
}; 
#endif
