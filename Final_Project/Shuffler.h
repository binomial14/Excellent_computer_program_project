#include <iostream>
#include <assert.h>
#include <algorithm>
#include <vector>
#include "MJtile.h"
using namespace std;

#ifndef SHUFFLER_H
#define SHUFFLER_H

class Shuffler{
public:
	Shuffler(){
		MJtile tmp;
		for(int i=0;i<144;++i){
			_tiles[i]=tmp;
		}
	}
	void init(){
		vector<int> v;
		for(int i=1;i<=144;++i){
			v.push_back(i);
		}
		random_shuffle(v.begin(),v.end());
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
