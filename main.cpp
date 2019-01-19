//
//  main.cpp
//  Loan_exam_IRFA_HYB
//
//  Created by Hedi Yebbous Bensaid on 19/01/2019.


#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cstdio>


using namespace std;

double Compute_PMT(int n, double PV, double r) {
    
    double b,PMT;
    b = pow(1+r,n) - 1;
    b = 1/b;
    
    PMT = PV*r*(1+ b);
    
    
    return PMT;
    
}

double Compute_PV( double PMT, int n, double r){
    
    double a,PV;
    a = pow(1+r,n) - 1;
    a = 1/a;
    a = a + 1;
    a = 1/a ;
    
    PV = a*(PMT/r);
    
    return PV;
    
}

int Compute_n(double PMT, double r, double PV) {
    double n;
    
    n = log(PMT/(PMT - r*PV))/log(1+r);
    n = n + 1;
    
    return (int) n;
}

double f(double r,double PMT,double PV,int n){
    double x,fv;
    x = log(PMT/(PMT - r*PV))/n;
    fv = exp(x) - 1;
    
    return fv;
}

double fc(double r,double PMT,double PV,int n){
    double x;
    x = pow(1+r,n) - 1;
    x = 1/x;
    x = x + 1;
    x = x*r - PMT/PV;
    
    return x;
}


int main() {
    
    int nb;
    double PV0,rate;
    
    cout << "1. Compute PMT " << endl;
    cout << "Enter the number of periods n (integer) : ";
    cin >> nb  ;
    
    nb = (int) nb;
    nb = abs(nb);
    
    
    cout << "Enter PV0 (strictly positive): " ;
    cin >> PV0;
    if (PV0)
    PV0 = abs(PV0);
    
    cout << "Enter interest rate r (%): " ;
    cin >> rate;
    
    rate = rate/100;
    double PMT_;
    
    PMT_ = Compute_PMT(nb,PV0,rate);
    
    cout << "PMT = " << PMT_ << endl;
    
    cout << endl;
    
    cout << "2. Compute PV " << endl;
    cout << "Enter PMT : " ;
    
    cin >> PMT_ ;
    cout << "Enter the number of periods n (integer) : ";
    cin >> nb  ;
    nb = (int) nb;
    nb = abs(nb);
    
    cout << "Enter interest rate r (% stricly positive): " ;
    cin >> rate;
    
    rate = rate/100;
    
    PV0 = Compute_PV(PMT_,nb,rate);
    
    cout << "PV0 = " << PV0 << endl;
    
    cout << "3. Compute number of periods " << endl;
    cout << "Enter PMT (strictly positive) : " ;
    
    cin >> PMT_ ;
    
    cout << "Enter interest rate r (% stricly positive): " ;
    cin >> rate;
    
    rate = rate/100;
    rate = abs(rate);
    
        cout << "Enter PV0 : " ;
        cin >> PV0;
        PV0 = abs(PV0);

    
    nb = Compute_n(PMT_,rate,PV0);
    if (nb <=0) {
        cout << " Negative period value, please check input data "<< endl;
    }
    
    cout << "Number of periods = " << nb << endl;
    
    
    cout << " 4. Compute the rate r " << endl;
    
    cout << "Enter PMT (strictly positive) : " ;
    
    cin >> PMT_ ;
    
    cout << "Enter the number of periods n (integer) : ";
    cin >> nb  ;
    nb = (int) nb;
    nb = abs(nb);
    

        cout << "Enter PV0 (strictly positive): " ;
        cin >> PV0;
        PV0 = abs(PV0);

    
    double r0,r1,tol,g;
    
    r0 = 1.0;
    r1 = 2.0;
    tol = 10^(-3);
    double temp;
    int i =0;
    do {
        
        temp = r1;
        g = (fc(r1,PMT_,PV0,nb)*(r1-r0))/(fc(r1,PMT_,PV0,nb)-fc(r0,PMT_,PV0,nb));
        
        r1 = r1 - g;
        
        r0 = temp;

        i++;
        
        cout << "value r0 " << r0 << endl;
        
    }
    while(abs(fc(r1,PMT_,PV0,nb))>tol);
    
    cout << " Value of r : " <<  r0*100 <<" % " << endl;
    cout << "Iteration : " << i << endl;
    
    
    
    return 0;
}
