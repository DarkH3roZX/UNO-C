#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

/*
 Structures
 */
// Card Linked List
typedef struct Node {
	int cardNumber;
	int number; // -1 if it's not a normal card type

	char type[8];
	char color[8];

	struct Node *next;
} Node;

// Linked List Temp
typedef struct {
	int cardNumber;
	int number;

	char type[8];
	char color[8];
} Temp1;

// Player Status
typedef struct {
	int podiumPlace;
	int playerNameInt;

	bool isAlreadyWin;
} Status;

// File Write
/*
typedef struct {
	int cardNumber;
	int number;

	char type[8];
	char color[8];
} FileWrite;
*/

// Tester
/*
typedef struct {
	int cardNumber;
	int number;

	char type[8];
	char color[8];
} Tester;
*/

// Function Prototypes
void logo();
void rpsUI();
char rpsIntToChar(int x);
int rpsWinnerFinder(char choice1, char choice2, int player1, int player2);
void insertAtEnd(Node** headRef, Node** tailRef, int* count, int cardNum, int num, char* type, char* color);
void deleteAtBeginning(Node** headRef, int* count);
void deleteAtMiddle(Node** headRef, int* count, int index);
void deleteAtEnd(Node** headRef, Node** tailRef, int* count);
void cardSave(Node* node, Temp1 *linkedListTemp, int index);
void printList(Node* node);
char * playerNumberToString(int x);
void doReverse(bool *reverse);
void doSkip(int *roundsPtr, int turnCycle[], int playerTurn, bool reversed);
void doWild(int turnCycle[], int playerTurn, bool *tempBool, Temp1 *linkedListTemp, bool isBotHaveTheColor[]);
void cardPrint(Temp1 linkedListTemp);
bool canInputCard(Node* node, Temp1 linkedListTemp, int playerCards);
bool canAddAnotherPlus(Node* node, bool discardPlus4, int playerCards);
void cardPickDelete(int *cardPicks, int *cardPicksDeclaration);
void totalColorsDelete(int *totalColors);

