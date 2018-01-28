/******************************************************************************
 FileName  [MJhand.h]
 Author    [HsuehYa Huang]
 Synopsis  [define a player's hand]
 ******************************************************************************/
#ifndef MJHAND
#define MJHAND

#include <iostream>
#include <vector> 
using namespace std;

#include "MJtile.h"
#include "MJcollection.h"
class MJhand{
    friend ostream& operator << (ostream&, MJhand&);
public:
    MJhand();
    MJhand(MJtile*, int);
    ~MJhand();
    
    int total_len() const;
    int faceup_len() const;
    void set_faceup_len(int f);
    bool stage() const;
    void set_stage(bool s);
    void set_last(const MJtile&); // debug code
    MJtile get_last()const;
    MJtile get_tile(int)const; // get a tile by its position (_faceup_len->1)
    int get_tile_suit(int)const;
    int get_tile_rank(int)const;
    int get_tile_suit_z(int)const; // count from 0
    int get_tile_rank_z(int)const; // count from 0
    
    int caneat(const MJtile&);
    bool canpong(const MJtile&);
    bool canminggone(const MJtile&);
    bool canangone(const MJtile&);
    bool canbugone(const MJtile&);
    bool canhu(const MJtile&);
    
    void arrange();
    void draw(MJcollection&);
    MJtile play(int);
    void faceup(int);
    void applique(int, MJcollection&);
    void initial(MJcollection&);
    
    //void listentiles
    vector<MJtile> eat(const MJtile&, int);
    vector<MJtile> pong(const MJtile&);
    vector<MJtile> minggone(const MJtile&, MJcollection&);
    vector<MJtile> angone(int, MJcollection&);
    vector<MJtile> bugone(int, MJcollection&);
    void huother(const MJtile&);
    void huown();
    MJhand* gethuhand();
    void showhandtoothers();
    
protected:
    int _total_len;
    int _faceup_len;
    int _stage;//0 normal stage, 1 draw stage
    MJtile _tiles[30];//total 17 tiles, at most 30 = 17+8+5
    bool noreveal[30];
    //MJtile _listen[9];//can listen up to 9 tiles
}; 
#endif
