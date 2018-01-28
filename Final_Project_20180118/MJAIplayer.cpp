#include "MJAIplayer.h"

const double _EXP1=2.718281828459045;

MJAIplayer::MJAIplayer(int _init_pos, int _init_money):dconst(-0.9),sconst(_EXP1){

	_position=_init_pos;
	_money=_init_money;

	_total_len=_faceup_len=_stage=0;
    for (int i=0; i<30; i++) {
        _tiles[i]=MJtile();
        //noreveal[i]=0; // ************delete this when uploading***********
    }
	
	for(int i=1;i<=4;++i){
		for(int j=1;j<=4;++j){
			for(int k=1;k<=9;++k){
				count_used_pos[i][j][k]=0;
			}
		}
	}
	for(int i=1;i<=4;++i){
		for(int j=1;j<=9;++j){
			count_tile[i][j]=count_my_tile[i][j]=count_my_tile_old[i][j]=_ts[i][j]=0;
		}
	}
}

void MJAIplayer::set_hand(MJtile* _init_tiles){
	_faceup_len=0;
    _total_len=16;
    _stage=0;
	for(int i=0;i<16;++i){
		_tiles[i].setfromId(_init_tiles[i].getTileId());
	}

	for(int i=0;i<30;++i){
		//noreveal[i]=0;// ************delete this when uploading***********
	}

	for(int i=1;i<=4;++i){
		for(int j=1;j<=4;++j){
			for(int k=1;k<=9;++k){
				count_used_pos[i][j][k]=0;
			}
		}
	}
	for(int i=1;i<=4;++i){
		for(int j=1;j<=9;++j){
			count_tile[i][j]=count_my_tile[i][j]=count_my_tile_old[i][j]=_ts[i][j]=0;
		}
	}
}

void MJAIplayer::getinfo(int position, vector<MJtile> ts, int tiles_num){
	for(int i=0;i<tiles_num;++i){
		if(count_used_pos[position][ts[i].suit()][ts[i].rank()]>=4)continue;
		count_used_pos[position][ts[i].suit()][ts[i].rank()]++;
		count_tile[ts[i].suit()][ts[i].rank()]++;
	}
	/*Print_Get();
	system("pause");*/
}

void MJAIplayer::strategy(int position, MJtile t, int &actiontype, int &actionparameter){
	// type: nothing=0 eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6 hu=7 play=8
	// actionparameter: 

	//ts_cal();
	reset_my_count();

	if(actiontype==8){ // play
		if(canhu(_tiles[total_len()+stage()-1])){
			actiontype=7;
			return;
		}
		if(canangone(_tiles[total_len()+stage()-1])){
			actiontype=4;
			actionparameter=total_len()-faceup_len()+stage();
			return;
		}
		if(canbugone(_tiles[total_len()+stage()-1])){
			actiontype=5;
			actionparameter=total_len()-faceup_len()+stage();
			return;
		}
		for(int i=faceup_len();i<=total_len()-1+stage();++i){
			if(_tiles[i].flower()){
				actiontype=6;
				actionparameter=i-faceup_len()+1;
				return;
			}
		}
		//cout<<"Jizz\n";
		actiontype=8;
		actionparameter=strategy_play();
		//cout<<"Bang!\n";
		return;
	}

	if(canhu(t)){ // huown
		actiontype=7;
		return;
	}

	// three kinds of moves
	ts_cal();
	double min_move=10000.0;

	double three_f=0.0;
	for(int i=1;i<=4;++i){
		if(i==t.suit())continue;
		three_f+=value_function(i);
	}

	if(position!=((_position-1)==0?4:(_position-1)) && canminggone(t)){
		// minggong
		_ts[t.suit()][t.rank()]-=3;
		double mm_test=three_f+value_function(t.suit());
		_ts[t.suit()][t.rank()]+=3;

		if(mm_test<min_move){
			min_move=mm_test;
			actiontype=3;
		}
	}

	if(canpong(t)){
		_ts[t.suit()][t.rank()]-=2;
		double mm_test=three_f+value_function(t.suit());
		_ts[t.suit()][t.rank()]+=2;
		if(mm_test<min_move){
			min_move=mm_test;
			actiontype=2;
		}
	}

	int check_eat=caneat(t);
	if(position==((_position-1)==0?4:(_position-1)) && check_eat){
		// might be possible to eat
		if(check_eat & 1){ // 123
			_ts[t.suit()][t.rank()-2]--;_ts[t.suit()][t.rank()-1]--;_ts[t.suit()][t.rank()]--;
			double mm_test=three_f+value_function(t.suit());
			_ts[t.suit()][t.rank()-2]++;_ts[t.suit()][t.rank()-1]++;_ts[t.suit()][t.rank()]++;
			if(mm_test<min_move){
				min_move=mm_test;
				actiontype=1;
				actionparameter=1;
			}
		}
		if(check_eat & 2){ // 234
			_ts[t.suit()][t.rank()-1]--;_ts[t.suit()][t.rank()]--;_ts[t.suit()][t.rank()+1]--;
			double mm_test=three_f+value_function(t.suit());
			_ts[t.suit()][t.rank()-1]++;_ts[t.suit()][t.rank()]++;_ts[t.suit()][t.rank()+1]++;
			if(mm_test<min_move){
				min_move=mm_test;
				actiontype=1;
				actionparameter=2;
			}
		}
		if(check_eat & 4){ // 345
			_ts[t.suit()][t.rank()]--;_ts[t.suit()][t.rank()+1]--;_ts[t.suit()][t.rank()+2]--;
			double mm_test=three_f+value_function(t.suit());
			_ts[t.suit()][t.rank()]++;_ts[t.suit()][t.rank()+1]++;_ts[t.suit()][t.rank()+2]++;
			if(mm_test<min_move){
				min_move=mm_test;
				actiontype=1;
				actionparameter=4;
			}
		}
	}

	if(min_move<9000.0)return;

	actiontype=0; // do nothing
	return;
}

