#include <bits/stdc++.h> 
class Node{
    public:
    Node * links[26];
    int cp ;
    int ew ;

    Node(){
        this -> cp = 0 ;
        this -> ew = 0 ;
    }

    bool containsKey(char ch){
        return links[ch - 'a'] != NULL ;
    }

    void putChar(char ch){
        links[ch - 'a'] = new Node() ;
    }

    Node * getRef(char ch){
        return links[ch - 'a'] ;
    }


};
class Trie{

    public:
    Node * root ;
    Trie(){
        // Write your code here.
        this -> root = new Node() ;
    }

    void insert(string &word){
        // Write your code here.
        Node * ptr = root ;
        for(int i = 0 ; i < word.size() ; i++){
            char ch = word[i] ;
            if(!ptr -> containsKey(ch)){
                ptr -> putChar(ch) ;
            }
            ptr = ptr -> getRef(ch) ;
            ptr -> cp++ ;
        }
        ptr -> ew++ ;
    }

    int countWordsEqualTo(string &word){
        // Write your code here.
        Node * ptr = root ;
        for(int i = 0 ; i < word.size() ; i++){
            char ch = word[i] ;
            if(!ptr -> containsKey(ch)){
                return 0 ;
            }
            ptr = ptr -> getRef(ch) ;
        }
        return ptr -> ew ;
    }

    int countWordsStartingWith(string &word){
        // Write your code here.
        Node * ptr = root ;
        for(int i = 0 ; i < word.size() ; i++){
            char ch = word[i] ;
            if(!ptr -> containsKey(ch)){
                return 0 ;
            }
            ptr = ptr -> getRef(ch) ;
        }
        return ptr -> cp ;
    }

    void erase(string &word){
        // Write your code here.
        // Checking if "word" is present in Trie or not 
        int count = countWordsEqualTo(word) ;
        if(count == 0) return; // if there is no instance of this "word"
        // in the trie , we don't have to delete it 

        // if the word is present then we delete it 
        Node * ptr = root ;
        for(int i = 0 ; i < word.size() ; i++){
            char ch = word[i] ;
            ptr = ptr -> getRef(ch) ;
            ptr -> cp-- ;
        }
        ptr -> ew-- ;
    }
};
