#include <iostream>
#include <assert.h>
#include <cstdio>

#include "MJgame.h"

using namespace std;

void Real_Game_Test();

int main(){
  Real_Game_Test();
  
  return 0;
}

void Real_Game_Test(){
  MJgame New_Game;
	New_Game.setting();
	New_Game.start();
	New_Game.end();
}
