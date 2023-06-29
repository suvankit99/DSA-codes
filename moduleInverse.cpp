#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Calculating modulo multiplicative inverse using Fermat's little theorem 
int power(int a, int n , int m) 
{
    int res = 1;
    while (n)
    {
        if (n & 1)
        {
            res = (res * a) % m;
            n--;
        }
        else
        {
            a = (a * a) % m;
            n /= 2;
        }
    }
    return res;
}

int main(){
    cout << "Calculating modulo multiplicative inverse using Fermat's little theorem\n" ;
    int a, m;
    cout << "Enter values of a and m , but m must be prime \n" ;
    cin >> a >> m ;

    cout << "mod inverse of a under mod m = " << power(a , m - 2 , m) ; 
    return 0 ;
}