int MJAIplayer::strategy_play(){
	//_hand.arrange();

	// categorize by suit
	vector<int> cnt_suit[5];
	for(int i=1;i<=total_len()-faceup_len()+stage();++i){
		cnt_suit[_tiles[i-1+faceup_len()].suit()].push_back(i);
	}

	// if that suit has only one tile, play that tile out
	for(int i=4;i>=4;--i){ // changed i>="4"  ******************
		if(cnt_suit[i].size()==1){
			return cnt_suit[i][0];
		}
	}

	
	// suit 4
	vector<int> cnt_rank[10];
	for(int i=0;i<cnt_suit[4].size();++i){
		cnt_rank[_tiles[cnt_suit[4][i]-1+faceup_len()].rank()].push_back(cnt_suit[4][i]);
	}
	for(int i=1;i<=7;++i){
		if(cnt_rank[i].size()==1){
			return cnt_rank[i][0];
		}
	}

	//return rand()%(_hand.total_len()-_hand.faceup_len()+_hand.stage())+1;

	// value function method
	ts_cal();
	double f[5];
	double all_f=0.0;
	for(int i=1;i<=4;++i){
		f[i]=value_function(i);
		all_f+=f[i];
	}

	double min_ans=10000.0;
	int min_pos=1;

	for(int i=1;i<=total_len()-faceup_len()+stage();++i){
		double this_ans;
		_ts[get_tile_suit(i)][get_tile_rank(i)]--;
		this_ans=all_f-f[get_tile_suit(i)]+value_function(get_tile_suit(i));
		_ts[get_tile_suit(i)][get_tile_rank(i)]++;

		if(this_ans<=min_ans){
			min_ans=this_ans;
			min_pos=i;
		}
	}

	return min_pos;
}

// ============================================================

inline double MJAIplayer::miss_tile_chances(int t_suit,int t_rank){
	if(t_rank<=0 || t_rank>9)return 1.0;
	return (double)exp((count_tile[t_suit][t_rank]+count_my_tile[t_suit][t_rank])/4.0-1.0);
}

inline double MJAIplayer::miss_tile_chances_2(int t_suit,int t1_rank,int t2_rank){
	if(t1_rank<=0 || t1_rank>9 || t2_rank<=0 || t2_rank>9)return 1.0;
	double n_p_1=(count_tile[t_suit][t1_rank]+count_my_tile[t_suit][t1_rank])/4.0-1.0;
	double n_p_2=(count_tile[t_suit][t2_rank]+count_my_tile[t_suit][t2_rank])/4.0-1.0;
	double n_p_12=n_p_1*n_p_2;

	return (double)exp(n_p_1+n_p_2-n_p_12);
}

inline double MJAIplayer::value_function(int _su){
	// _su: suit
	// results of value_function between different suits are independent!!

	// Calculate the value of my hand now

	return Find_Da(_su,1,0.0);
}

