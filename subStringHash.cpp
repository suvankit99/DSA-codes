#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll ;
ll dp[1000001];
ll inv[1000001];
ll mod = 1e9 + 7 ;

ll power(int a, int n, int m)
{
    ll res = 1;
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

void init(string s){
    const int p = 31;
    const int mod = 1e9 + 9;
    long long p_pow = 1;
    dp[0] = (s[0] - 'a' + 1) * p_pow;
    for (int i = 1; i < s.size(); i++)
    {
        p_pow = (p_pow * p) % mod;
        inv[i] = power(p, mod - 2, mod);
        dp[i] = (dp[i - 1] + (s[i] - 'a' + 1) * p_pow) % mod;
    }
}
long long subStringHash(int L , int R){
    long long res =  dp[R] ;
    if(L > 0) res = res - dp[L - 1] ;
    res = (res * inv[L]) % mod ;
    return res ;
}
int main()
{
    string s;
    cin >> s;
    init(s) ;
    int L , R ;
    cin >> L >> R ;
    cout << "Hash = " << subStringHash(L , R) << endl ;
    return 0;
}