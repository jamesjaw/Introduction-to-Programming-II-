#include <iostream>

#include "13144.h"

using namespace std;


void Array::move(int a){
    if(a>=0){
        if(cur+a>=size){
            cur = size;
        }
        else{
            cur += a;
        }
    }
    else if(a<0){
        //cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!";
        if(cur+a<=1){
            cur = 1;
        }
        else{
            //cout<<"\n!!";
            cur += a;
        }
    }
}

void Array::remove(){
    if(cur==size){
        cur--;
        size--;
    }
    else{
        for(int i=cur+1;i<=size;i++){
            mem[i-1] = mem[i];
        }
        size--;
    }
    //cout<<"cur = "<<cur <<" / "<<mem[cur]<<"\n";
}


void List::move(int a){
    if(a==0) return;
    if(a>0){
        for(int i=0;i<a;i++){
            if(cur->getNxt()==nullptr) return;
            cur = cur->getNxt();
        }
    }
    else if(a<0){
        a *=-1;
        for(int i=0;i<a;i++){
            if(cur->getPre()==nullptr) return;
            cur = cur->getPre();
        }
    }
}

void List::remove(){
    cur = cur->remove();
    size--;  //==========!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!shit!!!!!!!!!!!!
    //cout<<"did remove";
}

ContainerBase* create(int n, int* arr, int q, Operation* op){
    int tw = 0;
    int thr = 0;
    for(int i=1;i<=q;i++){
        if(op[i].type==2) tw++;
        if(op[i].type==3) thr++;
    }
    ContainerBase* anw;
    if(tw>=thr){  //array
        anw = new Array(n, arr);
    }
    else{        //linked list
        anw = new List(n, arr);
    }
    return anw;
}
