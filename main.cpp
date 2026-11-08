#include<stdio.h>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;   

string promptUser(){
    //todo: limit users to 20 characters, so if the cin is longer than 20, ask them to send again until it's 20 or less charcaters. also can not be 0 characters.
    cout << "Tell me a secret:";
    string userString = "";
    getline(cin,userString);
    return userString;
}

unordered_map<char,int> countFrequency(string str){
    unordered_map<char, int> freq;
    for(char c: str){
        freq[c]++;   
    }
    return freq;
}

void printFreqTable(unordered_map<char,int> freq){
    for ( auto [key, value] : freq) {
        cout << key << ": " << value << endl;
    }
}

int main (){
    string userString = promptUser();
    unordered_map<char,int> freqTable = countFrequency(userString);
    

}