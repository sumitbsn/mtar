#ifndef MTAR_H
#define MTAR_H

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "struct.h"
#include "prototype.h"
#define TABLE_SIZE 12
#define KEY_SIZE 512
#define PATH_LENGTH 500

char token_table[TABLE_SIZE][KEY_SIZE];

#endif
