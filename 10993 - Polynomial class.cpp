#include "13144.h"
#include <iostream>


using namespace std;

Polynomial::Polynomial(){
    greatestPower = 0;
    for(int i=0;i<101;i++){
        coefficients[i] = 0;
    }
}

Polynomial::Polynomial(const int a, const int b[51]){
    greatestPower = a;
    for(int i=0;i<51;i++){
        coefficients[i] = b[i];
    }
}

Polynomial Polynomial::add(const Polynomial a)const{
    int big = greatestPower>a.greatestPower?greatestPower:a.greatestPower;
    Polynomial z;
    z.greatestPower = big;
    for(int i=0;i<=big;i++){
        z.coefficients[i] = coefficients[i]+a.coefficients[i];
    }
    return z;
}

Polynomial Polynomial::subtract(const Polynomial a)const{
    int big = greatestPower>a.greatestPower?greatestPower:a.greatestPower;
    Polynomial z;
    z.greatestPower = big;
    for(int i=0;i<=big;i++){
        z.coefficients[i] = coefficients[i]-a.coefficients[i];
    }
    return z;
}

Polynomial Polynomial::multiplication(const Polynomial a)const{
    int big = greatestPower>a.greatestPower?greatestPower:a.greatestPower;
    Polynomial z;
    z.greatestPower = greatestPower+a.greatestPower;
    for(int i=0;i<=big;i++){
        for(int j=0;j<=big;j++){
            z.coefficients[i+j] += coefficients[j]*a.coefficients[i];
        }
    }
    return z;
}

void Polynomial::output() const{
    for(int i=greatestPower;i>=0;i--){
        cout<<coefficients[i];
        if(i!=0) cout<<" ";
    }
};
