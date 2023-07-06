#include "Interface.h"
using namespace std;



int main()
{
	setlocale(LC_ALL, "Ukr");
	Authentication a;
	a.Welcome();
	a.AuthenticationMenu();


	return 0;

}