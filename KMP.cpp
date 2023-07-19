#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// trivial algorithm 
vector<int> prefix_function(string s){
    // Time Complexity => O(N^3)
    int n = s.size() ;
    vector<int>pi(n , 0) ;
    for(int i = 0 ; i < n ; i++){
        for(int k = 0 ; k <= i ; k++){
            if(s.substr(0 , k) == s.substr(i - k + 1 , k)){
                pi[i] = k ;
            }
        }
    }
    return pi ;
}
// Optimized version 
// Time => O(n)
vector<int> prefix_function_optimized(string s){
    int n = (int)s.length();
    vector<int> pi(n , 0); // pi[0] = 0 
    int i = 1 , j = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        // if we keep not getting a match j will keep jumping back to the last such position where 
        // suffix == prefix 
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        // if there is a match assign pi[i] = j + 1 
        if (s[i] == s[j]) 
            j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> KMP(string txt , string pat){ 
    // Time complexity => O(M + N) , M = length of txt , N = length of pat
    // Generate new string 
    string s = pat + '$' + txt ;
    int n = s.size() ;
    vector<int>pi(n , 0) ;
    vector<int>occurences ; 
    for(int i = 1 ; i < n ; i++){
        int j = pi[i - 1] ;
        while(j > 0 && s[i] != s[j]){
            j = pi[j - 1] ;
        }
        if(s[i] == s[j]){
            j++ ;
        }
        pi[i] = j  ;
        if(pi[i] == pat.size()){
            occurences.push_back(i - 2 * pat.size()) ;
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
    vector<int>pos = KMP(txt , pat) ;
    for(auto it : pos){
        cout << it << " " ; 
    }
    return 0;
}