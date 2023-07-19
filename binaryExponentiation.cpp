#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Binary exponentiation calculates a^n in O(logn) time 

int power(int a , int n ){
    int res = 1 ;
    while(n){
        if(n & 1){
            res = res * a ;
            n-- ;
        }
        else{
            a = a * a ;
            n /= 2 ;
        }
    }
    return res ;
}

int main(){
    int a , n ;
    cin >> a >> n ;
    cout << "a^n = " << power(a , n) << endl;
    return 0 ;
}