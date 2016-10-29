/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* storing.h
* All functions that create/append/add/free/get/set structures.
***************************************************************/

#ifndef storingHeader
#define storingHeader

#include "defs.h"
#include "structures.h"

typedef struct _element element;

element *create_element(int el_n_words, int el_max_comutations);

int get_element_n_words(element *got_element);
int get_element_max_comut(element *got_element);
vector *get_element_word_vector(element *got_element);

void add_element_n_words(element *got_element);
void set_element_max_comut(element *got_element, int el_max_comut);

void print_element(item got_item);

#endif