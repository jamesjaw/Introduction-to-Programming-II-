#include <iostream>
#include <cstring>
#include <iomanip>
#include "13144.h"
using namespace std;

BigInt::BigInt(){
    sign = true;
    for(int i=0;i<N;i++){
        bigInt[i] = 0;
    }
}

BigInt::BigInt(char* a){
    sign = true;
    for(int i=0;i<N;i++){
        bigInt[i] = 0;
    }
    long long size = (long long)strlen(a);
    int idx = 0;
    int i = 0;
    for(i = size-1;i > 7;i -= 8){
        int temp = 0;              //!!!!!!!!!!!!!!!!!!!!!!記得歸零（宣告在外面的話）
        for(int j = i-7;j<=i;j++){  //???
            temp *= 10;
            temp += a[j] - '0';
        }
        bigInt[idx++] = temp;
    }
    int temp = 0;
    for(int j=0;j<=i;j++){  //???
        temp *= 10;
        temp += a[j]-'0';
    }
    bigInt[idx++] = temp;
}

BigInt::BigInt(const BigInt& a){
    sign = a.sign;
    // auto for??
    for(int i=0;i<N;i++){
        bigInt[i] = a.bigInt[i];
    }
}

BigInt & BigInt::operator = (const BigInt& a){
    this->sign = a.sign;
    for(int i=0;i<N;i++){
        this->bigInt[i] = a.bigInt[i];
    }
    return *this;
}

bool BigInt::operator < (BigInt a){
    if(this->sign==true && a.sign==false) return false;
    else if(this->sign==false && a.sign==true) return true;
    else{
        for(int i=N-1;i>=0;i--){
            if(bigInt[i]<a.bigInt[i]){
                if(sign==true) return true;
                else return false;
            }
            else if(bigInt[i]>a.bigInt[i]){
                if(sign==true) return false;
                else return true;
            }
        }
        return false;
    }
}

bool BigInt::operator > (BigInt a){
    if(this->sign==true && a.sign==false) return true;
    else if(this->sign==false && a.sign==true) return false;
    else{
        for(int i=N-1;i>=0;i--){
            if(bigInt[i]<a.bigInt[i]){
                if(sign==true) return false;
                else return true;
            }
            else if(bigInt[i]>a.bigInt[i]){
                if(sign==true) return true;
                else return false;
            }
        }
        return false;
    }
}
bool BigInt::operator == (BigInt a){
    if(*this>a==false && *this<a==false) return true;
    else return false;
}
bool BigInt::operator >= (BigInt a){
    if(*this < a == true) return false;
    else return true;
}
bool BigInt::operator <= (BigInt a){
    if(*this > a == true) return false;
    else return true;
}
BigInt BigInt::operator + (BigInt r){
    return *this;
}
BigInt BigInt::operator - (BigInt r){
    BigInt anw;
    for(int i=0;i<N;i++){
        anw.bigInt[i] = 0;
    }
    
    if(this->sign == false){
        anw.sign = false;
        for(int i=0;i<N;i++){
            anw.bigInt[i] += this->bigInt[i] + r.bigInt[i];
            if(anw.bigInt[i]>=BASE){   //
                anw.bigInt[i] = anw.bigInt[i] - BASE;  //
                anw.bigInt[i+1] += 1;
            }
        }
    }
    else{
        if(*this < r){
            anw.sign = false;
            for(int i=0;i<N;i++){
                if(r.bigInt[i] < this->bigInt[i]){
                    r.bigInt[i+1] -= 1;
                    r.bigInt[i] += BASE;
                    anw.bigInt[i] = r.bigInt[i] - this->bigInt[i];
                }
                else if(r.bigInt[i] == this->bigInt[i]){
                    anw.bigInt[i] = 0;
                }
                else if(r.bigInt[i] > this->bigInt[i]){
                    anw.bigInt[i] = r.bigInt[i] - this->bigInt[i];
                }
            }
        }
        else if(*this == r){
            anw.sign = true;
            for(int i=0;i<N;i++){
                anw.bigInt[i] = 0;
            }
        }
        else if(*this > r){
            anw.sign = true;
            for(int i=0;i<N;i++){
                if(this->bigInt[i] < r.bigInt[i]){
                    this->bigInt[i+1] -= 1;
                    this->bigInt[i] += BASE;
                    anw.bigInt[i] = this->bigInt[i] - r.bigInt[i];
                }
                else if(this->bigInt[i] == r.bigInt[i]){
                    anw.bigInt[i] = 0;
                }
                else if(this->bigInt[i] > r.bigInt[i]){
                    anw.bigInt[i] = this->bigInt[i] - r.bigInt[i];
                }
            }
        }
    }
    return anw;
}

istream& operator >> (istream& ccin, BigInt& input){
    char ininder[1300];
    cin>>ininder;
    input = BigInt(ininder);
    return ccin;;
}
ostream& operator << (ostream& ccou, BigInt& out){
    if(out.sign==false) cout<<"-";
    int s = 0;
    int h = 1;
    for(int i=149;i>=0;i--){
        if(out.bigInt[i]!=0){
            s = 1;
        }
        if(s==1){
            if(h==1){
                h = 0;
                cout<<out.bigInt[i];
            }
            else{
                cout<<setfill('0')<<setw(8)<<out.bigInt[i];
            }
        }
    }
    if(s==0){
        cout<<"0";
    }
    
    return ccou;
}

void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n){
    for(int i=0;i<n;i++){
        BigInt mis;
        cin>>mis;
        if(inosuke>=tanjiro && inosuke>=zenitsu){
            inosuke = inosuke - mis;
        }
        else if(tanjiro>=zenitsu &&tanjiro>=inosuke){
            tanjiro = tanjiro - mis;
        }
        else if(zenitsu>=tanjiro && zenitsu>=inosuke){
            zenitsu = zenitsu - mis;
        }
    }
}
