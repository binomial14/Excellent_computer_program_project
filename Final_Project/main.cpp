#include <iostream>
#include <assert.h>
#include <cstdio>
#include "MJtile.h"
#include "MJhand.h"
#include "Shuffler.h"
using namespace std;

inline void Test_MJhand(){
	Shuffler S;
	S.init();
	MJtile all_MJ[144];
	S.fill(all_MJ);
	
	MJhand Hand_Show=MJhand(all_MJ,30);
    cout<<"Shuffled, front 30:\n";
    cout<<"     ";
	for(int i=0;i<30;++i){
		printf("%2d  ",i);
	}
    cout<<endl<<Hand_Show;

    cout<<"Hand:\n";
    MJhand Hand=MJhand(all_MJ,10);
    Hand.arrange();
    cout<<Hand;

    int my_play;
    int _front=11, _back=20;
    while(1){
    	Hand.draw(all_MJ,_front,_back);
    	cout<<"Draw: front = "<<_front<<", back = "<<_back<<endl<<Hand;

    	cin>>my_play;
    	if(my_play<0)break;

        MJtile tmp_tile=MJtile(my_play);
        Hand.pong(tmp_tile);
        cout<<"Pong "<<my_play<<" :\n"<<Hand;

        cin>>my_play;
        if(my_play<0)break;
        
    	cout<<Hand.play(my_play);
    	cout<<"Play "<<my_play<<" :\n"<<Hand;

    	Hand.initial(all_MJ,_front,_back);
    	cout<<"Initial: front = "<<_front<<", back = "<<_back<<endl<<Hand;
    }
}

int main(){
	Test_MJhand();
	
    return 0;
}
