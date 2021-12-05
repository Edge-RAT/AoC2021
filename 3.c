#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "file_size.h"
#define FILENAME "input_3"

double binToInt(int * bin, int len, int inverse);
int populateArr(char ** binArr, char * commonBinString, int arrSize, int numToMatch);
int findCommonBit(char ** binArr, int arrSize, int index);
int main(void)
{
	FILE * fp = fopen(FILENAME, "r");
	char * line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int * binArr = NULL;
	int line_size = 0;
	int inverse = 0;
	double gamma = 0;
	double epsilon = 0;
	char common[13] = {0};
	int fileSize = get_file_size(FILENAME);
	char readings[13] = {0};
	char **arrOfReadings = calloc(fileSize, sizeof(readings));
	int lineCount = 0;
	while ((read = getline(&line, &len, fp)) != -1)
	{
		if (NULL == binArr)
		{
			line_size = read - 1;
			binArr = (int*)calloc(line_size, sizeof(int));
		}
		arrOfReadings[lineCount] = calloc(13, sizeof(char));
		strncpy(arrOfReadings[lineCount++], line, line_size);		
		for (int i = 0; i < line_size; i++)
		{
			if('1' == *(line+i))
			{
				*(binArr + i) += 1;
			}
			else
			{
				*(binArr + i) -= 1;
			}
		}
		
	}
	for (int i = 0; i < line_size; i++)
	{
		if(*(binArr + i) > 0)
		{
			printf("1");
			common[i] = '1';
		}
		else
		{
			printf("0");
			common[i] = '0';
		}
		printf(":%d,", *(binArr + i));
	}
	printf("\ncommon: %s\n", common);
	gamma =	binToInt(binArr, line_size, inverse);
	printf("\n%.0f", gamma);
	inverse = 1;  
	epsilon = binToInt(binArr, line_size, inverse);
	printf("\n%.0f",epsilon);
	printf("\nAnswer: %.0f", epsilon * gamma);
	fclose(fp);
	if(line)
	{
		free(line);
	}

	//PART 2
	for (int i = 0; i < line_size; i++ )
	{
		printf("\n%d, %d, %d, %s", \
				i, \
				fileSize, \
				findCommonBit(arrOfReadings, fileSize, i), \
				common);
		if(findCommonBit(arrOfReadings, fileSize, i) >= 0)
		{
			common[i] = '0';
			fileSize = populateArr(arrOfReadings, common, fileSize, i + 1);
		}
		else 
		{
			common[i] = '1';
			fileSize = populateArr(arrOfReadings, common, fileSize, i + 1);
		}

		if(1 == fileSize)
		{
			printf("\n%s",arrOfReadings[0]);
			break;
		}
/*		if ( fileSize < 10 )
		{
			printf("\n******\n");
			for (int j = 0; j < fileSize; j++)
			{
				printf("%s\n",arrOfReadings[j]);
			}
			printf("******");
		}*/
	}
	printf("\n%d", fileSize);
	for (int i = fileSize; i >= 0; i--)
	{
		if(arrOfReadings[i])
		{
			free(arrOfReadings[i]);
		}
	}
	return 0;
	
}

int findCommonBit(char ** binArr, int arrSize, int index)
{
	int total = 0;
	for (int i = 0; i < arrSize; i++)
	{
//		printf("%s\n",binArr[i]);
		if('1' == *(*(binArr+i)+index))
		{
			total += 1;
		}
		else
		{
			total -= 1;
		}
	}
	return total;
}

int populateArr(char ** binArr, char * commonBinString, int arrSize, int numToMatch)
{
	int matches = 0;
	int j = 0;
	for(int i = 0; i < arrSize; i++)
	{
		for(j = 0; j < numToMatch; j++)
		{
			if(binArr[i][j] == commonBinString[j])
			{
				
			}
			else
			{
				break;
			}
		}
		if (j == numToMatch)
		{
			binArr[matches] = binArr[i];
			matches++;
		}
	}
	return matches;	

}

double binToInt(int * bin, int len, int inverse)
{
	double sum = 0;
	for (int i = 0; i < len; i++)
	{
		if(inverse)
		{
			if( *(bin + len -1 -i) <= 0)
			{
				sum += pow(2, i);
			}

		}
		else
		{
			if( *(bin + len -1 -i) > 0)
			{
				sum += pow(2, i);
			}
		}
	}
	return sum;
}
			

