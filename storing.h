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
typedef struct _word_element word_element;
typedef struct _pal_problem pal_problem;

element *create_element(int el_n_words, int el_max_comutations);
int get_element_next_index(element *got_element);
int get_element_n_words(element *got_element);
int get_element_max_comut(element *got_element);
vector *get_element_word_vector(element *got_element);
void add_element_n_words(element *got_element);
void add_element_next_index(element *got_element);
void set_element_max_comut(element *got_element, int el_max_comut);
void print_element(item got_item);

word_element *create_word_element(char *el_word);
char *get_word_element_word(word_element *got_element);
void create_word_vectors(vector *indexing_vector);

pal_problem *create_pal_problem();
void set_problem_variables(pal_problem *new_problem, char *_word1, char *_word2, int _typeof_exe);
void addto_problem_position1(pal_problem *new_problem);
void addto_problem_position2(pal_problem *new_problem);
char *get_problem_word1(pal_problem *new_problem);
char *get_problem_word2(pal_problem *new_problem);
int get_problem_typeof_exe(pal_problem *new_problem);
void set_problem_position1(pal_problem *new_problem, int _value);
int get_problem_position1(pal_problem *new_problem);
void set_problem_position2(pal_problem *new_problem, int _value);
int get_problem_position2(pal_problem *new_problem);

void free_indexing_vector(vector *indexing_vector);

#endif