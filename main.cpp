#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "keyGenerator.h"
#include "cipher.h"

using namespace std;

bitset<16> doSwap(bitset<16> ri, vector<bool> internalKey){
	
	vector<vector<bool> >res;
	for(int  i=0; i<4; i++){
		vector<bool> temp1;
		res.push_back(temp1);
		for(int j=0; j<4; j++){
			bool temp2 = 0;
			res[i].push_back(temp2);
		}
	}


	for(int i=0; i<16; i++){
		res[i/4][i%4] = ri[15-i];
	}
	// printf("res awal\n");
	// printMat(res);

	//define rows pair
	vector<pair<int,int> > rowPair;
	rowPair.push_back(make_pair(0,1));
	rowPair.push_back(make_pair(0,2));
	rowPair.push_back(make_pair(0,3));
	rowPair.push_back(make_pair(1,2));
	rowPair.push_back(make_pair(1,3));
	rowPair.push_back(make_pair(2,3));

	
	/*SWAPPING*/
	//swap by row
	int count = 0;
	for(int i=0; i<6; i++){
		if(internalKey[count++]){
			//swap
			vector<bool> temp;
			for(int j=0; j<4; j++){
				temp.push_back(res[rowPair[i].first][j]);
				res[rowPair[i].first][j] = res[rowPair[i].second][j];
				res[rowPair[i].second][j] = temp[j];
			}
		}
	}
	//swap by column
	for(int i=0; i<6; i++){
		if(internalKey[count++]){
			//swap
			vector<bool> temp;
			for(int j=0; j<4; j++){
				temp.push_back(res[j][rowPair[i].first]);
				res[j][rowPair[i].first] = res[j][rowPair[i].second];
				res[j][rowPair[i].second] = temp[j];
			}
		}
	}

	//define corner elements pair
	vector<pair<int,int> > elem;
	elem.push_back(make_pair(0,0));
	elem.push_back(make_pair(0,3));
	elem.push_back(make_pair(3,3));
	elem.push_back(make_pair(3,0));

	//swap corner elem
	for(int i=0; i<elem.size(); i++){
		if(internalKey[count++]){ // swap
			bool temp = res[elem[i].first][elem[i].second];
			res[elem[i].first][elem[i].second] = res[elem[(i+1)%4].first][elem[(i+1)%4].second];
			res[elem[(i+1)%4].first][elem[(i+1)%4].second] = temp;
		}
	}

	bitset<16>x;
	for(int i=0; i<16; i++){
		x[i] = res[3-i/4][3-i%4];
	}

	return x;
}

bitset<16> roundFunction(bitset<16> ri, vector<bool> internalKey, bitset<4> sBox[4][4] ){
	bitset<16> res;

	// xor ri dengan kunci internal
	for(int i=0;i<16;i++){
		res[i] = ri[i] ^ internalKey[15-i];		
	}
	// cout<<"sub-result xor= "<<res<<endl;

	res = doSwap(res,internalKey);

	// cout<<"sub-result doSwap= "<<res<<endl;

	// // s-box
	for(int i=0; i<4; i++){
		//copy sub-bitset
		bitset<4>temp;
		for(int k=0; k<4; k++)
			temp[k] = res[(15-i*4) - (3-k)];

		//cout<<"temp= "<<temp<<endl;;
		//get index
		bitset<2>tempRow, tempCol;
		tempRow[0] = temp[2];
		tempRow[1] = temp[3];
		tempCol[0] = temp[0];
		tempCol[1] = temp[1];

		int row = (int)(tempRow.to_ulong());
		int col = (int)(tempCol.to_ulong());
		//printf("row col= %d %d\n",row,col);
		bitset<4> x = sBox[row][col];

		//substitute
		for(int k=0; k<4; k++)
			res[(15-i*4) - (3-k)] = x[k];		
	}

	//cout<<"sub-result sbox= "<<res<<endl;

	return res;
}


vector<bitset<16> > doFeistel(bitset<16> li, bitset<16> ri, vector<bool> internalKey, bitset<4> sBox[4][4] ){
	vector<bitset<16> > res;
	bitset<16> tempRi;
	bitset<16> tempLi;

	tempLi = ri;
	tempRi = li ^ roundFunction(ri, internalKey, sBox);

	res.push_back(tempLi);
	res.push_back(tempRi);

	return res;
}

vector<bitset<16> > undoFeistel(bitset<16> li, bitset<16> ri, vector<bool> internalKey, bitset<4> sBox[4][4] ){
	vector<bitset<16> > res;
	bitset<16> tempRi;
	bitset<16> tempLi;

	tempRi = li;
	tempLi = ri ^ roundFunction(li, internalKey, sBox);

	res.push_back(tempLi);
	res.push_back(tempRi);

	return res;
}


