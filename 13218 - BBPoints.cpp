#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

map<long long,set<long long>> boxbox;

long long where_pos[100005] = {0};

void mis1(long long x,long long dis){
    long long old_pos = where_pos[x];
    long long new_pos = old_pos + dis;
    
    where_pos[x] = new_pos;
    
    boxbox[old_pos].erase(x);
    if(boxbox[old_pos].empty()){
        //cout<<old_pos<<" = empty!!!\n";
        boxbox.erase(old_pos);
    }
    auto t = boxbox.find(new_pos);
    if(t!=boxbox.end()){
        t->second.insert(x);
    }
    else{
        //cout<<"creat a "<<new_pos<<" set\n";
        set<long long> temp;
        temp.insert(x);
        boxbox.insert(pair<long long,set<long long>>(new_pos,temp));
    }
}

void mis2(){
    //cout<<"mis2\n";
    long long x,y,dis;
    cin>>x>>y>>dis;
    
    auto t = boxbox.find(y);
    if(t!=boxbox.end()){
        //cout<<"w i s = ";
        //for(auto z : t->second) cout<<z<<" ";
        //cout<<"\n";
        //cout<<"x = "<<x<<" y = "<<y<<" mis2 deep\n";
        set<long long>::iterator it;
        it = t->second.lower_bound(x);
        //cout<<"it = "<<*it;
        if(it!=t->second.end()){
            if(*it - x <= dis){
                //cout<<"zzz\n";
                long long distance = *it - x;
                mis1(*it,(long long)distance * -1);
            }
        }
        
    }
    return;
}


int main(){
    long long n;
    cin>>n;
    set<long long> s;
    for(int i=1;i<=n;i++){
        s.insert(i);
    }
    boxbox.insert(pair<long long,set<long long>>(0,s));
    
    
    long long k;
    cin>>k;
    for(int i=0;i<k;i++){
        int mis;
        cin>>mis;
        if(mis==1){
            long long x,dis;
            cin>>x>>dis;
            mis1(x,dis);
        }
        else if(mis==2){
            mis2();
        }
    }
    //p
    for(int i=1;i<=n;i++){
        cout<<where_pos[i];
        if(i!=n) cout<<" ";
    }
    cout<<"\n";
    return 0;
}
