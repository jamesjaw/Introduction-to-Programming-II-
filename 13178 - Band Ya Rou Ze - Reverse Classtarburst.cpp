#include "13144.h"
#include <iostream>

using namespace std;

Node::~Node(){
    Node* temp = this;
    Node* pre = this;
    while(neighbors[0]!=nullptr && neighbors[0]!=pre){
        
    }
    while (neighbors[1]!=nullptr && neighbors[1]!= pre) {
        <#statements#>
    }
}

void List::init(std::string s){
    //cout<<"intin start\n";
    int idx = 0;
    head = new Node(s[idx++]);
    Node* temp = head;
    tail = head;
    while(s[idx]!='\0'){
        Node* newone = new Node(s[idx++]);
        temp->link(newone);
        newone->link(temp);
        temp = newone;
    }
    tail = temp;
    //cout<<"init end\n";
}

void List::merge(List &front, List &back){
    if(back.head == nullptr || front.head == nullptr) return;
    front.tail->link(back.head);
    back.head->link(front.tail);
    head = front.head;
    tail = back.tail;
}

void List::swap(List &a){
    Node* temp = head;
    head = a.head;
    a.head = temp;
    temp = tail;
    tail = a.tail;
    a.tail = temp;
}

void List::reverse(){
    Node* temp = head;
    head = tail;
    tail = temp;
}

List::~List(){
    if(head) delete head;
}
