#include <bits/stdc++.h>
#include <iostream>

using namespace std;

class Node
{
public:
    Node *links[26];
    bool flag = false;

    bool containsKey(char ch)
    {
        return links[ch - 'a'] != NULL;
    }
    void setEnd()
    {
        flag = true;
    }
    Node *getReference(char ch)
    {
        return links[ch - 'a'];
    }
    void putChar(char ch, Node *node)
    {
        links[ch - 'a'] = node;
    }
};

class Trie
{
public:
    Node *root;

    Trie()
    {
        this->root = new Node();
    }

    void insert(string word)
    {
        Node *ptr = root;
        for (int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if (!ptr->containsKey(ch))
            {
                ptr->putChar(ch, new Node());
            }
            ptr = ptr->getReference(ch);
        }
        ptr->setEnd();
    }

    bool search(string word)
    {
        Node *ptr = root;
        for (int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if (!ptr->containsKey(ch))
            {
                return false;
            }
            ptr = ptr->getReference(ch);
        }
        return ptr->flag; // Check if finally flag is true or not at the last reference node
    }

    bool startsWith(string prefix)
    {
        Node *ptr = root;
        for (int i = 0; i < prefix.size(); i++)
        {
            char ch = prefix[i];
            if (ptr->containsKey(ch))
            {
                ptr = ptr->getReference(ch);
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};
