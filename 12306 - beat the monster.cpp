#include <iostream>
#include <queue>

using namespace std;

int heal_and_damg[20][2] = {0};
int state[20][310][410] = {0};

struct ste{
    int lv;
    int hp;
    int b_hp;
    long long step;
};

queue<ste> QQ;

int main(){
    for(int i=0;i<20;i++){
        for(int j=0;j<310;j++){
            for(int k=0;k<410;k++){
                state[i][j][k] = 0;
            }
        }
    }
    
    int max_l,my_hp,boss_hp,boss_damg;
    cin>>max_l>>my_hp>>boss_hp>>boss_damg;
    for(int i=1;i<=max_l;i++) cin>>heal_and_damg[i][1]>>heal_and_damg[i][0];
    ste z;
    z.hp = my_hp;
    z.lv = 1;
    z.b_hp = boss_hp;
    z.step = 0;
    QQ.push(z);
    state[z.lv][z.hp][z.b_hp] = 1;
    int flag = 0;
    
    while(!QQ.empty()){
        ste now = QQ.front();
        //beat the monster!
        if(now.b_hp <= heal_and_damg[now.lv][1]){
            cout<<now.step + 1<<"\n";
            flag = 1;
            break;
        }
        QQ.pop();
        
        //attack
        if(now.hp > boss_damg){
            if(state[now.lv][now.hp - boss_damg][now.b_hp - heal_and_damg[now.lv][1]] == 0){
                state[now.lv][now.hp - boss_damg][now.b_hp - heal_and_damg[now.lv][1]] = 1;
                ste n;
                n.hp = now.hp - boss_damg;
                n.b_hp = now.b_hp - heal_and_damg[now.lv][1];
                n.lv = now.lv;
                n.step = now.step + 1;
                QQ.push(n);
            }
        }
        //heal
        if(now.hp + heal_and_damg[now.lv][0] <= my_hp && now.hp - boss_damg + heal_and_damg[now.lv][0] > 0){
            if(state[now.lv][now.hp - boss_damg + heal_and_damg[now.lv][0]][now.b_hp] == 0){
                state[now.lv][now.hp - boss_damg + heal_and_damg[now.lv][0]][now.b_hp] = 1;
                ste n;
                n.hp = now.hp - boss_damg + heal_and_damg[now.lv][0];
                if(n.hp >= my_hp) n.hp = my_hp;
                n.b_hp = now.b_hp;
                n.lv = now.lv;
                n.step = now.step + 1;
                QQ.push(n);
            }
        }
        //level up
        if(now.hp > boss_damg && now.lv + 1 <= max_l){
            if(state[now.lv + 1][now.hp - boss_damg][now.b_hp] == 0){
                state[now.lv + 1][now.hp - boss_damg][now.b_hp] = 1;
                ste n;
                n.hp = now.hp - boss_damg;
                n.b_hp = now.b_hp;
                n.lv = now.lv + 1;
                n.step = now.step + 1;
                QQ.push(n);
            }
        }
    }
    if(flag == 0) cout<<"-1\n";
    return 0;
}
