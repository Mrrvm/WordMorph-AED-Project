/**************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* defs.c
***************************************/

#include "defs.h"

char *get_filename_ext(char *filename)
{
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void file_error(char *msg)
{
    fprintf(stderr, KRED"Error during opening file attempt.\n"KNRM);
    fprintf(stderr, KRED"Msg: %s\n",msg);
    fprintf(stderr, KRED"Exit Program due to unmanaged error.\n"KNRM);

    exit(1);
}

void memory_error(char *msg)
{
    fprintf(stderr, KRED"Error during memory reserve attempt.\n"KNRM);
    fprintf(stderr, KRED"Msg: %s\n",msg);
    fprintf(stderr, KRED"Exit Program due to unmanaged error.\n"KNRM);

    exit(1);
}