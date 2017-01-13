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
	char design[10][10];

}cards[NUMBER_OF_CARDS];

deck cardsPlayer1[50], cardsPlayer2[50], cardsDealer[50];
int numberCardsPlayer1, numberCardsPlayer2, numberCardsDealer;
char heartCard[10][10], diamondCard[10][10], spadeCard[10][10], clubCard[10][10];
int sumPlayer1, sumPlayer2, sumDealer;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int goBack, index = 0, numberOfCards, index2 = 0;
char password[50], username[50], username2[50], password2[50];
long long int playerMoney, playerBet, playerMoney2;

bool isOk = false;
bool goToGameMenu;
bool showCard = false;

void hidePass(char password[50])
{
	int ch;
	int i = 0;

	while ((ch = _getch()) && ch != '\n' && ch != '\r')
	{
		if (ch == '\b' && i > 0)
		{
			cout << "\b \b";
			i--;
			password[i] = '\0';
		}
		else
		{
			cout << "*";
			password[i++] = (char)ch;
		}
	}

	password[i] = '\0';
}

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
	//cin.getline(password, 50);
	hidePass(password);

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

		cout << "\nParola trebuie sa contina minim 3 caractere !\n\n";

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

	//cin.getline(password, 50);
	hidePass(password);

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

	if (strchr(username, '\t') !=NULL)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "Username-ul nu trebuie sa contina caracterul tab!\n";
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

void renameCard(deck &card)
{
	switch (card.number)
	{
		case 2:
		{
			card.design[1][1] = '2';
			card.design[4][6] = '2';
			break;
		}
		case 3:
		{
			card.design[1][1] = '3';
			card.design[4][6] = '3';
			break;
		}
		case 4:
		{
			card.design[1][1] = '4';
			card.design[4][6] = '4';
			break;
		}
		case 5:
		{
			card.design[1][1] = '5';
			card.design[4][6] = '5';
			break;
		}
		case 6:
		{
			card.design[1][1] = '6';
			card.design[4][6] = '6';
			break;
		}
		case 7:
		{
			card.design[1][1] = '7';
			card.design[4][6] = '7';
			break;
		}
		case 8:
		{
			card.design[1][1] = '8';
			card.design[4][6] = '8';
			break;
		}
		case 9:
		{
			card.design[1][1] = '9';
			card.design[4][6] = '9';
			break;
		}
		case 10:
		{
			card.design[1][1] = 'X';
			card.design[4][6] = 'X';
			break;
		}
		case 11:
		{
			card.design[1][1] = 'J';
			card.design[4][6] = 'J';
			break;
		}
		case 12:
		{
			card.design[1][1] = 'Q';
			card.design[4][6] = 'Q';
			break;
		}
		case 13:
		{
			card.design[1][1] = 'K';
			card.design[4][6] = 'K';
			break;
		}
		case 14:
		{
			card.design[1][1] = 'A';
			card.design[4][6] = 'A';
			break;
		}
	}
	
}

void createDeckOfCards(deck cards[NUMBER_OF_CARDS])
{
	int i = 0, numberOfCard = 2;
	numberOfCards = NUMBER_OF_CARDS-1;

	while (i < 13)
	{
		cards[i].suit = 'H';
		cards[i].number = numberOfCard;
		
		for (int j = 0; j < 6; j++)
			strcpy_s(cards[i].design[j], heartCard[j]);

		renameCard(cards[i]);

		i++;
		numberOfCard++;
	}

	numberOfCard = 2;

	while (i < 26)
	{
		cards[i].suit = 'D';
		cards[i].number = numberOfCard;

		for (int j = 0; j < 6; j++)
			strcpy_s(cards[i].design[j], diamondCard[j]);

		renameCard(cards[i]);

		i++;
		numberOfCard++;
	}

	numberOfCard = 2;
	
	while (i < 39)
	{
		cards[i].suit = 'C';
		cards[i].number = numberOfCard;

		for (int j = 0; j < 6; j++)
			strcpy_s(cards[i].design[j], clubCard[j]);

		renameCard(cards[i]);

		i++;
		numberOfCard++;
	}

	numberOfCard = 2;

	while (i < 52)
	{
		cards[i].suit = 'S';
		cards[i].number = numberOfCard;

		for (int j = 0; j < 6; j++)
			strcpy_s(cards[i].design[j], spadeCard[j]);

		renameCard(cards[i]);

		i++;
		numberOfCard++;
	}
}

