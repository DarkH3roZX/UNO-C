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
} CardData;

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
void cardSave(Node* node, CardData *linkedListTemp, int index);
void printList(Node* node);
char * playerNumberToString(int x);
void doReverse(bool *reverse);
void doSkip(int turnCycle[], int playerTurn, bool reversed);
void doWild(int turnCycle[], int playerTurn, CardData *linkedListTemp, bool isBotHaveTheColor[]);
void cardPrint(CardData linkedListTemp);
bool canInputCard(Node* node, CardData linkedListTemp, int playerCards);
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
	FILE *statsFile; // Stats file

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
	char tempColor[7];

	CardData linkedListTemp;
	CardData linkedListTemp2;
	CardData linkedListTemp3;
	CardData linkedListTemp4;
	CardData linkedListTemp5;
	
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
	int playersLeft;
	int turnCycle[4];
	int cardPicks[8];
	int stats[4];

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
	int wildSkipAnyDeclaration[3];

	bool isBotWantToStackWithPlus4;
	bool botPutACard;
	bool isDoneChecking;
	bool isContinue;
	bool isSameColor;
	bool isBotHaveTheColor[4];

	CardData bot2Temp[3];

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

	// Creates new file if there is no file found
	statsFile = fopen("stats.evan", "rb");

	if (statsFile == NULL) {
		fclose(statsFile);
		statsFile = fopen("stats.evan", "wb");

		tempInt = 0;

		for (i = 0; i < 4; i++)
			fwrite(&tempInt, sizeof(int), 1, statsFile);
	}

	for (i = 0; i < 4; i++)
		fread(&stats[i], sizeof(stats[i]), 1, statsFile);

	fclose(statsFile);

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
			printf("3. Stats\n");
			printf("4. Credits\n");
			printf("5. Exit\n\n");
			
			printf("Your Choice : ");
			scanf("%d", &mainWarp);
			while (getchar() != '\n');
		}
		while (mainWarp != 1 && mainWarp != 2 && mainWarp != 3 && mainWarp != 4 && mainWarp != 5);

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
					printf("\nYou and your opponents pick a same choice, press \'Enter\' to play again!");
					getchar();

					continue;
				}

				// Prints what the player choose
				printf("\nYou pick ");

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
					printf("Press \'Enter\' to continue");
					getchar();
				}

				// If Bot 1 Wins
				else {
					winnersRPS[0] = 2;
					losersRPS[0] = 1;

					printf("You LOSE!\n");
					printf("Press \'Enter\' to continue");
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
						printf("\nBoth Bot 2 and 3 picks rock, it\'s a tie");
					else if (playerChoicesRPS[2] == 'p')
						printf("\nBoth Bot 2 and 3 picks paper, it\'s a tie");
					else if (playerChoicesRPS[2] == 's')
						printf("\nBoth Bot 2 and 3 picks scissors, it\'s a tie");
					
					printf("\nPress \'Enter\' to continue");
					getchar();

					continue;
				}

				// Prints what the player choose
				printf("\nBot 2 picks ");

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
					printf("Press \'Enter\' to continue");
					getchar();
				}

				// If Bot 3 Wins
				else {
					winnersRPS[1] = 4;
					losersRPS[1] = 3;

					printf("Bot 3 Wins!\n");
					printf("Press \'Enter\' to continue");
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
							printf("\nYou and Bot %d picks rock, it\'s a tie", losersRPS[1] - 1);
						else
							printf("\nBot %d and Bot %d picks rock, it\'s a tie", losersRPS[0] - 1, losersRPS[1] - 1);
					}
					else if (playerChoicesRPS[0] == 'p') {
						if (winnersRPS[0] != 1)
							printf("\nYou and Bot %d picks paper, it\'s a tie", losersRPS[1] - 1);
						else
							printf("\nBot %d and Bot %d picks paper, it\'s a tie", losersRPS[0] - 1, losersRPS[1] - 1);
					}
					else if (playerChoicesRPS[0] == 's') {
						if (winnersRPS[0] != 1)
							printf("\nYou and Bot %d picks scissors, it\'s a tie", losersRPS[1] - 1);
						else
							printf("\nBot %d and Bot %d picks scissors, it\'s a tie", losersRPS[0] - 1, losersRPS[1] - 1);
					}
					
					printf("\nPress \'Enter\' to continue");
					getchar();

					continue;
				}

				// If Player 1 Wins
				if (winnerRPS == losersRPS[0]) {
					turnCycle[2] = losersRPS[0];
					turnCycle[3] = losersRPS[1];

					if (winnersRPS[0] != 1)
						printf("\nYou win and get the 3rd turn!");
					else
						printf("\nBot %d win and get the 3rd turn!", winnerRPS - 1);
				}

				// If Player 2 Wins
				else {
					turnCycle[2] = losersRPS[1];
					turnCycle[3] = losersRPS[0];

					if (winnersRPS[0] != 1)
						printf("\nYou Lose and get the 4th turn!");
					else
						printf("\nBot %d win and get the 3rd turn!", winnerRPS - 1);
				}

				printf("\nPress \'Enter\' to continue");
				getchar();

				break;
			}
			while (true);
			
			// RPS Round 4 (Winner vs Winner)
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

					rpsUI(4);

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
							printf("\nYou and Bot %d picks rock, it\'s a tie", winnersRPS[1] - 1);
						else
							printf("\nBot %d and Bot %d picks rock, it\'s a tie", winnersRPS[0] - 1, winnersRPS[1] - 1);
					}
					else if (playerChoicesRPS[2] == 'p') {
						if (winnersRPS[0] == 1)
							printf("\nYou and Bot %d picks paper, it\'s a tie", winnersRPS[1] - 1);
						else
							printf("\nBot %d and Bot %d picks paper, it\'s a tie", winnersRPS[0] - 1, winnersRPS[1] - 1);
					}
					else if (playerChoicesRPS[2] == 's') {
						if (winnersRPS[0] == 1)
							printf("\nYou and Bot %d picks scissors, it\'s a tie", winnersRPS[1] - 1);
						else
							printf("\nBot %d and Bot %d picks scissors, it\'s a tie", winnersRPS[0] - 1, winnersRPS[1] - 1);
					}
					
					printf("\nPress \'Enter\' to continue");
					getchar();

					continue;
				}

				// If Player 1 Wins
				if (winnerRPS == winnersRPS[0]) {
					turnCycle[0] = winnersRPS[0];
					turnCycle[1] = winnersRPS[1];

					if (winnersRPS[0] == 1)
						printf("\nYou Win and get the 1st turn!");
					else
						printf("\nBot %d win and get the 1st turn!", winnerRPS - 1);
				}

				// If Player 2 Wins
				else {
					turnCycle[0] = winnersRPS[1];
					turnCycle[1] = winnersRPS[0];

					if (winnersRPS[0] == 1)
						printf("\nYou Lose and get the 2nd turn!");
					else
						printf("\nBot %d win and get the 1st turn!", winnerRPS - 1);
				}

				printf("\nPress \'Enter\' to continue");
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

			printf("\nPress \'Enter\' to continue");
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
			botPutACard = false;
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
				strcpy(linkedListTemp.type, "Wild");
				strcpy(linkedListTemp.color, "Black");
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

				// Bot 2 AI
				if (turnCycle[playerTurn] == 3 && playersLeft == 2) {
					// Saves the card value
					cardSave(bot2Head, &linkedListTemp, 0); // 1st index
					cardSave(bot2Head, &linkedListTemp2, 1); // 2nd index
					cardSave(discardHead, &linkedListTemp4, discardPileCount - 1); // Discard Pile Check

					// 2 Card Logic
					if (bot2Cards == 2 && ((strcmp(linkedListTemp.color, "Black") == 0 && strcmp(linkedListTemp2.color, linkedListTemp4.color) == 0) || strcmp(linkedListTemp2.color, "Black") == 0)) {
						cardSave(bot2Head, &linkedListTemp5, 0);
						deleteAtBeginning(&bot2Head, &bot2Cards);
						insertAtEnd(&bot2Head, &bot2Tail, &bot2Cards, linkedListTemp5.cardNumber, linkedListTemp5.number, linkedListTemp5.type, linkedListTemp5.color);
					}

					// 3 Card Logic
					else if (bot2Cards == 3) {
						cardSave(bot2Head, &linkedListTemp3, 2); // 3rd index
						// Cleans wildSkipAnyDeclaration
						for (i = 0; i < 3; i++)
							wildSkipAnyDeclaration[i] = 0;

						strcpy(tempColor, "x");
						isSameColor = false;

						for (i = 0; i < 3; i++) {
							cardSave(bot2Head, &bot2Temp[i], i);

							if (strcmp(bot2Temp[i].type, "+4") != 0)
								strcpy(tempColor, bot2Temp[i].color);
							else if (strcmp(tempColor, "x") != 0 && strcmp(bot2Temp[i].type, "+4") != 0 && strcmp(tempColor, bot2Temp[i].color) == 0)
								isSameColor = true;

							if (strcmp(bot2Temp[i].type, "+4") == 0)
								wildSkipAnyDeclaration[0]++;
							else if (strcmp(bot2Temp[i].type, "Skip") == 0)
								wildSkipAnyDeclaration[1]++;
							else
								wildSkipAnyDeclaration[2]++;
						}

						if (wildSkipAnyDeclaration[0] == 1 && wildSkipAnyDeclaration[1] == 1 && wildSkipAnyDeclaration[2] == 1 && isSameColor) {
							// Cleans bot 2 deck
							for (i = 0; i < 3; i++)
								deleteAtBeginning(&bot2Head, &bot2Cards);
							
							for (i = 0; i < 3; i++) {
								if (i == 0) {
									for (j = 0; j < 3; j++) {
										if (strcmp(bot2Temp[j].type, "+4") == 0) {
											insertAtEnd(&bot2Head, &bot2Tail, &bot2Cards, bot2Temp[j].cardNumber, bot2Temp[j].number, bot2Temp[j].type, bot2Temp[j].color);

											break;
										}
									}
								}
								else if (i == 1) {
									for (j = 0; j < 3; j++) {
										if (strcmp(bot2Temp[j].type, "Skip") == 0) {
											insertAtEnd(&bot2Head, &bot2Tail, &bot2Cards, bot2Temp[j].cardNumber, bot2Temp[j].number, bot2Temp[j].type, bot2Temp[j].color);

											break;
										}
									}
								}
								else if (i == 2) {
									for (j = 0; j < 3; j++) {
										if (strcmp(bot2Temp[j].type, "Skip") != 0 && strcmp(bot2Temp[j].type, "+4") == 0) {
											insertAtEnd(&bot2Head, &bot2Tail, &bot2Cards, bot2Temp[j].cardNumber, bot2Temp[j].number, bot2Temp[j].type, bot2Temp[j].color);

											break;
										}
									}
								}
							}
						}
					}
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
					
					if ((turnCycle[i] == 1 && playerCards == 1) ||
						(turnCycle[i] == 2 && bot1Cards == 1) ||
						(turnCycle[i] == 3 && bot2Cards == 1) ||
						(turnCycle[i] == 4 && bot3Cards == 1))
						printf("(UNO!)");
					
					puts("");
				}

				// Displays the current card
				cardSave(discardHead, &linkedListTemp, discardPileCount - 1);

				printf("\nCurrent Card : ");
				cardPrint(linkedListTemp);
				puts("");

				// Displays the cards
				printf("\n Cards \n", drawPileCount);
				printf("=======\n");

				// Prints the amount of bot 1 cards
				printf("\nBot 1 : ");

				for (i = 0; i < bot1Cards; i++)
					printf("[] ");
				
				//puts("");
				//printList(bot1Head);
				
				// Prints the amount of bot 2 cards
				printf("\nBot 2 : ");

				for (i = 0; i < bot2Cards; i++)
					printf("[] ");
				
				//puts("");
				//printList(bot2Head);
				
				// Prints the amount of bot 3 cards
				printf("\nBot 3 : ");

				for (i = 0; i < bot3Cards; i++)
					printf("[] ");

				//puts("");
				//printList(bot3Head);
				
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
						doSkip(turnCycle, playerTurn, reversed);
						rounds++;

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
						for (i = 0; i < (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : (turnCycle[playerTurn] == 4 ? bot3Cards : 0))); i++) {
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

						doWild(turnCycle, playerTurn, &linkedListTemp, isBotHaveTheColor);

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
								validInput = true;
								cardAmountInput = 0;

								// UI
								printf("Input the cards (Press 'Enter' -> 'Ctrl + Z' -> 'Enter' when you're done):\n");

								cardPickDelete(cardPicks, cardPicksDeclaration);

								do
								{
									if (scanf("%d", &cardPicks[cardAmountInput]) != 1)
										break;
									
									cardPicks[cardAmountInput]--;
									cardPicksDeclaration[cardAmountInput] = cardPicks[cardAmountInput];
									
									for (i = 0; i < cardAmountInput; i++) {
										if (cardPicks[cardAmountInput] == cardPicksDeclaration[i]) {
											validInput = false;

											break;
										}
									}

									cardAmountInput++;

									while (getchar() != '\n');
								}
								while (true);

								// Fixes the card index
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
									cardSave(playerHead, &linkedListTemp, cardPicks[i]);

									// Adds the current plus
									if (strcmp(linkedListTemp.type, "+2") == 0)
										currPlus += 2;
									else if (strcmp(linkedListTemp.type, "+4") == 0) {
										currPlus += 4;

										doWild(turnCycle, playerTurn, &linkedListTemp, isBotHaveTheColor);

										// Replaces The Discard Pile Wild
										if (discardPileCount <= 1)
											deleteAtBeginning(&discardHead, &discardPileCount);
										else 
											deleteAtEnd(&discardHead, &discardTail, &discardPileCount);
										
										insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
									}

									// Puts a card into a draw pile
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
							printf("You got %d cards, press \'Enter\' to continue", currPlus);
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
						isBotWantToStackWithPlus4 = false;

						if (strcmp(linkedListTemp2.type, "+4") == 0)
							discardPlus4 = true;
						else
							discardPlus4 = false;

						// Checks if the bot can stack a plus card or not
						if (turnCycle[playerTurn] == 2)
							canInputPlusCard = canAddAnotherPlus(bot1Head, discardPlus4, bot1Cards);
						else if (turnCycle[playerTurn] == 3)
							canInputPlusCard = canAddAnotherPlus(bot2Head, discardPlus4, bot2Cards);
						else if (turnCycle[playerTurn] == 4)
							canInputPlusCard = canAddAnotherPlus(bot3Head, discardPlus4, bot3Cards);
						
						// Counts the amount of plus card that the bot have
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

						// Case if the next player is in UNO
						if (reversed) {
							if (playerTurn == 0) {
								if ((turnCycle[3] == 1 && playerCards == 1) ||
								(turnCycle[3] == 2 && bot1Cards == 1) ||
								(turnCycle[3] == 3 && bot2Cards == 1) ||
								(turnCycle[3] == 4 && bot3Cards == 1))
								isBotWantToStackWithPlus4 = true;
							}
							else {
								if ((turnCycle[playerTurn - 1] == 1 && playerCards == 1) ||
								(turnCycle[playerTurn - 1] == 2 && bot1Cards == 1) ||
								(turnCycle[playerTurn - 1] == 3 && bot2Cards == 1) ||
								(turnCycle[playerTurn - 1] == 4 && bot3Cards == 1))
								isBotWantToStackWithPlus4 = true;
							}
						}
						else {
							if ((turnCycle[(playerTurn + 1) % 4] == 1 && playerCards == 1) ||
								(turnCycle[(playerTurn + 1) % 4] == 2 && bot1Cards == 1) ||
								(turnCycle[(playerTurn + 1) % 4] == 3 && bot2Cards == 1) ||
								(turnCycle[(playerTurn + 1) % 4] == 4 && bot3Cards == 1))
								isBotWantToStackWithPlus4 = true;
						}

						// Condition if the plus is only 2 or the plus is alr too many
						if (botTotalPlus2 > 0 || (botTotalPlus4 > 0 && currPlus > 4))
							isBotWantToStackWithPlus4 = true;
						
						// Condition if the topmost dicard pile is +4
						if (discardPlus4)
							isBotWantToStackWithPlus4 = true;
						
						if (botTotalPlus4 == 0)
							isBotWantToStackWithPlus4 = false;
						
						// Determines the botWarp
						botWarp = canInputPlusCard ? 0 : 1;
						
						// Stack It
						if (botWarp == 0) {
							// Empties cardPicks
							cardPickDelete(cardPicks, cardPicksDeclaration);

							// Checks the discard pile
							cardSave(discardHead, &linkedListTemp2, discardPileCount - 1);

							// Inputs cardPicks
							for (i = 0; i < (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards)); i++) {
								if (turnCycle[playerTurn] == 2)
									cardSave(bot1Head, &linkedListTemp, i);
								else if (turnCycle[playerTurn] == 3)
									cardSave(bot2Head, &linkedListTemp, i);
								else if (turnCycle[playerTurn] == 4)
									cardSave(bot3Head, &linkedListTemp, i);
								
								if ((strcmp(linkedListTemp.type, "+4") == 0 && isBotWantToStackWithPlus4) ||
									(strcmp(linkedListTemp.type, "+2") == 0 && !discardPlus4 && !isBotWantToStackWithPlus4)) {
									cardPicks[0] = i;

									break;
								}
							}

							// Cleans isBotHaveTheColor
							for (i = 0; i < 4; i++)
								isBotHaveTheColor[i] = false;

							/*
							 Puts a card into a discard pile
							 */
							if (turnCycle[playerTurn] == 2)
								cardSave(bot1Head, &linkedListTemp, cardPicks[0]);
							else if (turnCycle[playerTurn] == 3)
								cardSave(bot2Head, &linkedListTemp, cardPicks[0]);
							else if (turnCycle[playerTurn] == 4)
								cardSave(bot3Head, &linkedListTemp, cardPicks[0]);
							
							insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);

							// Adds the current plus
							if (strcmp(linkedListTemp.type, "+2") == 0)
								currPlus += 2;
							else {
								currPlus += 4;

								// Checks if the bot have the color
								for (i = 0; i < (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : (turnCycle[playerTurn] == 4 ? bot3Cards : 0))); i++) {
									// Checks so it wont check the inputted card
									if (i == cardPicks[0])
										continue;

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
									else if (strcmp(linkedListTemp2.color, "Black") == 0) {
										for (j = 0; j < 4; j++)
											isBotHaveTheColor[j] = true;
									}
								}
								
								// This code runs to prevent the player didn't pick a color
								if ((turnCycle[playerTurn] == 2 && bot1Cards == 1) || (turnCycle[playerTurn] == 3 && bot2Cards == 1) || (turnCycle[playerTurn] == 4 && bot3Cards == 1)) {
									for (i = 0; i < 4; i++)
										isBotHaveTheColor[i] = true;
								}

								doWild(turnCycle, playerTurn, &linkedListTemp, isBotHaveTheColor);
									
								// Replaces The Discard Pile Wild
								if (discardPileCount <= 1)
									deleteAtBeginning(&discardHead, &discardPileCount);
								else 
									deleteAtEnd(&discardHead, &discardTail, &discardPileCount);
								
								insertAtEnd(&discardHead, &discardTail, &discardPileCount, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
							}

							// Deletes the card from bot's pile
							if (cardPicks[0] == 0) {
								if (turnCycle[playerTurn] == 2)
									deleteAtBeginning(&bot1Head, &bot1Cards);
								else if (turnCycle[playerTurn] == 3)
									deleteAtBeginning(&bot2Head, &bot2Cards);
								else if (turnCycle[playerTurn] == 4)
									deleteAtBeginning(&bot3Head, &bot3Cards);
							}
							else if (cardPicks[0] == (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards)) - 1) {
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

							printf("Bot %d stacks the plus and now the total plus is %d\n", turnCycle[playerTurn] - 1, currPlus);
							printf("Press \'Enter\' to continue");
							getchar();
						}

						// No
						else if (botWarp == 1) {
							printf("Bot %d got %d cards, press \'Enter\' to continue", turnCycle[playerTurn] - 1, currPlus);
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

						if (canTakeCard)
							printf("2. Get a card from draw pile\n");
						else
							printf("2. Skip turn\n");

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
							validInput = true;
							cardAmountInput = 0;

							// UI
							printf("Input the cards (Press 'Enter' -> 'Ctrl + Z' -> 'Enter' when you're done):\n");

							cardPickDelete(cardPicks, cardPicksDeclaration);

							do
							{
								if (scanf("%d", &cardPicks[cardAmountInput]) != 1)
									break;
								
								cardPicks[cardAmountInput]--;
								cardPicksDeclaration[cardAmountInput] = cardPicks[cardAmountInput];
								
								for (i = 0; i < cardAmountInput; i++) {
									if (cardPicks[cardAmountInput] == cardPicksDeclaration[i]) {
										validInput = false;

										break;
									}
								}

								cardAmountInput++;

								while (getchar() != '\n');
							}
							while (true);

							if (!validInput || cardAmountInput < 1) {
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
											
											// Checks so l never go below 0
											if (l < 0)
												l = 3;
											
											// Checks so l never go above 3;
											l %= 4;

											if (!playerStats[turnCycle[l] - 1].isAlreadyWin)
												break;
										}
										while (true);

										rounds = l;
										doSkip(turnCycle, l, reversed);
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

										doWild(turnCycle, playerTurn, &linkedListTemp, isBotHaveTheColor);
										
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
						else if (gameWarp == 2 && canTakeCard) {
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
							else {
								printf("\nPress \'Enter\' to continue");
								getchar();
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

						puts("");

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
								 Inputs the card for the bot
								 */
								cardSave(discardHead, &linkedListTemp2, discardPileCount - 1);
								cardAmountInput = 0;
								validInput = true;
								isContinue = false;
								cardPickDelete(cardPicks, cardPicksDeclaration);
								isDoneChecking = false;

								printf("Bot %d inputs:\n", turnCycle[playerTurn] - 1);

								// LinkedListTemp = current player card that is currently in check
								// LinkedListTemp2 = current discard pile
								// LinkedListTemp3 = first card put on the discard pile
								
								// i = determines the index of cardPicks[]
								for (i = 0; i < 8; i++) {
									if (i == (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards)))
										break;
									
									// j = scroll through the cards
									for (j = 0; j < (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards)); j++) {
										// Checks so it wont check the same card
										for (k = 0; k < cardAmountInput; k++) {
											if (j == cardPicks[k]) {
												isContinue = true;

												break;
											}
										}

										if (isContinue) {
											isContinue = false;

											continue;
										}

										// Saves the card value
										if (turnCycle[playerTurn] == 2)
											cardSave(bot1Head, &linkedListTemp, j);
										else if (turnCycle[playerTurn] == 3)
											cardSave(bot2Head, &linkedListTemp, j);
										else if (turnCycle[playerTurn] == 4)
											cardSave(bot3Head, &linkedListTemp, j);
										
										// 1st card
										if (i == 0 && (strcmp(linkedListTemp.color, linkedListTemp2.color) == 0 || (strcmp(linkedListTemp.type, linkedListTemp2.type) == 0 && strcmp(linkedListTemp.type, "Normal") != 0) || (linkedListTemp.number == linkedListTemp2.number && linkedListTemp.number != -1) || strcmp(linkedListTemp.type, "Wild") == 0 || strcmp(linkedListTemp.type, "+4") == 0)) {
											// Saves the card value
											if (turnCycle[playerTurn] == 2)
												cardSave(bot1Head, &linkedListTemp3, j);
											else if (turnCycle[playerTurn] == 3)
												cardSave(bot2Head, &linkedListTemp3, j);
											else if (turnCycle[playerTurn] == 4)
												cardSave(bot3Head, &linkedListTemp3, j);
											
											if (strcmp(linkedListTemp.type, "Wild") == 0 || strcmp(linkedListTemp.type, "+4") == 0)
												isDoneChecking = true;

											cardPicks[i] = j;
											cardAmountInput++;
											
											break;
										}

										// Else
										else if (i != 0 && ((strcmp(linkedListTemp.type, linkedListTemp3.type) == 0 && strcmp(linkedListTemp.type, "Normal") != 0) || (linkedListTemp.number == linkedListTemp3.number && linkedListTemp.number != -1))) {
											cardPicks[i] = j;
											cardAmountInput++;

											break;
										}

										// Checks the card
										if (j == (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards)) - 1)
											isDoneChecking = true;
									}

									if (isDoneChecking)
										break;
								}

								// Prints the inputted card
								for (i = 0; i < cardAmountInput; i++) {
									// Saves the card value
									if (turnCycle[playerTurn] == 2)
										cardSave(bot1Head, &linkedListTemp, cardPicks[i]);
									else if (turnCycle[playerTurn] == 3)
										cardSave(bot2Head, &linkedListTemp, cardPicks[i]);
									else if (turnCycle[playerTurn] == 4)
										cardSave(bot3Head, &linkedListTemp, cardPicks[i]);

									cardPrint(linkedListTemp);
									puts("");
								}

								// Fixes the cardPicks index
								for (i = 0; i < cardAmountInput; i++) {
									tempInt = cardPicks[i];

									for (j = i + 1; j < cardAmountInput; j++) {
										if (cardPicks[j] > tempInt)
											cardPicks[j]--;
									}
								}

								// Inputs the card
								for (i = 0; i < cardAmountInput; i++) {
									// Saves the card value
									if (turnCycle[playerTurn] == 2)
										cardSave(bot1Head, &linkedListTemp2, cardPicks[i]);
									else if (turnCycle[playerTurn] == 3)
										cardSave(bot2Head, &linkedListTemp2, cardPicks[i]);
									else if (turnCycle[playerTurn] == 4)
										cardSave(bot3Head, &linkedListTemp2, cardPicks[i]);

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
												
												// Checks so l never go below 0
												if (l < 0)
													l = 3;
												
												// Checks so l never go above 3;
												l %= 4;

												if (!playerStats[turnCycle[l] - 1].isAlreadyWin)
													break;
											}
											while (true);

											rounds = l;
											doSkip(turnCycle, l, reversed);
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
											// Cleans isBotHaveTheColor
											for (j = 0; j < 4; j++)
												isBotHaveTheColor[j] = false;
											
											// Checks if the bot have the color
											for (j = 0; j < (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : (turnCycle[playerTurn] == 4 ? bot3Cards : 0))); j++) {
												// Checks so the system wont check the inputted wild
												if (j == cardPicks[i])
													continue;

												if (turnCycle[playerTurn] == 2)
													cardSave(bot1Head, &linkedListTemp3, j);
												else if (turnCycle[playerTurn] == 3)
													cardSave(bot2Head, &linkedListTemp3, j);
												else if (turnCycle[playerTurn] == 4)
													cardSave(bot3Head, &linkedListTemp3, j);
												
												if (strcmp(linkedListTemp3.color, "Blue") == 0)
													isBotHaveTheColor[0] = true;
												else if (strcmp(linkedListTemp3.color, "Red") == 0)
													isBotHaveTheColor[1] = true;
												else if (strcmp(linkedListTemp3.color, "Green") == 0)
													isBotHaveTheColor[2] = true;
												else if (strcmp(linkedListTemp3.color, "Yellow") == 0)
													isBotHaveTheColor[3] = true;
												else if (strcmp(linkedListTemp3.color, "Black") == 0) {
													for (k = 0; k < 4; k++)
														isBotHaveTheColor[k] = true;
													
													break;
												}	
											}

											// This code runs to prevent the player didn't pick a color
											if ((turnCycle[playerTurn] == 2 && bot1Cards == 1) || (turnCycle[playerTurn] == 3 && bot2Cards == 1) || (turnCycle[playerTurn] == 4 && bot3Cards == 1)) {
												for (i = 0; i < 4; i++)
													isBotHaveTheColor[i] = true;
											}

											if (strcmp(linkedListTemp2.type, "+4") == 0) {
												currPlus += 4;
												inPlusCondition = true;
											}

											doWild(turnCycle, playerTurn, &linkedListTemp2, isBotHaveTheColor);

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
									else if (cardPicks[i] == (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : bot3Cards)) - 1) {
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

								printf("\nPress \'Enter\' to continue");
								getchar();
							}

							// Grab a card from a draw pile
							else if (rng2 == 1) {
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

								// Checks whether the bot will input the card or no
								botPutACard = false;
								cardSave(discardHead, &linkedListTemp, discardPileCount - 1);

								for (i = 0; i < (turnCycle[playerTurn] == 2 ? bot1Cards : (turnCycle[playerTurn] == 3 ? bot2Cards : (turnCycle[playerTurn] == 4 ? bot3Cards : 0))); i++) {
									if (turnCycle[playerTurn] == 2)
										cardSave(bot1Head, &linkedListTemp2, i);
									else if (turnCycle[playerTurn] == 3)
										cardSave(bot2Head, &linkedListTemp2, i);
									else if (turnCycle[playerTurn] == 4)
										cardSave(bot3Head, &linkedListTemp2, i);

									if (strcmp(linkedListTemp.color, linkedListTemp2.color) == 0 || (strcmp(linkedListTemp.type, linkedListTemp2.type) == 0 && strcmp(linkedListTemp2.type, "Normal") != 0) || (linkedListTemp.number == linkedListTemp2.number && linkedListTemp2.number != -1) || strcmp(linkedListTemp2.type, "+4") == 0 || strcmp(linkedListTemp2.type, "Wild") == 0) {
										// Logic for bot 1
										if (turnCycle[playerTurn] == 2) {
											if (strcmp(linkedListTemp2.type, "+4") == 0) {
												if (reversed) {
													if (playerTurn == 0) {
														if ((turnCycle[3] == 1 && playerCards == 1) ||
														(turnCycle[3] == 2 && bot1Cards == 1) ||
														(turnCycle[3] == 3 && bot2Cards == 1) ||
														(turnCycle[3] == 4 && bot3Cards == 1))
														botPutACard = true;
													}
													else {
														if ((turnCycle[playerTurn - 1] == 1 && playerCards == 1) ||
														(turnCycle[playerTurn - 1] == 2 && bot1Cards == 1) ||
														(turnCycle[playerTurn - 1] == 3 && bot2Cards == 1) ||
														(turnCycle[playerTurn - 1] == 4 && bot3Cards == 1))
														botPutACard = true;
													}
												}
												else {
													if ((turnCycle[(playerTurn + 1) % 4] == 1 && playerCards == 1) ||
														(turnCycle[(playerTurn + 1) % 4] == 2 && bot1Cards == 1) ||
														(turnCycle[(playerTurn + 1) % 4] == 3 && bot2Cards == 1) ||
														(turnCycle[(playerTurn + 1) % 4] == 4 && bot3Cards == 1))
														botPutACard = true;
												}
											}
											else
												botPutACard = true;
										}

										// Logic for other bot
										else
											botPutACard = true;
										
										break;
									}
								}

								printf("\nBot %d grabs a card, Press \'Enter\' to conntinue", turnCycle[playerTurn] - 1);
								getchar();
							}

							break;
						}
						while (true);

						if (botPutACard) {
							botPutACard = false;

							continue;
						}
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

					if (playersLeft == 4) {
						printf("1st ");

						// Updates the file
						stats[turnCycle[playerTurn] - 1]++;
						statsFile = fopen("stats.evan", "wb");

						for (i = 0; i < 4; i++)
							fwrite(&stats[i], sizeof(stats[i]), 1, statsFile);

						fclose(statsFile);
					}
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
				botPutACard = false;
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
			do
			{
				do
				{
					system("cls");
					logo();

					printf(" Instructions \n");
					printf("==============\n\n");

					printf("1. Opening\n");
					printf("2. Cards\n");
					printf("3. Rules\n");
					printf("4. Closing\n");
					printf("5. Main Menu\n\n");

					printf("Your Choice : ");
					scanf("%d", &instructionsWarp);
					while (getchar() != '\n');
				}
				while (instructionsWarp != 1 && instructionsWarp != 2 && instructionsWarp != 3 && instructionsWarp != 4 && instructionsWarp != 5);

				if (instructionsWarp == 1) {
					system("cls");
					logo();

					printf(" Opening \n");
					printf("=========\n\n");

					printf("Welcome to UNO, the fun card game to play with. Your objectives is to get rid all of your\n");
					printf("cards and the first one to get rid of the card wins. This game consists of 4 players\n");
					printf("that include 1 player and 3 bots.\n\n");

					printf("Press \'Enter\' to go back to instructions menu");
					getchar();
				}
				else if (instructionsWarp == 2) {
					system("cls");
					logo();

					printf(" What Each Card Does \n");
					printf("=====================\n\n");

					printf("Number: Doesn't have any action\n");
					printf("Skip: Skips the turn of the next player\n");
					printf("Reverse: Reverses the player turn\n");
					printf("+2: Adds 2 card to the next player\n");
					printf("Wild: A player who puts the card can choose any color\n");
					printf("+4: Adds 4 card to the next player and a player who puts the card can choose any color\n\n");

					printf(" Card Amounts \n");
					printf("==============\n\n");

					printf("- One 0 cards each color\n");
					printf("- Two other cards each color\n");
					printf("- Eight Wilds\n");
					printf("- Four Wild Draw Fours\n");
					printf("- Each player got 7 cards from the beginning\n\n");

					printf("Press \'Enter\' to go back to instructions menu");
					getchar();
				}
				else if (instructionsWarp == 3) {
					system("cls");
					logo();

					printf(" Main Rules \n");
					printf("============\n\n");

					printf("1. A player can input a card if:\n");
					printf("- The card has the same color\n");
					printf("- The card has the same type/number\n\n");

					printf("2. A player can stack the inputted card if the inputted card has the same type/number\n\n");

					printf("3. A player can input a Wild card or a +4 card anytime but it cannot be stacked\n\n");

					printf("4. A player must take 1 card if they have no card to be inputted\n\n");

					printf("5. Inputted plus card can be stacked if the next player have one\n");
					printf("- For example if a player puts +2, the next player can put a plus 2 to stack the plus\n");
					printf("  if they have one and the total plus becomes 4\n");
					printf("- A +2 can be stacked by +4 but a +4 can\'t be stacked by +2\n\n");

					printf(" Discard Pile Rules \n");
					printf("====================\n\n");

					printf("1. If the card is a Number, nothing will happen\n\n");

					printf("2. If the card is a Reverse, the turn cycle will be reversed, but the 1st player will\n");
					printf("   input the card first\n");

					printf("3. If the card is a Skip, the 1st player will get skipped\n\n");

					printf("4. If the card is a +2, the 1st player will get 2 cards\n\n");

					printf("5. If the card is a Wild, the 1st player can choose what color to put\n\n");

					printf("6. There will never be a +4 in the first card of discard pile\n\n");

					printf("Press \'Enter\' to go back to instructions menu");
					getchar();
				}
				else if (instructionsWarp == 4) {
					system("cls");
					logo();

					printf(" Closing \n");
					printf("=========\n\n");

					printf("Thanks for reading the instructions, have fun and remember\n");
					printf("#cheatingisforpussies\n\n");

					printf("Press \'Enter\' to go back to instructions menu");
					getchar();
				}
			}
			while (instructionsWarp != 5);
		}

		// Stats
		else if (mainWarp == 3) {
			system("cls");
			logo();

			printf(" Stats \n");
			printf("=======\n\n");

			printf("Player Wins : %d\n", stats[0]);
			printf("Bot 1 Wins : %d\n", stats[1]);
			printf("Bot 2 Wins : %d\n", stats[2]);
			printf("Bot 3 Wins : %d\n\n", stats[3]);

			printf("Press \'Enter\' to go back to main menu");
			getchar();
		}

		// Credits
		else if (mainWarp == 4) {
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
	while (mainWarp != 5);
	
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

void insertAtBeginning(Node** headRef, int* count, int cardNum, int num, char* type, char* color) {
    Node* current = (Node*)malloc(sizeof(Node));
    current -> cardNumber = cardNum;
    current -> number = num;
    strcpy(current -> type, type);
    strcpy(current -> color, color);
    (*count)++;
    
    current -> next = (*headRef);
    (*headRef) = current;
}

void insertAtMiddle(Node** headRef, int* count, int cardNum, int num, char* type, char* color, int index) {
    Node* current = (Node*)malloc(sizeof(Node));
    current -> cardNumber = cardNum;
    current -> number = num;
    strcpy(current -> type, type);
    strcpy(current -> color, color);
    (*count)++;
    
    Node *newNode;
    newNode = (*headRef);
    
    int i;
    for (i = 0; i < index - 1; i++) {
        newNode = newNode -> next;
    }
    current -> next = newNode -> next;
    newNode -> next = current;
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
	else {
		(*tailRef) -> next = current;
	}
	
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

void cardSave(Node* node, CardData *linkedListTemp, int index) {
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

void doSkip(int turnCycle[], int playerTurn, bool reversed) {
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
}

void doWild(int turnCycle[], int playerTurn, CardData *linkedListTempPtr, bool isBotHaveTheColor[]) {
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
	}

	// If the turn is bot 3's
	else if (turnCycle[playerTurn] == 4) {
		colorPicker = rand() % 4 + 1;
	}

	// If the turn is the other bot's
	else {
		do
		{
			colorPicker = rand() % 4 + 1;

			if (isBotHaveTheColor[colorPicker - 1])
				break;
		}
		while (true);
	}

	// Changes the color
	if (colorPicker == 1)
		strcpy(wildCardInput, "Blue");
	else if (colorPicker == 2)
		strcpy(wildCardInput, "Red");
	else if (colorPicker == 3)
		strcpy(wildCardInput, "Green");
	else if (colorPicker == 4)
		strcpy(wildCardInput, "Yellow");

	// Changes the color of the wild card
	strcpy(linkedListTempPtr -> color, wildCardInput);
}

void cardPrint(CardData linkedListTemp) {
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

bool canInputCard(Node* node, CardData linkedListTemp, int playerCards) {
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
