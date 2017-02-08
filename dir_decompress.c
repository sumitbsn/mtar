/*******************************************Filename: dir_decompress.c*************************************************/
/*******************************************Header Filename: "mtar.h"***********************************************/
/************************************************Author: Sumit Kumar************************************************/
/*******************************************LICENSE: MIT License****************************************************/
/****************************************Copyright (c) [2016] [sumit kumar]*****************************************/

#include "mtar.h"

int dir_decompress(char *src_dir_path)
{
	char command_mkdir[PATH_LENGTH];
	char dest_dir_path[PATH_LENGTH];
	strcpy(dest_dir_path, src_dir_path);
	strcat(dest_dir_path, ".dc");
	strcpy(command_mkdir, "mkdir -p ");
	strcat(command_mkdir, dest_dir_path);
	
	system(command_mkdir);

	char command_find[PATH_LENGTH];
	strcpy(command_find, "find ");
	strcat(command_find, src_dir_path);

	char *file_path;
	char src_file_path[PATH_LENGTH];
	memset(src_file_path, PATH_LENGTH, 0);
	
	FILE *fp_cmd = popen(command_find, "r");
	if (fp_cmd == NULL) return -1;
	
    ssize_t len;

	while (getline(&file_path, &len, fp_cmd) != -1) {

		int i = 0;
		while (file_path[i] != '\n') {
			src_file_path[i] = file_path[i];
			i++;
		}
		src_file_path[i]= '\0';

		char dest_file_path[PATH_LENGTH];
		strcpy(dest_file_path, dest_dir_path);
		strcat(dest_file_path, "/");
		strcat(dest_file_path, src_file_path+strlen(src_dir_path)+1 );


		char command[PATH_LENGTH];    
		sprintf(command, "dirname %s", dest_file_path);

		FILE *fp_dirname = popen(command, "r");
		char parent_dir[PATH_LENGTH] = {0};
		fgets(parent_dir, sizeof(parent_dir), fp_dirname);
		pclose(fp_dirname);

		i = 0;
		while (parent_dir[i] != '\n') {
			i++;
		}
		parent_dir[i]= '\0';

		struct stat sb = {0};

    	if (stat(parent_dir, &sb) == 0 && S_ISDIR(sb.st_mode))
    	{
			//printf("dir already exist! %s\n",parent_dir);
		}	
		else
		{
			char command_submkdir[PATH_LENGTH] = {0};
			sprintf(command_submkdir, "mkdir -p %s", parent_dir);
			system(command_submkdir);
		}

		
    	if (stat(src_file_path, &sb) == 0 && S_ISDIR(sb.st_mode))
    	{
			//printf("it's a dir! %s\n", src_file_path);
		}	
		else
		{
			
			char *rl = NULL, *ke = NULL;
			rl = strstr(src_file_path, ".rl");
			ke = strstr(src_file_path, ".ke");
 
			if (rl != NULL && ke == NULL)
			{
				char dest[PATH_LENGTH] = {0};
				memcpy(dest, dest_file_path, strlen(dest_file_path)- 3) ;
				dest[strlen(dest_file_path) - 3] = '\0';

				runlength_decompress(src_file_path, dest);

			}
			if (rl == NULL && ke != NULL)
			{
				char dest[PATH_LENGTH] = {0};
				memcpy(dest, dest_file_path, strlen(dest_file_path)- 3) ;
				dest[strlen(dest_file_path) - 3] = '\0'; 
				keyword_decompress(src_file_path, dest);
			}


			if ((rl != NULL && ke != NULL) && rl-ke > 0)
			{
				char dest[PATH_LENGTH] = {0};
				memcpy(dest, dest_file_path, strlen(dest_file_path)- 3) ;
      			dest[strlen(dest_file_path) - 3] = '\0'; 
				runlength_decompress(src_file_path,dest);
				char new_dest_file_path[PATH_LENGTH] = {0};
				memcpy(new_dest_file_path, dest, strlen(dest)- 3) ;
      			new_dest_file_path[strlen(dest) - 3] = '\0'; 
		
				keyword_decompress(dest,new_dest_file_path);
				remove(dest);
			}
			if ((rl != NULL && ke != NULL) && ke-rl > 0)
			{
				char dest[PATH_LENGTH] = {0};
				memcpy(dest, dest_file_path, strlen(dest_file_path)- 3) ;
      			dest[strlen(dest_file_path) - 3] = '\0'; 
				keyword_decompress(src_file_path, dest);
				char new_dest_file_path[PATH_LENGTH] = {0};
				memcpy(new_dest_file_path, dest, strlen(dest)- 3) ;
      			new_dest_file_path[strlen(dest) - 3] = '\0'; 
				runlength_decompress(dest, new_dest_file_path);
				remove(dest);
			}
		}
	}
	pclose(fp_cmd);
}
