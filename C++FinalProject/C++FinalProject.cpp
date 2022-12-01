// C++FinalProject.cpp

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// global variables
int i, j;
int choice = 0;
int bank = 50;
int bet;
// blackjack variables
int cardCount = 0;
string dealerHand[10]{};
string playerHand[10]{};
// define card structure and deck
struct Card
{
	string value;
	string suit;
};
Card deck[52]{};

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
int getHandTotal(string arr[]);
int checkTotal(int total);
bool checkBank();
void buildDeck();
void betting();
void checkBet(int num);
void initialDeal();
void displayHand(string arr[], string str);
void hit();
void stay();
void dealerHit();
void playerLose();

// blackjack game
void blackJack()
{

	buildDeck();
	srand(time(0)); // set random to current time or shuffle will be the same each time
	random_shuffle(&deck[0], &deck[52]); // shuffle deck based on random number
	betting();
	
	initialDeal();
	
	displayHand(playerHand, "player");
	int playerTotal = getHandTotal(playerHand);
	int dealerTotal = getHandTotal(dealerHand);
	if (checkTotal(playerTotal) == 3)
	{
		cout << "You have busted!";
		bank -= bet;

	}

	cout << "\nYour total is: " << playerTotal;
}

// roulette game
void roulette()
{

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

// show the player how much money they have in the bank and ask how much they would like to bet
void betting()
{
	cout << "\n\n\tYou have $" << bank << ", in the bank." << endl;
	cout << "\n\tHow much would you like to bet? ";
	cin >> bet;
	checkBet(bet);
}

// function to check if bet is more than player has or negative
void checkBet(int num)
{
	if (num > bank || num < 1)
	{
		bet = 0;
		betting();
	}
}

// initial deal will be called at the beginning of each hand
void initialDeal()
{
	for (i = 1; i < 5; i++)
	{
		switch (i)
		{
		case 1:
			dealerHand[0] = deck[cardCount].value;
			break;
		case 2:
			dealerHand[1] = deck[cardCount].value;
			break;
		case 3:
			playerHand[0] = deck[cardCount].value;
			break;
		case 4:
			playerHand[1] = deck[cardCount].value;
			break;
		}
		cardCount++;
	}
}

// display either player or dealer hand
void displayHand(string arr[], string str)
{
	if (str == "player")
	{
		cout << "Your cards are: ";
	}
	else if (str == "dealer")
	{
		cout << "Dealer cards are: ";
	}
	for (i = 0; i < 10; i++)
	{
		if (!empty(arr[i]))
		{
			cout << arr[i] << " ";
		}
	}
}

// function to turn string card values into integer totals
int getHandTotal(string arr[])
{
	int total = 0;
	for (i = 0; i < 10; i++)
	{
		if (arr[i] == "10" || arr[i] == "J" || arr[i] == "Q" || arr[i] == "K")
		{
			total += 10;
			continue;
		}
		else if (arr[i] == "9")
		{
			total += 9;
			continue;
		}
		else if (arr[i] == "8")
		{
			total += 8;
			continue;
		}
		else if (arr[i] == "7")
		{
			total += 7;
			continue;
		}
		else if (arr[i] == "6")
		{
			total += 6;
			continue;
		}
		else if (arr[i] == "5")
		{
			total += 5;
			continue;
		}
		else if (arr[i] == "4")
		{
			total += 4;
			continue;
		}
		else if (arr[i] == "3")
		{
			total += 3;
			continue;
		}
		else if (arr[i] == "2")
		{
			total += 2;
			continue;
		}
		else if (arr[i] == "A")
		{
			int choice = 0;
			while (choice != 1 && choice != 11)
			{
				cout << "\nYou have an Ace. Would you like it to equal 1 or 11?\nPlease enter 1 or 11: ";
				cin >> choice;
			}
			if (choice == 1)
			{
				total += 1;
			}
			else
			{
				total += 11;
			}
			continue;
		}
	}
	return total;
}

// check if the total cards in the hand is less than, equal to, or over 21
int checkTotal(int total)
{
	if (total < 21)
	{
		return 1;
	}
	else if (total == 21)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

// check if the players' bank account is below 1
bool checkBank()
{
	if (bank < 1)
	{
		return false;
	}
	else return true;
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