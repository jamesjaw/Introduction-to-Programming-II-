
#include <iostream>
#include "function.h"
using namespace std;

Str::Str(char* s){
    int idx = 1;
    head = new Char(s[0]);
    tail = head;
    Char* temp = head;
    while(s[idx]!='\0'){
        temp->next = new Char(s[idx++]);
        temp = temp->next;
    }
    tail = temp;
}

Str::Str(const Str & a){
    Char* temp = a.head->next;
    head = new Char(a.head->text);
    tail = head;
    Char* temp1 = head;
    while(temp!=NULL){
        temp1->next = new Char(temp->text);
        temp1 = temp1->next;
        temp = temp->next;
    }
    tail = temp1;
}

Str& Str::strInsert(const Str & a){
    Str* cop = new Str(a);    //要用動態宣告 
    tail->next = cop->head;
    tail = cop->tail;
    return *this;
}
