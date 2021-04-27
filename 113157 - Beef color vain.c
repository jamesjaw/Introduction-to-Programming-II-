#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int p,q;

int a[100005] = {0};
int map[100005] = {0};

void cal(int dth){
    char c;
    scanf(" %c",&c);
    int flag = 0;
    while(c!=')'){
        if(c=='f'){
            getchar();
            if(flag ==0)
                cal(dth+1);
            else
                cal(dth);
        }
        else if(isdigit(c)){
            ungetc(c, stdin);
            int z;
            scanf("%d",&z);
            if(map[z]==0) map[z] = 1;
            if(flag==0){
                int ppp = p;
                for(int i=1;i<dth;i++) ppp *=p;
                map[z] *= ppp;
            }
            else if(flag==1){
                if(dth-1>0)
                map[z] *= p*(dth-1);
            }
        }
        else if(c==',') flag = 1;
        c = getchar();
    }
    if(c==')'){
        for(int i=1;i<=5;i++) printf("map[%d] = %d , ",i,map[i]);
        printf("\n");
        return;
    }
}

int main(){
    //for(int i=0;i<100005;i++) map[i] = 1;
    scanf("%d %d",&p,&q);
    
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    getchar();
    //printf("e = %c",e);
    getchar();
    //printf("zzz");
    cal(1);
    
    for(int i=1;i<=n;i++) printf("map[%d] = %d , ",i,map[i]);
    /*
    int anw = 0;
    for(int i=1;i<=n;i++){
        anw += a[i]*map[i];
    }
    //printf("anw = %d\n",anw);
    int m;
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        int c,b;
        scanf("%d %d",&c,&b);
        anw -= a[c]*map[c];
        anw += b*map[c];
        int sss = anw%q;
        printf("%d\n",sss);
    }
    */
    return 0;
}
