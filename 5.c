#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _GNU_SOURCE
#define FILENAME "input_5"
#define ROW 999
#define COL 999

int findThermal(int ** grid);
void printGrid(int ** grid, int row, int col);
void parseLine(int * x, int * y, char * line, int size);
int ** makeGrid(int row, int col);
int main (void) 
{
    FILE * fp = fopen(FILENAME, "r");
    // char * line = "976,35 -> 24,987";
    char * line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int ** grid = makeGrid(ROW, COL);
    // printGrid(grid, ROW, COL);
    int x[2] = {0};
    int y[2] = {0};
    while ((read = getline(&line, &len, fp)) != -1)
    {
        parseLine(x, y, line, read -1);        
        plotCoords(grid, x, y);
        for (int i = 0; i < 2; i++)
        {
            printf("x: %d, y: %d\n", x[i], y[i]);
        }
    }
    for (int i = 0; i < COL; i++){
        //grid[0][i] = 0;
    }
    printf("\n");
    // printGrid(grid, ROW, COL);
    // parseLine(x, y, line, strlen(line));
    printf("\n%d\n", findThermal(grid));
}

int findThermal(int ** grid)
{
    int thermal = 0;
    for (int i = 1; i < ROW; i++){
        for (int j = 0; j < COL; j++)
        {
            if (grid[i][j] > 1) 
            {
                thermal++;
            }
        }
    }
    return thermal;
}

void parseLine(int * x, int * y, char * line, int size)
{
    int digitCount = 0;
    char * digitStr = NULL;
    int coord = 0;
    for (int i = 0; i <= size; i++)
    {
        if (isdigit(line[i]))
        {
            digitCount++;
        }
        else
        {
            if (!digitCount)
            {
                continue;
            }
            digitStr = calloc(digitCount, sizeof(char));
            for (int j = 0; j < digitCount; j++)
            {
                digitStr[j] = line[i - digitCount + j];
                
            }
            digitCount = 0;
            switch (coord) {
                case 0 :
                    x[0] = atoi(digitStr);            
                    break;
                case 1 :
                    y[0] = atoi(digitStr);
                    break;
                case 2 :
                    x[1] = atoi(digitStr);
                    break;
                case 3 :
                    y[1] = atoi(digitStr);
                    break;
                case 4 :
                    coord = 0;
                    break;
            free(digitStr);
            }           
            coord++;
            
        }
    }    
    free(digitStr);
    return;
}

void plotCoords(int ** grid, int * x, int * y)
{
    if ( x[0] < x[1] && y[0] == y[1])
    {
        for (int i = x[0]; i <= x[1]; i++)
        {
            grid[i][y[0]]++;
        }
    }
    if ( x[0] > x[1] && y[0] == y[1])
    {
        for (int i = x[0]; i >= x[1]; i--)
        {
            grid[i][y[0]]++;
        }
    }
    if ( x[0] == x[1] && y[0] > y[1])
    {
        for (int i = y[0]; i >= y[1]; i--)
        {
            grid[x[0]][i]++;
        }
    }
    if ( x[0] == x[1] && y[0] < y[1])
    {
        for (int i = y[0]; i <= y[1]; i++)
        {
            grid[x[0]][i]++;
        }
    }

    // Diags
    if ( x[0] < x[1] && y[0] < y[1])
    {
        int j = x[0];
        for (int i = y[0]; i <= y[1]; i++)
        {
            grid[j][i]++;
            j++;
        }
    }
    if ( x[0] < x[1] && y[0] > y[1])
    {
        int j = x[0];
        for (int i = y[0]; i >= y[1]; i--)
        {
            grid[j][i]++;
            j++;
        }
    }
    if ( x[0] > x[1] && y[0] > y[1])
    {
        int j = x[0];
        for (int i = y[0]; i >= y[1]; i--)
        {
            grid[j][i]++;
            j--;
        }
    }
    if ( x[0] > x[1] && y[0] < y[1])
    {
        int j = x[0];
        for (int i = y[0]; i <= y[1]; i++)
        {
            grid[j][i]++;
            j--;
        }
    }
}

void printGrid(int ** grid, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ",grid[i][j]);
        }
        printf("\n");
    }
}

int ** makeGrid(int row, int col)
{
    int ** grid = NULL;
    grid = calloc(row, sizeof(int));
    for (int i = 0; i < col; i++)
    {
        *(grid + i) = calloc(col, sizeof(int));
    }
    return grid;    

}