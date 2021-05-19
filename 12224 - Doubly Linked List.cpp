#include <iostream>
#include <string>

#include "13144.h"

using namespace std;

void List::InsertHead(int data){
    cnt++;
    if(head==nullptr){
        head = new ListNode(data);
        tail = head;
        middle = head;
    }
    else{
        head->prev = new ListNode(data);
        head->prev->next = head;
        head = head->prev;
        
        if(cnt<=3 && cnt>=0){
            middle = head;
        }
        else if(cnt>3){
            if(cnt%2==1){
                middle = middle->prev;
            }
        }
    }
}

int  List::RemoveHead(){
    
    if(head==nullptr) throw out_of_range("\n");   //=============!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    cnt--;
    
    int anw = head->data;
    if(head->next!=nullptr){
        ListNode* t = head;
        head = head->next;
        head->prev = nullptr;
        delete t;
    }
    else{
        delete head;
        head = nullptr;
        tail = nullptr;
        middle =nullptr;
    }
    
    if(cnt<=3 && cnt>=0){
        middle = head;
    }
    else if(cnt>3){
        if(cnt%2==0){
            middle = middle->next;
        }
    }
    return anw;
}

void List::InsertTail(int data){
    cnt++;
    if(tail==nullptr){
        tail = new ListNode(data);
        head = tail;
        middle = head;
    }
    else{
        tail->next = new ListNode(data);
        tail->next->prev = tail;
        tail = tail->next;
        if(cnt<=3 && cnt>=0){
            middle = head;
        }
        else if(cnt>3){
            if(cnt%2==0){
                middle = middle->next;
            }
        }
    }
}

int  List::RemoveTail(){
    if(tail==nullptr) throw out_of_range("\n");
    cnt--;
    int anw = tail->data;
    if(tail->prev!=nullptr){
        ListNode* t = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete t;
    }
    else{
        delete tail;
        head = nullptr;
        tail = nullptr;
        middle =nullptr;
    }
    if(cnt<=3 && cnt>=0){
        middle = head;
    }
    else if(cnt>3){
        if(cnt%2==1){
            middle = middle->prev;
        }
    }
    return anw;
}
void List::Swap(){
    //cout<<"s = "<<middle->data<<"\n";
    if(cnt<=1) return;
    else if(cnt==2){
        int temp = head->data;
        head->data = tail->data;
        tail->data = temp;
    }
    else if(cnt>=3){
        if(cnt%2==0){
            ListNode* nm = tail;
            ListNode* nh = middle->next;
            ListNode* nt = middle;
            tail->next = head;
            head->prev = tail;
            middle = nm;
            head = nh;
            tail = nt;
            head->prev = nullptr;
            tail->next = nullptr;
        }
        else if(cnt%2==1){
            ListNode* nm = tail->prev;
            ListNode* nh = middle->next;
            ListNode* nt = middle;
            tail->next = head;
            head->prev = tail;
            middle = nm;
            head = nh;
            tail = nt;
            head->prev = nullptr;
            tail->next = nullptr;
        }
    }
    //cout<<"ss = "<<middle->data<<"\n";
}
int  List::getSize(){
    return cnt;
}
int  List::getMiddle(){
    return pos;
}
