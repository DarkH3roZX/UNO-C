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
// Draw Pile
typedef struct Node {
	int cardNumber;
	int number; // -1 if it's not a normal card type

	char type[8];
	char color[8];

	struct Node *next;
} Node;

// Linked List Helper
typedef struct {
	int cardNumber;
	int number;

	char type[8];
	char color[8];
} Temp1;

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
void insertAtBeginning(Node** headRef, int* count, int cardNum, int num, char* type, char* color);
void insertAtMiddle(Node** headRef, int* count, int cardNum, int num, char* type, char* color, int index);
void insertAtEnd(Node** headRef, Node** tailRef, int* count, int cardNum, int num, char* type, char* color);
void deleteAtBeginning(Node** headRef, int* count);
void deleteAtMiddle(Node** headRef, int* count, int index);
void deleteAtEnd(Node** headRef, Node** tailRef, int* count);
void cardDeckFinder(Node* node, Temp1 *cardDeckPtr, int index);
void printList(Node* node);
// Main Code
int main() {
	/*
	 Variables
	 */

	// File Pointers
	FILE *cards; // Card file

	// Card Deck Variables
	Node *cardHead = NULL, *cardTail = NULL;
	Temp1 linkedListTemp;

	int drawPileCount = 0;

	// Loop Variables
	int i, j, k, l;

	// Warp Variables
	int mainWarp;

	// Declaration Variables
	char startGameWord[16];

	// Temporary Variables;
	int tempInt;
	char tempChar;
	char tempString[100];
	
	// Rock Paper Scissors Variables
	int winnerRPS;
	int losersRPS[2];
	int winnersRPS[2];
	
	char playerChoicesRPS[4];

	bool rpsEnd;

	// Game Variables
	int rounds;
	int playersWon;
	int turnCycle[4];
	int podiumPlace[4];

	bool endGame;
	bool reversed;

	// Player Card Linked List
	Node *playerHead = NULL, *playerTail = NULL;
	Node *bot1Head = NULL, *bot1Tail = NULL;
	Node *bot2Head = NULL, *bot2Tail = NULL;
	Node *bot3Head = NULL, *bot3Tail = NULL;

	int playerCards;
	int bot1Cards;
	int bot2Cards;
	int bot3Cards;

	// RNG Variavles
	int rng1, rng2, rng3;

	// srand
	srand(time(NULL));
	
	/*
	 Utilities
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

			for (i = 0; i < 4; i++) {
				printf("%d. ", i + 1);
				
				if (turnCycle[i] == 1)
					printf("You");
				else if (turnCycle[i] == 2)
					printf("Bot 1");
				else if (turnCycle[i] == 3)
					printf("Bot 2");
				else if (turnCycle[i] == 4)
					printf("Bot 3");

				puts("");
			}

			printf("\nPress \'Enter\' to continue!");
			getchar();

			// Game Resetter
			endGame = false;
			rounds = 0;
			playersWon = 0;
			playerCards = 0;
			bot1Cards = 0;
			bot2Cards = 0;
			bot3Cards = 0;

			// Putting player cards
			for (i = 0; i < 7; i++) {
				// Pick a random card from draw pile
				rng1 = rand() % drawPileCount;

				// Changes the value of linkedListTemp to insert to the draw pile
				cardDeckFinder(cardHead, &linkedListTemp, rng1 + 1);

				// Puts a card into card deck
				insertAtEnd(&playerHead, &playerTail, &playerCards, linkedListTemp.cardNumber, linkedListTemp.number, linkedListTemp.type, linkedListTemp.color);
				
				// Deletes card from discard pile
				if (rng1 == 0)
					deleteAtBeginning(&cardHead, &drawPileCount);
				else if (rng1 == drawPileCount - 1)
					deleteAtEnd(&cardHead, &cardTail, &drawPileCount);
				else
					deleteAtMiddle(&cardHead, &drawPileCount, rng1);
			}
			system("cls");

			printList(playerHead);
			puts("");
			printList(cardHead);

			getchar();

			/*
			// Putting bot 1 cards
			for (i = 0; i < 7; i++) {

			}

			// Putting bot 2 cards
			for (i = 0; i < 7; i++) {

			}

			// Putting bot 3 cards
			for (i = 0; i < 7; i++) {

			}
			*/

			do
			{
				system("cls");
				logo();

				// Turn display
				printf("Players:\n");

				for (i = 0; i < 4; i++) {
					printf(" ");
					
					if (rounds % 4 == i) {

					}
					else {

					}
				}

				// 1st turn
				if (rounds % 4 == 0) {

				}

				// 2nd turn
				else if (rounds % 4 == 1) {

				}

				// 3rd turn
				else if (rounds % 4 == 2) {

				}

				// 4th turn
				else if (rounds % 4 == 3) {

				}
			}
			while (!endGame);
			

			getchar();
		}

		// Instructions
		else if (mainWarp == 2) {

		}

		// Credits
		else if (mainWarp == 3) {

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

void cardDeckFinder(Node* node, Temp1 *cardDeckPtr, int index) {
	while (node != NULL) {
		if (node -> cardNumber == index) {
			cardDeckPtr -> number = node -> number;
			strcpy(cardDeckPtr -> type, node -> type);
			strcpy(cardDeckPtr -> color, node -> color);

			break;
		}

		node = node -> next;
	}
}

void printList(Node* node) {
	while (node != NULL) {
		printf("%d %d %s %s\n", node -> cardNumber, node -> number, node -> type, node -> color);
		node = node -> next;
	}
	puts("");
}
