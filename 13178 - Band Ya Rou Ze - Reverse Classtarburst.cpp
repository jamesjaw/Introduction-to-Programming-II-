

    #include <iostream>
    #include <string>
    //#include "function.h"
    #include "13144.h"
    using namespace std;

    Node::~Node(){
        
        if(neighbors[0]){
            neighbors[0]->unLink(this);
            delete neighbors[0];
        }

        if(neighbors[1]){
            neighbors[1]->unLink(this);
            delete neighbors[1];
        }
    }

    void List::init(string s){
        //cout<<"intin start\n";
        int idx = 0;
        
        if(s[idx]=='\0') return;
        
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
        if(back.head == nullptr && front.head == nullptr) return;
        else if(front.head == nullptr){
            this->head = back.head;
            this->tail = back.tail;
        }
        else if(back.head == nullptr){
            this->head = front.head;
            this->tail = front.tail;
        }
        else{
            front.tail->link(back.head);
            back.head->link(front.tail);
            head = front.head;
            tail = back.tail;
        }
        
    }

    void List::swap(List &a){
        Node* temp = this->head;
        this->head = a.head;
        a.head = temp;
        
        Node* temp1 = this->tail;
        this->tail = a.tail;
        a.tail = temp1;
    }

    void List::reverse(){
        Node* temp = this->head;
        this->head = this->tail;
        this->tail = temp;
    }

    List::~List(){
        if(head){
            delete head;
        }
    }
