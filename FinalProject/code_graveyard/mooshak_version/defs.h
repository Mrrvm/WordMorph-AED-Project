/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* defs.h
* Auxiliary definitions or functions used many times
***************************************************************/

#ifndef defsHeader
#define defsHeader

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

/*DEBUG_OFF - No printfs
  DEBUG_ON  - Printfs
 */
#define DEBUG_OFF	

#ifdef DEBUG_ON
  #define spam(a) printf a
#else
  #define spam(a) (void)0
#endif

/*Represents infinte distance*/
#define INF 100*100*2
/*Represents heap elements with no parent*/
#define ORFAN -1
#define SQUARE(x) (x*x)

typedef void *item;
typedef enum
{
    FALSE=0,
    TRUE=1
} bool;

char *get_filename_ext(char *filename);
void file_error(char *msg);
void memory_error(char *msg);

#endif
