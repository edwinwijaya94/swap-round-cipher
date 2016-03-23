#ifndef CIPHER_H
#define CIPHER_H

using namespace std;

vector<vector<bitset<8> > > toBlockMessage(string message);
vector<vector<bitset<8> > > toUpaBlockMessage(vector<vector<bitset<8> > > blockMessage);
string leftShift(string s);
string rightShift(string s);
vector<vector<bitset<16> > > permute(vector<vector<bitset<8> > > upaBlock);
vector<vector<bitset<16> > > permute16(vector<vector<bitset<16> > > upaBlock);
vector<vector<bitset<16> > > reversePermute(vector<vector<bitset<16> > > permuteMessage);

#endif