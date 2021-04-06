#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    struct Node* R;
    struct Node* L;
    char c;
    int val;
}node;
char str[300005];
int pos=0;
int min = 2147000000;
node* maket(){
    char z;
    z = str[pos++];
    node* root = (node*)malloc(sizeof(node));
    if(z=='+'||z=='-'||z=='*'){
        root->c = z;
        root->L = maket();
        root->R = maket();
    }
    else{
        root->c = z;
        root->val = (int)(z-'0');
        root->L = NULL;
        root->R = NULL;
        
    }
    return root;
}
void cal(node* root){
    if(root->c=='+'){
        cal(root->L);
        cal(root->R);
        root->val = root->L->val + root->R->val;
    }
    else if(root->c=='-'){
        cal(root->L);
        cal(root->R);
        root->val = root->L->val - root->R->val;
    }
    else if(root->c=='*'){
        cal(root->L);
        cal(root->R);
        root->val = root->L->val * root->R->val;
    }
    else{
        return;
    }
}
void cal2(node* root){
    if(root->c=='+'){
        root->val = root->L->val + root->R->val;
    }
    else if(root->c=='-'){
        root->val = root->L->val - root->R->val;
    }
    else if(root->c=='*'){
        root->val = root->L->val * root->R->val;
    }
    //printf("%d\n",root->val);
}

int main(){
    int n;
    scanf("%d",&n);
    pos = 0;
    scanf("%s",str);
    node* head1 = maket();
    pos = 0;
    node* head2 = maket();
    cal(head1);
    cal(head2);
    min = head1->val;
    //printf("%d\n",head1->R->val);
    //printf("%c\n",head2->R->R->R->c);
    while(!((int)(head1->R->c-'0')>0 && (int)(head1->R->c-'0')<=9)){
        node* temp = head1->R->L;
        node* new = head1->R;
        head1->R->L = head1;
        head1->R = temp;
        head1 = new;
        cal2(head1->L);
        cal2(head1);
        if(head1->val<min) min = head1->val;
    }
    while(!((int)(head2->L->c-'0')>0 && (int)(head2->L->c-'0')<=9)){
        node* temp = head2->L->R;
        node* new = head2->L;
        head2->L->R = head2;
        head2->L = temp;
        head2 = new;
        cal2(head2->R);
        cal2(head2);
        if(head2->val<min) min = head2->val;
    }
    printf("%d\n",min);
    return 0;
}
