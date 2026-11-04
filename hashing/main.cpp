#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <fstream>

using namespace std;

int nextPrime(int);
void cleanWord(string&);
bool isPrime(int);
int hashFunction(string str, int tblSize);

int main(int argc, char* argv[])
{
    string inStr;
    vector<string> words;
    int collisions = 0;

    // cout << "Enter a string to hash: ";
    // getline(cin, inStr);

    ifstream fin;
    // fin.open("pg26752.txt");
    fin.open("frankenstein.txt");
    string word;
    while(getline(fin, word, ' '))
    {
        cleanWord(word);
        words.push_back(word);
    }

    // istringstream iss;
    // iss.str(inStr);
    // string word;
    // // for(auto word : inStr)
    // while(getline(iss, word, ' '))
    // {
    //     cleanWord(word);
    //     words.push_back(word);
    // }

    // for(auto word : words)
    // {
    //     cout << word << endl;
    // }

    int hashTableSize = words.size();
    hashTableSize = nextPrime(hashTableSize * 2);
    // cout << "hashTableSize: " << hashTableSize << endl;

    vector<list<string>> hashTable(hashTableSize);

    for(auto word : words)
    {
        int idx = hashFunction(word, hashTableSize);

        for(auto existing : hashTable.at(idx))
        {
            if(word != existing)
            {
                collisions++;
                break;
            }
        }
        hashTable.at(idx).push_back(word);
    }

    for(int i = 0; i < hashTableSize; i++)
    {
        cout << i << ": ";
        for(auto word : hashTable.at(i))
        {
            cout << word << ", ";
        }
        cout << endl;
    }

    cout << "TableSize: " << hashTableSize << endl;
    cout << "Total Collisions: " << collisions << endl;

    return 0;
}

int hashFunction(string str, int tblSize)
{
    int p = 31;
    int hashval = 0;
    int p_pow = 1;
    for(auto ch : str)
    {
        hashval = (hashval + (ch - 'a' + 1) * p_pow);
        p_pow = (p_pow * p) % tblSize;
    }
    return hashval%tblSize;
    // unsigned long hash = 0;
    // for(auto ch : str)
    // {
    //     hash = ch + (hash << 6) + (hash << 16) - hash;
    // }
    // return hash%tblSize;
    // unsigned long hash = 5381;
    // for(auto ch : str)
    // {
    //     hash = ch + (hash << 5) + hash;
    // }
    // return hash%tblSize;
    // int stringSum = 0;
    // for(auto ch : str)
    // {
    //     stringSum += ch;
    // }
    // stringSum %= tblSize;
    // return stringSum;
}

bool isPrime(int num)
{
    if(num <= 1) return false;
    if(num <= 3) return true;
    if(num%2 == 0 || num%3 == 0) return false;
    for(int i = 5; i * i <= num; i+= 6)
    {
        if(num%i == 0 || num%(i+2) == 0) return false;
    }
    return true;
}

int nextPrime(int num)
{
    while(!isPrime(num)) num++;
    return num;
}

void cleanWord(string& word)
{
    string cleanWord = "";
    for(auto ch : word)
    {
        if(isalpha(ch)) cleanWord += tolower(ch);
    }
    word = cleanWord;
}