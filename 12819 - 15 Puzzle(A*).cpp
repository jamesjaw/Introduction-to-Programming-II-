#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int map[5][5];
int k1[4] = {1,-1,0,0};
int k2[4] = {0,0,-1,1};
int num_row[16] = {0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4};
int num_col[16] = {0,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3};

struct state{
    int B[5][5];
    int pre_mov;
    int step;
    int h_value;
    int row;
    int col;
    
    state(int map[5][5]){
        pre_mov = 7;
        step = 0;
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                B[i][j] = map[i][j];
                if(map[i][j]==0){
                    //cout<<"row = "<<i<<" col = "<<j<<"\n";
                    row = i;
                    col = j;
                }
            }
        }
    }
    
    state(const state&s){
        pre_mov = s.pre_mov;
        step = s.step;
        row = s.row;
        col = s.col;
        h_value = s.h_value;
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                B[i][j] = s.B[i][j];
            }
        }
    }
    
    void set_h(){
        int v = 0;
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                if(B[i][j] != 0){
                    int x_dis = abs(num_row[B[i][j]] - i);
                    int y_dis = abs(num_col[B[i][j]] - j);
                    v += x_dis;
                    v += y_dis;
                    
                    if(num_row[B[i][j]] == i){
                        //cout<<"row . "<<num_row[B[i][j]]<<"\n";
                        for(int k=j;k<=4;k++){
                            if(B[i][k]>0 && B[i][j] > B[i][k] && num_row[B[i][k]] == i){
                                v += 2;
                            }
                        }
                    }
                    if(num_col[B[i][j]] ==j){
                        //cout<<"col . "<<num_col[B[i][j]]<<"\n";
                        for(int k=i;k<=4;k++){
                            if(B[k][j]>0 && B[i][j] > B[k][j] && num_col[B[k][j]] == j){
                                v += 2;
                            }
                        }
                    }
                }
            }
        }
        h_value = v;
    }
    
    void update(int next_move,int n_row,int n_col){
        pre_mov = next_move;
        int temp = B[row][col];
        B[row][col] = B[n_row][n_col];
        B[n_row][n_col] = temp;
        row = n_row;
        col = n_col;
        set_h();
        step++;
    }
    
    bool operator<(const state&s) const{
        return h_value + step > s.h_value + s.step;
    }
    
};

priority_queue<state> PQQ;

int main(){
    //init
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            cin>>map[i][j];
        }
    }
    
    state s(map);
    s.set_h();
    //cout<<s.h_value<<"\n";
    //cout<<s.row<<" "<<s.col<<"\n";
    
    
    PQQ.push(s);
    while(!PQQ.empty()){
        state now = PQQ.top();
        PQQ.pop();
        for(int i=0;i<4;i++){
            int new_row = now.row + k1[i];
            int new_col = now.col + k2[i];
            if(new_row>=1 && new_row<=4 && new_col >=1 && new_col<=4){
                if((now.pre_mov ^ 1) != i){
                    state new_state = now;
                    new_state.update(i, new_row, new_col);
                    if(new_state.h_value == 0){
                        cout<<new_state.step<<"\n";
                        return 0;
                    }
                    if(new_state.step < 80){
                        PQQ.push(new_state);
                    }
                }
            }
        }
        
    }
    cout<<"-1\n";
    
    
    return 0;
}
