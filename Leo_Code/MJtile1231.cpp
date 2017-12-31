//MJtile.cpp
#include <iostream>
#include <assert.h>
#include "MJtile.h"
using namespace std;

MJtile::MJtile(){
    _suit = _rank = _flowernum = _tileId = 0;
    }

MJtile::MJtile(int _Id){
    _suit = ((_Id-1)/4)%4+1;
    _rank = (_Id-1)/16+1;
    if((_rank == 8||_rank == 9) && (_suit == 4)){
        _flowernum=_Id-(16*(_rank-1)+12);
    }
    else
        _flowernum = 0;
    _tileId = _Id;
    }

MJtile::~MJtile(){
    _suit = _rank = _flowernum = _tileId = 0;
}

void MJtile::setfromId(int set_id){
    _suit=((set_id-1)/4)%4+1;
    
    // set _rank
    _rank=(set_id-1)/16+1;
    
    // set _flowernum
    if((_rank==8 || _rank==9) && (_suit==4)){
        _flowernum=set_id-(16*(_rank-1)+12);
    } else {
        _flowernum=0;
    }
    
    // set _tileId
    _tileId=set_id;
}

int MJtile::suit() const{
    return _suit;
}


int MJtile::rank() const{
    return _rank;
}

int MJtile::flower() const{
    return _flowernum;
}

int MJtile::getTileId() const{
    return _tileId;
}


bool MJtile::operator == (const MJtile& _draw) const{
    if(_suit==_draw.suit() && _rank == _draw.rank()){
        return 1;
    }
    else
        return 0;
}


bool MJtile::operator != (const MJtile& _draw) const{
    if(_suit==_draw.suit() && _rank == _draw.rank()){
        return 0;
    }
    else
        return 1;
}


bool MJtile::fromsuitrank(int rank, int suit) const{
    if(_rank == rank && _suit == suit){
        return 1;
    }
    else
        return 0;
}

ostream& operator << (ostream& output, const MJtile& tile_out){
    if(tile_out.suit()==4){
        if(tile_out.rank()==8){
            if(tile_out._flowernum==1)     output << "🀢";
            else if(tile_out._flowernum==2)output << "🀣";
            else if(tile_out._flowernum==3)output << "🀤";
            else if(tile_out._flowernum==4)output << "🀥";
        }
        else if(tile_out._rank==9){
            if(tile_out._flowernum==1)     output << "🀦";
            else if(tile_out._flowernum==2)output << "🀧";
            else if(tile_out._flowernum==3)output << "🀨";
            else if(tile_out._flowernum==4)output << "🀩";
        }
        else {
            if(tile_out._rank==1)     output << "🀀";
            else if(tile_out._rank==2)output << "🀁";
            else if(tile_out._rank==3)output << "🀂";
            else if(tile_out._rank==4)output << "🀃";
            else if(tile_out._rank==5)output << "🀄︎";
            else if(tile_out._rank==6)output << "🀅";
            else if(tile_out._rank==7)output << "🀆";
        }
    }
    else {
        if(tile_out._rank==1){
            if(tile_out._suit==1)     output << "🀙";
            else if(tile_out._suit==2)output << "🀐";
            else if(tile_out._suit==3)output << "🀇";
        }
        else if(tile_out._rank==2){
            if(tile_out._suit==1)     output << "🀚";
            else if(tile_out._suit==2)output << "🀑";
            else if(tile_out._suit==3)output << "🀈";
        }
        else if(tile_out._rank==3){
            if(tile_out._suit==1)     output << "🀛";
            else if(tile_out._suit==2)output << "🀒";
            else if(tile_out._suit==3)output << "🀉";
        }
        else if(tile_out._rank==4){
            if(tile_out._suit==1)     output << "🀜";
            else if(tile_out._suit==2)output << "🀓";
            else if(tile_out._suit==3)output << "🀊";
        }
        else if(tile_out._rank==5){
            if(tile_out._suit==1)     output << "🀝";
            else if(tile_out._suit==2)output << "🀔";
            else if(tile_out._suit==3)output << "🀋";
        }
        else if(tile_out._rank==6){
            if(tile_out._suit==1)     output << "🀞";
            else if(tile_out._suit==2)output << "🀕";
            else if(tile_out._suit==3)output << "🀌";
        }
        else if(tile_out._rank==7){
            if(tile_out._suit==1)     output << "🀟";
            else if(tile_out._suit==2)output << "🀖";
            else if(tile_out._suit==3)output << "🀍";
        }
        else if(tile_out._rank==8){
            if(tile_out._suit==1)     output << "🀠";
            else if(tile_out._suit==2)output << "🀗";
            else if(tile_out._suit==3)output << "🀎";
        }
        else if(tile_out._rank==9){
            if(tile_out._suit==1)     output << "🀡";
            else if(tile_out._suit==2)output << "🀘";
            else if(tile_out._suit==3)output << "🀏";
        }
        
        
    }
    
    return output;
    
}


/*ostream& operator << (ostream& output, const MJtile& tile_out){
    if(tile_out.suit()==4){
        if(tile_out.rank()==8){
            output << " __ \n| " << tile_out._flowernum << "|\n|";
            if(tile_out._flowernum==1)     output << "Me";
            else if(tile_out._flowernum==2)output << "La";
            else if(tile_out._flowernum==3)output << "Zu";
            else if(tile_out._flowernum==4)output << "Ju";
        }
        else if(tile_out._rank==9){
            output << " __ \n| " << tile_out._flowernum << "|\n|";
            if(tile_out._flowernum==1)     output << "Sp";
            else if(tile_out._flowernum==2)output << "Su";
            else if(tile_out._flowernum==3)output << "Au";
            else if(tile_out._flowernum==4)output << "Wi";
        }
        else {
            output << " __ \n|  |\n|";
            if(tile_out._rank==1)     output << "Ea";
            else if(tile_out._rank==2)output << "So";
            else if(tile_out._rank==3)output << "We";
            else if(tile_out._rank==4)output << "No";
            else if(tile_out._rank==5)output << "Mi";
            else if(tile_out._rank==6)output << "Fa";
            else if(tile_out._rank==7)output << "  ";
        }
    }
    else {
        output << " __ \n| " << tile_out._rank << "|\n| ";
        if(tile_out._suit==1)output << "O";
        else if(tile_out._suit==2)output << "I";
        else if(tile_out._suit==3)output << "W";
    }
    output << "|\n -- \n";
    
    return output;
    
}

int main(){
    int id1, id2;
    cin>>id1>>id2;
    MJtile mj1(id1);
    MJtile mj2(id2);
    cout<< mj1<<mj2;
    if(mj1==mj2)
        cout<<"Same tile."<<endl;
    else if(mj1!=mj2)
        cout<<"Different tile."<<endl;
    return 0;
}
/*/







