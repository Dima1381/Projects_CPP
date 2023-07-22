#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Player
{
	Player()
	{
		Banner();

		cout << "\nEnter Player Name: ";
		getline(cin, Name);

		cout << "\nDeposit Your Amount: $";
		cin >> Amount;
	}

	void Set_Name(const string& name) { this->Name = name; }
	void Set_Money(const int& money) { this->Amount = money; }

	string Get_Name() { return Name; }
	double Get_Amount() { return Amount; }

	void Banner()
	{
		cout << "\n===============================================================================================";
		cout << "\n               CCCCC      A        SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO     ";
		cout << "\n             CC          A  A      SS             III     NN N   NN   OO      OO    ";
		cout << "\n            CC          A    A     SSSSSSSSS      III     NN  N  NN   OO      OO    ";
		cout << "\n             CC        AAAAAAAA           SS      III     NN   N NN   OO      OO    ";
		cout << "\n               CCCCC  A        A   SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO     ";
		cout << "\n===============================================================================================\n";
	}

private:
	string Name;
	double Amount;
};

void Rules()
{
	system("cls");
	cout << "\n===============================================================================================\n";
	cout << "\t\t\tGame Rules";
	cout << "\n===============================================================================================";
	cout << "\n1. Choose Number Between 1 To 10";
	cout << "\n2. Winning Amount Will Be 10 Times Of Bid Amount";
	cout << "\n3. Loose Amount Will Be Biding Amount";
	cout << "\n4. You Can Leave A Game Any Time";
	cout << "\n===============================================================================================\n";
}

bool Game(Player& player)
{
	int bidamnt; // Bid Amount
	int guess; // The number specified by the player (1-10)
	int dice; // The winning number
	char choice;

	Rules();

	do {
		cout << "\nWelcome " << player.Get_Name() << " Are You Ready To Play? " << "\n\n";
		cout << "Enter Bid Amount: $";
		cin >> bidamnt;
		if (bidamnt > player.Get_Amount())
			cout << "You Can not Bid More Than Current Amount\n" << 
			"\nRe-enter Amount: ";
	} while (bidamnt > player.Get_Amount());

	do {
		cout << "Guess The Number Between 1 To 10 :";
		cin >> guess;
		if (guess <= 0 || guess > 10)
			cout << "\nNumber Sholud Be Between 1 To 10\n" <<
			"\nGuess Numer Again: ";
	} while (guess <= 0 || guess > 10);

	dice = rand() % 10 + 1;

	if (dice == guess)
	{
		cout << "\nHurray You Won " << bidamnt * 10 << "$";
		player.Set_Money(player.Get_Amount() + bidamnt * 10);
	}
	else
	{
		cout << "Sorry You Lose " << bidamnt << "$\n";
		player.Set_Money(player.Get_Amount() - bidamnt);
	}

	cout << "\nThe Winning Number Was: " << dice << "\n";
	cout << "\n" << player.Get_Name() << ", Your Remaining Amount Is " << player.Get_Amount() << "$\n";
	if (player.Get_Amount() == 0)
	{
		cout << "\nSorry You Don't Have Money To Play \n";
		return false; // continuation of the game is impossible
	}

	cout << "\nYou Want To Play Again Press (y/n)? ";
	cin >> choice;

	if (toupper(choice) == 'Y') 
		return true;
	
	else 
		return false;
	
}


int main()
{
	srand(time(0));

	Player player;

	while (Game(player)) {}

	cout << "\n===============================================================================================\n";
	cout << "Thanks For Playing Game Again Your Current Amount Is " << player.Get_Amount() << "$";
	cout << "\n===============================================================================================\n";
	return 0;
}

