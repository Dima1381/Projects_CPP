#include <iostream>
#include <unordered_map>
#include "Hash.h"


namespace hash
{

	class AutoTest
	{
	 private:
		 int NumberOfHash;
		 string GenerationString();
		 char receivingExistCodes(int);

	 public:
		 AutoTest(int count) : NumberOfHash(count) {};
		 void StatrHasing(int LenHash);

	};

	string AutoTest::GenerationString()
	{
		string str;
		string symbols = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

		int lenString = rand() % 25 + 5;

		for (int i = 0; i < lenString; i++)
		{
			str += receivingExistCodes(symbols[rand() % symbols.size() + 0]);
		}

		return str;
	}
	char AutoTest::receivingExistCodes(int x)
	{
		x += 122;

		while (!((x >= 48 && x <=57) || (x >= 65 && x <= 90) || (x >= 97 && x <= 122)))
		{
			if (x < 48) x += rand() % 22 + 1;
			else if (x > 122) x -= rand() % 122 + 1;

			else
				x -= 32;
		}
		return x;
	
	}
	void AutoTest::StatrHasing(int LenHash)
	{
		unordered_map<string, string> maphash;
		unordered_map<string, string>::iterator it = maphash.begin();

		string temp_str;
		string temp_hash;

		Hash hash;

		int col = 0;
		for (int i = 0; i < NumberOfHash; i++)
		{
			temp_str = GenerationString();
			temp_hash = hash.GetHash(temp_str, LenHash);

			
			it = maphash.find(temp_hash);

			if (it != maphash.end())
			{
				if (it->second != temp_str)
				{
					cout << "Colision '" << temp_str<< "' and '" << it->second << "' = " << it->first << endl;
					col++;
				}
			}

			maphash.insert({temp_hash, temp_str});
		}


		cout << "Col = " << col;
		maphash.clear();
	}
}


