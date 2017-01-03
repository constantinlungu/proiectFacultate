#include <iostream>
#include <windows.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>

#define NUMBER_OF_CARDS 52

using namespace std;

struct deck
{
	int number;
	char suit;
}cards[NUMBER_OF_CARDS];

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int goBack;

void gameMenu(char username[50], long long int playerMoney)
{
	cout << username << " has " << playerMoney<<"$";
}

void logarePassword(char username[50], int index)
{
	system("cls");

	ifstream pass("password.txt");
	ifstream money("money.txt");

	char password[50], currentPassword[50];
	long long int playerMoney;

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n\t\t\t\t\t\t       BLACK JACK \n\n\n";

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username: " << username << "\n";
	
	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
	cout << "Password: ";
	
	cin.get();
	cin.get(password, 50);

	//cout << password;

	if (strcmp(password, "0") == 0)
		goBack = 1;
	else
	{

		for (int i = 1; i <= index; i++)
			pass.getline(currentPassword, 50);


		if (strcmp(password, currentPassword) == 0)
		{
			for (int i = 1; i <= index; i++)
				money >> playerMoney;

			pass.close();
			money.close();

			gameMenu(username, playerMoney);
		}
		else
		{

			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nParola incorecta, va rugam sa incercati din nou !\n\n";

			system("pause");

			logarePassword(username, index);
		}
	}

}

void logareUsername()
{
	system("cls");

	ifstream name("username.txt");

	char username[50], currentName[50];
	int ok = 0, index = 0;

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n\t\t\t\t\t\t       BLACK JACK \n\n\n";

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";
		
	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username: ";
	cin >> username;

	if (strcmp(username, "0") == 0)
		goBack = 1;
	else
	{
		while (!name.eof())
		{
			index++;
			name >> currentName;
			if (_stricmp(username, currentName) == 0)
			{
				ok = 1;
				break;
			}

		}

		if (ok)
		{
			name.close();
			strcpy_s(username, currentName);
			logarePassword(username, index);
		}

		else
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nUsername inexistent, va rugam sa incercati din nou !\n\n";

			system("pause");

			logareUsername();
		}
	}
}

void inregistrare()
{

}

void menu()
{
	char option[20];

	do
	{
		system("cls");
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\n\t\t\t\t\t\t       BLACK JACK \n\n\n";
		cout << "1. Logare \n";
		cout << "2. Inregistrare \n";
		cout << "3. Iesire \n\n";
		cout << "Tastati 1 pentru a va loga sau 2 pentru a va inregistra: ";

		cin >> option;
	} while (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0);

	if (strcmp(option, "1") == 0)
		logareUsername();

	else
		if (strcmp(option, "2") == 0)
			inregistrare();
		else
			exit(0);

}


void createDeckOfCrads(deck cards[NUMBER_OF_CARDS])
{
	int i = 0, numberOfCard = 2;
	
	while (i < 13)
	{
		cards[i].suit = 'C';
		cards[i].number = numberOfCard;
		i++;
		numberOfCard++;
	}

	numberOfCard = 2;

	while (i < 26)
	{
		cards[i].suit = 'D';
		cards[i].number = numberOfCard;
		i++;
		numberOfCard++;
	}

	numberOfCard = 2;

	while (i < 39)
	{
		cards[i].suit = 'H';
		cards[i].number = numberOfCard;
		i++;
		numberOfCard++;
	}

	numberOfCard = 2;

	while (i < 52)
	{
		cards[i].suit = 'S';
		cards[i].number = numberOfCard;
		i++;
		numberOfCard++;
	}
}

void shuffleCards(deck cards[NUMBER_OF_CARDS])
{
	srand(time(0));

	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		int r = rand() % NUMBER_OF_CARDS;
		deck aux = cards[i];
		cards[i] = cards[r];
		cards[r] = aux;
	}

	/*for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		if (cards[i].number == 11)
			cout << "J" << cards[i].suit<<" ";
		else
			if (cards[i].number == 12)
				cout << "Q" << cards[i].suit << " ";
			else
				if (cards[i].number == 13)
					cout << "K" << cards[i].suit << " ";
				else
					if (cards[i].number == 14)
						cout << "A" << cards[i].suit << " ";
					else
							cout << cards[i].number << cards[i].suit << " ";
	}*/
}

int main()
{
	
	createDeckOfCrads(cards);
	shuffleCards(cards);
	
	do
	{
		goBack = 0;
		menu();
	} while (goBack);

	getchar();
	getchar();
}