#include "keyGenerator.h"

using namespace std;

// convert string to vector bitset
vector<bitset<8> > toBitset(string s){
	vector<bitset<8> > bsVec;
	for (std::size_t i = 0; i < s.size(); ++i){
      	bsVec.push_back(bitset<8>(s.c_str()[i]));
  	    cout<<"bitset= "<<bsVec[i]<<endl;
    }
    
  	return bsVec;
}


// put bitset to matrix
vector<vector<vector<bool> > > putBsMat(vector<bitset<8> > bsVec){

  	vector<vector<vector<bool> > > M;
    for(int i=0; i<8; i++){
      vector<vector<bool> > temp1;
      M.push_back(temp1);
      for(int j=0; j<4; j++){
        vector<bool> temp2;
        M[i].push_back(temp2);
        for(int k=0; k<4; k++){
          bool temp3;
          M[i][j].push_back(temp3);
        }
      }
    }

  	for(int i=0; i<8; i++){
  		cout<<"Mat "<<i<<endl;
      for(int j=0; j<16; j++){
  			M[i][j/4][j%4] = bsVec[j][7-i];
        cout<<M[i][j/4][j%4];
        if(!((j+1)%4))
          cout<<endl;
  		}
  	}
    //printf("putbsmat");
  	return M;
}

vector<bool> doXOR(vector<vector<bool> > M){
	vector<bool> res;
	int i,j;
  //int count = 0;
	//do XOR rows
	for(i=0; i<4; i++){
		bool temp = M[i][0];
    
		for(int j=1; j<4; j++)
			temp ^= M[i][j];
    
		res.push_back(temp);
	}

  //do XOR column
  for(j=0; j<4; j++){
    bool temp = M[0][j];
    for(int i=1; i<4; i++)
      temp ^= M[i][j];
    res.push_back(temp);
  }
  
  //printf("res size=%d", res.size());
  return res;
}

vector<vector<bool> > doRound(vector<vector<bool> > M){
  vector<vector<bool> > res = M;

  //printf("a1\n");
  bool temp = res[1][0];
  res[1][0] = res[2][0];
  res[2][0] = res[3][0];
  res[3][0] = res[3][1];
  res[3][1] = res[3][2];
  res[3][2] = res[3][3];
  res[3][3] = res[2][3];
  res[2][3] = res[1][3];
  res[1][3] = res[0][3];
  res[0][3] = res[0][2];
  res[0][2] = res[0][1];
  res[0][1] = res[0][0];
  res[0][0] = temp;

  return res;
}

// return 16 internal keys in binary string format
vector<vector<bool> > getInternalKeys(string key){

	// convert key to binary string, 16 pieces (STEP 1)
	vector<bitset<8> > bsVec = toBitset(key);

	// put bits to matrix (STEP 2)
	vector<vector<vector<bool> > > M = putBsMat(bsVec);


  /*KEY GENERATION*/
  vector<vector<bool> > intKeys;

  for(int i=0; i<8; i++){
    printf("Mat %d\n",i);
    printMat(M[i]);

  	for(int j=0; j<2; j++){
      //do XOR (STEP 3)
    	vector<bool> subkey1 = doXOR(M[i]);
      printf("subkey1= ");
      print(subkey1);
      // do round (STEP 4)
      M[i] = doRound(M[i]);

      //(STEP 5)    
      vector<bool> subkey2 = doXOR(M[i]);
      printf("subkey2= ");
      print(subkey2);

      vector<bool>key;
      key.insert(key.end(), subkey1.begin(), subkey1.end());
      key.insert(key.end(), subkey2.begin(), subkey2.end());

      printf("key= ");
      print(key);
      
      intKeys.push_back(key);

      M[i] = doRound(M[i]);
    }
	}

	return intKeys;
}

void print(vector<bool> v){
  for(int i=0; i<v.size(); i++)
    cout<<v[i];
  cout<<endl;
}

void printMat(vector<vector<bool> > M){
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++)
      cout<<M[i][j];
    cout<<endl;
  }
}