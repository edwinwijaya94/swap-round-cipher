#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include "keyGenerator.h"
#include "cipher.h"

using namespace std;


vector<vector<bitset<8> > > blockMessage;
vector<vector<bitset<8> > > upaBlockMessage;

//convert message to block message 128 bit
vector<vector<bitset<8> > > toBlockMessage(string message){
	bitset<8> paddingBitset;
	vector<bitset<8>> tempBitset;
	string tempMessage = message;
	string tempString = "";

	for(int i=0; i<=message.length(); i++){
		if (i % 16 == 0 && i != 0){
			tempBitset = toBitset(tempString);
			blockMessage.push_back(tempBitset);
			tempString = "";
		}

		tempString += message[i];
	}
	if (tempMessage.length() % 16 != 0){
		tempBitset = toBitset(tempString);
		for(int i=0;i<15-(message.length()%16);i++){
			tempBitset.push_back(paddingBitset);
		}
		blockMessage.push_back(tempBitset);
	}

	return blockMessage;
}

vector<vector<bitset<8> > > toUpaBlockMessage(vector<vector<bitset<8> > > blockMessage){
	vector<bitset<8>> tempBitset;

	for(int i=0;i<blockMessage.size();i++){
		for(int j=0;j<blockMessage[i].size();j++){
			if (j % 2 == 0 && j != 0){
				upaBlockMessage.push_back(tempBitset);
				tempBitset.clear();
			}

			tempBitset.push_back(blockMessage[i][j]);
		}
		upaBlockMessage.push_back(tempBitset);
		tempBitset.clear();
	}

	return upaBlockMessage;
}

string leftShift(string s){
	string res = "";

	res += s.substr(1,s.length()-1);
	res += s[0];

	return res;
}

string rightShift(string s){
	string res = "";

	res += s[s.length()-1];
	res += s.substr(0,s.length()-1);
	
	return res;
}
