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

#include "storing.h"

void manage_pal_data(char *word, vector *indexing_vector, int typeof_exe);
void manage_pal_file(char *file, vector *indexing_vector);
void manage_dic_data1(item got_char, item got_vector);
void manage_dic_data2(item got_char, item got_vector);
void manage_dic_file(char *file, void (*manage_dic_data)(item, item), vector *indexing_vector);
int read_pal_file(FILE* pal_file, char *first_word, char *second_word, int *typeof_exe);
#endif
