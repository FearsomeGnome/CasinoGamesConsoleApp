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
int dealerCards = 0;
int playerCards = 0;
int playerTotal = 0;
int dealerTotal = 0;
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
int getHandTotal(string arr[], string str);
int checkTotal(int total);
bool checkBank();
void buildDeck();
void betting();
void checkBet(int num);
void initialDeal();
void displayHand(string arr[], string str);
void stayOrHit();
void hit(string arr[], string str);
void stay(int pTotal);
void playerLose();
void playAgain();

// blackjack game
void blackJack()
{
	srand(time(0)); // set random to current time or shuffle will be the same each time
	random_shuffle(&deck[0], &deck[52]); // shuffle deck based on random number

	// reset variables
	cardCount = 0;
	dealerCards = 0;
	playerCards = 0;
	playerTotal = 0;
	dealerTotal = 0;

	betting();
	
	initialDeal();
	
	displayHand(playerHand, "player");
	// after the deal, get totals and check hands for 21
	playerTotal = getHandTotal(playerHand, "player");
	dealerTotal = getHandTotal(dealerHand, "dealer");
	int dealerState = checkTotal(dealerTotal);
	int playerState = checkTotal(playerTotal);
	if (dealerState == 2 && playerState == 2)
	{
		bet = 0;
		displayHand(dealerHand, "dealer");
		cout << "\n\n\tIt's a draw." << endl;
		playAgain();
	}
	else if (dealerState == 2)
	{
		cout << "\nThe dealer has blackjack. You lose.\n";
		bank -= bet;
		checkBank();
		playAgain();
	}
	else if (playerState == 2)
	{
		cout << "\n\n\tBLACKJACK! You win!\n";
		bank += bet;
		playAgain();
	}

	// if neither player or dealer got 21 on the deal, ask the player if they want to hit or stay
	cout << "\nYour total is: " << playerTotal;
	stayOrHit();
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
		buildDeck();
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
			dealerCards++;
			break;
		case 2:
			dealerHand[1] = deck[cardCount].value;
			dealerCards++;
			break;
		case 3:
			playerHand[0] = deck[cardCount].value;
			playerCards++;
			break;
		case 4:
			playerHand[1] = deck[cardCount].value;
			playerCards++;
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
	cout << "\n\n";
}

// function to turn string card values into integer totals
int getHandTotal(string arr[], string str)
{
	int size = 0;
	if (str == "player")
	{
		size = playerCards;
	}
	else
	{
		size = dealerCards;
	}

	int total = 0;
	for (i = 0; i < size; i++)
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
			if (str == "dealer")
			{
				if (total < 20)
				{
					total += 11;
					continue;
				}
				else
				{
					total += 1;
					continue;
				}
			}
			else
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
		playerLose();
	}
	else return true;
}

// if player runs out of money show the lose screen and end the program
void playerLose()
{
	cout << "\n\n";
	cout << "-------------------------------------------" << endl;
	cout << "|                                         |" << endl;
	cout << "|               GAME OVER                 |" << endl;
	cout << "|            You are bankrupt             |" << endl;
	cout << "|                                         |" << endl;
	cout << "-------------------------------------------" << endl;
	exit(0);
}

// hand is over ask player if they want to continue
void playAgain()
{
	int choice = 0;
	cout << "The hand is over, would you like to play again?\n";
	cout << "\t1. Play again!\n";
	cout << "\t2. Exit." << endl;
	cin >> choice;
	
	while (choice != 1 && choice != 2)
	{
		playAgain();
	}

	if (choice == 1)
	{
		blackJack();
	}
	else
	{
		exit(0);
	}
}

// add a card to the hand of player or dealer
void hit(string arr[], string str)
{
	if (str == "player")
	{
		arr[playerCards] = deck[cardCount].value;
		playerCards++;
		cardCount++;
	}
	else
	{
		arr[dealerCards] = deck[cardCount].value;
		dealerCards++;
		cardCount++;
	}
}

// function to recursively ask player to hit or stay
void stayOrHit()
{
	int playerState;
	int choice = 0;
	while (choice != 1 && choice != 2)
	{
		cout << "\nWould you like to take a card or stop?\n";
		cout << "\t1. Hit me!\n";
		cout << "\t2. Stay." << endl;
		cin >> choice;
	}
	if (choice == 1)
	{
		hit(playerHand, "player");
		displayHand(playerHand, "player");
		playerTotal = getHandTotal(playerHand, "player");
		playerState = checkTotal(playerTotal);
		switch (playerState)
		{
		case 1:
			cout << "\nYour total is: " << playerTotal;
			stayOrHit();
			break;
		case 2:
			cout << "\nYou have 21! It is now the dealer's turn.\n";
			stay(playerTotal);
			break;
		case 3:
			cout << "\n\t\tYou have BUSTED!\n";
			bank -= bet;
			checkBank();
			playAgain();
			break;
		}
	}
	else
	{
		cout << "\nIt is now the dealer's turn.\n";
		stay(playerTotal);
	}
}

// after player stays, or gets 21 it is now the dealers turn
// the dealer hits below 17 and stays anywhere above
void stay(int pTotal)
{
	int playerTotal = pTotal;
	displayHand(dealerHand, "dealer");
	int dealerTotal = getHandTotal(dealerHand, "dealer");
	if (dealerTotal > playerTotal && dealerTotal < 22)
	{
		cout << "\n\tDealer Wins.\n";
		bank -= bet;
		checkBank();
		playAgain();
	}
	else if (dealerTotal < 17)
	{
		hit(dealerHand, "dealer");
		cout << "\n";
		stay(playerTotal);
	}
	else if (dealerTotal > 21)
	{
		cout << "\n\tDealer BUSTS! You win!\n";
		bank += bet;
		playAgain();
	}
}