inline double MJAIplayer::Find_Da(int _su,int begin_r,double sum){
	// _su: suit
	// begin_r: avoid repeat calculating

	double min_ans=100000.0;
	bool check_left=0;
	// check_left: check if there are still ways to find dahzi
	// 1->yes, 0->no

	const int rlim=(_su==4)?7:9;
	for(int i=begin_r;i<=rlim;++i){
		if(_ts[_su][i]==0)continue;

		if(_ts[_su][i]>=3){ // pong
			check_left=1;
			_ts[_su][i]-=3;
			min_ans=min(min_ans,Find_Da(_su,(_ts[_su][i]==0)?(begin_r+1):begin_r,sum+dconst));
			_ts[_su][i]+=3;
		}

		if(_ts[_su][i]>=4){ // gone
			check_left=1;
			_ts[_su][i]-=4;
			min_ans=min(min_ans,Find_Da(_su,(_ts[_su][i]==0)?(begin_r+1):begin_r,sum+dconst));
			_ts[_su][i]+=4;
		}

		if(_su==4)continue; // wind and flower can't be eaten

		if(i+2<=9){
			if(_ts[_su][i+1]>=1 && _ts[_su][i+2]>=1){
				check_left=1;
				_ts[_su][i]--; _ts[_su][i+1]--; _ts[_su][i+2]--;
				min_ans=min(min_ans,Find_Da(_su,(_ts[_su][i]==0)?(begin_r+1):begin_r,sum+dconst));
				_ts[_su][i]++; _ts[_su][i+1]++; _ts[_su][i+2]++;
			}
		}
	}

	if(!check_left)return Find_UnDa(_su,sum);
	else return min_ans;
}

inline double MJAIplayer::Find_UnDa(int _su, double sum){
	double min_ans=100000.0;

	bool check_left=0;
	const int rlim=(_su==4)?7:9;
	for(int i=1;i<=rlim;++i){ // i -> rank
		if(_ts[_su][i]==0)continue;

		if(_ts[_su][i]>=2){
			check_left=1;
			_ts[_su][i]-=2;
			double m_ch=miss_tile_chances(_su,i);
			min_ans=min(min_ans,Find_UnDa(_su,sum+m_ch));
			_ts[_su][i]+=2;
		}

		if(_su==4)continue; // wind and flower can't be eaten
		// find might eat
		if(i+1<=9){ // i,i+1
			if(_ts[_su][i+1]>=1){
				check_left=1;
				_ts[_su][i]--;
				_ts[_su][i+1]--;
				double m_ch=miss_tile_chances_2(_su,i-1,i+2);
				//min(miss_tile_chances(_su,i-1),miss_tile_chances(_su,i+2));
				min_ans=min(min_ans,Find_UnDa(_su,sum+m_ch));
				_ts[_su][i]++;
				_ts[_su][i+1]++;
			}
		}
		if(i+2<=9){ // i,_,i+2
			if(_ts[_su][i+2]>=1){
				check_left=1;
				_ts[_su][i]--;
				_ts[_su][i+2]--;
				double m_ch=miss_tile_chances(_su,i+1);
				min_ans=min(min_ans,Find_UnDa(_su,sum+m_ch));
				_ts[_su][i]++;
				_ts[_su][i+2]++;
			}
		}
	}

	if(!check_left)return Find_Single(_su)+sum;
	else return min_ans;
}
inline double MJAIplayer::Find_Single(int _su){
	const int rlim=(_su==4)?7:9;
	double return_ans=0.0;
	for(int i=1;i<=rlim;++i){
		if(_ts[_su][i]==0)continue;
		return_ans+=sconst*miss_tile_chances(_su,i);
	}
	return return_ans;
}

// =====================================================

void MJAIplayer::reset_my_count(){
	for(int i=1;i<=4;++i){
		for(int j=1;j<=9;++j){
			count_my_tile[i][j]=0;
		}
	}

	for(int i=0;i<total_len()+stage();++i){
		count_my_tile[_tiles[i].suit()][_tiles[i].rank()]++;
	}

	for(int i=1;i<=4;++i){
		for(int j=1;j<=9;++j){
			if(count_my_tile_old[i][j]>count_my_tile[i][j]){
				count_my_tile[i][j]=count_my_tile_old[i][j];
			}
		}
	}
	for(int i=1;i<=4;++i){
		for(int j=1;j<=9;++j){
			count_my_tile_old[i][j]=count_my_tile[i][j];
		}
	}
}

void MJAIplayer::ts_cal(){
	// it is no need to consider flowers (suit=4, rank=8 or 9)
	for(int i=1;i<=4;++i){
		for(int j=1;j<=9;++j){
			_ts[i][j]=0; // Initialize
		}
	}

	for(int i=1;i<=total_len()-faceup_len()+stage();++i){
		_ts[_tiles[i-1+faceup_len()].suit()][_tiles[i-1+faceup_len()].rank()]++;
	}
}

void MJAIplayer::Print_Get()const{
	cout<<"Gotten Info: \n";

	for(int i=1;i<=4;++i){
		for(int j=1;j<=9;++j){
			cout<<count_tile[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
