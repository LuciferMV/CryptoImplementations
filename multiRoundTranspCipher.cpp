// writing Transposition Cipher in a modular and flexible way
/*
It provides flexibility to user have as many rounds of transposition, as he/she/it wants...

*/
#include <bits/stdc++.h>
#include <ctime>
#include <cstring>

using namespace std;

string encryptAndPopulateKeys(string msg, int totalRounds, vector<int> &keysSzAr, vector<vector<int> > &allKeys);
string decryptAlgo(string cipher,int totalRounds, vector<int> &keysSzAr, vector<vector<int> > &allKeys);
string encryptTransposition(string plainText,int szKey,vector<int> &key);
string decryptTranspose(string cipherText, int szKey, vector<int> &key);

int valRand = 14;
int selRand = 11;
int zelRand = 23;

int main()
{
	string msg;
	cout<<"Enter your message :"<<endl;
	getline(cin,msg);
	while(msg.length() == 0)
	{
		cout<<"Don't enter empty string"<<endl;
		cout<<"Enter your message :"<<endl;
		getline(cin,msg);
	}
	int totalRounds;
	cout<<"Enter the number of Rounds (greater than 0) of Transposition"<<endl;
	cin>>totalRounds;
	while(totalRounds <= 0)
	{
		cout<<"Number of rounds should be greater than 0"<<endl;
		cin>>totalRounds;
	}
	vector<int> keysSzAr(totalRounds);
	vector<vector<int> > allKeys(totalRounds);

	cout<<"************ ENCRYPTION BEGINS *********"<<endl<<endl;
	string finalCipherText = encryptAndPopulateKeys(msg,totalRounds,keysSzAr,allKeys);
	cout<<"So,the final Cipher Text is :"<<endl;
	cout<<finalCipherText<<endl;
	cout<<endl;
	cout<<"************ DECRYPTION BEGINS ***********"<<endl<<endl;
	string finalOutputPlainText = decryptAlgo(finalCipherText,totalRounds,keysSzAr,allKeys);
	cout<<"So,the final Plain Text Obtained is :"<<endl;
	cout<<finalOutputPlainText<<endl<<endl;
	cout<<"************* PROGRAM OVER **************"<<endl;
	return 0;
}

string encryptAndPopulateKeys(string msg, int totalRounds, vector<int> &keysSzAr, vector<vector<int> > &allKeys)
{
	//
	for (int i = 0; i < totalRounds; ++i)
	{
		cout<<"Encryption Round "<<(i+1)<<" :"<<endl;
		cout<<"Enter the size (greater than 0) of key in round "<<(i+1)<<" of encryption :"<<endl;
		cin>>keysSzAr[i];
		while(keysSzAr[i] <= 0)	
		{
			cout<<"The size of key should be greater than 0"<<endl;
			cout<<"Enter the size of key , again"<<endl;
			cin>>keysSzAr[i];
		}
		for(int j=0;j<keysSzAr[i];j++)
		{
			allKeys[i].push_back(0);
		}
		int errorFlag = 0;
		do
		{
			vector<int> checkList(keysSzAr[i]+1,0);
			errorFlag = 0;
			cout<<"Enter the key as some permutation of numbers from 1 to "<<keysSzAr[i]<<" ,separated by space :"<<endl;
			for(int j=0;j<keysSzAr[i];j++)
			{
				int tempK;
				cin>>tempK;
				if((tempK <=0 ) || (tempK > keysSzAr[i]))
				{
					errorFlag = 1;
					cout<<"Entered Value Out of Range"<<endl;
					cout<<"Please enter the permutation again"<<endl;
					break;
				}
				else
				{
					if(checkList[tempK]!=0)
					{
						errorFlag = 1;
						cout<<"Please Don't enter duplicate values, as it will lead to loss of data from message"<<endl;
						cout<<"Please Enter the Permuation again"<<endl;
						break;
					}
					else
					{
						checkList[tempK]=1;
						allKeys[i][j] = tempK;
					}
				}
			}
		}while(errorFlag);
		msg+="e";
		msg = encryptTransposition(msg,keysSzAr[i],allKeys[i]);
		cout<<"Encrypted Text After Round "<<(i+1)<<" is :"<<endl;
		//
		cout<<msg<<endl<<endl;
	}
	return msg;
}

string decryptAlgo(string cipher,int totalRounds, vector<int> &keysSzAr, vector<vector<int> > &allKeys)
{
	string msg = cipher;
	/*
	
	*/
	for(int i=(totalRounds-1);i >= 0; i--)
	{
		msg = decryptTranspose(msg,keysSzAr[i],allKeys[i]);
		
		int lenMsg = msg.length();
		int j = lenMsg-1;
		for(;j>=0;j--)
		{
			if(msg[j]=='e')
				break;
		}
		msg = msg.substr(0,j);
		cout<<"Decrypted Text After Round "<<(totalRounds-i)<<" is:"<<endl;
		cout<<msg<<endl;

	}
	
	return msg;
}
string encryptTransposition(string plainText,int szKey,vector<int> &key)
{
	int textSz = plainText.length();
	int numCols = szKey;
	int numRows;
	if(szKey!=0)
	{
		numRows = ceil((textSz*1.0)/numCols);
	}
	else
	{
		return plainText;
	}

	string cipherText = "";

	for(int i=0;i<szKey;i++)
	{
		int presCol = (key[i]-1);
		int txtPointer = presCol;

		for(int j=0;j<numRows;j++)
		{
			if(txtPointer < textSz)
			{

				cipherText.push_back(plainText[txtPointer]);
			}
			else
			{
				char paddChar;
				do
				{
					srand(time(NULL)+valRand);
					valRand = valRand*zelRand + selRand;
					zelRand = zelRand*selRand;
					selRand++;
					paddChar = (char)(97+(((rand() % 26)+26)%26));
				}while(paddChar=='e');
				cipherText.push_back(paddChar);
			}
			txtPointer+=numCols;
		}
	}
	return cipherText;
}
string decryptTranspose(string cipherText, int szKey, vector<int> &key)
{
	int textSz = cipherText.length();
	if(szKey == 0)
	{
		return cipherText;
	}

	vector<int> decryptionKey(szKey);
	for(int i=0;i<szKey;i++)
	{
		decryptionKey[key[i]-1] = (i+1);
	}
	string plainText = "";
	int numCols = szKey;
	int numRows = floor((textSz*1.0)/numCols);

	for(int i=0; i < numRows; i++)
	{
		for(int j=0;j<numCols;j++)
		{
			int presCol = ( decryptionKey[j] - 1 );
			int txtPointer = presCol*numRows + i;
			if(txtPointer < textSz)
			{
				plainText.push_back(cipherText[txtPointer]);
			}
			else
			{
				char paddChar;
				do
				{
					srand(time(NULL)+valRand);
					valRand = valRand*zelRand + selRand;
					zelRand = zelRand*selRand;
					selRand++;
					paddChar = (char)(97+(((rand() % 26)+26)%26));
				}while(paddChar=='e');
				cipherText.push_back(paddChar);
			}
		}
	}
	return plainText;
}
