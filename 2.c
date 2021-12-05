#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "file_size.h"

#define FILENAME "input_2"

int move(int * VPos, int * HPos, int distance, char* direction, int* depth);
int main(void) {
	int horizPos = 0;
	int vertPos = 0;
	FILE * fp = fopen(FILENAME, "r");
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	char * direction = NULL;
	int distance = 0;
	int depth = 0;
	while((read = getline(&line, &len, fp)) != -1)
	{
		char * token = strtok(line, " ");
		direction = token;
		while(token)
		{
			if(isdigit(token[0]))
			{
				distance = atoi(token);
			}
			token = strtok(NULL, " ");			

		}
		move(&vertPos, &horizPos, distance, direction, &depth);
	}
	printf("Distance Traveled: %d Depth: %d\n", vertPos * horizPos, depth);
	fclose(fp);
	if(line)
	{
		free(line);
	}
	return 0;

}


int move(int * VPos, int * HPos, int distance, char* direction, int* depth)
{
	printf("%s %d\n", direction, distance);
	printf("Start: A-%d\t H-%d\tD-%d", *VPos,*HPos,*depth);
	if (!strncmp("up", direction, strlen("up")))
	{
		 *VPos -= distance;
	}
	else if (!strncmp("down", direction, strlen("down")))
	{
		*VPos += distance;
	}
	else if (!strncmp("forward", direction, strlen("forward")))
	{
		*HPos += distance;
		*depth += (distance * *VPos);
	}
	printf("End: A-%d\t H-%d\tD-%d\n", *VPos,*HPos,*depth);
	return 0;
}
