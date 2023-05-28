#include <iostream>
#include <iomanip> 
#include <map>
#include "Hash.h"


namespace hash
{

	class AutoTest
	{
	 private:
		 int NumberOfHash; // 
		 string GenerationString(); // generation string len (5 - 25)
		 char receivingExistCodes(int); // Reduce a number to a real character in an ASCII table
		 void PrintCollision(short, const string &str1, const string &str2, const string &hash); // print collisions on the screen
	 public:
		 bool Display; // Off/On, print collisions on the screen
		 AutoTest(int count) : NumberOfHash(count), Display(true) {};
		 void StatrHasing(int LenHash);

	};

	string AutoTest::GenerationString()
	{
		string str;
		string symbols = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
		int CountSymbols = 62;
		int lenString = 5 + rand() % (25 - 5);

		for (int i = 0; i < lenString; i++)
		{
			str += receivingExistCodes(symbols[rand() % CountSymbols + 0]);
		}

		return str;
	}

	char AutoTest::receivingExistCodes(int x)
	{
		x += 50 + rand() % (122 - 50);

		while (!((x >= 48 && x <=57) || (x >= 65 && x <= 90) || (x >= 97 && x <= 122)))
		{
			if (x < 48) x += rand() % 25 + 5;
			else if (x > 122) x -= rand() % 122 + 10;

			else
				x -= 32;
		}
		return x;
	
	}

	void AutoTest::PrintCollision(short number, const string &str1, const string &str2, const string &hash)
	{
		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << "|" << setw(8) << number << " | " << setw(25) << str1 << " | " << setw(25) << str2 << " | " << setw(15) << hash << " |" << endl;
	}


	void AutoTest::StatrHasing(int LenHash)
	{
		if (LenHash <= 64 && LenHash >= 4)
		{
			multimap<string, string> maphash;
			multimap<string, string>::iterator it = maphash.begin();

			Hash hash;

			int NumberCollisions = 0;

			if (Display)
				cout << "Collision | " << setw(25) << "First string" << " | " << setw(25) << " Second string" << " | " << setw(10) << "Hash" << endl;

			for (int i = 0; i < NumberOfHash; i++)
			{
				string temp_str = GenerationString(); // random string generation, length 5-25
				string temp_hash = hash.GetHash(temp_str, LenHash); // generating hash from new string

				it = maphash.find(temp_hash);

				if (it != maphash.end())
				{
					auto it1 = maphash.lower_bound(temp_hash);
					auto it2 = maphash.upper_bound(temp_hash);

					while (it1 != it2) // traverse through all collisions for a given hashes
					{
						if (it1->first == temp_hash &&  it1->second != temp_str) // if strings with the same hash are not the same 
						{
							NumberCollisions++;

							if (Display) // Displaying a collision on the screen 
								PrintCollision(NumberCollisions, temp_str, it->second, it->first);
						}
						it1++;
					}
				}

				maphash.insert({ temp_hash, temp_str });
			}

			cout << "Number collisions = " << NumberCollisions;
			maphash.clear();
		}
		else
			LenHash > 64 ? cout << "Hash length is too long" << endl : cout << "Hash length is too short" << endl;
		
	}
}


