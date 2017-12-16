bool MJhand::canminggone(const MJtile& onemoreyen){
    int aretherepair=0;
    for(int i=_faceup_len;i<_total_len;++i){
        if(onemoreyen == _tiles[i])aretherepair++;
    }
    
    if(aretherepair<=2)return 0;
    else return 1;
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

void MJhand::minggone(const MJtile& _draw, MJcollection& cutegf){
    if(canminggone(_draw) == false)return;
    for(int cnt=0;cnt<3;++cnt){
        for(int i=_faceup_len;i<_total_len;++i){
            if(_tiles[i] == _draw){
                faceup(i-_faceup_len+1);
                break;
            }
        }
        if(cnt>0)continue;
        _tiles[_total_len].setfromId(_draw.getTileId());
        //++_total_len;
        _stage=1;
        faceup(_total_len-1+_stage-_faceup_len+1);
    }
    arrange();
    draw(cutegf);
}

