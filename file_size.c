#include <stdlib.h>
#include <stdio.h>
#include "file_size.h"
#define FILENAME "input_1"


int get_file_size(char* FileName) {
	FILE * fp = fopen(FileName, "r");
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i = 0;
	if (NULL == fp )
	{
		return 0;
	}

	while((read = getline(&line, &len, fp)) != -1) 
	{
		i++;
	}
	fclose(fp);
	if(line)
	{
		free(line);
	}
	return i;
}