// Main Code
int main() {
	/*
	 Variables
	 */

	// File Pointers
	FILE *cards; // Card file

	// Card Deck Variables
	Node *cardHead = NULL, *cardTail = NULL;
	int drawPileCount = 0;

	// Discard Pile Variables
	Node *discardHead = NULL, *discardTail = NULL;
	int discardPileCount = 0;

	// For Loop Variables
	int i, j, k, l;

	// Warp Variables
	int mainWarp;
	int instructionsWarp;
	int gameWarp;
	int botWarp;
	int plusWarp;
	int grabWarp;

	// Declaration Variables
	char startGameWord[16];

	// Temporary Variables;
	int tempInt;
	char tempChar;
	char tempString[100];
	bool tempBool;
	Temp1 linkedListTemp;
	Temp1 linkedListTemp2;
	
	// Rock Paper Scissors Variables
	int winnerRPS;
	int losersRPS[2];
	int winnersRPS[2];
	
	char playerChoicesRPS[4];

	bool rpsEnd;

	// Game Variables
	int rounds;
	int playersWon;
	int playerTurn;
	int cardAmountInput;
	int currPlus;
	int currMinus;
	int playersLeft;
	int turnCycle[4];
	int cardPicks[8];

	char podiumPlaceNames[4][7];

	bool reversed;
	bool roundZero;
	bool validSkip;
	bool inPlusCondition;
	bool canInputPlusCard;
	bool discardPlus4;

	Status playerStats[4];

	// AI Variables
	int botTotalPlus2;
	int botTotalPlus4;
	int biggestAmount;
	int cardNameInt;
	int totalColors[5];
	int typeAmounts[15];
	int wildCardAmount[2];
	int cardAmount[4][13];

	bool isBotWantToStack;
	bool isSomeoneInUNO;
	bool isBotHaveTheColor[4];

	// Validation Variables
	int maxCardAllowed;
	int allowedCardCount;
	int cardPicksDeclaration[8];
	
	bool validInput;
	bool canTakeCard;

	// Player Card Linked List
	Node *playerHead = NULL, *playerTail = NULL;
	Node *bot1Head = NULL, *bot1Tail = NULL;
	Node *bot2Head = NULL, *bot2Tail = NULL;
	Node *bot3Head = NULL, *bot3Tail = NULL;

	// Player card variables
	int playerCards;
	int bot1Cards;
	int bot2Cards;
	int bot3Cards;

	// RNG Variavles
	int rng1, rng2, rng3;

	// srand
	srand(time(NULL));
	
	/*
	 Utilities Code
	 */

	// File Write
	/*
	FileWrite fw;

	cards = fopen("cards.evan", "wb");

	for (i = 0; i < 112; i++) {
		scanf("%d %d %s %s", &fw.cardNumber, &fw.number, fw.type, fw.color);
		fwrite(&fw, sizeof(fw), 1, cards);
	}
	
	fclose(cards);
	*/

	// Putting cards to draw pile
	cards = fopen("cards.evan", "rb");

	if (cards == NULL) {
		logo();

		printf("Cards file not found!");
		getchar();

		return -1;
	}

	rewind(cards);

	for (i = 0; i < 112; i++) {
		fread(&linkedListTemp, sizeof(linkedListTemp), 1, cards);
		insertAtEnd(&cardHead, &cardTail, &drawPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
	}

	fclose(cards);

	//printList(cardHead);
	//getchar();

	// Puts the playerNameInt
	for (i = 0; i < 4; i++)
		playerStats[i].playerNameInt = i + 1;

	/*
	 Main Code
	 */
	do
	{
		do
		{
			system("cls");
			logo();
			
			printf("Where do you want to go?\n");
			printf("1. Play UNO\n");
			printf("2. How To Play\n");
			printf("3. Credits\n");
			printf("4. Exit\n\n");
			
			printf("Your Choice : ");
			scanf("%d", &mainWarp);
			while (getchar() != '\n');
		}
		while (mainWarp != 1 && mainWarp != 2 && mainWarp != 3 && mainWarp != 4);

		// Play Game
		if (mainWarp == 1) {
			// Start Game Menu
			do
			{
				// tempString Resetter
				strcpy(tempString, "");

				system("cls");
				logo();

				printf("Type \"UNO\" to start : ");
				scanf("%s", startGameWord);
				while (getchar() != '\n');

				for (i = 0; i < strlen(startGameWord); i++)
					tempString[i] = tolower(startGameWord[i]);

				strcpy(startGameWord, tempString);
			}
			while (strcmp(startGameWord, "uno") != 0);
			
			// RPS Round 1
			do
			{
				// UI
				do
				{
					system("cls");
					logo();

					rpsUI(1);

					printf("You\n");
					printf("Vs.\n");
					printf("Bot 1\n\n");

					printf("r. Rock\n");
					printf("p. Paper\n");
					printf("s. Scissors\n");
					printf("Your choice : ");
					scanf("%c", &playerChoicesRPS[0]);
					while (getchar() != '\n');
				}
				while (playerChoicesRPS[0] != 'r' && playerChoicesRPS[0] != 'p' && playerChoicesRPS[0] != 's');

				// Opponent Picks
				playerChoicesRPS[1] = rpsIntToChar(rand() % 3);

				// This program finds a winner
				winnerRPS = rpsWinnerFinder(playerChoicesRPS[0], playerChoicesRPS[1], 1, 2);

				// If the RPS is a tie
				if (winnerRPS == 0) {
					printf("You and your opponents pick a same choice, press \'Enter\' to play again!");
					getchar();

					continue;
				}

				// Prints what the player choose
				printf("You pick ");

				if (playerChoicesRPS[0] == 'r')
					printf("Rock");
				else if (playerChoicesRPS[0] == 'p')
					printf("Paper");
				else if (playerChoicesRPS[0] == 's')
					printf("Scissors");

				// Prints what bot 1 chooses
				printf("\nBot 1 picks ");

				if (playerChoicesRPS[1] == 'r')
					printf("Rock");
				else if (playerChoicesRPS[1] == 'p')
					printf("Paper");
				else if (playerChoicesRPS[1] == 's')
					printf("Scissors");

				puts("\n");

				// If Player Wins
				if (winnerRPS == 1) {
					winnersRPS[0] = 1;
					losersRPS[0] = 2;

					printf("You WIN!\n");
					printf("Press \'Enter\' To Continue!");
					getchar();
				}

				// If Bot 1 Wins
				else {
					winnersRPS[0] = 2;
					losersRPS[0] = 1;

					printf("You LOSE!\n");
					printf("Press \'Enter\' To Continue!");
					getchar();
				}

				break;
			}
			while (true);

			// RPS Round 2
			do
			{
				// UI
				system("cls");
				logo();

				rpsUI(2);

				printf("Bot 2\n");
				printf("Vs.\n");
				printf("Bot 3\n\n");

				printf("Press \'Enter\' for Bot 2 and 3 to play RPS!");
				getchar();

				// Bot 2 and 3 Picks
				playerChoicesRPS[2] = rpsIntToChar(rand() % 3);
				playerChoicesRPS[3] = rpsIntToChar(rand() % 3);
				
				// If bot 2 and 3 picks the same choice
				if (playerChoicesRPS[2] == playerChoicesRPS[3]) {
					if (playerChoicesRPS[2] == 'r')
						printf("Both Bot 2 and 3 picks rock, it\'s a tie");
					else if (playerChoicesRPS[2] == 'p')
						printf("Both Bot 2 and 3 picks paper, it\'s a tie");
					else if (playerChoicesRPS[2] == 's')
						printf("Both Bot 2 and 3 picks scissors, it\'s a tie");
					
					printf("\nPress \'Enter\' to continue!");
					getchar();

					continue;
				}

				// Prints what the player choose
				printf("Bot 2 picks ");

				if (playerChoicesRPS[2] == 'r')
					printf("Rock");
				else if (playerChoicesRPS[2] == 'p')
					printf("Paper");
				else if (playerChoicesRPS[2] == 's')
					printf("Scissors");

				// Prints what bot 1 chooses
				printf("\nBot 3 picks ");

				if (playerChoicesRPS[3] == 'r')
					printf("Rock");
				else if (playerChoicesRPS[3] == 'p')
					printf("Paper");
				else if (playerChoicesRPS[3] == 's')
					printf("Scissors");

				puts("\n");

				// This program finds a winner
				winnerRPS = rpsWinnerFinder(playerChoicesRPS[2], playerChoicesRPS[3], 3, 4);

				// If Bot 2 Wins
				if (winnerRPS == 3) {
					winnersRPS[1] = 3;
					losersRPS[1] = 4;

					printf("Bot 2 Wins!\n");
					printf("Press \'Enter\' To Continue!");
					getchar();
				}

				// If Bot 3 Wins
				else {
					winnersRPS[1] = 4;
					losersRPS[1] = 3;

					printf("Bot 3 Wins!\n");
					printf("Press \'Enter\' To Continue!");
					getchar();
				}

				break;
			}
			while (true);

			//RPS Round 3 (Loser vs Loser)
			do
			{				
				// If player Loses Round 1
				if (winnersRPS[0] != 1) {
					do
					{
						// UI
						system("cls");
						logo();

						rpsUI(3);
					
						printf("Player\n");
						printf("Vs.\n");
						printf("Bot %d\n\n", losersRPS[1] - 1);

						printf("r. Rock\n");
						printf("p. Paper\n");
						printf("s. Scissors\n");
						printf("Your choice : ");
						scanf("%c", &playerChoicesRPS[0]);
						while (getchar() != '\n');
					}
					while (playerChoicesRPS[0] != 'r' && playerChoicesRPS[0] != 'p' && playerChoicesRPS[0] != 's');

					playerChoicesRPS[1] = rpsIntToChar(rand() % 3);
				}
				
				// If player Wins Round 1
				else {
					// UI
					system("cls");
					logo();

					rpsUI(3);

					printf("Bot %d\n", losersRPS[0] - 1);
					printf("Vs.\n");
					printf("Bot %d\n\n", losersRPS[1] - 1);

					printf("Press \'Enter\' for Bot %d and %d to play RPS!", losersRPS[0] - 1, losersRPS[1] - 1);
					getchar();

					playerChoicesRPS[0] = rpsIntToChar(rand() % 3);
					playerChoicesRPS[1] = rpsIntToChar(rand() % 3);
				}

				// Finding a RPS winner
				winnerRPS = rpsWinnerFinder(playerChoicesRPS[0], playerChoicesRPS[1], losersRPS[0], losersRPS[1]);

				// Tie condition
				if (winnerRPS == 0) {
					if (playerChoicesRPS[0] == 'r') {
						if (winnersRPS[0] != 1)
							printf("You and Bot %d picks rock, it\'s a tie", losersRPS[1] - 1);
						else
							printf("Bot %d and Bot %d picks rock, it\'s a tie", losersRPS[0] - 1, losersRPS[1] - 1);
					}
					else if (playerChoicesRPS[0] == 'p') {
						if (winnersRPS[0] != 1)
							printf("You and Bot %d picks paper, it\'s a tie", losersRPS[1] - 1);
						else
							printf("Bot %d and Bot %d picks paper, it\'s a tie", losersRPS[0] - 1, losersRPS[1] - 1);
					}
					else if (playerChoicesRPS[0] == 's') {
						if (winnersRPS[0] != 1)
							printf("You and Bot %d picks scissors, it\'s a tie", losersRPS[1] - 1);
						else
							printf("Bot %d and Bot %d picks scissors, it\'s a tie", losersRPS[0] - 1, losersRPS[1] - 1);
					}
					
					printf("\nPress \'Enter\' to continue!");
					getchar();

					continue;
				}

				// If Player 1 Wins
				if (winnerRPS == losersRPS[0]) {
					turnCycle[2] = losersRPS[0];
					turnCycle[3] = losersRPS[1];

					if (winnersRPS[0] != 1)
						printf("You win and get the 3rd turn!");
					else
						printf("Bot %d win and get the 3rd turn!", winnerRPS - 1);
				}

				// If Player 2 Wins
				else {
					turnCycle[2] = losersRPS[1];
					turnCycle[3] = losersRPS[0];

					if (winnersRPS[0] != 1)
						printf("You Lose and get the 4th turn!");
					else
						printf("Bot %d win and get the 3rd turn!", winnerRPS - 1);
				}

				printf("\nPress \'Enter\' to continue!");
				getchar();

				break;
			}
			while (true);
			
			//RPS Round 4 (Winner vs Winner)
			do
			{
				// If player Wins Round 1
				if (winnersRPS[0] == 1) {
					do
					{
						// UI
						system("cls");
						logo();

						rpsUI(4);
					
						printf("Player\n");
						printf("Vs.\n");
						printf("Bot %d\n\n", winnersRPS[1] - 1);

						printf("r. Rock\n");
						printf("p. Paper\n");
						printf("s. Scissors\n");
						printf("Your choice : ");
						scanf("%c", &playerChoicesRPS[2]);
						while (getchar() != '\n');
					}
					while (playerChoicesRPS[2] != 'r' && playerChoicesRPS[2] != 'p' && playerChoicesRPS[2] != 's');

					playerChoicesRPS[3] = rpsIntToChar(rand() % 3);
				}
				
				// If player Loses Round 1
				else {
					// UI
					system("cls");
					logo();

					rpsUI(3);

					printf("Bot %d\n", winnersRPS[0] - 1);
					printf("Vs.\n");
					printf("Bot %d\n\n", winnersRPS[1] - 1);

					printf("Press \'Enter\' for Bot %d and %d to play RPS!", winnersRPS[0] - 1, winnersRPS[1] - 1);
					getchar();

					playerChoicesRPS[2] = rpsIntToChar(rand() % 3);
					playerChoicesRPS[3] = rpsIntToChar(rand() % 3);
				}

				// Finding a RPS winner
				winnerRPS = rpsWinnerFinder(playerChoicesRPS[2], playerChoicesRPS[3], winnersRPS[0], winnersRPS[1]);

				// Tie condition
				if (winnerRPS == 0) {
					if (playerChoicesRPS[2] == 'r') {
						if (winnersRPS[0] == 1)
							printf("You and Bot %d picks rock, it\'s a tie", winnersRPS[1] - 1);
						else
							printf("Bot %d and Bot %d picks rock, it\'s a tie", winnersRPS[0] - 1, winnersRPS[1] - 1);
					}
					else if (playerChoicesRPS[2] == 'p') {
						if (winnersRPS[0] == 1)
							printf("You and Bot %d picks paper, it\'s a tie", winnersRPS[1] - 1);
						else
							printf("Bot %d and Bot %d picks paper, it\'s a tie", winnersRPS[0] - 1, winnersRPS[1] - 1);
					}
					else if (playerChoicesRPS[2] == 's') {
						if (winnersRPS[0] == 1)
							printf("You and Bot %d picks scissors, it\'s a tie", winnersRPS[1] - 1);
						else
							printf("Bot %d and Bot %d picks scissors, it\'s a tie", winnersRPS[0] - 1, winnersRPS[1] - 1);
					}
					
					printf("\nPress \'Enter\' to continue!");
					getchar();

					continue;
				}

				// If Player 1 Wins
				if (winnerRPS == winnersRPS[0]) {
					turnCycle[0] = winnersRPS[0];
					turnCycle[1] = winnersRPS[1];

					if (winnersRPS[0] == 1)
						printf("You Win and get the 1st turn!");
					else
						printf("Bot %d win and get the 1st turn!", winnerRPS - 1);
				}

				// If Player 2 Wins
				else {
					turnCycle[0] = winnersRPS[1];
					turnCycle[1] = winnersRPS[0];

					if (winnersRPS[0] == 1)
						printf("You Lose and get the 2nd turn!");
					else
						printf("Bot %d win and get the 1st turn!", winnerRPS - 1);
				}

				printf("\nPress \'Enter\' to continue!");
				getchar();

				break;
			}
			while (true);

			// Turn display
			system("cls");
			logo();

			printf(" Turns \n");
			printf("=======\n\n");

			for (i = 0; i < 4; i++)
				printf("%d. %s\n", i + 1, playerNumberToString(turnCycle[i]));

			printf("\nPress \'Enter\' to continue!");
			getchar();

			// Game Resetter
			reversed = false;
			rounds = 0;
			playersWon = 0;
			playerCards = 0;
			bot1Cards = 0;
			bot2Cards = 0;
			bot3Cards = 0;
			playersLeft = 4;
			roundZero = true;
			tempBool = true;
			currPlus = 0;
			inPlusCondition = false;
			canTakeCard = true;

			for (i = 0; i < 4; i++) {
				playerStats[i].isAlreadyWin = false;
				playerStats[i].podiumPlace = 0;
			}

			// Gives the players cards
			for (i = 0; i < 28; i++) {
				// Pick a random card from draw pile
				rng1 = rand() % drawPileCount;

				// Saves card value
				cardSave(cardHead, &linkedListTemp, rng1);

				// Putting player cards
				if (i % 4 == 0)
					insertAtEnd(&playerHead, &playerTail, &playerCards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

				// Putting bot 1 cards
				else if (i % 4 == 1)
					insertAtEnd(&bot1Head, &bot1Tail, &bot1Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

				// Putting bot 2 cards
				else if (i % 4 == 2)
					insertAtEnd(&bot2Head, &bot2Tail, &bot2Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

				// Putting bot 3 cards
				else if (i % 4 == 3)
					insertAtEnd(&bot3Head, &bot3Tail, &bot3Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

				// Deletes the card from draw pile
				if (rng1 == 0)
					deleteAtBeginning(&cardHead, &drawPileCount);
				else if (rng1 == drawPileCount - 1)
					deleteAtEnd(&cardHead, &cardTail, &drawPileCount);
				else
					deleteAtMiddle(&cardHead, &drawPileCount, rng1);
			}

			// Puts 1st card in a discard pile
			while (true) {
				// Picks a random card from draw pile
				rng1 = rand() % drawPileCount;

				// Saves card value
				cardSave(cardHead, &linkedListTemp, rng1);

				// Check if the card is unvalid to be put in the discard pile
				if (strcmp(linkedListTemp.type, "+4") == 0)
					continue;

				/*
				linkedListTemp.number = -1;
				strcpy(linkedListTemp.type, "Reverse");
				strcpy(linkedListTemp.color, "Blue");
				*/				

				// Putting a card
				insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

				// Deletes the card from draw pile
				if (rng1 == 0)
					deleteAtBeginning(&cardHead, &drawPileCount);
				else if (rng1 == drawPileCount - 1)
					deleteAtEnd(&cardHead, &cardTail, &drawPileCount);
				else
					deleteAtMiddle(&cardHead, &drawPileCount, rng1);
				
				break;
			}

			/*
			 Game Code
			 */
			do
			{
				// Reset
				playerTurn = rounds % 4;

				// This program makes the code doesn't run when a player in a turn already win
				if (playerStats[turnCycle[playerTurn] - 1].isAlreadyWin) {
					if (reversed)
						rounds--;
					else
						rounds++;
					
					if (rounds < 0)
						rounds = 3;
					
					if (rounds > 4000)
						rounds = 1;
					
					continue;
				}

				// Endgame
				if (playersLeft == 1 && !playerStats[turnCycle[playerTurn] - 1].isAlreadyWin) {
					if (turnCycle[playerTurn] == 1)
						printf("You lose and get 4th place!");
					else 
						printf("Bot %d lose and get 4th place!", turnCycle[playerTurn] - 1);
					
					getchar();
					
					printf("Game ends, press \'Enter\' to continue");
					getchar();

					playerStats[turnCycle[playerTurn] - 1].podiumPlace = 4;

					break;
				}

				// Logo Input
				system("cls");
				logo();

				// Turn display
				if (reversed)
					printf("Players (reversed):\n");
				else
					printf("Players:\n");

				for (i = 0; i < 4; i++) {
					// Puts a bracket for the player's turn
					if (playerTurn == i) {
						printf("[");
						printf("%s", playerNumberToString(turnCycle[i]));
						printf("] ");
					}
					else
						printf(" %s  ", playerNumberToString(turnCycle[i]));
					
					if (playerStats[turnCycle[i] - 1].isAlreadyWin)
						printf("(UNO GAME!)");
					
					puts("");
				}

				// Displays the current card
				if (tempBool)
					cardSave(discardHead, &linkedListTemp, discardPileCount - 1);
				else
					tempBool = true;

				printf("\nCurrent Card : ");
				cardPrint(linkedListTemp);
				puts("");

				// Displays the cards
				printf("\n Cards \n");
				printf("=======\n");

				// Prints the amount of bot 1 cards
				printf("\nBot 1 : ");

				/*
				for (i = 0; i < bot1Cards; i++)
					printf("[] ");
				*/

				puts("");
				printList(bot1Head);
				
				// Prints the amount of bot 2 cards
				printf("\nBot 2 : ");

				/*
				for (i = 0; i < bot2Cards; i++)
					printf("[] ");
				*/
				
				puts("");
				printList(bot2Head);
				
				// Prints the amount of bot 3 cards
				printf("\nBot 3 : ");

				/*
				for (i = 0; i < bot3Cards; i++)
					printf("[] ");
				*/

				puts("");
				printList(bot3Head);
				
				puts("\n");

				printf("You:\n");
				printList(playerHead);

				// If the first card is an action card
				if (roundZero) {
					if (strcmp(linkedListTemp.type, "Reverse") == 0) {
						doReverse(&reversed);
						roundZero = false;
					}
					else if (strcmp(linkedListTemp.type, "Skip") == 0) {
						doSkip(&rounds, turnCycle, playerTurn, reversed);
						roundZero = false;

						continue;
					}
					else if (strcmp(linkedListTemp.type, "+2") == 0) {
						if (turnCycle[playerTurn] == 1)
							printf("You ");
						else if (turnCycle[playerTurn] == 2)
							printf("Bot 1 ");
						else if (turnCycle[playerTurn] == 3)
							printf("Bot 2 ");
						else if (turnCycle[playerTurn] == 4)
							printf("Bot 3 ");
						
						printf("got 2 cards, press \'Enter\' to continue");
						getchar();
						
						// +2 algorithm
						for (i = 0; i < 2; i++) {
							// Pick a random card from draw pile
							rng1 = rand() % drawPileCount;

							// Saves card value
							cardSave(cardHead, &linkedListTemp, rng1);

							// Putting player cards
							if (turnCycle[0] == 1)
								insertAtEnd(&playerHead, &playerTail, &playerCards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

							// Putting bot 1 cards
							else if (turnCycle[0] == 2)
								insertAtEnd(&bot1Head, &bot1Tail, &bot1Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

							// Putting bot 2 cards
							else if (turnCycle[0] == 3)
								insertAtEnd(&bot2Head, &bot2Tail, &bot2Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

							// Putting bot 3 cards
							else if (turnCycle[0] == 4)
								insertAtEnd(&bot3Head, &bot3Tail, &bot3Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

							// Deletes the card from draw pile
							if (rng1 == 0)
								deleteAtBeginning(&cardHead, &drawPileCount);
							else if (rng1 == drawPileCount - 1)
								deleteAtEnd(&cardHead, &cardTail, &drawPileCount);
							else
								deleteAtMiddle(&cardHead, &drawPileCount, rng1);
						}

						// Skip Algorithm
						rounds++;
						roundZero = false;

						continue;
					}
					else if (strcmp(linkedListTemp.type, "Wild") == 0) {
						// Cleans isBotHaveTheColor
						for (i = 0; i < 4; i++)
							isBotHaveTheColor[i] = false;
						
						// Checks if the bot have the color
						for (i = 0; i < turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards); i++) {
							if (turnCycle[playerTurn] == 2)
								cardSave(bot1Head, &linkedListTemp2, i);
							else if (turnCycle[playerTurn] == 3)
								cardSave(bot2Head, &linkedListTemp2, i);
							else if (turnCycle[playerTurn] == 4)
								cardSave(bot3Head, &linkedListTemp2, i);
							
							if (strcmp(linkedListTemp2.color, "Blue") == 0)
								isBotHaveTheColor[0] = true;
							else if (strcmp(linkedListTemp2.color, "Red") == 0)
								isBotHaveTheColor[1] = true;
							else if (strcmp(linkedListTemp2.color, "Green") == 0)
								isBotHaveTheColor[2] = true;
							else if (strcmp(linkedListTemp2.color, "Yellow") == 0)
								isBotHaveTheColor[3] = true;
						}

						doWild(turnCycle, playerTurn, &tempBool, &linkedListTemp, isBotHaveTheColor);

						if (discardPileCount <= 1)
							deleteAtBeginning(&discardHead, &discardPileCount);
						else 
							deleteAtEnd(&discardHead, &discardTail, &discardPileCount);

						insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

						roundZero = false;

						continue;
					}
					else
						roundZero = false;
				}

				// If the game is in plus condition
				if (inPlusCondition) {
					cardSave(discardHead, &linkedListTemp, discardPileCount - 1);

					// Checks so the player can't input a +2 if the discard pile is a +4
					if (strcmp(linkedListTemp.type, "+4") == 0)
						discardPlus4 = true;
					else
						discardPlus4 = false;
					
					// Player Turn
					if (turnCycle[playerTurn] == 1) {
						canInputPlusCard = canAddAnotherPlus(playerHead, discardPlus4, playerCards);

						// If the player can input a plus card
						if (canInputPlusCard) {
							// UI
							printf("Current Plus = %d\n", currPlus);
							printf("1. Stack it\n");
							printf("2. Give Up!\n");

							printf("Your Choice : ");
							scanf("%d", &plusWarp);
							while (getchar() != '\n');

							if (plusWarp != 1 && plusWarp != 2)
								continue;
							
							// Stack It
							if (plusWarp == 1) {
								// Puts the card amount
								validInput = true;

								// UI
								printf("Choose the amount of cards that you want to input : ");
								scanf("%d", &cardAmountInput);
								while (getchar() != '\n');

								// If user inputs invalid value
								if (cardAmountInput < 1 || cardAmountInput > playerCards) {
									printf("Invalid Input\n");
									validInput = false;

									getchar();

									continue;
								}

								cardPickDelete(cardPicks, cardPicksDeclaration);

								// Inputs the card
								printf("Choose the cards that you want to input:\n");

								for (i = 0; i < cardAmountInput; i++) {
									scanf("%d", &cardPicks[i]);
									cardPicks[i]--;

									cardPicksDeclaration[cardPicks[i]]++;

									// Checks so the player can't input the same card
									if (cardPicksDeclaration[cardPicks[i]] > 1)
										validInput = false;
								}

								while (getchar() != '\n');

								// Fixes the card index
								currMinus = 0;

								for (i = 0; i < cardAmountInput; i++) {
									tempInt = cardPicks[i];

									for (j = i + 1; j < cardAmountInput; j++) {
										if (cardPicks[j] > tempInt)
											cardPicks[j]--;
									}
								}

								if (!validInput) {
									printf("Invalid Input!");
									getchar();

									continue;
								}

								// Checks if the card inputted is valid or not
								for (i = 0; i < cardAmountInput; i++) {
									cardSave(playerHead, &linkedListTemp, cardPicks[i]);

									if (i != 0)
										cardSave(playerHead, &linkedListTemp2, cardPicks[i - 1]);
									else
										strcpy(linkedListTemp2.type, linkedListTemp.type);

									if ((strcmp(linkedListTemp.type, "+2") != 0 && strcmp(linkedListTemp.type, "+4") != 0) || (i != 0 && strcmp(linkedListTemp.type, linkedListTemp2.type) != 0) || (strcmp(linkedListTemp.type, "+2") == 0 && discardPlus4) || (strcmp(linkedListTemp.type, "+4") == 0 && cardAmountInput > 1)) {
										validInput = false;

										break;
									}
								}

								if (!validInput) {
									printf("Invalid Input!");
									getchar();

									continue;
								}

								// Puts a card into a discard pile
								for (i = 0; i < cardAmountInput; i++) {
									// Adds the current plus
									if (strcmp(linkedListTemp.type, "+2") == 0)
										currPlus += 2;
									else if (strcmp(linkedListTemp.type, "+4") == 0) {
										currPlus += 4;

										doWild(turnCycle, playerTurn, &tempBool, &linkedListTemp, isBotHaveTheColor);
										
										// Replaces The Discard Pile Wild
										if (discardPileCount <= 1)
											deleteAtBeginning(&discardHead, &discardPileCount);
										else 
											deleteAtEnd(&discardHead, &discardTail, &discardPileCount);
									}

									// Puts a card into a draw pile
									cardSave(playerHead, &linkedListTemp, cardPicks[i]);
									insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

									// Deletes the card from player's pile
									if (cardPicks[i] == 0)
										deleteAtBeginning(&playerHead, &playerCards);
									else if (cardPicks[i] == playerCards - 1)
										deleteAtEnd(&playerHead, &playerTail, &playerCards);
									else
										deleteAtMiddle(&playerHead, &playerCards, cardPicks[i]);
								}
							}
						}

						// If Not
						if (!canInputPlusCard || plusWarp == 2) {
							printf("You got %d cards, Press \'Enter\' to continue", currPlus);
							getchar();

							// Puts the card back to the draw pile if it runs out
							if (drawPileCount < currPlus) {
								for (i = 0; i < discardPileCount - 1; i++) {
									cardSave(discardHead, &linkedListTemp, i);

									if (strcmp(linkedListTemp.type, "Wild") == 0 || strcmp(linkedListTemp.type, "+4") == 0)
										strcpy(linkedListTemp.color, "Black");

									insertAtEnd(&cardHead, &cardTail, &drawPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
									deleteAtBeginning(&discardHead, &discardPileCount);
								}
							}

							// Adds the card to the player
							for (i = 0; i < currPlus; i++) {
								rng1 = rand() % drawPileCount;

								cardSave(cardHead, &linkedListTemp, rng1);
								insertAtEnd(&playerHead, &playerTail, &playerCards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

								if (rng1 == 0)
									deleteAtBeginning(&cardHead, &drawPileCount);
								else if (rng1 == drawPileCount - 1)
									deleteAtEnd(&cardHead, &cardTail, &drawPileCount);
								else
									deleteAtMiddle(&cardHead, &drawPileCount, rng1);
							}

							inPlusCondition = false;
							currPlus = 0;
						}
					}

					// Bot's Turn
					else {
						isBotWantToStack = false;
						isSomeoneInUNO = false;

						// Checks if the bot can stack a plus card or not
						if (turnCycle[playerTurn] == 2)
							canInputPlusCard = canAddAnotherPlus(bot1Head, discardPlus4, bot1Cards);
						else if (turnCycle[playerTurn] == 3)
							canInputPlusCard = canAddAnotherPlus(bot2Head, discardPlus4, bot2Cards);
						else if (turnCycle[playerTurn] == 4)
							canInputPlusCard = canAddAnotherPlus(bot3Head, discardPlus4, bot3Cards);
						
						// Condition if there's a player who have 1 card left, so the bot will add the plus card
						if (playerCards == 1 || bot1Cards == 1 || bot2Cards == 1 || bot3Cards == 1) {
							isBotWantToStack = true;
							isSomeoneInUNO = true;
						}
						
						// Counts the plus card that the bot have
						botTotalPlus2 = 0;
						botTotalPlus4 = 0;

						for (i = 0; i < (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards)); i++) {
							if (turnCycle[playerTurn] == 2)
								cardSave(bot1Head, &linkedListTemp, i);
							else if (turnCycle[playerTurn] == 3)
								cardSave(bot2Head, &linkedListTemp, i);
							else if (turnCycle[playerTurn] == 4)
								cardSave(bot3Head, &linkedListTemp, i);
							
							if (strcmp(linkedListTemp.type, "+2") == 0)
								botTotalPlus2++;
							else if (strcmp(linkedListTemp.type, "+4") == 0)
								botTotalPlus4++;
						}

						// If the plus is already too big, then the bot will put a card
						if (botTotalPlus2 > 0 || (botTotalPlus4 > 0 && currPlus > 4))
							isBotWantToStack = true;
						
						// Decides whether the bot will put a +4 or not
						if ((botTotalPlus2 == 0 && botTotalPlus4 > 0 && currPlus > 4) || (isSomeoneInUNO && botTotalPlus4 > 0))
							discardPlus4 = true;

						// Decides the bot choice
						botWarp = isBotWantToStack && canInputPlusCard ? 0 : 1;
						
						// Stack It
						if (botWarp == 0) {
							// This code decides the amount of plus cards the bot will input
							if (!discardPlus4 && 16 - botTotalPlus2 * 2 == currPlus)
								cardAmountInput = botTotalPlus2;
							else
								cardAmountInput = 1;

							// Inputs cardPicks
							tempInt = 0;

							for (i = 0; i < playerCards; i++) {
								if (turnCycle[playerTurn] == 2)
									cardSave(bot1Head, &linkedListTemp, cardPicks[i]);
								else if (turnCycle[playerTurn] == 3)
									cardSave(bot2Head, &linkedListTemp, cardPicks[i]);
								else if (turnCycle[playerTurn] == 4)
									cardSave(bot3Head, &linkedListTemp, cardPicks[i]);

								if ((strcmp(linkedListTemp.type, "+2") == 0 && !discardPlus4) || (strcmp(linkedListTemp.type, "+4") == 0 && discardPlus4)) {
									cardPicks[tempInt] = i;
									tempInt++;
								}

								if (tempInt == cardAmountInput)
									break;
							}

							if (strcmp(linkedListTemp.type, "+4") == 0)
								discardPlus4 = true;

							// Fixes the card index
							currMinus = 0;

							for (i = 0; i < cardAmountInput; i++) {
								tempInt = cardPicks[i];

								for (j = i + 1; j < cardAmountInput; j++) {
									if (cardPicks[j] > tempInt)
										cardPicks[j]--;
								}
							}
							
							// Puts a card into a discard pile
							for (i = 0; i < cardAmountInput; i++) {
								// Puts a card into a draw pile
								if (turnCycle[playerTurn] == 2)
									cardSave(bot1Head, &linkedListTemp, cardPicks[i]);
								else if (turnCycle[playerTurn] == 3)
									cardSave(bot2Head, &linkedListTemp, cardPicks[i]);
								else if (turnCycle[playerTurn] == 4)
									cardSave(bot3Head, &linkedListTemp, cardPicks[i]);
								
								insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

								// Adds the current plus
								if (strcmp(linkedListTemp.type, "+2") == 0)
									currPlus += 2;
								else {
									currPlus += 4;

									doWild(turnCycle, playerTurn, &tempBool, &linkedListTemp, isBotHaveTheColor);
										
									// Replaces The Discard Pile Wild
									if (discardPileCount <= 1)
										deleteAtBeginning(&discardHead, &discardPileCount);
									else 
										deleteAtEnd(&discardHead, &discardTail, &discardPileCount);
								}

								// Deletes the card from bot's pile
								if (cardPicks[i] == 0) {
									if (turnCycle[playerTurn] == 2)
										deleteAtBeginning(&bot1Head, &bot1Cards);
									else if (turnCycle[playerTurn] == 3)
										deleteAtBeginning(&bot2Head, &bot2Cards);
									else if (turnCycle[playerTurn] == 4)
										deleteAtBeginning(&bot3Head, &bot3Cards);
								}
								else if (cardPicks[i] == playerCards - 1) {
									if (turnCycle[playerTurn] == 2)
										deleteAtEnd(&bot1Head, &bot1Tail, &bot1Cards);
									else if (turnCycle[playerTurn] == 3)
										deleteAtEnd(&bot2Head, &bot2Tail, &bot2Cards);
									else if (turnCycle[playerTurn] == 4)
										deleteAtEnd(&bot3Head, &bot3Tail, &bot3Cards);
								}
								else {
									if (turnCycle[playerTurn] == 2)
										deleteAtMiddle(&bot1Head, &bot1Cards, cardPicks[0]);
									else if (turnCycle[playerTurn] == 3)
										deleteAtMiddle(&bot2Head, &bot2Cards, cardPicks[0]);
									else if (turnCycle[playerTurn] == 4)
										deleteAtMiddle(&bot3Head, &bot3Cards, cardPicks[0]);
								}
							}

							printf("Bot %d stacks the plus and now the total plus is %d\n", turnCycle[playerTurn] - 1, currPlus);
							printf("Press \'Enter\' to continue");
							getchar();
						}

						// No
						else if (botWarp == 1) {
							printf("Bot %d got %d cards, Press \'Enter\' to continue", turnCycle[playerTurn] - 1, currPlus);
							getchar();

							// Puts the card back to the draw pile if it runs out
							if (drawPileCount < currPlus) {
								for (i = 0; i < discardPileCount - 1; i++) {
									cardSave(discardHead, &linkedListTemp, i);

									if (strcmp(linkedListTemp.type, "Wild") == 0 || strcmp(linkedListTemp.type, "+4") == 0)
										strcpy(linkedListTemp.color, "Black");

									insertAtEnd(&cardHead, &cardTail, &drawPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
									deleteAtBeginning(&discardHead, &discardPileCount);
								}
							}

							// Adds the card to the bot
							for (i = 0; i < currPlus; i++) {
								rng1 = rand() % drawPileCount;

								cardSave(cardHead, &linkedListTemp, rng1);

								if (turnCycle[playerTurn] == 2)
									insertAtEnd(&bot1Head, &bot1Tail, &bot1Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
								else if (turnCycle[playerTurn] == 3)
									insertAtEnd(&bot2Head, &bot2Tail, &bot2Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
								else if (turnCycle[playerTurn] == 4)
									insertAtEnd(&bot3Head, &bot3Tail, &bot3Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

								if (rng1 == 0)
									deleteAtBeginning(&cardHead, &drawPileCount);
								else if (rng1 == drawPileCount - 1)
									deleteAtEnd(&cardHead, &cardTail, &drawPileCount);
								else
									deleteAtMiddle(&cardHead, &drawPileCount, rng1);
							}

							inPlusCondition = false;
							currPlus = 0;
						}
					}
				}

				// If Not In Plus Condition
				else {
					// Player's turn
					if (turnCycle[playerTurn] == 1) {
						// UI
						printf("1. Input a card\n");
						printf("2. Get a card from draw pile\n");

						// Checks if the player can input a card or not
						cardSave(discardHead, &linkedListTemp, discardPileCount - 1);

						printf("Your Choice : ");
						scanf("%d", &gameWarp);
						while (getchar() != '\n');

						if (gameWarp == 1) {
							if (!canInputCard(playerHead, linkedListTemp, playerCards)) {
								printf("You can\'t input a card\n");
								getchar();

								continue;
							}
						}
						else if (gameWarp != 2)
							continue;

						// Input a card
						if (gameWarp == 1) {
							// Puts the card amount
							validInput = true;

							// UI
							printf("Choose the amount of cards that you want to input : ");
							scanf("%d", &cardAmountInput);
							while (getchar() != '\n');

							// If user inputs invalid value
							if (cardAmountInput < 1 || cardAmountInput > playerCards) {
								printf("Invalid Input\n");
								getchar();

								continue;
							}

							cardPickDelete(cardPicks, cardPicksDeclaration);

							// Inputs the card
							printf("Choose the cards that you want to input:\n");

							for (i = 0; i < cardAmountInput; i++) {
								scanf("%d", &cardPicks[i]);
								cardPicks[i]--;

								cardPicksDeclaration[cardPicks[i]]++;

								// Checks so the player can't input the same card
								if (cardPicksDeclaration[cardPicks[i]] > 1)
									validInput = false;
							}

							while (getchar() != '\n');

							if (!validInput) {
								printf("Invalid Input!");
								getchar();

								continue;
							}

							// Checks if the card inputted is valid or not
							for (i = 0; i < cardAmountInput; i++) {
								if (i == 0)
									cardSave(discardHead, &linkedListTemp, discardPileCount - 1);
								else
									cardSave(playerHead, &linkedListTemp, cardPicks[i - 1]);
								
								cardSave(playerHead, &linkedListTemp2, cardPicks[i]);

								// Checks the Wild card
								if (cardAmountInput == 1 && (strcmp(linkedListTemp2.type, "Wild") == 0 || strcmp(linkedListTemp2.type, "+4") == 0))
									break;
								
								// Checks the first card
								if (i == 0 && !((strcmp(linkedListTemp2.type, linkedListTemp.type) == 0 && strcmp(linkedListTemp2.type, "Normal") != 0) || strcmp(linkedListTemp2.color, linkedListTemp.color) == 0 || (linkedListTemp.number == linkedListTemp2.number && linkedListTemp2.number != -1))) {
									validInput = false;

									break;
								}

								// Checks the stacked one
								if (i > 0 && !((strcmp(linkedListTemp2.type, linkedListTemp.type) == 0 && strcmp(linkedListTemp2.type, "Normal") != 0) || (linkedListTemp.number == linkedListTemp2.number && linkedListTemp2.number != -1))) {
									validInput = false;

									break;
								}

								// Wild Check 2
								if ((strcmp(linkedListTemp2.type, "Wild") == 0 || strcmp(linkedListTemp2.type, "+4") == 0) && i > 0) {
									validInput = false;

									break;
								}
							}

							if (!validInput) {
								printf("Invalid Input!");
								getchar();

								continue;
							}

							// Fixes the card index
							currMinus = 0;

							for (i = 0; i < cardAmountInput; i++) {
								tempInt = cardPicks[i];

								for (j = i + 1; j < cardAmountInput; j++) {
									if (cardPicks[j] > tempInt)
										cardPicks[j]--;
								}
							}

							// Puts a card into a discard pile
							for (i = 0; i < cardAmountInput; i++) {
								// Puts a card into a discard pile
								cardSave(playerHead, &linkedListTemp, cardPicks[i]);
								insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

								// If the inputted card is an action card
								if (linkedListTemp.number == -1) {
									// Skip
									if (strcmp(linkedListTemp.type, "Skip") == 0) {
										l = rounds % 4;

										// Checks so the system won't skip the player who have won
										do
										{
											if (reversed)
												l--;
											else
												l++;
											
											if (l == 0)
												l = 3;				

											if (!playerStats[turnCycle[l] - 1].isAlreadyWin)
												break;
										}
										while (true);

										doSkip(&rounds, turnCycle, l, reversed);
									}

									// Reverse
									else if (strcmp(linkedListTemp.type, "Reverse") == 0)
										doReverse(&reversed);

									// +2
									else if (strcmp(linkedListTemp.type, "+2") == 0) {
										currPlus += 2;
										inPlusCondition = true;
									}

									// Wild and +4
									else if (strcmp(linkedListTemp.type, "+4") == 0 || strcmp(linkedListTemp.type, "Wild") == 0) {
										if (strcmp(linkedListTemp.type, "+4") == 0) {
											currPlus += 4;
											inPlusCondition = true;
										}

										doWild(turnCycle, playerTurn, &tempBool, &linkedListTemp, isBotHaveTheColor);
										
										// Replaces The Discard Pile Wild
										if (discardPileCount <= 1)
											deleteAtBeginning(&discardHead, &discardPileCount);
										else 
											deleteAtEnd(&discardHead, &discardTail, &discardPileCount);

										insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
									}
								}

								// Deletes the card from player's pile
								if (cardPicks[i] == 0)
									deleteAtBeginning(&playerHead, &playerCards);
								else if (cardPicks[i] == playerCards - 1)
									deleteAtEnd(&playerHead, &playerTail, &playerCards);
								else
									deleteAtMiddle(&playerHead, &playerCards, cardPicks[i]);
							}
						}

						// Grab a card from a draw pile
						else if (gameWarp == 2) {
							// Checks so the player can't grab many cards
							if (!canTakeCard) {
								printf("You can\'t take another card, press \'Enter\' to continue");
								getchar();

								continue;
							}

							// Pick a random card from draw pile
							rng1 = rand() % drawPileCount;

							// Saves card value
							cardSave(cardHead, &linkedListTemp, rng1);

							// Putting player cards
							insertAtEnd(&playerHead, &playerTail, &playerCards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

							// Deletes the card from draw pile
							if (rng1 == 0)
								deleteAtBeginning(&cardHead, &drawPileCount);
							else if (rng1 == drawPileCount - 1)
								deleteAtEnd(&cardHead, &cardTail, &drawPileCount);
							else
								deleteAtMiddle(&cardHead, &drawPileCount, rng1);

							// Prints the card that the player gets
							printf("\nYou got ");
							cardPrint(linkedListTemp);
							
							cardSave(discardHead, &linkedListTemp, discardPileCount - 1);

							if (canInputCard(playerHead, linkedListTemp, playerCards)) {
								printf("Do you wanna input the card?\n");
								printf("1. Yes\n");
								printf("2. No\n\n");
								
								do
								{
									printf("Your choice : ");
									scanf("%d", &grabWarp);
									while (getchar() != '\n');
								}
								while (grabWarp != 1 && grabWarp != 2);

								if (grabWarp == 1) {
									canTakeCard = false;

									continue;
								}
							}
						}
					}

					// Bot's turn
					else {
						printf("Press \'Enter\' for ");

						if (turnCycle[playerTurn] == 2)
							printf("Bot 1 ");
						else if (turnCycle[playerTurn] == 3)
							printf("Bot 2 ");
						else if (turnCycle[playerTurn] == 4)
							printf("Bot 3 ");

						printf("to play their cards");
						getchar();

						// Checks if bot can input a card or no
						cardSave(discardHead, &linkedListTemp, discardPileCount - 1);

						if (turnCycle[playerTurn] == 2)
							rng2 = canInputCard(bot1Head, linkedListTemp, bot1Cards) ? 0 : 1;
						else if (turnCycle[playerTurn] == 3)
							rng2 = canInputCard(bot2Head, linkedListTemp, bot2Cards) ? 0 : 1;
						else if (turnCycle[playerTurn] == 4)
							rng2 = canInputCard(bot3Head, linkedListTemp, bot3Cards) ? 0 : 1;

						do
						{							
							// Input a card
							if (rng2 == 0) {
								/*
								Card Amount Input Counter
								*/
								
								// Empties typeAmounts
								for (i = 0; i < 15; i++)
									typeAmounts[i] = 0;
								
								// Resets isBotHaveTheColor
								for (i = 0; i < 4; i++)
									isBotHaveTheColor[i] = false;
								
								// Empties cardAmount
								for (i = 0; i < 4; i++) {
									for (j = 0; j < 13; j++)
										cardAmount[i][j] = 0;
								}

								// Empties wildCardAmount
								wildCardAmount[0] = 0;
								wildCardAmount[1] = 0;
								
								// Counts the amount of type that the bot have and isBotHaveTheColor Calculator
								for (i = 0; i < (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards)); i++) {
									if (turnCycle[playerTurn] == 2)
										cardSave(bot1Head, &linkedListTemp, i);
									else if (turnCycle[playerTurn] == 3)
										cardSave(bot2Head, &linkedListTemp, i);
									else if (turnCycle[playerTurn] == 4)
										cardSave(bot3Head, &linkedListTemp, i);

									// Checks the color
									if (strcmp(linkedListTemp.color, "Blue") == 0) {
										isBotHaveTheColor[0] = true;
										tempInt = 0;
									}
									else if (strcmp(linkedListTemp.color, "Red") == 0) {
										isBotHaveTheColor[1] = true;
										tempInt = 1;
									}
									else if (strcmp(linkedListTemp.color, "Green") == 0) {
										isBotHaveTheColor[2] = true;
										tempInt = 2;
									}
									else if (strcmp(linkedListTemp.color, "Yellow") == 0) {
										isBotHaveTheColor[3] = true;
										tempInt = 3;
									}
									
									// If the card is a normal type
									if (linkedListTemp.number != -1) {
										typeAmounts[linkedListTemp.number]++;
										cardAmount[tempInt][linkedListTemp.number]++;
									}
									
									// If the card is an action type
									else {
										if (strcmp(linkedListTemp.type, "Reverse") == 0) {
											typeAmounts[10]++;
											cardAmount[tempInt][10]++;
										}
										else if (strcmp(linkedListTemp.type, "Skip") == 0) {
											typeAmounts[11]++;
											cardAmount[tempInt][11]++;
										}
										else if (strcmp(linkedListTemp.type, "+2") == 0) {
											typeAmounts[12]++;
											cardAmount[tempInt][12]++;
										}
										else if (strcmp(linkedListTemp.type, "Wild") == 0) {
											typeAmounts[13]++;
											wildCardAmount[0]++;

											for (j = 0; j < 4; j++)
												isBotHaveTheColor[j] = true;
										}
										else if (strcmp(linkedListTemp.type, "+4") == 0) {
											typeAmounts[14]++;
											wildCardAmount[1]++;

											for (j = 0; j < 4; j++)
												isBotHaveTheColor[j] = true;
										}
									}
								}

								// Counts the maximum amount of card the bot can stack
								biggestAmount = 0;

								for (i = 0; i < 13; i++) {
									if (typeAmounts[i] > biggestAmount) {
										biggestAmount = typeAmounts[i];
										cardNameInt = i;
									}
								}
								
								// cardAmountInput Calculator
								cardSave(discardHead, &linkedListTemp2, discardPileCount - 1);
								cardAmountInput = 1;
								validInput = true;

								// Inputs the card for the bot
								cardPickDelete(cardPicks, cardPicksDeclaration);

								for (i = 0; i < cardAmountInput; i++) {
									if (turnCycle[playerTurn] == 2)
										cardPicks[i] = rand() % bot1Cards;
									else if (turnCycle[playerTurn] == 3)
										cardPicks[i] = rand() % bot2Cards;
									else if (turnCycle[playerTurn] == 4)
										cardPicks[i] = rand() % bot3Cards;

									// Checks if the card inputted is valid or not
									cardSave(discardHead, &linkedListTemp, discardPileCount - 1);
									
									if (turnCycle[playerTurn] == 2)
										cardSave(bot1Head, &linkedListTemp2, cardPicks[i]);
									else if (turnCycle[playerTurn] == 3)
										cardSave(bot2Head, &linkedListTemp2, cardPicks[i]);
									else if (turnCycle[playerTurn] == 4)
										cardSave(bot3Head, &linkedListTemp2, cardPicks[i]);
									
									if (!(strcmp(linkedListTemp2.color, linkedListTemp.color) == 0 || (strcmp(linkedListTemp2.type, linkedListTemp.type) == 0 && strcmp(linkedListTemp2.type, "Normal") != 0) || (linkedListTemp2.number == linkedListTemp.number && linkedListTemp2.number != -1) || strcmp(linkedListTemp2.type, "Wild") == 0 || strcmp(linkedListTemp2.type, "+4") == 0)) {
										validInput = false;

										break;
									}

									// Puts the card into discard pile
									insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp2.cardNumber, linkedListTemp2.number, linkedListTemp2.type, linkedListTemp2.color);

									// If the inputted card is an action card
									if (linkedListTemp2.number == -1) {
										// Skip
										if (strcmp(linkedListTemp2.type, "Skip") == 0) {
											l = rounds % 4;

											// Checks so the system won't skip the player who have won
											do
											{
												if (reversed)
													l--;
												else
													l++;
												
												if (l == 0)
													l = 3;				
												
												if (!playerStats[turnCycle[l] - 1].isAlreadyWin)
													break;
											}
											while (true);

											doSkip(&rounds, turnCycle, l, reversed);
										}

										// Reverse
										else if (strcmp(linkedListTemp2.type, "Reverse") == 0)
											doReverse(&reversed);

										// +2
										else if (strcmp(linkedListTemp2.type, "+2") == 0) {
											currPlus += 2;
											inPlusCondition = true;
										}

										// Wild and +4
										else if (strcmp(linkedListTemp2.type, "+4") == 0 || strcmp(linkedListTemp2.type, "Wild") == 0) {
											if (strcmp(linkedListTemp2.type, "+4") == 0) {
												currPlus += 4;
												inPlusCondition = true;
											}

											doWild(turnCycle, playerTurn, &tempBool, &linkedListTemp2, isBotHaveTheColor);
											
											// Replaces The Discard Pile Wild
											if (discardPileCount <= 1)
												deleteAtBeginning(&discardHead, &discardPileCount);
											else 
												deleteAtEnd(&discardHead, &discardTail, &discardPileCount);

											insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp2.cardNumber, linkedListTemp2.number, linkedListTemp2.type, linkedListTemp2.color);
										}
									}

									// Deletes the card from bot's pile
									if (cardPicks[i] == 0) {
										if (turnCycle[playerTurn] == 2)
											deleteAtBeginning(&bot1Head, &bot1Cards);
										else if (turnCycle[playerTurn] == 3)
											deleteAtBeginning(&bot2Head, &bot2Cards);
										else if (turnCycle[playerTurn] == 4)
											deleteAtBeginning(&bot3Head, &bot3Cards);
									}
									else if (cardPicks[i] == playerCards - 1) {
										if (turnCycle[playerTurn] == 2)
											deleteAtEnd(&bot1Head, &bot1Tail, &bot1Cards);
										else if (turnCycle[playerTurn] == 3)
											deleteAtEnd(&bot2Head, &bot2Tail, &bot2Cards);
										else if (turnCycle[playerTurn] == 4)
											deleteAtEnd(&bot3Head, &bot3Tail, &bot3Cards);
									}
									else {
										if (turnCycle[playerTurn] == 2)
											deleteAtMiddle(&bot1Head, &bot1Cards, cardPicks[i]);
										else if (turnCycle[playerTurn] == 3)
											deleteAtMiddle(&bot2Head, &bot2Cards, cardPicks[i]);
										else if (turnCycle[playerTurn] == 4)
											deleteAtMiddle(&bot3Head, &bot3Cards, cardPicks[i]);
									}
								}

								if (!validInput)
									continue;

								printf("\nBot %d puts a card, Press \'Enter\' to conntinue", turnCycle[playerTurn] - 1);
								getchar();
							}

							// Grab a card from a draw pile
							else if (rng2 == 1) {
								// Pick a random card from draw pile
								rng1 = rand() % drawPileCount;

								// Saves card value
								cardSave(cardHead, &linkedListTemp, rng1);

								// Putting bot cards
								if (turnCycle[playerTurn] == 2)
									insertAtEnd(&bot1Head, &bot1Tail, &bot1Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
								else if (turnCycle[playerTurn] == 3)
									insertAtEnd(&bot2Head, &bot2Tail, &bot2Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
								else if (turnCycle[playerTurn] == 4)
									insertAtEnd(&bot3Head, &bot3Tail, &bot3Cards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

								// Deletes the card from draw pile
								if (rng1 == 0)
									deleteAtBeginning(&cardHead, &drawPileCount);
								else if (rng1 == drawPileCount - 1)
									deleteAtEnd(&cardHead, &cardTail, &drawPileCount);
								else
									deleteAtMiddle(&cardHead, &drawPileCount, rng1);
								
								printf("\nBot %d grabs a card, Press \'Enter\' to conntinue", turnCycle[playerTurn] - 1);
								getchar();
							}

							break;
						}
						while (true);
					}
				}

				// This program runs if the cards on the draw pile ran out
				if (drawPileCount == 0) {
					for (i = 0; i < discardPileCount - 1; i++) {
						cardSave(discardHead, &linkedListTemp, i);

						if (strcmp(linkedListTemp.type, "Wild") == 0 || strcmp(linkedListTemp.type, "+4") == 0)
							strcpy(linkedListTemp.color, "Black");

						insertAtEnd(&cardHead, &cardTail, &drawPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
						deleteAtBeginning(&discardHead, &discardPileCount);
					}
				}

				// This program runs if one of the player wins
				if ((turnCycle[playerTurn] == 1 && playerCards == 0) || (turnCycle[playerTurn] == 2 && bot1Cards == 0) || (turnCycle[playerTurn] == 3 && bot2Cards == 0) || (turnCycle[playerTurn] == 4 && bot3Cards == 0)) {
					if (turnCycle[playerTurn] == 1)
						printf("You win and get ");
					else
						printf("Bot %d wins and get ", turnCycle[playerTurn] - 1);

					if (playersLeft == 4)
						printf("1st ");
					if (playersLeft == 3)
						printf("2nd ");
					if (playersLeft == 2)
						printf("3rd ");
					
					printf("place, Press \'Enter\' to continue");
					getchar();

					playerStats[turnCycle[playerTurn] - 1].isAlreadyWin = true;
					playerStats[turnCycle[playerTurn] - 1].podiumPlace = 5 - playersLeft;
					playersLeft--;
					playersWon++;
				}

				// Next round update code
				if (reversed)
					rounds--;
				else
					rounds++;
				
				if (rounds < 0)
					rounds = 3;
				
				if (rounds > 4000)
					rounds = 1;
				
				canTakeCard = true;
			}
			while (true);

			/* 
			 Podium Place Shower
			 */

			// Creating podium place positions
			for (i = 0; i < 4; i++)
				strcpy(podiumPlaceNames[playerStats[i].podiumPlace - 1], playerNumberToString(i + 1));

			system("cls");
			logo();

			printf(" Podium Place \n");
			printf("==============\n\n");

			printf("       %6s           \n", podiumPlaceNames[0]);
			printf("       =======       \n");
			printf("%6s |  1  |          \n", podiumPlaceNames[1]);
			printf("=======|     |       \n");
			printf("|  2  ||     | %s    \n", podiumPlaceNames[2]);
			printf("|     ||     |=======\n");
			printf("|     ||     ||  3  |\n\n");

			printf("Loser : %s\n\n", podiumPlaceNames[3]);

			printf("Press \'Enter\' to continue");
			getchar();
		}

		// Instructions
		else if (mainWarp == 2) {
			system("cls");
			logo();

			printf(" Instructions \n");
			printf("==============\n\n");

			printf("Press \'Enter\' to go back to main menu");
			getchar();
		}

		// Credits
		else if (mainWarp == 3) {
			system("cls");
			logo();

			printf(" Credits \n");
			printf("=========\n\n");

			printf("%20s | DarkH3roZX\n", "Programmer");
			printf("%20s | adVenT47\n\n", "Programmer Assistor");

			printf("%20s | adVenT47\n", "Sketch");
			printf("%20s | DarkH3roZX\n\n", "Sketch");

			printf("%20s | DarkH3roZX\n", "Tester 1");
			printf("%20s | adVenT47\n\n", "Tester 2");

			printf("=================\n");
			printf(" Vagous Alliance \n");
			printf("=================\n\n");

			printf("Press \'Enter\' to go back to main menu");
			getchar();
		}
	}
	while (mainWarp != 4);
	
	// Exit Menu
	system("cls");
	logo();

	printf("Thank You For Playing Our Game!");
	getchar();

	return 0;
}

void logo() {
	printf("================================\n");
	printf(" =   =   ==   =   /===\\        \n");
	printf(" |   |   |\\   |   |   |        \n");
	printf(" |   |   | \\  |   |   |        \n");
	printf(" |   |   |  \\ |   |   |        \n");
	printf(" \\===/   =   ==   \\===/       \n");
	printf("================================\n\n");
}

void rpsUI(int round) {
	printf(" Rock Paper Scissors Round %d\n", round);
	printf("=============================\n\n");
}

char rpsIntToChar(int x) {
	if (x == 0)
		return 'r';
	else if (x == 1)
		return 'p';
	else if (x == 2)
		return 's';
}

int rpsWinnerFinder(char choice1, char choice2, int player1, int player2) {
	if (choice1 == 'r' && choice2 == 'p')
		return player2;
	else if (choice1 == 'r' && choice2 == 's')
		return player1;
	else if (choice1 == 'p' && choice2 == 'r')
		return player1;
	else if (choice1 == 'p' && choice2 == 's')
		return player2;
	else if (choice1 == 's' && choice2 == 'r')
		return player2;
	else if (choice1 == 's' && choice2 == 'p')
		return player1;
	else
		return 0; // If player 1 and 2 chooses the same
}

void insertAtEnd(Node** headRef, Node** tailRef, int* count, int cardNum, int num, char* type, char* color) {
	Node* current = (Node*)malloc(sizeof(Node));
	current -> cardNumber = cardNum;
	current -> number = num;
	strcpy(current -> type, type);
	strcpy(current -> color, color);
	(*count)++;
	
	// for initial insert
	if ((*count) == 1)
		(*headRef) = current;
	// for end insert
	else
		(*tailRef) -> next = current;
	
	(*tailRef) = current;
	(*tailRef) -> next = NULL;
}

void deleteAtBeginning(Node** headRef, int* count) {
	Node* current = (*headRef);
	
	(*headRef) = (*headRef) -> next;
	free(current);
	(*count)--;
}

void deleteAtMiddle(Node** headRef, int* count, int index) {
	Node* current = (*headRef);
	
	int i;
	for (i = 0; i < index - 1; i++) {
		current = current -> next;
	}
	
	Node* deleteNode = current -> next;
	current -> next = deleteNode -> next;
	free(deleteNode);
	(*count)--;
}

void deleteAtEnd(Node** headRef, Node** tailRef, int* count) {
	Node* current = (*headRef);
	
	while (current -> next -> next != NULL) {
		current = current -> next;
	}
	
	Node* deleteNode = current -> next;
	(*tailRef) = current;
	(*tailRef) -> next = NULL;
	free(deleteNode);
	(*count)--;
}

void cardSave(Node* node, Temp1 *linkedListTemp, int index) {
	int i;

	for (i = 0; i < index; i++)
		node = node -> next;
	
	linkedListTemp -> cardNumber = node -> cardNumber;
	linkedListTemp -> number = node -> number;
	strcpy(linkedListTemp -> type, node -> type);
	strcpy(linkedListTemp -> color, node -> color);
}

void printList(Node* node) {
	int x = 1;

	while (node != NULL) {
		printf("%d. ", x);

		if (strcmp(node -> color, "Black") != 0)
			printf("%s ", node -> color);
		
		if (node -> number != -1)
			printf("%d ", node -> number);
		else
			printf("%s ", node -> type);

		puts("");
		//printf("- %d %s %s\n", node -> number, node -> type, node -> color);
		node = node -> next;
		x++;
	}

	puts("");
}

char * playerNumberToString(int x) {
	if (x == 1)
		return "Player";
	else if (x == 2)
		return "Bot 1";
	else if (x == 3)
		return "Bot 2";
	else if (x == 4)
		return "Bot 3";
}

void doReverse(bool *reverse) {
	if (*reverse)
		*reverse = false;
	else
		*reverse = true;
}

void doSkip(int *roundsPtr, int turnCycle[], int playerTurn, bool reversed) {
	if (turnCycle[playerTurn] == 1)
		printf("You ");
	else if (turnCycle[playerTurn] == 2)
		printf("Bot 1 ");
	else if (turnCycle[playerTurn] == 3)
		printf("Bot 2 ");
	else if (turnCycle[playerTurn] == 4)
		printf("Bot 3 ");
	
	printf("got skipped, press \'Enter\' to continue");
	getchar();

	if (reversed)
		(*roundsPtr)--;
	else
		(*roundsPtr)++;
}

void doWild(int turnCycle[], int playerTurn, bool *tempBoolPtr, Temp1 *linkedListTempPtr, bool isBotHaveTheColor[]) {
	int colorPicker;

	char wildCardInput[7];

	// If the turn is player's
	if (turnCycle[playerTurn] == 1) {
		do
		{
			puts("");
			printf("1. Blue\n");
			printf("2. Red\n");
			printf("3. Green\n");
			printf("4. Yellow\n");

			// Player Picks a color
			printf("Pick a color : ");
			scanf("%d", &colorPicker);
			while (getchar() != '\n');
		} 
		while (colorPicker != 1 && colorPicker != 2 && colorPicker != 3 && colorPicker != 4);

		// Prints name
		printf("You chose ");

		// Prints color
		if (colorPicker == 1) {
			strcpy(wildCardInput, "Blue");
			printf("Blue");
		}
		else if (colorPicker == 2) {
			strcpy(wildCardInput, "Red");
			printf("Red");
		}
		else if (colorPicker == 3) {
			strcpy(wildCardInput, "Green");
			printf("Green");
		}
		else if (colorPicker == 4) {
			strcpy(wildCardInput, "Yellow");
			printf("Yellow");
		}
	}

	// If the turn is bot's
	else {
		do
		{
			colorPicker = rand() % 4;

			if (isBotHaveTheColor[colorPicker])
				break;
		}
		while (true);
		
		// Prints name
		if (turnCycle[playerTurn] == 2)
			printf("Bot 1 chooses ");
		else if (turnCycle[playerTurn] == 3)
			printf("Bot 2 chooses ");
		else if (turnCycle[playerTurn] == 4)
			printf("Bot 3 chooses ");
		
		// Prints color
		if (colorPicker == 0) {
			strcpy(wildCardInput, "Blue");
			printf("Blue");
		}
		else if (colorPicker == 1) {
			strcpy(wildCardInput, "Red");
			printf("Red");
		}
		else if (colorPicker == 2) {
			strcpy(wildCardInput, "Green");
			printf("Green");
		}
		else if (colorPicker == 3) {
			strcpy(wildCardInput, "Yellow");
			printf("Yellow");
		}
	}

	printf(", Press \'Enter\' To Continue");
	getchar();

	// Changes the color of the wild card
	strcpy(linkedListTempPtr -> color, wildCardInput);

	*tempBoolPtr = false;
}

void cardPrint(Temp1 linkedListTemp) {
	//printf("%d %s %s\n", linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

	// Chosen Wild
	if (strcmp(linkedListTemp.color, "Black") != 0 && (strcmp(linkedListTemp.type, "Wild") == 0 || strcmp(linkedListTemp.type, "+4") == 0))
		printf("%s (%s)", linkedListTemp.type, linkedListTemp.color);

	// Normal
	else {
		if (strcmp(linkedListTemp.color, "Black") != 0)
			printf("%s ", linkedListTemp.color);
		
		if (linkedListTemp.number != -1)
			printf("%d ", linkedListTemp.number);
		else
			printf("%s ", linkedListTemp.type);
	}
}

bool canInputCard(Node* node, Temp1 linkedListTemp, int playerCards) {
	int i;

	for (i = 0; i < playerCards; i++) {
		if ((strcmp(node -> type, linkedListTemp.type) == 0 && strcmp(node -> type, "Normal") != 0) || (node -> number == linkedListTemp.number && linkedListTemp.number != -1) || strcmp(node -> color, linkedListTemp.color) == 0 || strcmp(node -> type, "+4") == 0 || strcmp(node -> type, "Wild") == 0)
			return true;
		
		node = node -> next;
	}

	return false;
}

bool canAddAnotherPlus(Node* node, bool discardPlus4, int playerCards) {
	int i;

	for (i = 0; i < playerCards; i++) {
		if ((strcmp(node -> type, "+2") == 0 && !discardPlus4) || strcmp(node -> type, "+4") == 0)
			return true;
		
		node = node -> next;
	}

	return false;
}

void cardPickDelete(int *cardPicks, int *cardPicksDeclaration) {
	int i;

	for (i = 0; i < 8; i++) {
		cardPicksDeclaration[i] = 0;
		cardPicks[i] = 0;
	}
}

void totalColorsDelete(int *totalColors) {
	int i;

	for (i = 0; i < 5; i++)
		totalColors[i] = 0;
}