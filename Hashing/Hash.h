
using namespace std;

namespace hash
{

	class Hash
	{
	private:
		string hash;

		int gelControlSum(string userString); // Sum of all characters in string, in ASCII table code 
		char receivingExistCodes(int); // // Reduce a number to a real character in an ASCII table

	public:
		
		string GetHash(string userString, short lenHash)
		{
			if (lenHash > 3)
			{
				this->hash.clear();

				// minimum hash length 2^n
				unsigned int minLenHash = 2;
				// a hash length that is close to the desired length
				unsigned int realMinHash = 0;

				// Sault original string
				unsigned int originalSault = gelControlSum(userString);
				unsigned int originalLenStr = userString.size();

				// get string lengths 2^n closer to the given hash length
				while (minLenHash <= lenHash)
					realMinHash = (minLenHash *= 2);
				
				// we get closer to the length of the given line - 2^n
				// example : if original string lengths = 20, lengths hash will be = 32 (2^n)
				// length of the hash must be longer than the original string
				while (minLenHash <= originalLenStr)
					minLenHash *= 2;

				// number of symbols that must be added to the hash length
				int addCount = minLenHash - originalLenStr;

				// adding
				for (int i = 0; i < addCount; i++)
				{
					userString += receivingExistCodes(userString[i] + userString[i + 1]);
				}

				// Maximum hash length sault
				int maxlenHashSault = gelControlSum(userString);
				int maxLenStr = userString.size();

				// hash compressions : userString.size / 2, until userString.size != realMinHash
				while (userString.size() != realMinHash)
				{
					int center = userString.size() / 2;

					for (int i = 0; i < center; i++)
					{
						this->hash += receivingExistCodes(userString[center - i] + userString[center + i]);
					}

					userString = this->hash;
					this->hash.clear();
				}

				int rem = realMinHash - lenHash;
				int countCompress = realMinHash / rem;

				// build a new hash from the previous hash, his new length = actual required length - 4 ( (-4) - because we will add 4 saults to the hash)
				for (int i = 0; hash.size() < (lenHash - 4); i++)
				{
					if (i % countCompress == 0)
						hash += receivingExistCodes(userString[i] + userString[++i]);
					else
						hash += userString[i];
				}

				// adding saults
				hash += receivingExistCodes(originalSault);
				hash += receivingExistCodes(originalLenStr);

				hash += receivingExistCodes(maxlenHashSault);
				hash += receivingExistCodes(maxLenStr);

				return hash;
			}
			return "";
		}

	};

	int Hash::gelControlSum(string userString)
	{
		int sault = 0, lenUserStr = userString.length();

		for (int i = 0; i < lenUserStr; i++)
		{
			sault += (int)userString[i];
		}
		return sault;
	}

	char Hash::receivingExistCodes(int x)
	{
	    x += rand() % 122 + 50;

		while (!((x >= 48 && x <=57) || (x >= 65 && x <= 90) || (x >= 97 && x <= 122)))
		{
			if (x < 48) x += rand() % 22 + 1;
			else if (x > 122) x -= rand() % 122 + 1;

			else
				x -= 10;
		}
		return x;
	}

}