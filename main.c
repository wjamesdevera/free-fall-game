#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>	

typedef struct {
	int value;
	int xPos;
	int yPos;
	bool isCorrectAnswer;
} obstacle;

typedef struct {
	char profile;
	int xPos;
	int yPos;
} player;

int BOARDHEIGHT = 25;
int BOARDWIDTH = 50;
int BOARDXPOS = 20;
int BOARDYPOS = 0;

int playerScore = 0;

char *questions[100];
char *question;
char *answer;

void gotoxy(int x, int y) 
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/**
 * Function for rendering/printing borders of the game
*/
void renderBorders()
{
	int i;
	for (i = 0; i < BOARDHEIGHT; i++)
	{
		gotoxy(BOARDXPOS, i);
		printf("|");
		gotoxy((BOARDXPOS + BOARDWIDTH), i);
		printf("|");
	}
}

/**
 * render player score on the screen
*/
void renderGameScore()
{
	gotoxy(2, 2);
	printf("Score: %d", playerScore);
}

/**
 * render game question on the screen
*/
void renderGameQuestion() {
	gotoxy(2, 3);
	printf("%s", question);
}


#define MAX_LINES 100
#define MAX_LENGTH 100
char *questions[MAX_LINES];
int lineCount = 0; // MAX NUMBER OF LINES IN THE TEXT FILE
/**
 * Grab questions from a csv file or can be a text file
*/
void fetchGameQuestions() 
{
	FILE *questionFile;
	char buffer[MAX_LENGTH];
	
	questionFile = fopen("./game_qa/game_questions.csv", "r");
	if (questionFile == NULL)
	{
		printf("Error: could not open file. \n");
		return;
	}

	while (fgets(buffer, MAX_LENGTH, questionFile) != NULL && lineCount < MAX_LINES)
	{
		int len = strlen(buffer);
		if (len > 0 && buffer[len-1] == '\n')
		{
			buffer[len-1] = '\0'; // remove newline character
		}
		questions[lineCount] = (char*) malloc(sizeof(char) * (len+1));
		strcpy(questions[lineCount], buffer);
		lineCount++;
	}
	
	fclose(questionFile);
}

int randomNumberCount = 0;
char *randomNumbers[MAX_LINES];
void fetchRandomNumbers()
{
	FILE *file;
	char buffer[MAX_LENGTH];
	file = fopen("./game_qa/random_numbers.txt", "r");
	
	if (file == NULL)
	{
		printf("Error: could not open random numbers file\n");
		return;
	}

	while (fgets(buffer, MAX_LENGTH, file) != NULL && randomNumberCount < MAX_LINES)
	{
		int len = strlen(buffer);
		if (len > 0 && buffer[len-1] == '\n')
		{
			buffer[len-1] = '\0'; // remove newline character
		}
		randomNumbers[randomNumberCount] = (char*) malloc(sizeof(char) * (len+1));
		strcpy(randomNumbers[randomNumberCount], buffer);
		randomNumberCount++;
	}
	fclose(file);
}

void generateRandomQuesiton() 
{
	srand(time(NULL));
	int randomIndex = rand() % lineCount;
	question = strtok(questions[randomIndex], ",");
	answer =  strtok(NULL, ",");
}

char* generateRandomNumber()
{
	srand(time(NULL));
	int randomIndex = rand() % randomNumberCount;
	return randomNumbers[randomIndex];
}


int main(int argc, char *argv[])
{
	// fetchGameQuestions();
	// generateRandomQuesiton();
	// printf("\e[?25l"); // Makes cursor invisible
	// bool gameOn = true;
	// // while (gameOn)
	// // {
	// 	system("cls");
    // 	renderBorders();
	// 	renderGameScore();
	// 	renderGameQuestion();
	// }
	// printf("\e[?25h"); // Makes cursor visible
	fetchRandomNumbers();
	char *num = generateRandomNumber();
	printf("%s\n", num);
    return 0;
}
