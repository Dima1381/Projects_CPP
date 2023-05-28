#include <iostream>
#include <string>
#include "AutoTest.h"

using namespace hash;

int main()
{
    srand(time(NULL));

    AutoTest atest(500000); // Number of generated strings
    atest.Display = false;
    atest.StatrHasing(26); // Length of the hash

    return 0;
}

// 1 000(4) = 0.1%
// 10 000(4) = 0.05%
// 100 000(5) = 0.01%

//1 000 000(6) = 0.002%