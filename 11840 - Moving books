#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct N{
    struct N* up;
    struct N* dw;
    int no;
}node;
node** top;
node* bot;
int pos[26];
char oder[6];

void ref(int a){
    node* temp = top[pos[a]];
    while(temp->no!=a){
        top[pos[a]]->dw->up = NULL;
        top[pos[a]] = top[pos[a]]->dw;
        top[temp->no]->up = temp;
        temp->dw = top[temp->no];
        top[temp->no] = temp;
        pos[temp->no] = temp->no;
        temp = top[pos[a]];
    }
}
void mov(int a,int b){
    node* tempa = top[pos[a]];
    node* tempb = top[pos[b]];
    while(tempa->no!=a){
        pos[tempa->no] = pos[b];
        tempa = tempa->dw;
    }
    top[pos[b]] = top[pos[a]];
    top[pos[a]] = tempa->dw;
    tempa->dw->up = NULL;
    tempa->dw = tempb;
    tempb->up = tempa;
    pos[tempa->no] = pos[b];
}
int main(){
    int n;
    scanf("%d",&n);
    top = (node**)malloc(sizeof(node*)*n);
    bot = (node*)malloc(sizeof(node)*n);
    for(int i=0;i<n;i++){
        bot[i].dw = NULL;
        bot[i].up = (node*)malloc(sizeof(node));
        top[i] = bot[i].up;
        bot[i].up->up = NULL;
        bot[i].up->dw = &bot[i];
        bot[i].up->no = i;
        bot[i].no = -1;
        pos[i] = i;
    }
    while(1){
        scanf("%s",oder);
        if(oder[0]=='e') break;
        else if(oder[0]=='m'){
            int a,b;
            scanf("%d",&a);
            scanf("%s",oder);
            scanf("%d",&b);
            if(pos[a]!=pos[b]){
                if(oder[1]=='n'){
                    ref(a);
                    ref(b);
                    mov(a,b);
                }
                else if(oder[1]=='v'){
                    ref(a);
                    mov(a,b);
                }
            }
        }
        else if(oder[0]=='p'){
            int a,b;
            scanf("%d",&a);
            scanf("%s",oder);
            scanf("%d",&b);
            if(pos[a]!=pos[b]){
                if(oder[1]=='n'){
                    ref(b);
                    mov(a,b);
                }
                else if(oder[1]=='v'){
                    mov(a,b);
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%d:",i);
        node* temp = bot[i].up;
        while(temp!=NULL){
            printf(" %d",temp->no);
            temp = temp->up;
        }
        printf("\n");
    }
    return 0;
}
