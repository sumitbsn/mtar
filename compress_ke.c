/*******************************************Filename: compress_ke.c*************************************************/
/*******************************************Header Filename: "mtar.h"***********************************************/
/************************* Description : Replace more occuring word for token value. *******************************/
/************************************************Author: Sumit Kumar************************************************/
/*******************************************LICENSE: MIT License****************************************************/
/****************************************Copyright (c) [2016] [sumit kumar]*****************************************/

#include "mtar.h"

int read_token_table(char* token_file) {
	char *line = 0;
    ssize_t len = 0;

	FILE *table = fopen(token_file, "r");	
	while(getline(&line, &len, table) != -1)
	{	
		char index[TABLE_SIZE];
		char *key = (char*)malloc(KEY_SIZE);
		memset(key, KEY_SIZE, '\0');
		sscanf(line,"%s %s", key, index);
		strcpy((token_table[atoi(index+1)]),key);
	}
	fclose(table);
}

char *find_token_index(char *string){
	int i = 0;
	int max = 0;
	char *ret = malloc(strlen(string));
	for (i = 1; i <= TABLE_SIZE; i++)
	{
		if (  strncmp( string, token_table[i], strlen(token_table[i])) == 0) {
			if (strlen(token_table[i]) > max) {
				max = strlen(token_table[i]);
				memset(ret, strlen(string), '\0');
				sprintf(ret, "$%d", i);
				strcat(ret, (string + strlen(token_table[i])));
			
			}
		}
	}
	if (max > 0) return ret;
	return string;
}

int keyword_compress(char *input_file, char *output_file)
{
	
	FILE *fout = fopen(output_file,"w");

    int count=0;
    	
	FILE *fin = fopen(input_file,"r");
	if(fin == NULL)
	{
		printf("Invalid input %s\n",input_file);
	}
	
	read_token_table("token_table.dat");
	
	char buff[1000];
	memset(buff, 0, 1000);
	char ch;

	while((ch = fgetc(fin)) != EOF)
	{	
		if (isspace(ch)) {
			if (count) {
				fprintf(fout, "%s", find_token_index(buff));
				count = 0;
			}
		}

		while (isspace(ch)) {
			fprintf(fout, "%c", ch);
			ch = fgetc(fin);
		}

		if (!isspace(ch)) {

			if (ch != '\n' || ch != '\t') {
				if (ch == '$') ch = (char)225;
				buff[count++] = ch;
				buff[count] = '\0';
			}
			else {
				fprintf(fout, "%c", ch);
			}
		}
	}
	fclose(fin);
	fclose(fout);
	
}	

