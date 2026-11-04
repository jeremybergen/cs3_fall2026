#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <bitset>

using namespace std;

class Node
{
    private:
    char _ch;
    int _freq;
    Node* _left;
    Node* _right;

    public:
    Node(char ch = '\0', int freq = 0, Node* left = nullptr, Node* right = nullptr) : _ch(ch), _freq(freq), _left(left), _right(right) {}
    char getCh() { return _ch; }
    int getFreq() { return _freq; }
    Node* getLeft() { return _left; }
    Node* getRight() { return _right; }
};

class Compare
{
    public:
    bool operator()(Node* left, Node* right)
    {
        return left->getFreq() > right->getFreq();
    }
};

Node* buildHuffmanTree(string text);
void buildCode(Node* root, unordered_map<char, string>& huffmanCode, string str);
string encodeStr(unordered_map<char, string>& huffmanCode, string str);
string decodeStr(Node* root, string str);
string bitsetStr(string str);

int main(int argc, char* argv[])
{
    // string text = "aaaaaaabbbcccccccccccccdddddeeeffffgg";
    // string text = "this is a sentence with lots of ts and ses";
    string text;

    // cout << "Enter text to encode: ";
    // getline(cin, text);
    ifstream fin;
    fin.open("pg26752.txt");
    string inLine;
    while(getline(fin, inLine))
    {
        text += inLine;
    }

    string encodedStr;
    string decodedStr;
    unordered_map<char, string> huffmanCode;
    Node* root;

    root = buildHuffmanTree(text);
    buildCode(root, huffmanCode, "");
    encodedStr = encodeStr(huffmanCode, text);
    decodedStr = decodeStr(root, encodedStr);

    if(encodedStr.length() % 8 != 0)
    {
        for(int i = 0; i < encodedStr.length() % 8; i++)
        {
            encodedStr += "0";
        }
    }
    // cout << "Encoded: " << encodedStr << endl;

    // cout << "Decoded: " << decodedStr << endl;
    string codedStr = bitsetStr(encodedStr);
    cout << "codedStr.length(): " << codedStr.length() << endl;
    // cout << "codedStr: " << codedStr << endl;
    cout << "Original bits: " << text.length() << endl;
    cout << "Encoded bits: " << encodedStr.length()/8.0 << endl;
    cout << "Saved rate: " << encodedStr.length()/(text.length()*8.0) << endl;

    Node* encodedRoot;
    string encodedStr2;
    string decodedStr2;
    unordered_map<char, string> encodedHuffmanCode;
    // Node* root;

    encodedRoot = buildHuffmanTree(codedStr);
    buildCode(encodedRoot, encodedHuffmanCode, "");
    // for(auto elem : encodedHuffmanCode)
    // {
    //     cout << elem.first << ", " << elem.second << endl;
    // }
    encodedStr2 = encodeStr(encodedHuffmanCode, codedStr);
    decodedStr2 = decodeStr(encodedRoot, encodedStr2);

    // cout << "Encoded2: " << encodedStr2 << endl;

    // cout << "Decoded2: " << decodedStr2 << endl;
    // string codedStr = bitsetStr(encodedStr);
    // cout << "codedStr.length(): " << codedStr.length() << endl;
    // cout << "codedStr: " << codedStr << endl;
    cout << "Original bits2: " << codedStr.length() << endl;
    cout << "Encoded bits2: " << encodedStr2.length()/8.0 << endl;
    cout << "Saved rate2: " << encodedStr2.length()/(codedStr.length()*8.0) << endl;
    cout << "Encoded2 Saved Rate: " << encodedStr2.length()/(text.length()*8.0) << endl;


    return 0;
}

string bitsetStr(string str)
{
    
    string tmpStr = "";
    string outStr = "";
    int counter = 0;
    for(char ch : str)
    {
        tmpStr += ch;
        if(counter == 7) 
        {
            bitset<8> bits(tmpStr);
            // cout << "DEBUG: tmpStr: " << tmpStr << endl;
            outStr += (char)bits.to_ulong();
            counter = 0;
            tmpStr = "";
            continue;
        }
        counter++;
    }
    return outStr;
}

string decodeStr(Node* root, string str)
{
    string outStr = "";
    Node* curNode = root;
    for(auto ch : str)
    {
        if(ch == '0')
        {
            curNode = curNode->getLeft();
        }
        else
        {
            curNode = curNode->getRight();
        }

        if(curNode->getLeft() == nullptr && curNode->getRight() == nullptr)
        {
            outStr += curNode->getCh();
            curNode = root;
        }
    }
    return outStr;
}

string encodeStr(unordered_map<char, string>& huffmanCode, string str)
{
    string outStr = "";
    for(auto ch : str)
    {
        outStr += huffmanCode[ch];
    }
    return outStr;
    // cout << str << " encoded: " << outStr << endl;
}

void buildCode(Node* root, unordered_map<char, string>& huffmanCode, string str)
{
    if(root == nullptr) return;

    //print
    if(!root->getLeft() && !root->getRight())
    {
        // cout << root->getCh() << ": " << str << endl;
        huffmanCode[root->getCh()] = str;
    }
    buildCode(root->getLeft(), huffmanCode, str + "0");
    buildCode(root->getRight(), huffmanCode, str + "1");
}

Node* buildHuffmanTree(string text)
{
    priority_queue<Node*, vector<Node*>, Compare> pq;
    unordered_map<char, int> charFreq;

    for(char ch : text)
    {
        charFreq[ch]++;
    }

    // for(auto ch : charFreq)
    // {
    //     cout << ch.first << ": " << ch.second << endl;
    // }
    for(auto it = charFreq.begin(); it != charFreq.end(); it++)
    {
        pq.push(new Node(it->first, it->second));
    }

    // while(!pq.empty())
    // {
    //     cout << pq.top()->getCh() << ": " << pq.top()->getFreq() << endl;
    //     pq.pop();
    // }



    while(pq.size() > 1)
    {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newRoot = new Node('\0', left->getFreq() + right->getFreq(), left, right);
        pq.push(newRoot);
    }
    
    Node* root = pq.top();
    pq.pop();
    return root;
}