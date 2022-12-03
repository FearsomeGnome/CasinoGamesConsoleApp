// C++FinalProject.cpp
/*
This is a console app that allows the user to play blackjack and a simplified version
of roulette. Blackjack creates and shuffles a deck of cards and allows the user to take cards
place bets and then watch the dealer play their hand and shows wins and loses. Roulette will
display the available numbers to bet on and allow the player to choose and bet on up to 38 numbers
or until their bank is empty. A winning number pays 36 to 1. A random number is chosen and used
as the index number to pick from the wheel array. Wins and loses are displayed as appropriate.
Exiting either game takes the player back to the main menu and their bank total will persist
through either game.
*/

#include <iostream>
#include <algorithm>
#include <string>
// necessary line to resize window, indicates you are using windows 2000 or later
#define _WIN32_WINNT 0x0500
// The above line must come before you include windows.h
#include <Windows.h>

using namespace std;

// global variables
int i, j;
int choice = 0;
int bank = 50;
// roulette variables and wheel const
int numCtr = 0;
string winningNum;
struct Bets
{
	string num;
	int amount;
};
Bets playerBets[38]{};
const string wheelNums[38] = { "00", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
	"17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36" };
// blackjack variables
int bet;
int cardCount = 0;
int dealerCards = 0;
int playerCards = 0;
int playerTotal = 0;
int dealerTotal = 0;
string dealerHand[10]{};
string playerHand[10]{};
// define card structure and deck size
struct Card
{
	string value;
	string suit;
};
Card deck[52]{};

// Universal functions - defined below main
void menu();
void betting();
bool checkBank();
void checkBet(int num);
void playAgain(string str);
// Roulette functions - defined below main
void roulette();
void chooseNum();
void displayBets();
bool keepChoosing();
void clearPlayerBets();
void checkAndDisplay(string str);
// Blackjack functions - defined below main
void blackJack();
void stay();
void buildDeck();
void stayOrHit();
void playerLose();
void initialDeal();
int checkTotal(int total);
void clearHand(string arr[]);
void hit(string arr[], string str);
void displayHand(string arr[], string str);
int getHandTotal(string str, string card1, string card2 = "0");


int main()
{
	HWND console = GetConsoleWindow(); // assign handle to console
	RECT r; // create rect
	GetWindowRect(console, &r); // store current console dimensions
	// MoveWindow(window handle, x, y, width, height, redraw window bool)
	MoveWindow(console, r.left, r.top, 800, 1000, TRUE);
	
	// call menu
	menu();
	
	return 0;
}

// show the player what games they can play and ask them to choose a game
void menu()
{
	cout << "    -------------------------------------------" << endl;
	cout << "    |                  MENU                   |" << endl;
	cout << "    |            1. Black Jack                |" << endl;
	cout << "    |            2. Roulette                  |" << endl;
	cout << "    |            3. Exit                      |" << endl;
	cout << "    -------------------------------------------" << endl;
	cout << " Welcome player, which game would you like to play? ";
	// save players choice into variable
	cin >> choice;
	// check player choice to ensure correct entry and if not replay menu
	while (choice != 1 && choice != 2 && choice != 3)
	{
		menu();
	}
	// show player game based on choice
	if (choice == 1)
	{
		cout << "\n\tShuffling new deck....\n";
		Sleep(2000);
		buildDeck();
		blackJack();
	}
	else if (choice == 2)
	{
		roulette();
	}
	else
	{
		exit(0);
	}
}

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
	playerTotal += getHandTotal("player", playerHand[0], playerHand[1]);
	dealerTotal += getHandTotal("dealer", dealerHand[0], dealerHand[1]);
	int dealerState = checkTotal(dealerTotal);
	int playerState = checkTotal(playerTotal);
	if (dealerState == 2 && playerState == 2)
	{
		bet = 0;
		displayHand(dealerHand, "dealer");
		cout << "\n\n\tIt's a draw." << endl;
		bank += bet;
		playAgain("blackjack");
	}
	else if (dealerState == 2)
	{
		cout << "\n    The dealer has blackjack. You lose.\n";
		displayHand(dealerHand, "dealer");
		checkBank();
		playAgain("blackjack");
	}
	else if (playerState == 2)
	{
		cout << "\n\n\tBLACKJACK! You win!\n";
		bank += (bet * 2);
		playAgain("blackjack");
	}

	// if neither player or dealer got 21 on the deal, ask the player if they want to hit or stay
	cout << "\n\tYour total is: " << playerTotal;
	stayOrHit();
}