int main(){
	
	//S-BOX
	bitset<4> sBox[4][4];

	//define s-box
	sBox[0][0] = bitset<4>(10);	
	sBox[0][1] = bitset<4>(9);	
	sBox[0][2] = bitset<4>(12);	
	sBox[0][3] = bitset<4>(1);	
	sBox[1][0] = bitset<4>(4);	
	sBox[1][1] = bitset<4>(5);	
	sBox[1][2] = bitset<4>(13);	
	sBox[1][3] = bitset<4>(6);	
	sBox[2][0] = bitset<4>(2);	
	sBox[2][1] = bitset<4>(0);	
	sBox[2][2] = bitset<4>(7);	
	sBox[2][3] = bitset<4>(11);	
	sBox[3][0] = bitset<4>(8);	
	sBox[3][1] = bitset<4>(15);	
	sBox[3][2] = bitset<4>(3);	
	sBox[3][3] = bitset<4>(14);	

	//string s = "tubeskriptografi";
	string s= "n9#56*)?|`hjn7$@";
	cout<<"Key: "<<s<<endl;
	vector<vector<bool> > res = getInternalKeys(s);
	
	//time performance
	std::clock_t start;
    double duration;

    start = std::clock();

	string message = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
	vector<vector<bitset<8> > > mainBlockMessage;
	vector<vector<bitset<8> > >  mainUpaBlockMessage;
	vector<vector<bitset<16> > > mainPermuteMessage;
	vector<vector<bitset<16> > > mainFeistel;
	vector<vector<bitset<16> > > mainReversePermuteMessage;
	vector<bitset<16> > resultFeistel;

	// getline(cin, message);

	// cout << "message : " << message << endl;
	// cout << "left shift : " << leftShift(message) << endl;
	// cout << "right shift : " << rightShift(message) << endl;
	// cout << message.length() << endl;

	mainBlockMessage = toBlockMessage(message);
	// cout<<"m block size awal "<<mainBlockMessage.size()<<endl;
	mainUpaBlockMessage = toUpaBlockMessage(mainBlockMessage);
	mainPermuteMessage = permute(mainUpaBlockMessage);
	//mainReversePermuteMessage = reversePermute(mainPermuteMessage);

	// cout<<"a "<<mainPermuteMessage.size()<<endl;
	// cout<<"b "<<mainPermuteMessage[1].size()<<endl;
	
	for(int j=0; j<mainPermuteMessage.size(); j+=2){
		for(int k=0; k<mainPermuteMessage[j].size(); k++){
			for(int i=0; i<16; i++){
				resultFeistel = doFeistel(mainPermuteMessage[j][k], mainPermuteMessage[j+1][k], res[i], sBox);			
			}
			mainFeistel.push_back(resultFeistel);
		}
	}
	
	
	mainReversePermuteMessage = reversePermute(mainFeistel);
	// cout<<"m size "<<mainReversePermuteMessage.size()<<endl;
	//convert to ascii string
	string encrypted="";
	for(int i=0; i<mainReversePermuteMessage.size(); i++){
		for(int j=0; j<mainReversePermuteMessage[i].size(); j++){
			bitset<8>temp1,temp2;
			//cout<<"bitset enc="<<mainReversePermuteMessage[i][j]<<endl;
			for(int k=0; k<8; k++)
				temp1[k] = mainReversePermuteMessage[i][j][15-(7-k)];
			for(int k=0; k<8; k++)
				temp2[k] = mainReversePermuteMessage[i][j][k];
			// cout<<"temp1 enc="<<temp1<<endl;
			// cout<<"temp2 enc="<<temp2<<endl;
			encrypted += char(temp1.to_ulong());
			// cout<<"temp1= "<<char(temp1.to_ulong());
			encrypted += char(temp2.to_ulong());
		}
	}
	// cout<<"encrypted size= "<<encrypted.size();
	cout<<"Encrypted\n"<<encrypted<<endl;

	// bitset<8>b('A');
	// cout<<char(b.to_ulong())<<endl;

	/*DECRYPTION*/

	vector<vector<bitset<8> > > mainBlockMessage2;
	vector<vector<bitset<8> > >  mainUpaBlockMessage2;
	vector<vector<bitset<16> > > mainPermuteMessage2;
	vector<vector<bitset<16> > > mainFeistel2;
	vector<vector<bitset<16> > > mainReversePermuteMessage2;
	vector<bitset<16> > resultFeistel2;

	// mainBlockMessage2 = toBlockMessage(encrypted);
	// cout<<"m block size "<<mainBlockMessage2.size()<<endl;
	// mainUpaBlockMessage2 = toUpaBlockMessage(mainBlockMessage2);
	mainPermuteMessage2 = permute16(mainReversePermuteMessage);
	// mainReversePermuteMessage2 = reversePermute(mainPermuteMessage2);

	for(int j=0; j<mainPermuteMessage2.size(); j+=2){
		for(int k=0; k<mainPermuteMessage2[j].size(); k++){
			for(int i=0; i<16; i++){
				resultFeistel2 = undoFeistel(mainPermuteMessage2[j][k], mainPermuteMessage2[j+1][k], res[i], sBox);			
			}
			mainFeistel2.push_back(resultFeistel2);
		}
	}

	mainReversePermuteMessage2 = reversePermute(mainFeistel2);
	// cout<<"m2 size "<<mainReversePermuteMessage2.size()<<endl;
	//convert to ascii string
	string decrypted="";
	for(int i=0; i<mainReversePermuteMessage2.size(); i++){
		for(int j=0; j<mainReversePermuteMessage2[i].size(); j++){
			bitset<8>temp1,temp2;
			for(int k=0; k<8; k++)
				temp1[k] = mainReversePermuteMessage2[i][j][15-(7-k)];
			for(int k=0; k<8; k++)
				temp2[k] = mainReversePermuteMessage2[i][j][k];
			decrypted += char(temp1.to_ulong());
			decrypted += char(temp2.to_ulong());
		}
	}
	// cout<<"decrypted size= "<<decrypted.size();
	cout<<"Decrypted\n"<<decrypted<<endl;

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"Time elapsed: "<< duration <<'\n';


	return 0;
}
