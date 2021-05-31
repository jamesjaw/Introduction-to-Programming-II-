#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int getvalue(vector<int> v){
    int value = 0;
    int len = (int)v.size();
    for(int i=0;i<len;i++){
        int z = v[i]*(len-i);
        value += z;
    }
    return value;
}

vector<int> readv(){
    int num;
    cin>>num;
    vector<int> vz;
    while(num!=0){
        vz.push_back(num);
        cin>>num;
    }
    return vz;
}

void printv(vector<int> v){
    int len = (int)v.size();
    for(int i=0;i<len;i++){
        cout<<v[i];
        cout<<" ";
    }
    cout<<"\n";
}

struct mycompare{
    bool operator()(const vector<int>& L ,const vector<int>& R)const{
        int value_L = getvalue(L);
        int value_R = getvalue(R);
        
        if(value_L < value_R)return true;
        else return false;
    }
};


vector<int> vec;
set<vector<int>,mycompare> myset;
int main(){
    string s;
    while(cin>>s){
        //output
        if(s[0]=='o'){
            //cout<<"o\n";
            for(auto it:myset){
                printv(it);
            }
        }
        //insert
        else if(s[0]=='i'){
            //cout<<"i\n";
            vector<int> temp = readv();
            int temp_value = getvalue(temp);
            int flag = 0;
            //set<vector<int,mycompare>>::iterator it;
            for(auto it:myset){
                int it_value = getvalue(it);
                if(temp_value == it_value){
                    cout<<"exist\n";
                    flag = 1;
                    myset.erase(it);
                    vector<int> new_one;
                    for(auto re = temp.rbegin();re!=temp.rend();re++){
                        new_one.push_back(*re);
                    }
                    temp.reserve(temp.size());
                    myset.insert(new_one);
                    break;
                }
            }
            if(flag == 0) myset.insert(temp);
            
        }
        //range_out
        else if(s[0]=='r'){
            //cout<<"r\n";
            vector<int> low,up;
            low = readv();
            up = readv();
            int low_v = getvalue(low);
            int up_v = getvalue(up);
            //cout<<"low = "<<low_v<<" up = "<<up_v<<"\n";
            for(auto it:myset){
                int v = getvalue(it);
                //cout<<" v = "<<v<<"\n";
                if(v>up_v) break;
                if(v>=low_v) printv(it);
            }
        }
    }
    
    
    return 0;
}
