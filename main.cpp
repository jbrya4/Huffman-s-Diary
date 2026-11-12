#include<stdio.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>

using namespace std;   

//Reference: https://www.geeksforgeeks.org/cpp/huffman-coding-in-cpp/

string promptUser(){
    //todo: limit users to 20 characters, so if the cin is longer than 20, ask them to send again until it's 20 or less charcaters. also can not be 0 characters.
    cout << "Tell me a secret:";
    string userString = "";
    getline(cin,userString);
    return userString;
}
void printFreqTable(unordered_map<char,int> freq);
unordered_map<char,int> countFrequency(const string str){
    unordered_map<char, int> freq;
    for(char c: str){
        freq[c]++;   
    }
    char userInput;
    cout << "Would like to see the frequency table? Type Y for yes, and N for no." << endl;
    cin >> userInput;
    if(userInput == 'Y' || userInput == 'y'){
        printFreqTable(freq);
    }
    return freq;
}

void printFreqTable(unordered_map<char,int> freq){
    for ( auto& pair : freq) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char ch, int freq): ch (ch), freq(freq), left(nullptr), right(nullptr) {}
    Node (char ch, int freq, Node* left, Node* right): ch(ch), freq(freq), left(left), right(right) {}
};

//Comparison object used for ordering the pq
struct compare {
    bool operator() (Node* l, Node* r){
        return l->freq > r->freq;
    }
};

priority_queue<Node*,vector<Node*>,compare> buildPriorityQueue(unordered_map<char,int> freq){
    // Create a priority queue to store live nodes of the Huffman tree
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Create a leaf node for each character and add it to the priority queue
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }
    //priority queue is in order of lowest to highest frequency
    //highest priority = lowest frequency 

    // Do till there is more than one node in the queue
    while (pq.size() != 1) {
        // Remove the two nodes of highest priority (lowest frequency) from the queue
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        // Create a new internal node with these two nodes
        // as children and with frequency equal to the sum
        // of the two nodes' frequencies
        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }
    return pq;
}

//print Huffman Codes

void buildHCodes (Node* root, string str, unordered_map<char,string>&huffmanCode){
    if (root == nullptr){
        return;
    }
    //if this node has no children
    if(!root->left && !root->right){
        huffmanCode[root->ch] = str;
    }

    buildHCodes(root->left, str + "0", huffmanCode);
    buildHCodes(root->right, str + "1", huffmanCode);

}

void printHCodes(unordered_map<char, string> huffmanCode){
    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << "\n";
    }
}

void decode (string str, Node* root) {
        cout << "\nDecoded string:\n";
        Node* curr = root;
        for (char bit : str) {
            if (bit == '0') {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }

            // Reached a leaf node
            if (!curr->left && !curr->right) {
                cout << curr->ch;
                curr = root;
            }
        }
        cout << "\n";
    };

//build huffman tree and generate huffman codes
void buildHuffmanTree(string userString, unordered_map<char,int> freq)
{
    priority_queue<Node*,vector<Node*>,compare> pq = buildPriorityQueue(freq);
    
    //Root stores pointer to the root of the Huffman Tree
    Node* root = pq.top();

    // Traverse the Huffman Tree and store Huffman Codes in a map
    //each character has a unique huffman code that corresponds to it
    unordered_map<char, string> huffmanCodeMap;
    buildHCodes(root, "", huffmanCodeMap);

    char userInput;
   
    string str = "";
    for (char ch : userString) {
        str += huffmanCodeMap[ch];
    }
    cout << "Would you like to see the encoded string? Type Y for yes and N for no." << endl;
    cin >> userInput;
    if(userInput == 'Y' || userInput == 'y'){
            cout << "\nEncoded string:\n" << str << "\n";        
    }

    //ask user if they'd like to decode the string
    cout << "Would you like to decode the encoded string? Type Y for yes and N for no." << endl;
    cin >> userInput;
    if(userInput == 'Y' || userInput == 'y'){
           decode(str, root);

    }
}

int main (){
    string userString = promptUser();
    unordered_map<char,int> freqTable = countFrequency(userString);
    buildHuffmanTree(userString, freqTable);
}