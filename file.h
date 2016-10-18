/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* file.h
* All functions related to reading/creating/managing files.
***************************************************************/

#ifndef fileHeader
#define fileHeader

#include "defs.h"

void manage_dic_file(FILE *dic_file);
int read_pal_file(FILE* pal_file, char *first_word, char *second_word, int *typeof_exe);
#endif
