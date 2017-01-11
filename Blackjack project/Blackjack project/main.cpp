#include <iostream>
#include <windows.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>

#define NUMBER_OF_CARDS 52
#define title "\n\t\t\t\t\t\t       BLACK JACK \n\n\n"
#define login "\n\t\t\t\t\t\t       BLACK JACK (Log in) \n\n\n"
#define signup "\n\t\t\t\t\t\t       BLACK JACK (Sign up) \n\n\n"
#define options "\n\t\t\t\t\t\t       BLACK JACK (Options) \n\n\n"

using namespace std;

struct deck
{
	int number;
	char suit;
}cards[NUMBER_OF_CARDS];

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int goBack, index=0;
char password[50], username[50];
long long int playerMoney;

bool isOk = false;
bool goToGameMenu;

void loginPassword()
{
	if (!isOk)
	{
		isOk = true;
		getchar();
	}
	system("cls");

	ifstream pass("password.txt");
	ifstream money("money.txt");

	char currentPassword[50];

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << login;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username: " << username << "\n";
	
	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
	cout << "Password: ";
	
	//cin.get();
	cin.getline(password, 50);

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

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\n\t\t\t\t\t      V-ati logat cu succes ! \n";

			getchar();
		}
		else
		{

			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nParola incorecta, va rugam sa incercati din nou !\n\n";

			system("pause");

			loginPassword();
		}
	}

}

void loginUsername()
{
	system("cls");

	ifstream name("username.txt");

	char currentName[50];
	int ok = 0;
	index = 0;

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << login;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";
		
	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username: ";
	cin >> username;

	isOk = false;

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
			loginPassword();
		}

		else
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nUsername inexistent, va rugam sa incercati din nou !\n\n";

			system("pause");

			loginUsername();
		}
	}
}

void signupMoney()
{
	system("cls");

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << signup;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username: " << username << "\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Password : ";
	for (unsigned i = 0; i < strlen(password); i++)
		cout << "*";
	cout << "\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Suma cu care doriti sa va inregistrati: ";

	cin >> playerMoney;

	if (playerMoney == 0)
		goBack = 1;
	else
	{
		if (playerMoney < 0)
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "Suma inregistrata trebuie sa fie mai mare decat 0! \n";

			system("pause");

			signupMoney();
		}
		else
		{

			ofstream writeUsername("username.txt", ios::app);
			ofstream writePass("password.txt", ios::app);
			ofstream writeMoney("money.txt", ios::app);

			writeUsername << username << "\n";
			writePass << password << "\n";
			writeMoney << playerMoney << "\n";

			writeUsername.close();
			writePass.close();
			writeMoney.close();

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\n\t\t\t\t\t      V-ati inregistrat cu succes ! \n";

			getchar();
			getchar();

		}


	}
}

int verifyPassword(char password[50])
{
	int ok = 1;

	if (strlen(password) < 3 && strcmp(password, "0") != 0)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "Parola trebuie sa contina minim 3 caractere !\n\n";

		ok = 0;
	}

	if (ok)
		return 1;
	
	return 0;
}

void signupPassword()
{
	system("cls");

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << signup;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username: " << username << "\n";
	
	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
	cout << "Password (minim 3 caractere): ";

	cin.getline(password, 50);

	if (strcmp(password, "0") == 0)
		goBack = 1;
	else
		if (!verifyPassword(password))
		{
			cout << "\n";
			system("pause");
			signupPassword();
		}
		else
			signupMoney();
}

int verifyUsername(char username[50])
{
	ifstream readUsername("username.txt");
	char currentName[50];
	int ok = 1;
	bool okIndex = false;

	cout << "\n";

	if (!isalpha(username[0]) && strcmp(username, "0") != 0)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "Username-ul trebuie sa inceapa cu o litera !\n";
		ok = 0;
	}

	if (strlen(username) < 3 && strcmp(username, "0") != 0)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "Username-ul trebuie sa contina minim 3 caractere !\n";
		ok = 0;
	}

	if (strchr(username, ' ') != NULL)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "Username-ul nu trebuie sa contina spatii !\n";
		ok = 0;
	}

	if (index == 0)
		okIndex = true;

	while (!readUsername.eof())
	{
		readUsername >> currentName;

		if (okIndex)
			index++;

		if (_stricmp(username, currentName) == 0 && strcmp(currentName, "") != 0)
		{
			ok = 0;

			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "Acest username este deja inregistrat ! \n";

			break;
		}
	}

	readUsername.close();

	if (ok)
		return 1;

	return 0;
}

