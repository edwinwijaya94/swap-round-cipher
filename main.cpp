#include <iostream>
#include <vector>
#include <string>
#include "keyGenerator.h"
#include "cipher.cpp"


using namespace std;

int main(){
	string s = "kriptografitubes";
	vector<vector<bool> > res = getInternalKeys(s);
	// for(int i=0; i<res.size(); i++){
	// 	for(int j=0; j<res[i].size(); j++)
	// 		cout<<res[i][j];
	// 	cout<<endl;
	// }
	return 0;
}