#include <iostream>
#include <vector>
#include <set>

using namespace std;


struct seg{
    int start;
    int end;
    int mid;
    seg(int s,int e){
        start = s;
        end = e;
        mid = (s + e)/2;
    }
};



struct cmp{
    bool operator()(const seg&L, const seg&R)const{
        int l_len = (L.end - L.start)/2;
        int r_len = (R.end - R.start)/2;
        
        if(l_len != r_len){
            return l_len > r_len;
        }
        else{
            return L.start < R.start;
        }
    }
};


set<seg,cmp> swag;
set<int> pos;
vector<int> id2pos;
int main(){
    
    int n,m,s;
    cin>>n>>m>>s;
    int min_dis = n+1;
    
    pos.insert(0);
    pos.insert(n+1);
    swag.insert(seg(0,n+1));
    id2pos.resize(m + 1, 1);
    for(int i=0;i<2*m;i++){
        char oder;
        int num;
        cin>>oder>>num;
        
        if(oder=='i'){
            auto pick = swag.begin();
            //cout<<"seg("<<pick->start<<","<<pick->end<<")\n";
            if(pick->start != 0){
                min_dis = min(pick->mid - pick->start , min_dis);
                //cout<<"f\n";
            }
            if(pick->end != n+1){
                min_dis = min(pick->end - pick->mid , min_dis);
                //cout<<"z\n";
            }
            
            
            seg f1(pick->start,pick->mid);
            
            
            seg f2(pick->mid,pick->end);
            
            id2pos[num] = pick->mid;
            pos.insert(pick->mid);
            
            swag.erase(pick);
            //cout<<"f1seg("<<f1.start<<","<<f1.end<<")\n";
            //cout<<"f2seg("<<f2.start<<","<<f2.end<<")\n";
            swag.insert(f1);
            swag.insert(f2);
            
        }
        
        else if(oder=='o'){
            int mid = id2pos[num];
            auto it = pos.find(mid);
            auto L_it = it;
            auto R_it = it;
            int L = *(--L_it);
            int R = *(++R_it);
            
            
            
            swag.erase(seg(L,mid));
            swag.erase(seg(mid,R));
            swag.insert(seg(L,R));
            
            id2pos[num] = -1;
            pos.erase(mid);
            
        }
    }
    
    if(min_dis >= s)
        cout<<"YES\n";
    else
        cout<<"NO\n";
    
    if(min_dis == n+1)
        cout<<"INF\n";
    else
        cout<<min_dis<<"\n";
    
    return 0;
}