void signupUsername()
{
	index = 0;
	system("cls");

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << signup;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username (minim 3 caractere): ";

	if (!isOk)
	{
		getchar();
		isOk = true;
	}
	
	cin.getline(username, 50);
	

	if (strcmp(username, "0") == 0)
		goBack = 1;
	else
	{

		if (!verifyUsername(username))
		{
			cout << "\n";
			system("pause");
			signupUsername();
		}
		else
			signupPassword();
	}


}

void menu()
{
	char option[20];

	do
	{
		system("cls");
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << title;
		cout << "1. Log in \n";
		cout << "2. Sign up \n";
		cout << "3. Exit \n\n";
		cout << "Choose an option: ";

		cin >> option;
	} while (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0);

	if (strcmp(option, "1") == 0)
		loginUsername();

	else
		if (strcmp(option, "2") == 0)
		{
			isOk = false;
			signupUsername();
		}
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

void option1()
{
	char newUsername[50];
	bool ok;

	if (!isOk)
	{
		isOk = true;
		getchar();
	}

	do {

		ok = true;
		system("cls");

		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << options;

		cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

		cout << "New username: ";

		cin.getline(newUsername, 50);

		if (!verifyUsername(newUsername))
		{
			ok = false;
			cout << "\n";
			system("pause");
		}

	} while (!ok && strcmp(newUsername, "0") != 0);

	if (strcmp(newUsername, "0") != 0)
	{
		char currentPassword[50];

		do
		{
			cout << "\n";

			system("cls");

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << options;

			cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

			SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

			cout << "New username: " << newUsername << "\n";

			SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
			cout << "Password: ";

			cin.getline(currentPassword, 50);

			if (strcmp(currentPassword, "0") != 0)
			{
				if (strcmp(password, currentPassword) != 0)
				{
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

					cout << "\nParola incorecta ! \n\n";
					system("pause");
				}
			}
		} while (strcmp(password, currentPassword) != 0 && strcmp(currentPassword, "0") != 0);

		if (strcmp(currentPassword, "0") != 0)
		{
			ifstream readUsername("username.txt");
			ofstream writeTemp("temp.txt");

			char strTemp[50];

			while (readUsername >> strTemp)
			{

				if (strcmp(strTemp, username) == 0)
					strcpy_s(strTemp, newUsername);

				writeTemp << strTemp << "\n";
			}

			strcpy_s(username, newUsername);

			readUsername.close();
			writeTemp.close();

			remove("username.txt");
			rename("temp.txt", "username.txt");

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\n\t\t\t\t\t   Username-ul a fost schimbat cu succes ! \n";

			getchar();
		}
	}
}

void option2()
{
	char newPassword[50];
	bool ok;

	if (!isOk)
	{
		isOk = true;
		getchar();
	}

	do {

			ok = true;
			system("cls");

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << options;

			cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

			SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

			cout << "New password: ";

			cin.getline(newPassword, 50);

			if (!verifyPassword(newPassword))
			{
				ok = false;
				cout << "\n";
				system("pause");
			}

		} while (!ok && strcmp(newPassword, "0") != 0);

	if (strcmp(newPassword, "0") != 0)
	{
		char currentPassword[50];

		do
		{
			cout << "\n";

			system("cls");

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << options;

			cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

			SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

			cout << "New password: ";

			for (int i = 1; i <= strlen(newPassword); i++)
				cout << "*";

			SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
			cout << "\nOld password: ";

			cin.getline(currentPassword, 50);

			if (strcmp(currentPassword, "0") != 0)
			{
				if (strcmp(password, currentPassword) != 0)
				{
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

					cout << "\nParola incorecta ! \n\n";
					system("pause");
				}
			}

		} while (strcmp(password, currentPassword) != 0 && strcmp(currentPassword, "0") != 0);

		if (strcmp(currentPassword, "0") != 0)
		{
			ifstream readPassword("password.txt");
			ofstream writeTemp("temp.txt");

			char strTemp[50];

			int i = 0;

			while (readPassword.getline(strTemp,50))
			{
				i++;

				if (strcmp(strTemp, password) == 0 && i==index)
					strcpy_s(strTemp, newPassword);

				writeTemp << strTemp << "\n";
			}

			strcpy_s(password, newPassword);

			readPassword.close();
			writeTemp.close();

			remove("password.txt");
			rename("temp.txt", "password.txt");

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\n\t\t\t\t\t   Parola a fost schimbata cu succes ! \n";

			getchar();
		}
	}
}

void option3()
{
	long long int newMoney;
	bool ok;
	char currentPassword[50];

	do
	{
		system("cls");

		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << options;

		cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

		cout << "How much money do you want to add in account ?: ";

		cin >> newMoney;

		if (newMoney < 0)
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "\nSuma trebuie sa fie mai mare decat 0 ! \n\n";
			system("pause");
		}

	} while (newMoney < 0 && newMoney != 0);

	if (newMoney != 0)
	{
		if (!isOk)
		{
			isOk = true;
			getchar();
		}

		do {

			system("cls");

			ok = true;

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << options;

			cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

			SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

			cout << "How much money do you want to add in account ?: " << newMoney << "\n";

			cout << "Confirm password: ";

			cin.getline(currentPassword, 50);

			if (strcmp(currentPassword, "0") != 0)
			{
				if (strcmp(password, currentPassword) != 0)
				{
					ok = false;
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

					cout << "\nParola incorecta ! \n\n";
					system("pause");
				}
			}

		} while (!ok && strcmp(currentPassword, "0") != 0);

		if (strcmp(currentPassword, "0") != 0)
		{

			ifstream readMoney("money.txt");
			ofstream writeTemp("temp.txt");

			long long int temp;

			int i = 0;

			while (readMoney >> temp)
			{
				i++;

				if (temp == playerMoney && i == index)
					temp = temp + newMoney;

				writeTemp << temp << "\n";
			}

			playerMoney = playerMoney + newMoney;

			readMoney.close();
			writeTemp.close();

			remove("money.txt");
			rename("temp.txt", "money.txt");

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\n\t\t\t\t\t   Banii au fost adaugati cu succes ! \n";

			getchar();
		}
	}

}

