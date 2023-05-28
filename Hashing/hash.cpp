#include <iostream>
#include <string>
#include "AutoTest.h"

using namespace hash;

int main()
{
    srand(time(NULL));

    AutoTest atest(100000); // Number of generated strings
    atest.Display = false; // print collisions on the screen true/false
    atest.StatrHasing(5); // Length of the hash

    return 0;
}