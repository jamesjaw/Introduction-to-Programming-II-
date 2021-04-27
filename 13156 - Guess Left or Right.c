#include <stdio.h>
#include <stdlib.h>

#define max 200005

int Lc[max];
int Rc[max];
int nodeidx[max];
int anw[max];
int inoder[max];
int pointto[max];
int root,idx;

void output(int root){
    if(root){
        output(Lc[root]);
        anw[idx++] = root;
        output(Rc[root]);
    }
}
void init(int n){
    for(int i=0;i<=n;i++) pointto[i] = 0;
    return;
}

void check(int n){
    int flag = 0;
    for(int i=1;i<=n;i++){
        if(anw[i]!=inoder[i]){
            printf("NO\n");
            flag = 1;
            break;
        }
    }
    if(flag == 0) printf("YES\n");
}

int main(){
    int n;
    while (~scanf("%d",&n)) {
        init(n);
        for(int i=1;i<=n;i++){
            scanf("%d %d",&Lc[i],&Rc[i]);
            if(Lc[i]!=0) pointto[Lc[i]]+=1;
            if(Rc[i]!=0) pointto[Rc[i]]+=1;
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&inoder[i]);
            nodeidx[inoder[i]] = i;
        }
        
        for(int i=1;i<=n;i++){
            if(pointto[i]==0){
                root = i;
                break;
            }
        }
        for(int i=1;i<=n;i++){
            if(Lc[i]!=0 && nodeidx[Lc[i]] > nodeidx[i]){
                int temp = Lc[i];
                Lc[i] = Rc[i];
                Rc[i] = temp;
            }
            if(Rc[i]!=0 && nodeidx[Rc[i]] < nodeidx[i]){
                int temp = Rc[i];
                Rc[i] = Lc[i];
                Lc[i] = temp;
            }
        }
        idx = 1;
        output(root);
        check(n);
    }
    return 0;
}
