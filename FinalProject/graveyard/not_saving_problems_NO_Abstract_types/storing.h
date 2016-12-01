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
typedef struct _pal_problem pal_problem;
typedef struct _word_vector_element word_vector_element;
typedef struct _adj_element adj_element;
typedef struct _solution_element solution_element;

element *create_element(int el_n_words, int el_max_comutations);
int get_element_got_graph(element *got_element);
int get_element_next_index(element *got_element);
int get_element_n_words(element *got_element);
int get_element_max_comut(element *got_element);
int get_element_n_problems(element *got_element);
word_vector_element *get_element_word_vector(element *got_element);
int get_element_sorted(element *got_element);
void set_element_word_vector(element *got_element, word_vector_element *word_vector);
void add_element_n_problems(element *got_element);
void add_element_n_words(element *got_element);
void add_element_next_index(element *got_element);
void sub_element_n_problems(element *got_element);
void set_element_got_graph(element *got_element);
void set_element_max_comut(element *got_element, int el_max_comut);
void set_element_word_vector(element *got_element, word_vector_element *_word_vector);
void set_element_sorted(element *got_element);
void free_element(item got_item);

word_vector_element *create_word_vector(int n_words);
word_vector_element get_word_vector_element(int i, word_vector_element *got_word_vector);
char *get_word_vector_word(int i, word_vector_element *got_word_vector);
adj_element *get_word_vector_head(int i, word_vector_element *got_word_vector);
void copy_word_to_vector(char *_word, word_vector_element *got_word_vector, int i);
void set_word_vector_element_head(word_vector_element *got_word_vector, int i, adj_element *_head);
void print_word_vector(word_vector_element *got_word_vector, int n_words);
void free_word_vector(word_vector_element *got_word_vector, int n_words);

adj_element *create_adj_element(int word_position, int n_comut);
void push_adj_el_to_word_vector_el(int i, word_vector_element *got_word_vector, adj_element *new_element);
void free_word_vector_el_list(adj_element *head);
adj_element *get_next_adj_element(adj_element *curr_node);
int get_adj_element_dic_index(adj_element *curr_node);
int get_adj_element_weight(adj_element *curr_node);
int get_adj_element_n_comut(adj_element *curr_node);

solution_element *create_solution_element(int _parent_index);

pal_problem *create_pal_problem();
void set_problem_variables(pal_problem *new_problem, char *_word1, char *_word2, int _typeof_exe);
char *get_problem_word1(pal_problem *new_problem);
char *get_problem_word2(pal_problem *new_problem);
int get_problem_typeof_exe(pal_problem *new_problem);
int get_problem_position1(pal_problem *new_problem);
int get_problem_position2(pal_problem *new_problem);
solution_element *get_problem_head(pal_problem *new_problem);
void set_problem_position1(int _position, pal_problem *new_problem);
void set_problem_position2(int _position, pal_problem *new_problem);
void set_problem_typeof_exe(pal_problem *new_problem, int _typeof_exe);

#endif