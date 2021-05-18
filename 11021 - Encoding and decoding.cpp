#include <iostream>
#include <string>
#include <sstream>
#include "13144.h"

using namespace std;

void RleCodec::encode(){
    if(encoded==true)return;
    else{
        stringstream ss;
        encoded = true;
        int count = 1;
        int size = (int)code_str.size();
        char temp = code_str[0];
        int i=1;
        for(;i<size;i++){
            if(code_str[i]==temp){
                temp = code_str[i];
                count++;
            }
            else{
                if(count<27){
                    ss<<'Q'<<(char)('@'+ count)<<temp;  //@ is 64 A is 65 .by the way a is 97
                }
                else{
                    cout<<"c>26\n";
                    while (count>=27) {
                        ss<<'Q'<<'Z'<<temp;
                        count -= 26;
                    }
                    ss<<'Q'<<(char)('@'+ count)<<temp;
                }
                count = 1;
                temp = code_str[i];
            }
        }
        
        if(count<27){
            ss<<'Q'<<(char)('@'+ count)<<temp;  //@ is 64 A is 65 .by the way a is 97
        }
        else{
            while (count>=27) {
                ss<<'Q'<<'Z'<<temp;
                count -= 26;
            }
            ss<<'Q'<<(char)('@'+ count)<<temp;
        }
        
        count = 1;
        temp = code_str[i];
        
        code_str = ss.str();
        ss.str("");
        ss.clear();
    }
}

void RleCodec::decode(){
    if(encoded==false)return;
    else{
        stringstream ss;
        encoded = false;
        int size = (int)code_str.size();
        int count = 0;
        for(int i=0;i<size;i++){
            if(code_str[i]=='Q'){
                count = (int)code_str[++i] - '@';
                char z = code_str[++i];
                for(int j=0;j<count;j++){
                    ss<<z;
                }
            }
        }
        code_str = ss.str();
        ss.str("");
        ss.clear();
    }
}
