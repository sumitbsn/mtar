#ifndef PROTOTYPE_H
#define PROTOTYPE_H

int dir_compress(char *, int );
int dir_decompress(char *);
int read_token_table(char *);
char *find_token_index(char *);
int keyword_compress(char *, char *);
int runlength_compress(char *, char *);
char *find_word(char *);
int keyword_decompress(char *,char *);
int runlength_decompress(char *, char *);
STACK* initstack(int );
STACK clean_stack(STACK *);
int pop(STACK *);

#endif
