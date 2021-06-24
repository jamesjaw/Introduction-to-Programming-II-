#include <iostream>
#include <set>
#include <queue>
using namespace std;

struct state{
    int map[8];
    int step = 0;
    state(){
        
    }
    state(int* a){
        for(int i=0;i<8;i++){
            map[i] = a[i];
        }
    }
    state(const state&a){
        for(int i=0;i<8;i++){
            map[i] = a.map[i];
        }
        step = a.step;
    }
    
    void move1(){
        for(int i=0;i<7;i++){
            swap(map[i],map[7]);
        }
    }
    void move2(int i){
        swap(map[i],map[(i+1)%8]);
    }
    void move3(int i){
        swap(map[i],map[(i+4)%8]);
    }
    
    bool operator == (const state& a) const{
        for(int i=0;i<8;i++){
            if(map[i] != a.map[i]) return false;
        }
        //if(step != a.step) return false;
        return true;
    }
    
    bool operator < (const state& a) const{
        for(int i=0;i<8;i++){
            if(map[i] != a.map[i]) return map[i] < a.map[i];
        }
        return false;
    }
};

void update(){
    
}


int sor[8] = {0,1,2,7,3,6,5,4};

int main(){
    int t;
    cin>>t;
    for(int q=0;q<t;q++){
        queue<state> QQ;
        set<state> vised;
        state A;
        state B;
        for(auto v:sor){
            cin>>A.map[v];
        }
        for(auto v:sor){
            cin>>B.map[v];
        }
        QQ.push(A);
        vised.insert(A);
        int flag = 0;
        while(!QQ.empty()){
            state now = QQ.front();
            QQ.pop();
            if(now == B){
                cout<<now.step<<"\n";
                flag = 1;
                break;
            }
            state new_state;
            //move1
            new_state = now;
            new_state.move1();
            new_state.step++;
            if(vised.count(new_state) == 0){
                QQ.push(new_state);
                vised.insert(new_state);
            }
            //move2
            for(int i=0;i<8;i++){
                new_state = now;
                new_state.move2(i);
                new_state.step++;
                if(vised.count(new_state) == 0){
                    QQ.push(new_state);
                    vised.insert(new_state);
                }
            }
            //move3
            for(int i=0;i<4;i++){
                new_state = now;
                new_state.move3(i);
                new_state.step++;
                if(vised.count(new_state) == 0){
                    QQ.push(new_state);
                    vised.insert(new_state);
                }
            }
            //cout<<"zz\n";
        }
        
        if(flag == 0){
            cout<<"-1\n";
        }
    }
    
    return 0;
}
