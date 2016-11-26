/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* execution.h
* All functions that directly allow the wordmorphism to happen
***************************************************************/

#ifndef executionHeader
#define executionHeader

#include "heap.h"

void run_position_search(pal_problem *new_problem, vector *indexing_vector);
path_element *run_problem_solver(pal_problem *new_problem, vector *indexing_vector);
void print_graph(item got_item);

#endif