void optionMenu()
{
	char option[20];

	do {
		system("cls");

		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

		cout << "Player: " << username << "\n";
		cout << "Money: " << playerMoney << "$";

		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << options;
		cout << "1. Change username \n";
		cout << "2. Change password \n";
		cout << "3. Add money \n";
		cout << "4. Log in to another account \\ Log out \n";
		cout << "5. Back \n\n";
		cout << "Choose an option: ";

		cin >> option;

		isOk = false;

	} while (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0 && strcmp(option, "4") != 0 && strcmp(option, "5") != 0);

	if (strcmp(option, "1") == 0)
	{
		option1();
		optionMenu();
	}
	else
		if (strcmp(option, "2") == 0)
		{
			option2();
			optionMenu();
		}
		else
			if (strcmp(option, "3") == 0)
			{
				option3();
				optionMenu();
			}
			else
				if (strcmp(option, "4") == 0)
					goBack = 1;
				else
					goToGameMenu = true;

}

void optionGame()
{
	char option[20];

	do
	{
		system("cls");

		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

		cout << "Player: " << username << "\n";
		cout << "Money: " << playerMoney << "$";

		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << title;
		cout << "1. Single player \n";
		cout << "2. Two players \n";
		cout << "3. Back \n\n";
		cout << "Choose an option: ";

		cin >> option;
	} while (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0);

	if (strcmp(option, "1") == 0)
	{

	}
	else
		if (strcmp(option, "2") == 0)
		{

		}
		else
			goToGameMenu = true;

}

void gameMenu()
{

	char option[20];
	goToGameMenu = false;

	do {
		system("cls");

		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

		cout << "Player: " << username << "\n";
		cout << "Money: " << playerMoney << "$";

		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << title;
		cout << "1. Play \n";
		cout << "2. Options \n";
		cout << "3. Exit \n\n";
		cout << "Choose an option: ";

		cin >> option;

	} while (strcmp(option, "1") != 0 && strcmp(option, "2") != 0 && strcmp(option, "3") != 0);

	if (strcmp(option, "1") == 0)
	{
		optionGame();

		if (goToGameMenu)
			gameMenu();
	}
	else
		if (strcmp(option, "2") == 0)
		{
			optionMenu();

			if (goToGameMenu)
				gameMenu();
		}
		else
			exit(0);


}

int main()
{
	
	createDeckOfCrads(cards);
	shuffleCards(cards);
	
	Back:
	do
	{
		goBack = 0;
		menu();
	} while (goBack);

	goBack = 0;
	gameMenu();

	if (goBack)
		goto Back;

	getchar();

}
