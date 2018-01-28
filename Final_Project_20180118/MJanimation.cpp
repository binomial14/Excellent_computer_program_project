#include "MJanimation.h"

MJanimation::MJanimation(){

}

MJanimation::~MJanimation(){

}

void MJanimation::Opening(){
	for(int i=1;i<=10;++i){
		for(int j=0;j<i;++j){
			cout<<"*******************************************"<<endl;
		}
			cout<<"*********Welcome to Taiwan Mahjong*********"<<endl;
		for(int j=i+1;j<=11;++j){
			cout<<"*******************************************"<<endl;
		}

		Sleep(150);
		system("cls");
	}
	for(int i=9;i>=5;--i){
		for(int j=0;j<i;++j){
			cout<<"*******************************************"<<endl;
		}
			cout<<"*********Welcome to Taiwan Mahjong*********"<<endl;
		for(int j=i+1;j<=11;++j){
			cout<<"*******************************************"<<endl;
		}

		Sleep(150);
		system("cls");
	}

	for(int i=0;i<5;++i){
		for(int j=0;j<5;++j){
			cout<<"*******************************************"<<endl;
		}
			cout<<"*********Welcome to Taiwan Mahjong*********"<<endl;
		for(int j=6;j<=11;++j){
			cout<<"*******************************************"<<endl;
		}
		Sleep(200);
		if(i==4)break;
		system("cls");
		Sleep(100);
	}

	return;
}