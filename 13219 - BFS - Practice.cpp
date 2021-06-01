#include <iostream>
#include <queue>

using namespace std;

struct pos{
    int x;
    int y;
    long long step;
};

int k1[4] = {0,0,1,-1};
int k2[4] = {1,-1,0,0};

queue<pos> q;

int main(){
    int row,col;
    cin>>row>>col;
    char** map = new char*[row];
    for(int i=0;i<row;i++) map[i] = new char[col];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>map[i][j];
        }
    }
    /*
    cout<<"test\n";
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
    */
    pos start, end;
    int x,y;
    cin>>x>>y;
    start.x = x-1;
    start.y = y-1;
    start.step = 0;
    map[x-1][y-1] = 'x';
    
    cin>>x>>y;
    end.x = x-1;
    end.y = y-1;
    
    q.push(start);
    while(!q.empty()){
        pos t = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            if(((t.x+k1[i]>=0)&&(t.x+k1[i]<row))&&((t.y+k2[i]>=0)&&(t.y+k2[i]<col)) && map[t.x+k1[i]][t.y+k2[i]]=='0'){
                //cout<<"!!!\n";
                map[t.x+k1[i]][t.y+k2[i]] = '1';
                pos z;
                z.x = t.x+k1[i];
                z.y = t.y+k2[i];
                z.step = t.step + 1;
                if(z.x==end.x && z.y==end.y){
                    cout<<z.step<<"\n";
                    return 0;
                }
                q.push(z);
            }
        }
    }
    cout<<"-1\n";
    return 0;
}
