#include <iostream>
#include <assert.h>
#include <cstdio>

#include "MJgame.h"

using namespace std;

/*void Set_MJCol(MJtile *T);
void Test_Week10();
void Test_Hu();*/
void Real_Game_Test();

int main(){
	//Test_MJhand();
    //Test_Hu();
	Real_Game_Test();

    return 0;
}

void Real_Game_Test(){
	MJgame New_Game;
	New_Game.setting();
	New_Game.start();
	New_Game.end();
}

/*void Set_MJCol(MJtile *T){
    Shuffler S;
    S.init();
    S.fill(T);

    cout<<"Enter how many tiles you want to set: ";
    int N,_ID;
    cin>>N;

    cout<<"Enter MJtile Id for each tile:\n";
    for(int i=0;i<N;++i){
        //cout<<"i="<<i<<" : ";
        cin>>_ID;
        T[i].setfromId(_ID);
    }

}

void Test_Week10(){
    Shuffler S;
    S.init();
    MJtile all_MJ[144];
    S.fill(all_MJ);
    Set_MJCol(all_MJ);

    cout<<"Set initial length of Hand: ";
    int H_len;
    cin>>H_len;
    
    // Show shuffled tiles
    MJhand Hand_Show=MJhand(all_MJ,30);
    cout<<"Shuffled, front 30:\n";
    cout<<"     ";
    for(int i=0;i<30;++i){
        printf("%2d  ",i);
    }
    cout<<endl<<Hand_Show;


    // Initialize MJcollection
    MJcollection _MJC=MJcollection(all_MJ);
    MJtile _tmp_tile;
    for(int i=0;i<H_len;++i){
        _tmp_tile=_MJC.drawfronttile();
    }

    // Initialize Hand
    cout<<"Hand:\n";
    MJhand Hand=MJhand(all_MJ,H_len);
    cout<<Hand;
    Hand.initial(_MJC);
    cout<<Hand;

    // Start testing
    puts("=========================================");
    puts("D : Draw");
    puts("P : Play");
    puts("p : pong");
    puts("m : minggone");
    puts("a : angone");
    //puts("A : angone (draw first)");
    puts("b : bugone");
    puts("e : eat");
    puts("Start Testing:");

    int my_play;
    char input_s[10];
    while(1){
        // draw first

        cout<<"Enter what you want to do: ";
        cin>>input_s;

        if(input_s[0]=='D'){ // Draw
            Hand.draw(_MJC);
            cout<<Hand;
        }
        else if(input_s[0]=='P'){ // Play
            cout<<"Play(count from faceup_len): ";
            cin>>my_play;
            if(my_play<0)break;
            cout<<Hand.play(my_play);
            cout<<"Play "<<my_play<<" :\n"<<Hand;

            Hand.initial(_MJC);
            cout<<"Initial:\n"<<Hand;
        }
        else if(input_s[0]=='p'){ // pong
            cout<<"Which ID do you want to pong: ";
            cin>>my_play; // enter index
            if(my_play<0)break;

            Hand.pong(MJtile(my_play));
            cout<<Hand;
        }
        else if(input_s[0]=='m'){ // minggone
            cout<<"Which ID do you want to minggone: ";
            cin>>my_play; // enter index
            if(my_play<0)break;

            Hand.minggone(MJtile(my_play),_MJC);
            cout<<Hand;
        }
        else if(input_s[0]=='a'){ // angone
            cout<<"Which tile do you want to angone(count from faceup_len): ";
            cin>>my_play; // enter index
            if(my_play<0)break;

            Hand.angone(my_play,_MJC);
            cout<<Hand;
        }
        else if(input_s[0]=='b'){ // bugone
            cout<<"Which tile do you want to bugone(count from faceup_len): ";
            cin>>my_play; // enter index
            if(my_play<0)break;

            Hand.bugone(my_play,_MJC); // bugone
            cout<<Hand;
        }
    }
}

void Test_Hu(){
    int my_play;

    Shuffler S;
    S.init();
    MJtile all_MJ[144];
    S.fill(all_MJ);
    //Set_MJCol(all_MJ);
    MJcollection _MJC=MJcollection(all_MJ);

    cout<<"Set initial length of Hand: ";
    int H_len;
    cin>>H_len;

    MJtile _MJs[30];
    cout<<"Enter "<<H_len<<" tiles: ";
    for(int i=0;i<H_len;++i){
        cin>>my_play;
        _MJs[i].setfromId(my_play);
    }

    MJhand Hand=MJhand(_MJs,H_len);
    cout<<"Enter _faceup_len: ";
    cin>>my_play;
    Hand.set_faceup_len(my_play);
    Hand.initial(_MJC);
    cout<<"Initialized:\n";
    cout<<Hand;

    cout<<"Enter a kind of hu:\n";
    cout<<"o : huother\n";
    cout<<"w : huown\n";

    char input_s[10];
    cin>>input_s;

    if(input_s[0]=='o'){
        cout<<"Enter tile Id: ";
        cin>>my_play;

        Hand.huother(MJtile(my_play));

        cout<<Hand;
    }
    else if(input_s[0]=='w'){
        cout<<"Enter tile Id: ";
        cin>>my_play;

        Hand.set_stage(1);
        Hand.set_last(MJtile(my_play));

        Hand.huown();

        cout<<Hand;

    }
}

*/
