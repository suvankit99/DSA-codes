#include <bits/stdc++.h>
#include <iostream>
typedef long long ll ;
using namespace std;

vector<int> rabin_karp(string const& pat, string const& txt) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = pat.size(), T = txt.size();
    // precomputing powers of p 
    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    // computing hash values for all prefixes of string txt
    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (txt[i] - 'a' + 1) * p_pow[i]) % m; 

    // computing hash values of pattern
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (pat[i] - 'a' + 1) * p_pow[i]) % m; 

    // comparing hash value of every substring of length |pattern| with hash value of pattern 
    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) { 
        long long cur_h = (h[i+S] + m - h[i]) % m; 
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t ; 
    cin >> t ; 
    while(t--){
        string txt ;
        cin >> txt ;
        string pat ; 
        cin >> pat ;
        vector<int>res = rabin_karp(pat , txt ) ;
        for(auto it : res){
            cout << it << " " ;
        }
        cout << "\n" ;
    }
    return 0;
}