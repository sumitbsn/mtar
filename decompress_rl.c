#include "mtar.h"

STACK* initstack(int size)
{
    STACK *s;
    s = (STACK *)malloc(sizeof(STACK));
    s->stack = malloc(sizeof(int ) * size);
    s->top = -1;
    s->size = size;
    return s;
}
STACK clean_stack(STACK * s)
{
    free(s->stack);
    free(s);
}

push(STACK * s, int data)
{
    if(s->top == s->size)
    {    
        printf("Stack overflow\n");
    }
    *(s->stack+(++s->top)) = data;
}

int pop(STACK * s)
{
    if(s->top == -1)
    {
        return -1;
    }
    return *(s->stack+s->top--);
}
print_stack(STACK *s)
{
    int i;
    for(i = s->top; i >= 0; i--)
    {
        printf("%d\n",*(s->stack+i));
    }
}

int runlength_decompress(char *input_file, char* out_file)
{
    printf("Runlength decompression is processing!\n");
    
    FILE *fp_out = fopen(out_file, "w");
    char *line = 0;
    ssize_t len;
    int count=0;
    FILE *fp;
    int init_val=10;
    fp = fopen(input_file, "r");
    if (fp == NULL) 
    printf("invalid file:%s \n", input_file);
	while (getline(&line, &len, fp) != -1) {
        int i = 0, k = 0;
		while (i < strlen(line)) {
			if((line[i] == '\\' ) && isdigit(line[i+1]))
			{
				fprintf(fp_out,"%c",line[i+1]);
                i = i+2;
            }
            else
            {
                if(isdigit(line[i]))
                {
                    int j = 0, val = 0, popval = 0;
                    int power; 
                    STACK *s = initstack(init_val);
                    while(isdigit(line[i]))
                        push(s, (int)line[i++]-48);
                    while((popval = pop(s)) >= 0) 
                        val = val + popval * (int) pow(10,j++);
                    clean_stack(s);
                    for(j = 0; j < val; j++)
                    {
                        if(line[i] == (char)224 ) {
                            line[i] = '\\' ;
                        }
                        fprintf(fp_out,"%c",line[i]);
                    }
                    i++;
				}
                else
                {
                    if(line[i] == (char)224 )
                    {
                        line[i] = '\\';
                    }
                    fprintf(fp_out,"%c",line[i]);
                    i++;
                }
            }
        }
    }
    fclose(fp);
    fclose(fp_out);
    return 0;
    
}
