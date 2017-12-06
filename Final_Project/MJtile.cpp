//MJtile.cpp
#include <iostream>
#include <assert.h>
#include "MJtile.h"
using namespace std;

MJtile::MJtile(){
	_suit=_rank=_flowernum=_tileId=0;
}

MJtile::MJtile(int id){
	// set _suit
	_suit=((id-1)/4)%4+1;
	
	// set _rank
	_rank=(id-1)/16+1;
	
	// set _flowernum
	if((_rank==8 || _rank==9) && (_suit==4)){
		_flowernum=id-(16*(_rank-1)+12);
	} else {
		_flowernum=0;
	}
	
	// set _tileId
	_tileId=id;
}

MJtile::~MJtile(){
	_suit=_rank=_flowernum=_tileId=0;
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

bool MJtile::operator == (const MJtile& yen) const{
	if(_rank==yen._rank&&_suit==yen._suit){
		return 1;
	}
	else
		return 0;
}

bool MJtile::operator != (const MJtile& yen) const{
	if(_rank==yen._rank&&_suit==yen._suit){
		return 0;
	}
	else
		return 1;
}

 bool MJtile::fromsuitrank(int rank2, int suit2) const{
 	if(_rank==rank2&&_suit==suit2){
		return 1;
	}
	else 
		return 0;	
 	
 }

ostream& operator << (ostream& output, const MJtile& tile_out){
	
	if(tile_out._suit==4){
		if(tile_out._rank==8){
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