void shuffleCards(deck cards[NUMBER_OF_CARDS])
{
	srand(time(0));

	numberOfCards = NUMBER_OF_CARDS - 1;

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

			//cin.getline(currentPassword, 50);
			hidePass(currentPassword);

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

			//cin.getline(newPassword, 50);
			hidePass(newPassword);

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

			//cin.getline(currentPassword, 50);
			hidePass(currentPassword);

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

			//cin.getline(currentPassword, 50);
			hidePass(currentPassword);

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

void cardsDesign()
{
	ifstream cards("cards.txt");

	for (int i = 0; i < 6; i++)
		cards.getline(heartCard[i], 10);

	for (int i = 0; i < 6; i++)
		cards.getline(diamondCard[i], 10);

	for (int i = 0; i < 6; i++)
		cards.getline(clubCard[i], 10);

	for (int i = 0; i < 6; i++)
		cards.getline(spadeCard[i], 10);

}

void sumCardsDealer(int number)
{
	if (number <= 10)
		sumDealer += number;

	if (number > 10 && number < 14)
		sumDealer += 10;

	if (number == 14)
	{
		if (sumDealer + 11 > 21)
			sumDealer += 1;
		else
			sumDealer += 11;
	}

}

deck takeCard(deck cards[NUMBER_OF_CARDS])
{
	deck card;
	if (numberOfCards > 0)
	{
		card = cards[numberOfCards];
		numberOfCards--;
	}
	else
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\nSe amesteca cartile...";
		shuffleCards(cards);
		Sleep(1000);
		card = cards[numberOfCards];
		numberOfCards--;
	}

	return card;
}

void printCards()
{
	system("cls");
	cout << "PlayerMoney: " << playerMoney<<endl;
	cout << "PlayerBet: " << playerBet<<endl;
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << title;

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << username << "'s cards: "<<sumPlayer1<<" \n";

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < numberCardsPlayer1; j++)
			cout << cardsPlayer1[j].design[i] << "  ";

		cout << "\n";
	}

	cout << "\n";

	SetConsoleTextAttribute(h, 9 | FOREGROUND_INTENSITY);

	if (!showCard)
	{
		cout << "Dealer's cards: \n";
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < numberCardsDealer - 1; j++)
				cout << cardsDealer[j].design[i] << "  ";

			cout << "\n";
		}
	}
	else
	{
		cout << "Dealer's cards: " << sumDealer << "\n";
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < numberCardsDealer; j++)
				cout << cardsDealer[j].design[i] << "  ";

			cout << "\n";
		}
	}

	cout << "\n";

}

void sumCardsPlayer(int number, int &sumPlayer)
{
	if (number <= 10)
		sumPlayer += number;

	if (number > 10 && number < 14)
		sumPlayer += 10;

	if (number == 14)
	{
		int option;
		do
		{
			printCards();
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\nDoresti ca AS-ul sa aiba valoarea 11 sau 1 ?: ";
			cin >> option;


		} while (option != 1 && option != 11);

		if (option == 1)
			sumPlayer += 1;
		else
			sumPlayer += 11;
	}

}

void addMoney(long long int amountOfMoney,int index)
{
	ifstream money("money.txt");
	ofstream writeTemp("temp.txt");

	long long int temp;

	int i = 0;

	while (money >> temp)
	{
		i++;

		if (i == index)
			temp = temp + amountOfMoney;

		writeTemp << temp << "\n";
	}

	money.close();
	writeTemp.close();

	remove("money.txt");
	rename("temp.txt", "money.txt");
}

void updateMoney(int index)
{
	ifstream readMoney("money.txt");
	ofstream writeTemp("temp.txt");

	long long int temp;

	int i = 0;

	while (readMoney >> temp)
	{
		i++;

		if (i == index)
			temp = temp - playerBet;

		writeTemp << temp << "\n";
	}

	readMoney.close();
	writeTemp.close();

	remove("money.txt");
	rename("temp.txt", "money.txt");
}

