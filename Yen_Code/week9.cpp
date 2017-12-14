//
//  main.cpp
//  week9
//
//  Created by yenyen on 2017/12/8.
//  Copyright © 2017年 yenyen. All rights reserved.
//

#include <iostream>
#include "MJtile.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

class MJhand{
    friend ostream& operator << (ostream&, const MJhand&);
public:
    MJhand();
    MJhand(MJtile*, int);
    ~MJhand();
    int faceup_len() const ;
    int caneat(const MJtile&);
    bool canpong(const MJtile&);
    bool cangone(const MJtile&);
    //bool canhu(const MJtile&);
    void arrange();
    void draw(MJtile* , int&, int&);
    void play(int);
    void faceup(int);
    void applique(int, MJtile* , int&, int&);
    void initial(MJtile* , int&, int&);
    //void eat(const MJtile&);
    void pong(const MJtile&);
    //void minggone(const MJtile&);
    //void angone(const MJtile&);
    //void bugone(const MJtile&);
    //bool hu(const MJtile&);
private:
    int _total_len;
    int _faceup_len;
    int _stage;
    MJtile _tiles[30];
};


MJhand::MJhand(){
    _total_len=_faceup_len=_stage=0;
    for (int i=0; i<30; i++) {
        _tiles[i]=MJtile();
    }
}

MJhand::MJhand(MJtile* yen, int n){
    _faceup_len=0;
    _total_len=n;
    _stage=0;
    for (int i=0; i<30; i++) {
        yen->setfromid(_tiles[i].getTileId());
    }
}

int MJhand::faceup_len() const{
    return _faceup_len;
}

bool MJhand::canpong(const MJtile& onemoreyen){
    int i=0;
    int aretherepair=0;
    for(;i<30;i++){
        if(onemoreyen.operator==(_tiles[i])){
            aretherepair++;
            break;
        }
    }
    if (aretherepair==0) {
        return 0;
    }
    i++;
    //continue to compare the left tiles
    for (; i<30;i++) {
        if(onemoreyen.operator==(_tiles[i])) return 1;
    }
    return 0;
}

bool MJhand::cangone(const MJtile& onemoreyen){
    int i=0;
    int aretheresthsame=0;
    for(;i<30;i++){
        if(onemoreyen.operator==(_tiles[i])){
            aretheresthsame++;
            break;
        }
    }
    if (aretheresthsame==0) return 0;
    i++;
    for (; i<30;i++) {
        if(onemoreyen.operator==(_tiles[i])){
            aretheresthsame++;
            break;
        }
    }
    if (aretheresthsame==1) return 0;
    i++;
    for (; i<30;i++) {
        if(onemoreyen.operator==(_tiles[i])) return 1;
    }
    return 0;
}

bool MJhand::canangone(const MJtile& onemoreyen){
    int aretherepair=0;
    for(int i=_faceup_len;i<_total_len;++i){
        if(onemoreyen == _tiles[i])aretherepair++;
    }
    if(aretherepair<=3)return 0;
    else return 1;
}

bool MJhand::canbugone(const MJtile& onemoreyen){
    for (int i=0; i<_faceup_len; i++) {
        if (_tiles[i]==_tiles[i+1]&&_tiles[i]==_tiles[i+2]) {
            if(onemoreyen == _tiles[i]) return 1;
            else break;
        }
    }
    return 0;
}
