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
	int xPos;
	int yPos;
} player;

int BOARDHEIGHT = 25;
int BOARDWIDTH = 50;
int BOARDXPOS = 20;
int BOARDYPOS = 0;

int playerScore = 0;

char *questions[100];

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

void renderGameScore()
{
	gotoxy(2, 2);
	printf("Score: %d", playerScore);
}

void renderGameQuestion() {
	
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
		return 1;
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
}



int main(int argc, char *argv[])
{
	// printf("\e[?25l"); // Makes cursor invisible
	// bool gameOn = true;
	// while (gameOn)
	// {
	// 	system("cls");
    // 	renderBorders();
	// }
	// printf("\e[?25h"); // Makes cursor visible

	fetchGameQuestions();
	int i;
	for (i = 0; i < lineCount; i++)
	{
		printf("%s\n", questions[i]);
	}
    return 0;
}
