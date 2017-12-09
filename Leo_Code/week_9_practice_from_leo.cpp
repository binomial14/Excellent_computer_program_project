#include <iostream>
using namespace std;

#include "MJtile.h"
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
    MJtile play(int);
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
    int _stage;//0 normal stage, 1 draw stage
    MJtile _tiles[30];//total 17 tiles, at most 30 = 17+8+5
};

int MJhand::caneat(const MJtile&_draw){
    if(_draw._suit()==4)
        return 0;
    else
    {
        int _return1 = 0;
        int _return2 = 0;
        int _return4 = 0;
        int _return = 0;
        for(int i = _faceup_len;i<_total_len;i++){
            if(_draw._rank() == 1 || _draw._rank() == 2)//can't situation 345
            {
                if(_tiles[i]._rank()+1 == _draw._rank() && _tiles[i]._rank()-1 == _draw._rank())//situation 456
                {
                    _return2 = 2;
                }
                else if(_tiles[i]._rank()-1 == _draw._rank() && _tiles[i]._rank()-2 == _draw._rank())//situation 567
                {
                    _return4 = 4;
                }
            }
            else if(_draw._rank() == 8 || _draw._rank() == 9)//can't situation 567
            {
                if(_tiles[i]._rank()+2 == _draw._rank() && _tiles[i]._rank()+1 == _draw._rank())//situation 345
                {
                    _return1 = 1;
                }
                else if(_tiles[i]._rank()+1 == _draw._rank() && _tiles[i]._rank()-1 == _draw._rank())//situation 456
                {
                    _return2 = 2;
                }

            }
            else
            {
                if(_tiles[i]._rank()+2 == _draw._rank() && _tiles[i]._rank()+1 == _draw._rank())//situation 345
                {
                    _return1 = 1;
                }
                else if(_tiles[i]._rank()+1 == _draw._rank() && _tiles[i]._rank()-1 == _draw._rank())//situation 456
                {
                    _return2 = 2;
                }
                else if(_tiles[i]._rank()-1 == _draw._rank() && _tiles[i]._rank()-2 == _draw._rank())//situation 567
                {
                    _return4 = 4;
                }
            }
        }
        _return = _return1 + _return2 + _return4;
        return _return;
        
    }
}

void MJhand::pong(const MJtile&_draw){
    if(canpong(_draw) == true)
    {
        int thefirstpong;
        for(int i = _faceup_len;i<_total_len;i++)
        {
            if(_tiles[i].suit() == _draw.suit() && _tiles[i].rank() == _draw.rank())
            {
                faceup(i);
                thefirstpong = i;
                break;
            }
        }
        faceup(_total_len);
        faceup(thefirstpong);
    }
    else
        return;
}














