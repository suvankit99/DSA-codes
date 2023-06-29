#include <iostream>
#include<bits/stdc++.h>
using namespace std;

// Computing polynomial rolling hash function 
long long compute_hash(string const& s) {
    const int p = 31;
    const int mod = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % mod;
        p_pow = (p_pow * p) % mod;
    }
    return hash_value;
}
int main() {
	// your code goes here
	string s ;
    cout << "Enter string = " ;
    cin >> s ; 
    cout << "Hash = " << compute_hash(s) << endl ;
	return 0;
}
