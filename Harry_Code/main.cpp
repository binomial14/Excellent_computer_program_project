#include <iostream>
#include <assert.h>
#include <cstdio>
#include "MJtile.h"
#include "MJhand.h"
#include "Shuffler.h"
using namespace std;

int main(){
	Shuffler S;
    S.init();
    MJtile M[144];
    S.fill(M);
    /*M[0].setfromId(0);
    M[1].setfromId(1);
    M[2].setfromId(2);*/

    MJhand Hand_Show=MJhand(M,30);
    //Hand_Show.arrange();
    cout<<"Shuffled:\n";
    cout<<Hand_Show;

    MJhand Hand=MJhand(M,10);
    cout<<Hand;
    Hand.arrange();
    cout<<Hand;


    int N;
    /*while(cin>>N){
        MJtile Mtest=MJtile(N);
        cout<<"pong:"<<Hand.canpong(Mtest)<<", gone"<<Hand.cangone(Mtest)<<endl;

    }*/
    int aa=11,bb=20;
    Hand.draw(M,aa,bb);
    puts("Draw");
    cout<<Hand;
    Hand.arrange();
    //cout<<Hand;
	
	/*puts("Play");
    cout<<Hand.play(10);
    cout<<Hand;*/
    
    /*puts("Face up");
    Hand.faceup(10);*/
    /*Hand.faceup(8);
    Hand.faceup(5);*/
    //cout<<Hand;
    
    puts("Play");
    cout<<Hand.play(5);
    cout<<Hand;
    
    puts("Initial");
    Hand.initial(M,aa,bb);
	printf("frontind = %d, backind = %d\n",aa,bb);
    cout<<Hand;
	
    return 0;
}
