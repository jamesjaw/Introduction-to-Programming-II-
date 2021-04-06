#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    struct Node* R;
    struct Node* L;
    char c;
    int val;
}node;
int p,q;
void cal(node* root){
    if(root->c=='n'){
        return;
    }
    else if(root->c=='f'){
        cal(root->L);
        cal(root->R);
        root->val = ((((root->L->val)%q)*(p%q))%q + (root->R->val)%q)%q;
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
        int z;
        scanf("%d",&z);
        root->c = 'n';
        root->val = z;
        root->L = NULL;
        root->R = NULL;
    }
    return root;
}
int main(){
    
    scanf("%d %d",&p,&q);
    node* head = bul();
    cal(head);
    
    printf("%d\n",head->val%q);
    return 0;
}
