#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

vector<bitset<8> > toBitset(string s);
vector<vector<vector<bool> > > putBsMat(vector<bitset<8> > bsVec);
vector<bool> doXOR(vector<vector<bool> >M);
vector<vector<bool> > doRound(vector<vector<bool> > M);
vector<vector<bool> > getInternalKeys(string key);
void print(vector<bool> v);
void printMat(vector<vector<bool> > M);
#endif