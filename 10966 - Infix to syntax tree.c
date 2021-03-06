#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef FUNCTION_H
#define FUNCTION_H

#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;
BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);

BTNode* EXPR(){
    BTNode* R = FACTOR();
    if(pos==-1||expr[pos]=='(') return R;   //pos--放在這更直覺一點
    BTNode* M = makeNode(expr[pos--]);
    M->right = R;
    M->left = EXPR();
    return M;
}
BTNode* FACTOR(){
    BTNode* head;
    char z = expr[pos--];
    if(z==')'){
            head = EXPR();
            pos--;             //pos--在這
        }
    else{
        head = makeNode(z);
       
    }
    return head;
}
BTNode* makeNode(char c){
    BTNode* head = (BTNode*)malloc(sizeof(BTNode));
    if(c=='A'){
        head->data = ID_A;
        head->left = NULL;
        head->right = NULL;
    }
    else if(c=='B'){
        head->data = ID_B;
        head->left = NULL;
        head->right = NULL;
    }
    else if(c=='C'){
        head->data = ID_C;
        head->left = NULL;
        head->right = NULL;
    }
    else if(c=='D'){
        head->data = ID_D;
        head->left = NULL;
        head->right = NULL;
    }
    else if(c=='&'){
        head->data = OP_AND;
    }
    else if(c=='|'){
        head->data = OP_OR;
    }
    return head;
}
void freeTree(BTNode *root);
void printPrefix(BTNode *root);

#endif

int main(void){
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';
    while (scanf("%s", expr)!=EOF)
    {
        pos = strlen(expr) - 1;
        BTNode *root = EXPR();
        printPrefix(root);
        printf("\n");
        freeTree(root);
    }

    return 0;
}

/* print a tree by pre-order. */
void printPrefix(BTNode *root){
    if (root != NULL) {
        printf("%c",sym[root->data]);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


