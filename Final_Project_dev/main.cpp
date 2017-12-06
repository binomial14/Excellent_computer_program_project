#include <iostream>
#include <assert.h>
#include "MJtile.h"
using namespace std;

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
