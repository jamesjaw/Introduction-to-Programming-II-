#include <iostream>
#include <set>
#include <string>
#include <map>
#include "13144.h"

using namespace std;
namespace oj{

    void insert(std::map<int,String> &ma,int key,const std::string &str){
        auto test = ma.find(key);
        string ss;
        if(test!=ma.end()){
            ss = str + test->second.str;
            ma.erase(test);
        }
        else{
            ss = str;
        }
        ma.insert(pair<int, String>(key,String(ss))); //為啥要加pair宣告不直接（key,string)
    }

    void output(const std::map<int,String> &ma,int begin,int end){
        for(auto &v:ma){
            if(v.first > end) break;
            if(v.first >= begin && v.first <= end){
                cout<<v.second<<' ';
            }
        }
    }
    void erase(std::map<int,String> &ma,int begin,int end){
        set<int> s;
        for(auto &v : ma){
            if(v.first > end) break;
            if(v.first >= begin && v.first <= end){
                s.insert(v.first);
            }
        }
        for(auto d:s){
            ma.erase(d); //可以直接刪key或是刪一組pair(iter)?
        }
    }

    std::ostream& operator<<(std::ostream & o,const std::map<int,String> & a){
        for(auto &v:a){
            o<<v.second<<' ';
        }
        return o;
    }
}
