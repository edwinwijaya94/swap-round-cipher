#ifndef CIPHER_H
#define CIPHER_H

using namespace std;

vector<vector<bitset<8> > > toBlockMessage(string message);
vector<vector<bitset<8> > > toUpaBlockMessage(vector<vector<bitset<8> > > blockMessage);
string leftShift(string s);
string rightShift(string s);

#endif