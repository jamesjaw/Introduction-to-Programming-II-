#include "13155.h"
#include <stdio.h>
#include <stdlib.h>

struct Graph* createGraph(int a){
    struct Graph* gra = (struct Graph*)malloc(sizeof(struct Graph));
    gra->vertices_num = a;
    gra->adjLists = (struct Node**)malloc(sizeof(struct Node*)*a);
    for(int i=0;i<a;i++){
        gra->adjLists[i] = NULL;
    }
    return gra;
}
void addEdge(struct Graph* gra, int a, int b){
    struct Node* tempa = (struct Node*)malloc(sizeof(struct Node));
    tempa->next = gra->adjLists[b];
    tempa->id = a;
    gra->adjLists[b] = tempa;
    struct Node* tempb = (struct Node*)malloc(sizeof(struct Node));
    tempb->next = gra->adjLists[a];
    tempb->id = b;
    gra->adjLists[a] = tempb;
}
int findMax(struct Graph* gra, int cur, int pre){
    struct Node* temp = gra->adjLists[cur];
    int max = cur;
    while(temp!=NULL){
        if(temp->id == pre) {
            temp = temp->next;
        }
        else{
            int z = findMax(gra, temp->id, cur);
            if(z>max) max = z;
            temp = temp->next;
        }
    }
    return max;
}
void freeGraph(struct Graph* gra){
    for(int i=0;i<gra->vertices_num;i++){
        struct Node* t = gra->adjLists[i];
        struct Node* p;
        while(t !=NULL){
            p = t;
            t = t->next;
            free(p);
        }
    }
    return;
}
