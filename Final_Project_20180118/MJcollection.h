#ifndef MJCOLLECTION
#define MJCOLLECTION

#include "MJtile.h" 
class MJcollection{
public:
	MJcollection(){
        _frontind = _backind = 0;
        for(int i = 0;i<144;i++){
            _t[i] = MJtile();
        }
    }
	MJcollection(MJtile* mjs){
        _frontind = 0;
        _backind = 143;
        for(int i = 0;i<144;i++){
            _t[i] = mjs[i];
        }
    }
	~MJcollection(){ }
	
	int frontind() const{
        return _frontind;
    }
	int backind() const{
        return _backind;
    }
	int size() const{
        return _backind - _frontind + 1;
	}
    void change_front(int _set_front){
        _frontind = _set_front;
    }
    void change_back(int _set_back){
        _backind  = _set_back;
    }
	bool checkduplicate() const{
        for(int i = _frontind;i<=_backind;i++){
            for(int j = _frontind;j<=_backind;j++){
                if(_t[i].getTileId() == _t[j].getTileId() && i!=j){
                    return false;
                }
            }
        }
        return true;
	}
	MJtile drawfronttile() const{
        _frontind++;
        return _t[_frontind-1];
	}
	MJtile drawbacktile() const{
        _backind--;
        return _t[_backind+1];
	}
	
private:
	MJtile _t[144];
	mutable int _frontind;
	mutable int _backind;
}; 
#endif
