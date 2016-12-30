#include "mtar.h"

int runlength_compress(char *input_file, char* out_file) {
    
    FILE *fp_out = fopen(out_file, "w");
    char *line;
    ssize_t len;
    int count=0;
    FILE *fp;
    fp = fopen(input_file, "r");
    if (fp == NULL) printf("invalid file:%s \n", input_file);
	    
	while (getline(&line, &len, fp) != -1) {

		int freq[1000] = {0};
		char data[1000];
		memset(data, 0, 1000);
		int i = 0, j = 0, k = 0;
		while (i < strlen(line)) {
			if(line[i]==line[i-1]) 
			{
				freq[k-1]++;
				i++;
			}
			else 
			{
				data[k]=line[i];
				freq[k]++;
				k++;
				i++;
			
			}
		}
		for(i=0;i<k;i++) {
			if(isdigit(data[i]) == 0)	{
				if (data[i] == '\\')
					data[i] = (char)224;

				if(freq[i]<3) {
					for(j=0; j<freq[i]; j++)
						fprintf(fp_out,"%c",data[i]);
				}
				else
					fprintf(fp_out,"%d%c",freq[i], data[i]);
			}
			else 
			{ 
				for(j=0;j<freq[i];j++) {
					fprintf(fp_out,"\\%c",data[i]);
				}
			}
		}	
	}

    fclose(fp_out);
    fclose(fp);
}    

