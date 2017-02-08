/*******************************************Filename: decompress_ke.c*************************************************/
/*******************************************Header Filename: "mtar.h"***********************************************/
/************************************************Author: Sumit Kumar************************************************/
/*******************************************LICENSE: MIT License****************************************************/
/****************************************Copyright (c) [2016] [sumit kumar]*****************************************/

#include "mtar.h"

char *find_word(char *string){
	int i = 0;
	if ( string[0] == '$' && 0 < atoi(string+1) && atoi(string+1) <= TABLE_SIZE) {
		
		char *ret = malloc(sizeof(string) + KEY_SIZE);
		char int_len[10] = {0};
		memset(int_len, 0, 10);
		sprintf(int_len, "%d", atoi(string+1));
		sprintf (ret, "%s%s", token_table[atoi(string+1)], string + strlen(int_len) + 1) ;
		return ret;
	}
	return string;
}

int keyword_decompress(char *input_file, char *output_file)
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
				fprintf(fout, "%s", find_word(buff));
				count = 0;
			}
		}

		while (isspace(ch)) {
			fprintf(fout, "%c", ch);
			ch = fgetc(fin);
		}

		if (!isspace(ch)) {

			if (ch != '\n' || ch != '\t') {
				if (ch == (char)225) {
					ch = '$';
					fprintf(fout, "%c", ch);
					continue;
				}
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
