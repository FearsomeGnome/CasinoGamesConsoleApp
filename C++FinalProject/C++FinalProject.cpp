// C++FinalProject.cpp

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

// global variables
int choice = 0;
int bank = 50;
int bet;
// define card structure and deck
struct card
{
	string value;
	string suit;
};
card deck[52]{};

// show the player what games they can play and ask them to choose a game
void menu()
{
	cout << "-------------------------------------------" << endl;
	cout << "|                  MENU                   |" << endl;
	cout << "|            1. Black Jack                |" << endl;
	cout << "|            2. Roulette                  |" << endl;
	cout << "|                                         |" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "Welcome player, which game would you like to play?" << endl;
	// save players choice into variable
	cin >> choice;
}

// defined below main
void betting();
void checkBet(int num);

// build card deck
void buildDeck()
{
	string suits[4] = { "Clubs", "Hearts", "Diamonds", "Spades" };
	string cardValue[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			deck[count].suit = suits[i];
			deck[count].value = cardValue[j];
			count++;
		}
	}
}

// blackjack game
void blackJack()
{
	buildDeck();
	srand(time(0)); // set random to current time or shuffle will be the same each time
	random_shuffle(&deck[0], &deck[52]); // shuffle deck based on random number

}

// roulette game
void roulette()
{

}

// if player runs out of money show the lose screen and end the program
void playerLose()
{
	cout << "-------------------------------------------" << endl;
	cout << "|                                         |" << endl;
	cout << "|               GAME OVER                 |" << endl;
	cout << "|            You are bankrupt             |" << endl;
	cout << "|                                         |" << endl;
	cout << "-------------------------------------------" << endl;
	exit(0);
}

int main()
{
	// call menu
	menu();
	// check player choice to ensure correct entry and if not replay menu
	while (choice != 1 && choice != 2)
	{
		menu();
	}
	// show player game based on choice
	if (choice == 1)
	{
		blackJack();
	}
	else
	{
		// roulette
	}

	return 0;
}

// show the player how much money they have in the bank and ask how much they would like to bet
void betting()
{
	cout << "You have $" << bank << ", in the bank." << endl;
	cout << "\nHow much would you like to bet?" << endl;
	cin >> bet;
	checkBet(bet);
}

// function to check if bet is more than player has or negative
void checkBet(int num)
{
	if (num > bank || num < 0)
	{
		bet = 0;
		betting();
	}
}