Here I use string hashing, strings can be any information, for example passwords.
The information is represented as a string from 5-25 characters long, and contains both numbers and upper/lowercase letters.
Hash length 4-64 characters (32-512 bits)

The results of this hashing algorithm are:

      N     |  H  |      C    
-------------------------------
    5 000   |  4  |   0.06% (≈ 3)
   10 000   |  4  |    0.1% (≈ 10)
  100 000   |  5  |  0.017% (≈ 17)
1 000 000   |  6  | 0.0025% (≈ 25)

Where:
N - Number of input data (strings)
H - Length hash
C - collision probability (≈ approximate number of collisions)

Some concepts:
Salt — is a random string that is generated based on the input string and added to the hash (in my case to the end of the hash)
The checksum (control sum)(for this algorithm) is the sum of the ASCII table codes of all characters of the line.

There are 3 files here : hash.cpp (main), AutoTest.h and Hash.h

hash.h :
Contains:
 - int gelControlSum(string) - is a string checksum function.
 - char receivingExistCodes(int) - function that takes a number and converts it to a valid character in the ASCII table, which lies in the range: 0-1 or a-z or A-Z.
 - string GetHash(string userString, short lenHash) - the main function that generates a hash code takes as input a string (from which we will generate a hash) and the length of the hash that we want to receive.
 
AutoTest.h
Since testing a large number of hashes manually is not optimal, especially when dealing with millions of inputs)
So to automate the testing, the AutoTest class was created.
Contains:
 - string GenerationString() - a simple function that generates a random string 5-25 characters long.
 - char receivingExistCodes(int) - the function, which is also present in hash.h, takes a number and converts it to a valid character in the ASCII table, which is in the range: 0-1 or a-z or A-Z.
 - PrintCollision - function to display collisions on the screen so the user can look at the data and the hash code.
 - bool Display - indicates whether the PrintCollision function will be called, the value is set by the user directly in the main function)
 - void StatrHasing(int LenHash) - the main function that is responsible for the self-test. The basis of which is a multimap for hashing storage.




