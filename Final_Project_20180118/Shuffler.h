#include <iostream>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "MJtile.h"
using namespace std;

#ifndef SHUFFLER_H
#define SHUFFLER_H

class Shuffler{
public:
	Shuffler(){
		for(int i=0;i<144;++i){
			_tiles[i]=MJtile();
		}
	}
	void init(){
		vector<int> v;
		/*srand((unsigned)time(NULL));
		for(int i=1;i<=144;++i){
			int r=(rand()*103+97)%144;
			while(_tiles[r].getTileId()!=0){
				r=(rand()*103+97)%144;
			}
			_tiles[r].setfromId(i);
		}*/
		for(int i=1;i<=144;++i){
			v.push_back(i);
		}
		random_shuffle(v.begin(),v.end());
		//random_shuffle(v.begin(),v.end()); // debug
		//random_shuffle(v.begin(),v.end());

		for(int i=0;i<144;++i){
			MJtile tmp(v[i]);
			_tiles[i]=tmp;
		}
	}
	void fill(MJtile tiles[])const{
		for(int i=0;i<144;++i){
			tiles[i]=_tiles[i];
		}
	}
private:
	MJtile _tiles[144];
};

#endif
