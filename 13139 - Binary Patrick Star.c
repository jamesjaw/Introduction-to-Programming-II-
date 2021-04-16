#include <stdio.h>
//#include "function.h"
#include <stdlib.h>
#define maxN 1000000

int lch[maxN], rch[maxN], sz[maxN];


typedef struct _Node {
    struct _Node *left, *right;
    int id;
} Node;

Node* buildBinaryTree(int, int*, int*);
void Traversal(Node*, int*);
void freeBinaryTree(Node*);

Node* buildBinaryTree(int N, int* R, int* L){
    Node* root = (Node*)malloc(sizeof(Node)*N);
    for(int i=0;i<N;i++){
        root[i].id = i;
        if(R[i]==-1) root[i].left = NULL;
        else root[i].left = &root[R[i]];
        if(L[i]==-1) root[i].right = NULL;
        else root[i].right = &root[L[i]];
    }
    return root;
}
void Traversal(Node* root, int* sz){
    if(root->left==NULL&&root->right==NULL){
        sz[root->id] = 1;
        return;
    }
    else if(root->left!=NULL&&root->right==NULL){
        Traversal(root->left, sz);
        sz[root->id] = 1+sz[root->left->id];
    }
    else if(root->left==NULL&&root->right!=NULL){
        Traversal(root->right, sz);
        sz[root->id] = 1+sz[root->right->id];
    }
    else if(root->left!=NULL&&root->right!=NULL){
        Traversal(root->left, sz);
        Traversal(root->right, sz);
        sz[root->id] = 1+sz[root->left->id]+sz[root->right->id];
    }
    
}
void freeBinaryTree(Node* root){
    free(root);
    return;
}
int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d %d", lch + i, rch + i);
        }
        Node* root = buildBinaryTree(n, lch, rch);
        Traversal(root, sz);
        for (int i = 0; i < n; i++) {
            printf("%d%c", sz[i], " \n"[i == n - 1]);
        }
        freeBinaryTree(root);
    }
}
