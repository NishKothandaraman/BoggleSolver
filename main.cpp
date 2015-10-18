#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unordered_map>

using namespace std;

int n;                                              // matrix size
unordered_map<string, int> hmap;                    // hash map to store words found from word matrix

struct Matrix                                       // structure to hold the word matrix
{
    char x;
    int visited;
};

struct TrieStruct                                   // Trie to hold dictionary words
{
    bool value;                                     // value to tell if node is leaf node or not
    unordered_map<char, TrieStruct*> childNodes;    // childNodes of the Trie Structure
    TrieStruct()
    {
        value = false;                              // initializing value to false
    }
};

class Trie                                          // class holding Trie Structure and required functions
{
    TrieStruct* t;

public:
    
    Trie()
    {
        t = new TrieStruct();                       // initializing TrieStruct
    }

    void addToTrie(string s)                        // adding dictionary words to Trie
    {
        TrieStruct* currNode = t;
        for(int i = 0; i < s.length(); i++)
        {
            if(currNode->childNodes.count(s[i]) == 0)
            {
                currNode->childNodes[s[i]] = new TrieStruct();
            }
            currNode = currNode->childNodes[s[i]];
        }
        currNode->value = true;
    }
    
    bool searchInTrie(string s)                     // searching words in Trie
    {
        if(t == NULL)
        {
            return false;
        }
        TrieStruct* currNode = t;
        for(int i = 0; i < s.length(); i++)
        {
            if(currNode->childNodes.count(s[i]) == 0)
            {
                return false;
            }
            currNode = currNode->childNodes[s[i]];
        }
        return currNode->value;
    }

};

void input(Matrix wordMatrix[10][10])           // accepting matrix from user
{
    cout<<"\nEnter size of the word matrix ";
    cin>>n;
    
    cout<<"\nEnter the letters (row-wise) \n";
    int i,j;
    for(i = 0;i < n;i++)
    {
        cout<<"Row "<<i+1<<" ";
        for(j = 0;j < n;j++)
        {
            cin>>wordMatrix[i][j].x;
            wordMatrix[i][j].visited = 0;
        }
    }
}

void display(Matrix wordMatrix[10][10]) // displaying matrix to user
{
    int i,j;
    cout<<"\nThe wordMatrix is ";
    for(i = 0;i < n;i++)
    { cout<<"\n";
        for(j = 0;j < n;j++)
            cout<<wordMatrix[i][j].x<<" ";
    }
    cout<<"\n\n";
}

void checkWord(char next,Matrix wordMatrix[10][10], int i, int j,string s,Trie* t)
{
    // to generate all possible combinations of words from the matrix
    
    if(i == n || j == n || i == -1 || j == -1 || wordMatrix[i][j].visited == 1)
    {
        return;
    }
    
    wordMatrix[i][j].visited = 1;
    
    if(s.length() > 3)
    {
        if(t->searchInTrie(s))
        {
              hmap[s] = 1;
        }
    }
    
    s += wordMatrix[i][j].x;
    
    checkWord(wordMatrix[i+1][j-1].x,wordMatrix,i+1,j-1,s,t);
    checkWord(wordMatrix[i+1][j].x,wordMatrix,i+1,j,s,t);
    checkWord(wordMatrix[i+1][j+1].x,wordMatrix,i+1,j+1,s,t);
    checkWord(wordMatrix[i][j+1].x,wordMatrix,i,j+1,s,t);
    checkWord(wordMatrix[i-1][j+1].x,wordMatrix,i-1,j+1,s,t);
    checkWord(wordMatrix[i-1][j].x,wordMatrix,i-1,j,s,t);
    checkWord(wordMatrix[i-1][j-1].x,wordMatrix,i-1,j-1,s,t);
    checkWord(wordMatrix[i][j-1].x,wordMatrix,i,j-1,s,t);
    
    wordMatrix[i][j].visited = 0;
}

void findWords(Matrix wordMatrix[10][10],Trie* t)
{
    // passing each letter to checkWord
    
    int i,j;
    for(i = 0;i < n;i++)
    {
        for(j = 0;j < n;j++)
        {
           string s = "";
           checkWord(wordMatrix[i][j].x,wordMatrix,i,j,s,t);
        }
    }
}

void displayFoundWords()                        // printing all words formed from word matrix
{
    for(auto iter = hmap.begin(); iter != hmap.end(); iter++)
    {
        cout<<iter->first<<"\n";
    }
}

int main()
{
    Matrix wordMatrix[10][10];                  // word matrix to hold the boggle board
    Trie t = Trie();                            // Trie to store dictionary words
    string s;
    ifstream file1;                             // dictionary file
    
    input(wordMatrix);                          // input word matrix
    display(wordMatrix);
    
    file1.open("dictionary.txt");
    
    if (file1.good())
    {
        while(getline(file1,s))                 // getting words from dictionary
        {
            t.addToTrie(s);                     // adding dictionary words to Trie
        }
        file1.close();
    }
    
    findWords(wordMatrix,&t);
    displayFoundWords();
    
    return 0;
}