void result()
{
	char option[50];
	long long int moneyWon=0;

	if (sumPlayer1 < 21)
	{
		if (sumDealer <= 21 && sumDealer > sumPlayer1)
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t\t\t Ai pierdut ! \n\n";
		}

		if (sumDealer > 21)
		{
			SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t\t\t Ai castigat " << playerBet << " $ !\n\n";
			moneyWon = 2*playerBet;
			playerMoney += moneyWon;
			addMoney(moneyWon, index);
		}

		if (sumDealer < sumPlayer1)
		{
			SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t\t\t Ai castigat " << playerBet << " $ !\n\n";
			moneyWon = 2*playerBet;
			playerMoney += moneyWon;
			addMoney(moneyWon, index);
		}

		if (sumDealer == sumPlayer1)
		{
			SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
			moneyWon = playerBet;
			playerMoney += moneyWon;
			addMoney(moneyWon, index);
			cout << "\t\t\t\t\t\t\t Egalitate ! \n\n";
		}

	}

	if (sumPlayer1 == 21)
	{
		if (sumDealer == 21)
		{
			SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
			moneyWon = playerBet;
			playerMoney += moneyWon;
			addMoney(moneyWon, index);
			cout << "\t\t\t\t\t\t\t Egalitate ! \n\n";
		}

		if (sumDealer < sumPlayer1 || sumDealer > 21)
		{
			if (numberCardsPlayer1 == 2)
			{
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "\t\t\t\t\t\t\t Black Jack !\n";

				SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
				cout << "\t\t\t\t\t\t\t Ai castigat " << (long long int)((float)(3 / 2)*playerBet) << " $ !\n\n";
				moneyWon = playerBet + (3 / 2)*playerBet;
				playerMoney += moneyWon;
				addMoney(moneyWon, index);
			}
			else
			{
				SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
				cout << "\t\t\t\t\t\t\t Ai castigat " << playerBet << " $ !\n\n";
				moneyWon = 2*playerBet;
				playerMoney += moneyWon;
				addMoney(moneyWon, index);
			}
		}
	}

	if (sumPlayer1 > 21)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\t\t\t\t\t\t Ai pierdut ! \n\n";
	}

	system("pause");

	do
	{
		system("cls");
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << title;

		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
		
		cout << "Joci din nou (D\\N) ?: ";
		cin >> option;

	} while (_stricmp(option, "D") != 0 && _stricmp(option, "N") != 0);

	if (_stricmp(option, "D") == 0)
		goBack = 0;
	else
		goBack = 1;

}

void dealerTurn()
{
	showCard = true;
	while (sumDealer < 17)
	{
		cardsDealer[numberCardsDealer++] = takeCard(cards);
		sumCardsDealer(cardsDealer[numberCardsDealer - 1].number);
		
		printCards();
	}

	printCards();
	result();
}

void checkSumPlayer(int sum)
{
	if (sum > 21)
	{
		showCard = true;
		printCards();
		result();
	}
}

void doubleDown()
{
	updateMoney(index);
	cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
	sumCardsPlayer(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);
	
	playerMoney -= playerBet;
	playerBet *= 2;

	checkSumPlayer(sumPlayer1);

	if (sumPlayer1 <= 21)
	{
		printCards();
		dealerTurn();
	}

}

void firstHandPlayer()
{
	showCard = false;
	numberCardsPlayer1 = 0;
	numberCardsDealer = 0;
	sumPlayer1 = 0;
	sumDealer = 0;

	int ok = 0;
	char option[50];

	cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
	sumCardsPlayer(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);

	cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
	sumCardsPlayer(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);

	

	cardsDealer[numberCardsDealer++] = takeCard(cards);
	sumCardsDealer(cardsDealer[numberCardsDealer - 1].number);

	cardsDealer[numberCardsDealer++] = takeCard(cards);
	sumCardsDealer(cardsDealer[numberCardsDealer - 1].number);

	if (sumPlayer1 == 21)
		dealerTurn();
	else
	{

		if (playerMoney >= playerBet)
		{

			ok = 1;
			do
			{
				printCards();

				SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);

				cout << "Hit, Stand  or Double Down (H\\S\\D): ";
				cin >> option;

			} while (_stricmp(option, "H") != 0 && _stricmp(option, "S") != 0 && _stricmp(option, "D") != 0);

		}
		if (ok && _stricmp(option, "D") == 0)
				doubleDown();
		else
		{

			do
			{
				if(!ok)
					do
					{
						printCards();
						SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);

						cout << "Hit or Stand (H\\S): ";
						cin >> option;
					} while (_stricmp(option, "H") != 0 && _stricmp(option, "S") != 0);

				if (_stricmp(option, "H") == 0)
				{
					cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
					sumCardsPlayer(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);
				}

				checkSumPlayer(sumPlayer1);
				ok = 0;

			} while (_stricmp(option, "H") == 0 && sumPlayer1 < 21);

			if (sumPlayer1 <= 21)
				dealerTurn();
		}

		
	}

}

