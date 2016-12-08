/***********************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* file.h
* All functions related to reading/creating/managing files and its data
************************************************************************/

#ifndef fileHeader
#define fileHeader

#include "heap.h"

/************************* PAL FILE FUNCTIONS **************************/
void manage_pal_file(char *file, vector *indexing_vector);
int read_pal_file(FILE* pal_file, pal_problem *new_problem);

/************************* DIC FILE FUNCTIONS **************************/
void manage_dic_data1(item got_char, item got_vector);
void manage_dic_data2(item got_char, item got_vector);
void manage_dic_file(char *file, void (*manage_dic_data)(item, item), vector *indexing_vector);

/*********************** OUTPUT FILE FUNCTIONS *************************/
char *create_output_filename(char *pal_filename);
void write_to_file(vector *indexing_vector, pal_problem *new_problem, FILE *output_file, path_element *path_vector);

#endif
