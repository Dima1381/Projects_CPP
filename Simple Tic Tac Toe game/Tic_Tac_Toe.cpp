#include <iostream>
using namespace std;

char Matrix[3][3]{ '1','2','3','4','5','6','7','8','9' };
char Player = 'X';
short Step; // number of players moves

void Draw()
{
	system("cls");
	cout << "Tic Tac Toe game ^) " << endl;

	for (int i = 0; i < 3; i++)
	{
		cout << "-------------" << endl;
		cout << "| ";
		for (int j = 0; j < 3; j++)
		{
			cout << Matrix[i][j] << " | ";
		}
		cout << endl;
	}
	cout << "-------------" << endl;
}

void Input()
{
	int a;

	while (1)
	{
		cout << "\nIt's " << Player << " turn. Press the number of the field: ";
		cin >> a;

		if (a == 1 && Matrix[0][0] == '1')
		{
			Matrix[0][0] = Player;
			break;
		}
		else if (a == 2 && Matrix[0][1] == '2')
		{
			Matrix[0][1] = Player;
			break;
		}
		else if (a == 3 && Matrix[0][2] == '3')
		{
			Matrix[0][2] = Player;
			break;
		}
		else if (a == 4 && Matrix[1][0] == '4')
		{
			Matrix[1][0] = Player;
			break;
		}
		else if (a == 5 && Matrix[1][1] == '5')
		{
			Matrix[1][1] = Player;
			break;
		}
		else if (a == 6 && Matrix[1][2] == '6')
		{
			Matrix[1][2] = Player;
			break;
		}
		else if (a == 7 && Matrix[2][0] == '7')
		{
			Matrix[2][0] = Player;
			break;
		}
		else if (a == 8 && Matrix[2][1] == '8')
		{
			Matrix[2][1] = Player;
			break;
		}
		else if (a == 9 && Matrix[2][2] == '9')
		{
			Matrix[2][2] = Player;
			break;
		}
		else
			cout << "Field is already in use try again!" << endl;
	}
}

void TogglePlayer()
{
	if (Player == 'X')
		Player = 'O';
	else
		Player = 'X';
}

char CheckWin()
{
	// check rows
	for (int i = 0; i < 3; i++)
	{
		if ((Matrix[i][0] == Matrix[i][1]) && (Matrix[i][1] == Matrix[i][2]))
			return Matrix[i][0];
	}

	// cheak cols
	for (int i = 0; i < 3; i++)
	{
		if ((Matrix[0][i] == Matrix[1][i]) && (Matrix[1][i] == Matrix[2][i]))
			return Matrix[0][i];
	}

	// 1st diagonal
	if ((Matrix[0][0] == Matrix[1][1]) && (Matrix[1][1] == Matrix[2][2]))
			return Matrix[0][0];

	// 2nd diagonal
	if ((Matrix[0][2] == Matrix[1][1]) && (Matrix[1][1] == Matrix[2][0]))
		return Matrix[1][1];

	return '/';
}

int main()
{
	Step = 0;
	Draw();

	while (1)
	{
		Step++;

		Input();
		Draw();
		if (CheckWin() == 'X')
		{
			cout << "\nX - win" << endl;
			break;
		}
		else if (CheckWin() == 'O')
		{
			cout << "\n0 - win" << endl;
			break;
		}
		else if (CheckWin() == '/' && Step == 9)
		{
			cout << "It's a Draw" << endl;
			break;
		}
		TogglePlayer();
			
	}
}
