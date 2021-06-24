#include <iostream>
#include <queue>
#include <list>
#include <string>
using namespace std;


int main(){
    int m;
    cin>>m;
    int us = 0;
    int af = 0;
    int jp = 0;
    list<pair<int,queue<int>>> QQ;
    for(int i=0;i<m;i++){
        string s;
        int num;
        cin>>s;
        if(s == "ENQUEUE"){
            cin>>num;
            int contry = num % 3;
            //us
            if(contry == 0){
                //cout<<"us\n";
                if(us == 0){
                    //cout<<"us_n\n";
                    queue<int> us_q;
                    us_q.push(num);
                    QQ.push_back(pair<int,queue<int>>(0,us_q));
                    us++;
                }
                else{
                    //cout<<"us_x\n";
                    /*
                    for(auto v:QQ){
                        if(v.first == 0){
                            v.second.push(num);
                            us++;
                            break;
                        }
                    }
                    */
                    
                    auto it = QQ.begin();
                    for(;it!=QQ.end();++it){
                        if(((*it).second.front())%3 == num % 3) break;
                    }
                    if(it!=QQ.end()) (*it).second.push(num);
                    us++;
                     
                }
            }
            //af
            else if(contry == 1){
                //cout<<"af\n";
                if(af == 0){
                    queue<int> af_q;
                    af_q.push(num);
                    QQ.push_back(pair<int,queue<int>>(1,af_q));
                    af++;
                }
                else{
                    /*
                    for(auto v:QQ){
                        if(v.first == 1){
                            v.second.push(num);
                            af++;
                            break;
                        }
                    }
                     */
                    auto it = QQ.begin();
                    for(;it!=QQ.end();++it){
                        if(((*it).second.front())%3 == num % 3) break;
                    }
                    if(it!=QQ.end()) (*it).second.push(num);
                    af++;
                }
            }
            //jp
            else if(contry == 2){
                //cout<<"jp\n";
                if(jp == 0){
                    queue<int> jp_q;
                    jp_q.push(num);
                    QQ.push_back(pair<int,queue<int>>(2,jp_q));
                    jp++;
                }
                else{
                    /*
                    for(auto v:QQ){
                        if(v.first == 2){
                            v.second.push(num);
                            jp++;
                            break;
                        }
                    }
                     */
                    auto it = QQ.begin();
                    for(;it!=QQ.end();++it){
                        if(((*it).second.front())%3 == num % 3) break;
                    }
                    if(it!=QQ.end()) (*it).second.push(num);
                    jp++;
                }
            }
        }
        else if(s == "DEQUEUE"){
            if(!QQ.empty()){
                auto v = QQ.begin();
                int man = v->second.front();
                cout<<man<<"\n";
                v->second.pop();
                if(v->second.empty()){
                    //cout<<"!\n";
                    QQ.pop_front();
                }
                if(man%3 == 0) us--;
                else if(man%3 == 1) af--;
                else if(man%3 == 2) jp--;
            }
        }
    }
    /*
    auto z = QQ.begin();
    cout<<z->second.front()<<"\n";
    z->second.pop();
    cout<<z->second.front()<<"\n";
    z->second.pop();
    cout<<z->second.front()<<"\n";
    z->second.pop();
    cout<<z->second.front()<<"\n";
    cout<<us<<"\n";
    cout<<af<<"\n";
     */
    return 0;
}
