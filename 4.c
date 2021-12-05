#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "input_4"
#define BOARDS 100
#define ROW 5
#define COL 5

int calcAnswer(int board[][COL], int selection);
void printBoard(int board[][COL]);
int check_victory( int board[][COL], int row, int col);
int get_guess( char * guesses, int * intGuess);
void printBoards( int boards[][ROW][COL], int numBoards);
void makeGuess(int * guesses, int board[][ROW][COL], int numGuess);
int main (void)
{
	int bingoBoards[BOARDS][ROW][COL] = {0};
	FILE * fp = fopen(FILENAME, "r");
	char * line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char * token = NULL;
	int tkCount = 0;
	int lineCount = 0;
	int board = 0;
	int value = 0;
	char guess[500] = {0};
	char junk[500] = {0};
	int intGuess[500] = {0};	
	fgets(guess, 500, fp);
	fgets(junk, 500, fp);
	while ((read = getline(&line, &len, fp)) != -1)
	{
		if (lineCount % 6 == 0 && lineCount != 0) 
		{
			board++;
		}
		tkCount = 0;
		token = strtok(line, " ");
		while (token)
		{
			value = atoi(token);
			bingoBoards[board][lineCount%6][tkCount] = value;
			tkCount++;
			token = strtok(NULL, " ");

						
		}
		lineCount++;
	}
	int numGuess = get_guess(guess, intGuess);
	makeGuess(intGuess, bingoBoards, numGuess);
	fclose(fp);
	if(line)
	{
		free(line);
	}
	/*printf("%d", numGuess);
	for (int i = 0; i < numGuess; i++)
	{
		printf("%d\n", intGuess[i]);
	}*/
	//printBoards(bingoBoards, BOARDS);
	return 0;
}

void makeGuess(int * guesses, int board[][ROW][COL], int numGuess)
{
	int victories = 0;
	int victoryBoard[BOARDS] = {0};
	int selection = 0;
	for (int i = 0; i < numGuess; i++)
	{
		selection = guesses[i];
		for (int i = 0; i < BOARDS; i++)
		{
			for (int v = 0; v <= victories; v++)
			{
				//part2
				if ( i == victoryBoard[v] && victoryBoard[0] != 0)
				{
					break;
				}
				else if (v == victories)
				{
					for (int j = 0; j < ROW; j++)
					{
						for (int k = 0; k < COL; k++)
						{
							if (selection == board[i][j][k])
							{
								board[i][j][k] += 100;
								if (check_victory(board[i], j, k))
								{
									//part2							
									if (98 == victories)
									{
										printf("\nWinning Board\nrow: %d, col: %d, sel: %d\n\n", j, k, selection);
										printBoard(board[i]);
										printf("\nAnswer: %d\n",calcAnswer(board[i], selection));
										return;
									}
									victoryBoard[victories] = i;
									victories++;
									//return;
								}
							}
						}
					}
				}
			}
		}
	}
}

int calcAnswer(int board[][COL], int selection)
{
	int sum = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] < 100)
			{
				sum += board[i][j];
			}
		}
	}
	return sum * selection;


}

void printBoard(int board[][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%d ", board[i][j]);
		}		
		printf("\n");
	}
}

//When guess is made successful on a board, pass board/row/col and check
int check_victory( int board[][COL], int row, int col)
{
	int rowVictory = 1;
	int colVictory = 1;
	for(int i = 0; i < ROW; i++)
	{
		//check Col
		if (board[row][i] < 100) 
		{
			rowVictory = 0;
		}

		//check Row
		if (board[i][col] < 100)
		{
			colVictory = 0;
		}		
	}
	return (rowVictory||colVictory);
}

int get_guess( char * guesses, int * intGuess)
{
	int numGuess = 0;
	int value = 0;
	char * token = strtok(guesses, ",");
	while (token)
	{
		value = atoi(token);
		intGuess[numGuess] = value;
		token = strtok(NULL, ",");
		numGuess++;
	}
	return numGuess;
	
}

void printBoards( int boards[][ROW][COL], int numBoards)
{
	for (int i = 0; i < numBoards; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			for (int k = 0; k < COL; k++)
			{
				printf("%d ", boards[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
		

