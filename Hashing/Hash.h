
using namespace std;

namespace hash
{

	class Hash
	{
	private:
		string hash;

		int gelControlSum(string userString);
		char receivingExistCodes(int);

	public:
		
		string GetHash(string userString, short lenHash)
		{
			if (lenHash > 3)
			{
				this->hash.clear();


				// мінімальна довжина хешу 2^n
				unsigned int minLenHash = 2;
				// довжина хешу, яка приближена до потрібної довжини
				unsigned int realMinHash = 0;

				// соль оригінального рядка
				unsigned int originalSault = gelControlSum(userString);
				unsigned int originalLenStr = userString.size();

				// отримання довжини рядка, 2^n ближчий до заданій довжині хешу
				while (minLenHash <= lenHash)
				{
					realMinHash = (minLenHash *= 2);
				}

				// отримуємо ближчу до довжини заданого рядка - 2^n
				while (minLenHash <= originalLenStr)
				{
					minLenHash *= 2;
				}

				// довжина хешу ма були, як мінімум в 2 рази більшої за оригінальний рядок
				if ((minLenHash - originalLenStr) < minLenHash) minLenHash * 2;

				// кількість симфолів які необхідно додати до довжини хешу
				int addCount = minLenHash - originalLenStr;

				// додавання 
				for (int i = 0; i < addCount; i++)
				{
					userString += receivingExistCodes(userString[i] + userString[i + 1]);
				}

				int maxlenHashSault = gelControlSum(userString);
				int maxLenStr = userString.size();

				// зжатие хеша

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

				for (int i = 0; hash.size() < (lenHash - 4); i++)
				{
					if (i % countCompress == 0)
						hash += receivingExistCodes(userString[i] + userString[++i]);
					else
						hash += userString[i];
				}

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
		// 48-57   65 - 90   97-122
		x += 122;

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