void bet()
{
	bool ok;

	if (playerMoney > 0)
	{
		do
		{
			ok = true;
			system("cls");
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << title;
			cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

			SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
			cout << "Ce suma doresti sa pariezi ?: ";

			cin >> playerBet;

			if (playerBet < 0)
			{
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

				cout << "Suma pariata trebuie sa fie > 0 !\n\n";

				ok = false;
			}

			if (playerBet > playerMoney)
			{
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

				cout << "Suma pariata trebuie sa fie <= ";

				SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

				cout << playerMoney;

				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

				cout << " !\n\n";

				ok = false;
			}

			if (!ok)
				system("pause");

		} while (playerBet < 0 || playerBet > playerMoney);
	}
	else
	{
		playerBet = 0;
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\nNu aveti suficienti bani in cont, adaugati din meniul de optiuni !\n\n";
		system("pause");

	}
}

void singlePlayer()
{
	bet();

	if (playerBet>0)
	{
		playerMoney = playerMoney - playerBet;
		updateMoney(index);

		system("cls");
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << title;

		firstHandPlayer();
	}
	else
		goBack = 1;


}

void result2()
{
	char option[50];

	if (sumPlayer1 < 21)
	{
		if (sumPlayer2 <= 21 && sumPlayer2 > sumPlayer1)
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t\t\t"<<username2<<" a castigat ! \n\n";
		}

		if (sumPlayer2 > 21)
		{
			SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t\t\t" << username << " a castigat ! \n\n";
		}

		if (sumPlayer2 < sumPlayer1)
		{
			SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t\t\t" << username << " a castigat ! \n\n";
		}

		if (sumPlayer2 == sumPlayer1)
		{
			SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t\t\t Egalitate ! \n\n";
		}

	}

	if (sumPlayer1 == 21)
	{
		if (sumPlayer2 == 21)
		{
			SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
			cout << "\t\t\t\t\t\t\t Egalitate ! \n\n";
		}

		if (sumPlayer2 < sumPlayer1 || sumPlayer2 > 21)
		{
			if (numberCardsPlayer1 == 2)
			{
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "\t\t\t\t\t\t\t Black Jack !\n";

				SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
				cout << "\t\t\t\t\t\t\t" << username << " a castigat ! \n\n";
			}
			else
			{
				SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
				cout << "\t\t\t\t\t\t\t" << username << " a castigat ! \n\n";
			}
		}
	}

	if (sumPlayer1 > 21)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\t\t\t\t\t\t\t" << username2 << " a castigat ! \n\n";
	}

	system("pause");

	do
	{
		system("cls");
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << title;

		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

		cout << "Jucati din nou (D\\N) ?: ";
		cin >> option;

	} while (_stricmp(option, "D") != 0 && _stricmp(option, "N") != 0);

	if (_stricmp(option, "D") == 0)
		goBack = 0;
	else
		goBack = 1;

}

void printCards2()
{
	system("cls");

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << title;

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << username << "'s cards: " << sumPlayer1 << " \n";

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < numberCardsPlayer1; j++)
			cout << cardsPlayer1[j].design[i] << "  ";

		cout << "\n";
	}

	cout << "\n";

	SetConsoleTextAttribute(h, 9 | FOREGROUND_INTENSITY);

	cout << username2 << "'s cards: " << sumPlayer2 << " \n";

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < numberCardsPlayer2; j++)
			cout << cardsPlayer2[j].design[i] << "  ";

		cout << "\n";
	}

	cout << "\n";

}

void sumCardsPlayer2(int number, int &sumPlayer)
{
	if (number <= 10)
		sumPlayer += number;

	if (number > 10 && number < 14)
		sumPlayer += 10;

	if (number == 14)
	{
		int option;
		do
		{
			printCards2();
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\nDoresti ca AS-ul sa aiba valoarea 11 sau 1 ?: ";
			cin >> option;


		} while (option != 1 && option != 11);

		if (option == 1)
			sumPlayer += 1;
		else
			sumPlayer += 11;
	}

}

void doubleDown3()
{
	cardsPlayer2[numberCardsPlayer2++] = takeCard(cards);
	sumCardsPlayer2(cardsPlayer2[numberCardsPlayer2 - 1].number, sumPlayer2);

	printCards2();
	result2();

}

