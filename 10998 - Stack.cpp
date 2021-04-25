#include "13144.h"
#include <iostream>


using namespace std;


List_stack::List_stack(){
    head = new ListNode(0);
    tail = head;
}

List_stack::~List_stack(){
    ListNode* temp = head;
    while(temp!=NULL){
        ListNode* f = temp;
        temp = temp->nextPtr;
        delete f;
    }
}

void List_stack::pop(){
    if(tail!=head){
        tail = tail->prevPtr;
        delete tail->nextPtr;
        tail->nextPtr = NULL;
    }
}

void List_stack::push(const int &x){
    tail->nextPtr = new ListNode(x);
    tail->nextPtr->prevPtr = tail;
    tail = tail->nextPtr;
}

void List_stack::print(){
    ListNode* temp = tail;
    while(temp!=head){
        cout<<temp->data;
        if(temp->prevPtr!=head)cout<<" ";
        temp = temp->prevPtr;
    }
}
