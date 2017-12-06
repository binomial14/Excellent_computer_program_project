/****************************************************************************** 
   FileName  [MJhand.h]
   Author    [HsuehYa Huang]
   Synopsis  [define a player's hand] 
******************************************************************************/ 
#ifndef MJHAND
#define MJHAND

#include <iostream> 
using namespace std;

#include "MJtile.h" 
class MJhand{
	friend ostream& operator << (ostream&, const MJhand&);
public:
	MJhand();
	MJhand(MJtile*);
	~MJhand();
	
	int faceup_len() const ;
	
	int caneat(const MJtile&);
	bool canpong(const MJtile&);
	bool cangone(const MJtile&);
	bool canhu(const MJtile&);
	
	void arrange();
	void draw(MJtile* , int&, int&);
	void play(int);
	void faceup(int);
	void applique(int, MJtile* , int&, int&);
	void initial(MJtile* , int&, int&);
	
	void eat(const MJtile&);
	void pong(const MJtile&);
	void gone(const MJtile&);
	bool hu(const MJtile&);
	
	
private:
	int _total_len;
	int _faceup_len;
	int _stage;//0 normal stage, 1 draw stage
	MJtile _tiles[30];//total 17 tiles, at most 30 = 17+8+5
}; 
#endif