void player2Turn()
{
	int ok1 = 0;
	char option[50];

	ok1 = 1;

	do
	{
		printCards2();

		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
		cout << "Randul lui " << username2 << "\n";

		SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);

		cout << "Hit, Stand  or Double Down (H\\S\\D): ";
		cin >> option;

	} while (_stricmp(option, "H") != 0 && _stricmp(option, "S") != 0 && _stricmp(option, "D") != 0);

	if (ok1 && _stricmp(option, "D") == 0)
		doubleDown3();
	else
	{

		do
		{
			if (!ok1)
				do
				{
					printCards2();

					SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
					cout << "Randul lui " << username2 << "\n";

					SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);

					cout << "Hit or Stand (H\\S): ";
					cin >> option;

				} while (_stricmp(option, "H") != 0 && _stricmp(option, "S") != 0);

				if (_stricmp(option, "H") == 0)
				{
					cardsPlayer2[numberCardsPlayer2++] = takeCard(cards);
					sumCardsPlayer2(cardsPlayer2[numberCardsPlayer2 - 1].number, sumPlayer2);
				}

				ok1 = 0;

		} while (_stricmp(option, "H") == 0 && sumPlayer2 < 21);

		printCards2();

		result2();

	}
}

void checkSumPlayer2()
{
	if (sumPlayer1 > 21)
	{
		printCards2();
		result2();
	}
}

void doubleDown2()
{
	cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
	sumCardsPlayer2(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);
	
	printCards2();

	if (sumPlayer1 <= 21 && sumPlayer2 != 21)
		player2Turn();
	else
		result2();

}

void firstHandPlayer2()
{
	numberCardsPlayer1 = 0;
	numberCardsPlayer2 = 0;
	sumPlayer1 = 0;
	sumPlayer2 = 0;

	int ok1 = 0;
	char option[50];

	cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
	sumCardsPlayer2(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);

	cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
	sumCardsPlayer2(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);



	cardsPlayer2[numberCardsPlayer2++] = takeCard(cards);
	sumCardsPlayer2(cardsPlayer2[numberCardsPlayer2 - 1].number, sumPlayer2);

	cardsPlayer2[numberCardsPlayer2++] = takeCard(cards);
	sumCardsPlayer2(cardsPlayer2[numberCardsPlayer2 - 1].number, sumPlayer2);

	if (sumPlayer1 == 21)
		player2Turn();
	else
	{
		if (sumPlayer2 != 21)
		{
			ok1 = 1;
			do
			{
				printCards2();

				SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
				cout << "Randul lui " << username << "\n";

				SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);

				cout << "Hit, Stand  or Double Down (H\\S\\D): ";
				cin >> option;

			} while (_stricmp(option, "H") != 0 && _stricmp(option, "S") != 0 && _stricmp(option, "D") != 0);

			if (ok1 && _stricmp(option, "D") == 0)
				doubleDown2();
			else
			{

				do
				{
					if (!ok1)
						do
						{
							printCards2();

							SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
							cout << "Randul lui " << username << "\n";

							SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);

							cout << "Hit or Stand (H\\S): ";
							cin >> option;
						} while (_stricmp(option, "H") != 0 && _stricmp(option, "S") != 0);

						if (_stricmp(option, "H") == 0)
						{
							cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
							sumCardsPlayer2(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);
						}

						checkSumPlayer2();
						ok1 = 0;

				} while (_stricmp(option, "H") == 0 && sumPlayer1 < 21);

				if (sumPlayer1 <= 21)
					player2Turn();
			}
		
		}
		else
		{
			ok1 = 1;
			do
			{
				printCards2();

				SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
				cout << "Randul lui " << username << "\n";

				SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);

				cout << "Hit, Stand  or Double Down (H\\S\\D): ";
				cin >> option;

			} while (_stricmp(option, "H") != 0 && _stricmp(option, "S") != 0 && _stricmp(option, "D") != 0);

			if (ok1 && _stricmp(option, "D") == 0)
				doubleDown2();
			else
			{

				do
				{
					if (!ok1)
						do
						{
							printCards2();

							SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
							cout << "Randul lui " << username << "\n";

							SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);

							cout << "Hit or Stand (H\\S): ";
							cin >> option;
						} while (_stricmp(option, "H") != 0 && _stricmp(option, "S") != 0);

						if (_stricmp(option, "H") == 0)
						{
							cardsPlayer1[numberCardsPlayer1++] = takeCard(cards);
							sumCardsPlayer2(cardsPlayer1[numberCardsPlayer1 - 1].number, sumPlayer1);
						}

						checkSumPlayer2();
						ok1 = 0;

				} while (_stricmp(option, "H") == 0 && sumPlayer1 < 21);

				result2();
			}
		}

	}

}

