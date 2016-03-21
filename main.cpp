#include <iostream>
#include <vector>
#include <string>
#include "keyGenerator.h"
#include "cipher.h"


using namespace std;

int main(){
	string s = "kriptografitubes";
	vector<vector<bool> > res = getInternalKeys(s);
	// for(int i=0; i<res.size(); i++){
	// 	for(int j=0; j<res[i].size(); j++)
	// 		cout<<res[i][j];
	// 	cout<<endl;
	// }

	string message = "Vincent Theophilus Ciputra";
	vector<vector<bitset<8> > > mainBlockMessage;
	vector<vector<bitset<8> > >  mainUpaBlockMessage;

	// getline(cin, message);

	cout << "message : " << message << endl;
	cout << "left shift : " << leftShift(message) << endl;
	cout << "right shift : " << rightShift(message) << endl;
	cout << message.length() << endl;

	mainBlockMessage = toBlockMessage(message);
	mainUpaBlockMessage = toUpaBlockMessage(mainBlockMessage);

	//print block message
	for(int i=0;i<mainBlockMessage.size();i++){
		cout << "block message " << i << " : ";
		for(int j=0;j<mainBlockMessage[i].size();j++){
			cout << mainBlockMessage[i][j];
		}
		cout << endl;
	}

	//print upa block message
	for(int i=0;i<mainUpaBlockMessage.size();i++){
		cout << "upa block message i " << i << " : " << endl;
		for(int j=0;j<mainUpaBlockMessage[i].size();j++){
				cout << mainUpaBlockMessage[i][j];
		}
		cout << endl;
	}

	return 0;
}
