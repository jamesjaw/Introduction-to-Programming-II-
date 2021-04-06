#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    struct Node* R;
    struct Node* L;
    char c;
    unsigned int val;
}node;
unsigned int p,q;
void cal(node* root){
    if(root->c=='n'){
        return;
    }
    else if(root->c=='f'){
        cal(root->L);
        cal(root->R);
        unsigned long long R = ((((unsigned long long)root->L->val)%q)*((unsigned long long)p%q))%q;
        root->val = ((unsigned int)R + (root->R->val)%q)%q;
    }
}
node* bul(){
    char cc;
    scanf(" %c",&cc);
    node* root = (node*)malloc(sizeof(node));
    if(cc=='f'){
        getchar();
        root->c = cc;
        root->L = bul();
        getchar();
        root->R = bul();
        getchar();
    }
    else{
        ungetc(cc, stdin);
        unsigned int z;
        scanf("%u",&z);
        root->c = 'n';
        root->val = z%q;
        root->L = NULL;
        root->R = NULL;
    }
    return root;
}
int main(){
    
    scanf("%u %u",&p,&q);
    node* head = bul();
    cal(head);
    
    printf("%u\n",head->val);
    return 0;
}
