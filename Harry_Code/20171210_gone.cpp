void MJhand::gone(const MJtile& t){
    if(cangone(t)){
        for(int i=_faceup_len;i<_total_len+_stage;i++){
            if(_tiles[i]==t){
                faceup(i);
                break;
            }
        }
        for(int j=_total_len+_stage-1;j>=_faceup_len;j--){
            _tiles[j+1].setfromId(_tiles[j].getTileId());
        }
        _tiles[_faceup_len].setfromId(t.getTileId());
        _stage=1;
        _faceup_len+=1;
        for(int i=_faceup_len;i<_total_len+_stage;i++){
            if(_tiles[i]==t){
                faceup(i);
                break;
            }
        }
        for(int i=_faceup_len;i<_total_len+_stage;i++){
            if(_tiles[i]==t){
                faceup(i);
                break;
            }
        }
    }
}