// roulette game
void roulette()
{
	bool keepGoing = true; // variable for use during betting

	cout << "\n    The numbers available to bet on are:\n\n";
	for (i = 0; i < 38; i++)
	{
		if (i < 19 || i > 19)
		{
			cout << "[" << wheelNums[i] << "] ";
		}
		else
		{
			cout << "[" << wheelNums[i] << "]\n";
		}
	}
	cout << "\n";

	chooseNum();
	while (keepGoing)
	{
		keepGoing = keepChoosing();
		if (keepGoing)
		{
			chooseNum();
		}
	}

	displayBets();
	// generate random number to use as index on the wheel / define winning number
	cout << "\n\tSpinning the wheel....\n";
	srand(time(0));
	int randNum = rand() % 38;
	winningNum = wheelNums[randNum];
	Sleep(1000);
	cout << "   ...\n";
	Sleep(800);
	cout << "       ...\n";
	Sleep(600);
	cout << "           ...\n";
	// display winning number to player and complete the round
	cout << "\n   The winning number is: " << winningNum << endl;
	Sleep(1000);
	checkAndDisplay(winningNum);
	Sleep(1000);
	checkBank();
	playAgain("roulette");
}

// build card deck
void buildDeck()
{
	string suits[4] = { "Clubs", "Hearts", "Diamonds", "Spades" };
	string cardValue[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	int count = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 13; j++)
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
	if (bank > 0)
	{
		bet = 0;
		cout << "\n\n\tYou have $" << bank << ", in the bank." << endl;
		cout << "\n\tHow much would you like to bet? $";
		cin >> bet;
		checkBet(bet);
		bank -= bet;
	}
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
		cout << "\n   Dealing...." << endl;
		Sleep(1500);
		cout << "\n\tYour cards are: ";
	}
	else if (str == "dealer")
	{
		cout << "\n\tDealer cards are: ";
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
int getHandTotal(string str, string card1, string card2)
{
	int total = 0;
	string arr[2] = { card1, card2 };
	for (i = 0; i < 2; i++)
	{
		if (arr[i] == "0")
		{
			break;
		}
		else if (arr[i] == "10" || arr[i] == "J" || arr[i] == "Q" || arr[i] == "K")
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
					cout << "\n  You have an Ace. Would you like it to equal 1 or 11?\n  Please enter 1 or 11: ";
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
		return false;
	}
	else return true;
}

// if player runs out of money show the lose screen and end the program
void playerLose()
{
	cout << "\n\n";
	cout << "    -------------------------------------------" << endl;
	cout << "    |                                         |" << endl;
	cout << "    |               GAME OVER                 |" << endl;
	cout << "    |            You are bankrupt             |" << endl;
	cout << "    |                                         |" << endl;
	cout << "    -------------------------------------------" << endl;
	exit(0);
}

// hand is over ask player if they want to continue
void playAgain(string str)
{
	choice = 0;
	bet = 0;

	if (str == "blackjack")
	{
		clearHand(playerHand);
		clearHand(dealerHand);
		cout << "\n    The hand is over, would you like to play again?\n";
		cout << "\t1. Play again!\n";
		cout << "\t2. Exit." << "\n   ";
		cin >> choice;

		while (choice != 1 && choice != 2)
		{
			playAgain("blackjack");
		}

		if (choice == 1)
		{
			blackJack();
		}
		else
		{
			menu();
		}
	}
	else if (str == "roulette")
	{
		numCtr = 0;
		winningNum.clear();
		clearPlayerBets();
		cout << "\n\n    The round is over, would you like to play again?\n";
		cout << "\t1. Play again!\n";
		cout << "\t2. Exit." << "\n   ";
		cin >> choice;

		while (choice != 1 && choice != 2)
		{
			playAgain("roulette");
		}

		if (choice == 1)
		{
			roulette();
		}
		else
		{
			menu();
		}
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
		cout << "\n\n    Would you like to take a card or stop?\n";
		cout << "\t1. Hit me!\n";
		cout << "\t2. Stay." << "\n   ";
		cin >> choice;
	}
	if (choice == 1)
	{
		hit(playerHand, "player");
		displayHand(playerHand, "player");
		playerTotal += getHandTotal("player", playerHand[playerCards - 1]);
		playerState = checkTotal(playerTotal);
		switch (playerState)
		{
		case 1:
			cout << "\n\tYour total is: " << playerTotal;
			stayOrHit();
			break;
		case 2:
			cout << "\n    You have 21! It is now the dealer's turn.\n";
			stay();
			break;
		case 3:
			cout << "\n\tYou have BUSTED!\n";
			checkBank();
			playAgain("blackjack");
			break;
		}
	}
	else
	{
		cout << "\n\tIt is now the dealer's turn.\n";
		stay();
	}
}

// after player stays, or gets 21 it is now the dealers turn
// the dealer hits below 17 and stays anywhere above
void stay()
{
	displayHand(dealerHand, "dealer");
	if (dealerTotal > playerTotal && dealerTotal < 22 && dealerTotal >= 17)
	{
		Sleep(2000);
		cout << "\n\tDealer Stays\n";
		Sleep(2000);
		cout << "\n\tDealer Wins with " << dealerTotal << "\n";
		checkBank();
		playAgain("blackjack");
	}
	else if (dealerTotal < 17)
	{
		Sleep(2000);
		cout << "\n\tDealer hits...";
		Sleep(2000);
		hit(dealerHand, "dealer");
		dealerTotal += getHandTotal("dealer", dealerHand[dealerCards - 1]);
		cout << "\n";
		stay();
	}
	else if (dealerTotal > 21)
	{
		Sleep(2000);
		cout << "\n\tDealer BUSTS! You won $" << bet * 2 << "!\n";
		bank += (bet * 2);
		playAgain("blackjack");
	}
	else if (dealerTotal >= 17 && dealerTotal == playerTotal)
	{
		Sleep(2000);
		cout << "\n\tDealer Stays";
		Sleep(2000);
		cout << "\n\n\tIt's a draw." << endl;
		bank += bet;
		playAgain("blackjack");
	}
	else if (dealerTotal >= 17 && dealerTotal < playerTotal)
	{
		Sleep(2000);
		cout << "\n\tDealer stays. You won $" << bet * 2 << "!\n";
		bank += (bet * 2);
		playAgain("blackjack");
	}
}

// clear a hand of all saved cards
void clearHand(string arr[])
{
	for (i = 0; i < 10; i++)
	{
		if (arr[i] == " ")
			break;
		arr[i].clear();
	}
}

// function to ask player to choose numbers and save them to array
void chooseNum()
{
	cout << "\n\tPlease choose a number to bet on: ";
	cin >> playerBets[numCtr].num;
	// check for valid input
	for (i = 0; i < 38; i++)
	{
		if (playerBets[numCtr].num == wheelNums[i])
		{
			betting();
			playerBets[numCtr].amount = bet;
			break;
		}
		else if (i == 37 && playerBets[numCtr].num != wheelNums[i])
		{
			cout << "\n\tYou have entered an invalid number. Please choose again." << endl;
			cin.ignore();
			cin.clear();
			playerBets[numCtr].num.clear();
			chooseNum();
			break;
		}
	}
}

// ask the player if they want to keep choosing numbers and betting
bool keepChoosing()
{
	if (numCtr == 37 || bank == 0)
	{
		cout << "\n\tYou cannot place anymore bets." << endl;
		return false;
	}

	cout << "\n   Would you like to choose another number to bet on?\n";
	cout << "\t\t1. Yes\n";
	cout << "\t\t2. No\n\t";
	cin >> choice;

	while (choice != 1 && choice != 2)
	{
		keepChoosing();
	}
	
	if (choice == 1)
	{
		numCtr++;
		return true;
	}
	else
		return false;
}

// function to display players bets and numbers bet on
void displayBets()
{
	for (i = 0; i < 38; i++)
	{
		if (!empty(playerBets[i].num))
		{
			cout << "\n\tYou have bet $" << playerBets[i].amount << ", on number " << playerBets[i].num << "." << endl;
		}
	}
}

// check players numbers against winning and display message for each
void checkAndDisplay(string str)
{
	for (i = 0; i < 38; i++)
	{
		Sleep(500);
		if (empty(playerBets[i].num))
		{
			break;
		}
		else if (playerBets[i].num == str)
		{
			cout << "\n\n\tYou have matched the winning number! " << playerBets[i].num << endl;
			cout << "\n\tYou won $" << playerBets[i].amount * 36;
			bank += playerBets[i].amount * 36;
		}
		else
		{
			cout << "\n\n\tThis number was a bust. " << playerBets[i].num << endl;
			cout << "\n\tYou lost $" << playerBets[i].amount;
		}
	}
}

// clear player bets and nums for roulette
void clearPlayerBets()
{
	for (i = 0; i < 38; i++)
	{
		if (empty(playerBets[i].num))
		{
			break;
		}
		else
		{
			playerBets[i].num.clear();
			playerBets[i].amount = 0;
		}
	}
}