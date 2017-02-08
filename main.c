/*******************************************Filename: main.c*************************************************/
/*******************************************Header Filename: "mtar.h"***********************************************/
/************************************************Author: Sumit Kumar************************************************/
/*******************************************LICENSE: MIT License****************************************************/
/****************************************Copyright (c) [2016] [sumit kumar]*****************************************/

#include "mtar.h"

int main(int argc, char **argv)
{
	char dir_path[PATH_LENGTH];
	int compress_type = 0;
	if(argc ==2) dir_decompress(argv[1]) ;	
	if(argc == 3)
	{
		strcpy(dir_path, argv[2]);
		
		if(strcmp(argv[1], "-rl") == 0)
		{
			compress_type = 1;
			dir_compress(dir_path, compress_type);
		}
		else if(strcmp(argv[1],"-ke") == 0)
		{
			compress_type = 2;
			dir_compress(dir_path, compress_type);
		}
		else
			printf("Invalid Input\n");
	}
	if(argc == 4)
	{
		strcpy(dir_path, argv[3]);
		if((strcmp(argv[1], "-rl") == 0) && (strcmp(argv[2], "-ke") == 0))
		{
			compress_type = 3;
			dir_compress(dir_path, compress_type);
		}
		else if((strcmp(argv[1], "-ke") == 0) && (strcmp(argv[2], "-rl") == 0))
		{
			compress_type = 4;
			dir_compress(dir_path, compress_type);
		}
		else
			printf("Invalid Input\n");
	}
	if((argc < 2) || (argc > 4))
		printf("Invalid Input\n");
	return 0;
}
