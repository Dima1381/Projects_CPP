#include <iostream>
#include <string>
#include "AutoTest.h"

using namespace hash;

int main()
{
    srand(time(NULL));

    AutoTest atest(15000); // 
    
    atest.StatrHasing(5);

    return 0;
}

