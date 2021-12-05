#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#define FILENAME "input_1"
#define ARRLENGTH 3
int compareTwoNum(int num1, int num2);
int sumArray(int * numArr, int len);
int main(void) {
	FILE * fp = fopen(FILENAME, "r");
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int num = 0;
	int numInc = 0;
	int prevNum = -1;
	int numArr[3] = {0};
	int i = 0;
	if (NULL == fp )
	{
		return 0;
	}

	while((read = getline(&line, &len, fp)) != -1) 
	{
		if (3 == i )
		{
			i =0;
		}
		numArr[i] = atoi(line);
		if (numArr[2] != 0)
		{
			num = sumArray(numArr, ARRLENGTH);
			if (compareTwoNum(prevNum, num) > 0 && prevNum != -1)
			{
				numInc++;
			}
			prevNum = num;
		}
		i++;
	}
	fclose(fp);
	if(line)
	{
		free(line);
	}
	printf("%d", numInc);
	return 0;
}

/* Compare two numbers,
 * Return: 
 * 	1 - increase
 * 	-1 - decrease
 * 	0 - same
 */

int compareTwoNum(int num1, int num2)
{
	if (num1 < num2)
	{
		return 1;
	}else if (num1 > num2)
	{
		return -1;
	}else
	{
		return 0;
	}
}

int sumArray(int * numArr, int len)
{
	int sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum += numArr[i];
	}
	return sum;
}

