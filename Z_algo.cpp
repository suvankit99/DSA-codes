#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Trivial algo 
vector<int> Z_function(string s ){
    // Time => O(N^2)
    int n = s.size() ;
    vector<int>Z(n , 0) ; // Z[0] = 0 
    for(int i = 1 ; i < n ; i++){
        for(int j = i ; j < n ; j++){
            if(s[j] == s[j - i]){
                Z[i]++ ;
            }
            else{
                break ;
            }
        }
    }
    return Z ;
}
// optimized algo 
// Terminology => Right most segment match == Z-box
vector<int> z_function(string s) {
    // Time => O(N)
    int n = s.size();
    vector<int> z(n , 0);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        // initialize z[i]
        if(i < r) { \
        // it can be either r - i i.e. characters remaining in Z-box or the z[i - l] 
            z[i] = min(r - i, z[i - l]);
        }
        // We are expanding the z box or the right most segment match here 
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        // updating l and r
        // if we go out of the Z box 
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// string matching :  Time => O(M + N)
vector<int> Z_algorithm_string_match(string txt , string pat){
    string s = pat + '#' + txt ;
    int n = s.size() ;
    vector<int>z(n , 0) ;
    int l = 0 , r = 0 ;
    vector<int>occurences ;
    for(int i = 1 ; i < n ; i++){
        if(i < r) { 
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
        if(z[i] == pat.size()){
            occurences.push_back(i - pat.size() - 1) ;
        }
    }
    return occurences ;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string txt;
    cin >> txt ;
    string pat;
    cin >> pat ;
    vector<int>pos = Z_algorithm_string_match(txt , pat) ;
    for(auto it : pos){
        cout << it << " " ; 
    }
    return 0;
}