void signupMoney2()
{
	system("cls");

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << signup;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username jucator 2: " << username2 << "\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Password : ";
	for (unsigned i = 0; i < strlen(password2); i++)
		cout << "*";
	cout << "\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Suma cu care doriti sa va inregistrati: ";

	cin >> playerMoney2;

	if (playerMoney2 == 0)
		goBack = 1;
	else
	{
		if (playerMoney2 < 0)
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "Suma inregistrata trebuie sa fie mai mare decat 0! \n";

			system("pause");

			signupMoney2();
		}
		else
		{

			ofstream writeUsername("username.txt", ios::app);
			ofstream writePass("password.txt", ios::app);
			ofstream writeMoney("money.txt", ios::app);

			writeUsername << username2 << "\n";
			writePass << password2 << "\n";
			writeMoney << playerMoney2 << "\n";

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

void signupPassword2()
{
	system("cls");

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << signup;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username jucator 2: " << username2 << "\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
	cout << "Password (minim 3 caractere): ";

	//cin.getline(password, 50);
	hidePass(password2);

	if (strcmp(password2, "0") == 0)
		goBack = 1;
	else
		if (!verifyPassword(password2))
		{
			cout << "\n";
			system("pause");
			signupPassword2();
		}
		else
			signupMoney2();
}

void signupUsername2()
{
	index2 = 0;
	system("cls");

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << signup;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username jucator 2 (minim 3 caractere): ";

	if (!isOk)
	{
		getchar();
		isOk = true;
	}

	cin.getline(username2, 50);


	if (strcmp(username2, "0") == 0)
		goBack = 1;
	else
	{

		if (!verifyUsername(username2))
		{
			cout << "\n";
			system("pause");
			signupUsername2();
		}
		else
			signupPassword2();
	}


}

void loginPassword2()
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

	cout << "Username jucator 2: " << username2 << "\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);
	cout << "Password: ";

	//cin.get();
	//cin.getline(password, 50);
	hidePass(password2);

	//cout << password;

	if (strcmp(password2, "0") == 0)
		goBack = 1;
	else
	{

		for (int i = 1; i <= index2; i++)
			pass.getline(currentPassword, 50);


		if (strcmp(password2, currentPassword) == 0)
		{
			for (int i = 1; i <= index; i++)
				money >> playerMoney2;

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

			loginPassword2();
		}
	}
}

void loginUsername2()
{
	system("cls");

	ifstream name("username.txt");

	char currentName[50];
	int ok = 0;
	index2 = 0;

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << login;

	cout << "Tastati 0 pentru a reveni la meniul anterior !\n\n";

	SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

	cout << "Username jucator 2: ";
	cin >> username2;

	isOk = false;

	if (strcmp(username2, "0") == 0)
		goBack = 1;
	else
	{
		while (!name.eof())
		{
			index2++;
			name >> currentName;
			if (_stricmp(username2, currentName) == 0)
			{
				ok = 1;
				break;
			}

		}

		if (ok)
		{
			name.close();
			strcpy_s(username2, currentName);
			loginPassword2();
		}

		else
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\nUsername inexistent, va rugam sa incercati din nou !\n\n";

			system("pause");

			loginUsername2();
		}
	}
}

void multiPlayer()
{
	firstHandPlayer2();
}

void optionGame()
{
	char option[20];
	goBack = 0;

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
		cardsDesign();
		createDeckOfCards(cards);
		shuffleCards(cards);

		do
		{
			singlePlayer();

		} while (!goBack);

		if (goBack == 1)
			optionGame();
	}
	else
		if (strcmp(option, "2") == 0)
		{
			cardsDesign();
			createDeckOfCards(cards);
			shuffleCards(cards);

			char option2[50];
			do
			{
				system("cls");

				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

				cout << title;

				cout << "1. Log in player 2 \n";
				cout << "2. Sign up player 2 \n";
				cout << "3. Back \n\n";

				cout << "Choose an option: ";
				cin >> option2;

			} while (strcmp(option2, "1") != 0 && strcmp(option2, "2") != 0 && strcmp(option2, "3") != 0);

			if (strcmp(option2, "1") == 0)
					loginUsername2();
			else
				if (strcmp(option2, "2") == 0)
				{
					isOk = false;
					signupUsername2();
				}
				else
					goBack = 1;
			if(!goBack)
				do
				{
					if (!goBack)
						multiPlayer();

				} while (!goBack);

			if (goBack == 1)
				optionGame();
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
