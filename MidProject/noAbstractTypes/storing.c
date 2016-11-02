/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* structures.c
* All functions that create/append/add/free/get/set structures.
***************************************************************/

#include "storing.h"

struct _element {
	int next_index;
	int n_words;
	int max_comut;
	char **word_vector;
};

struct _pal_problem {
	char word1[100];
	char word2[100];
	int position1;
	int position2;
	int typeof_exe;
};

/*************** ELEMENT OF INDEXING VECTOR *******************/

element *create_element(int el_n_words, int el_max_comut) {

	element *new_element = NULL;

	new_element = (element *)malloc(sizeof(element));
    if (new_element == NULL) {
        memory_error("Unable to reserve index_element memory");
    }

    new_element->next_index = 0;
    new_element->n_words = el_n_words;
    new_element->max_comut = el_max_comut;
    new_element->word_vector = NULL;
    
    return new_element;
}

int get_element_next_index(element *got_element) {
	return got_element->next_index;
}

int get_element_n_words(element *got_element) {
	return got_element->n_words;
}

int get_element_max_comut(element *got_element) {
	return got_element->max_comut;
}

char **get_element_word_vector(element *got_element) {
	return got_element->word_vector;
}

void add_element_n_words(element *got_element) {
	got_element->n_words ++;
	return;
}

void add_element_next_index(element *got_element) {
	got_element->next_index ++;
	return;
}

void set_element_max_comut(element *got_element, int el_max_comut) {
	got_element->max_comut = el_max_comut;
	return;
}

void set_element_word_vector(element *got_element, char **_word_vector) {
	got_element->word_vector = _word_vector;
	return;
}

void free_element(item got_item) {

	element *got_element = (element *)got_item;
	free(got_element);
}

/***************** ELEMENT OF WORD VECTOR *********************/

char **create_word_vector(int n_words) {

	char **word_vector = NULL;

	word_vector = (char **)calloc(n_words, sizeof(char*));
	if(word_vector == NULL) {
		memory_error("Unable to reserve word_element memory");
	}
 
	return word_vector; 
}

void copy_word_to_vector(char *_word, char **got_word_vector, int i) {

	got_word_vector[i] = (char *)calloc(strlen(_word)+1, sizeof(char));
	strcpy(got_word_vector[i], _word);
	return;
}	

void print_word_vector(char **word_vector, int n_words) {

	int i = 0;

	while(i<n_words) {
		spam(("%s ", word_vector[i]));
		i++;
	}
	spam(("\n"));
	return;
}

/******************* CREATE WORD VECTORS **********************/

void create_word_vectors(vector *indexing_vector) {

	int size = 0, i = 0;
	char **word_vector = NULL;
	element *got_element = NULL;
	int n_words = 0;

	size = get_vector_size(indexing_vector);

	while(i < size) {
		got_element = get_vector_item(i, indexing_vector);
		if(got_element != NULL) {
			n_words = get_element_n_words(got_element);
			if(n_words > 0) {
				word_vector = create_word_vector(n_words);
   				set_element_word_vector(got_element, word_vector);
			}
		}
		i++;
	}
	return;
}

char *get_word_element(int index, char **word_vector) {
	return word_vector[index];
}

/********************* PROBLEM STRUCTURE **********************/

pal_problem *create_pal_problem() {

	pal_problem *new_problem = NULL;

	new_problem = (pal_problem *)malloc(sizeof(pal_problem));
	if(new_problem == NULL) {
		memory_error("Unable to reserve problem memory");
	}

	return new_problem;
}

void set_problem_variables(pal_problem *new_problem, char *_word1, char *_word2, int _typeof_exe) {

	strcpy(new_problem->word1, _word1);
	strcpy(new_problem->word2, _word2);
	new_problem->typeof_exe =  _typeof_exe;
	new_problem->position1 = 0;
	new_problem->position2 = 0;
	return;
}

void set_problem_position1(pal_problem *new_problem, int _value) {
	new_problem->position1 = _value;
	return;
}

void addto_problem_position1(pal_problem *new_problem) {
	new_problem->position1 ++;
	return;
}

void set_problem_position2(pal_problem *new_problem, int _value) {
	new_problem->position2 = _value;
	return;
}

void addto_problem_position2(pal_problem *new_problem) {
	new_problem->position2 ++;
	return;
}

char *get_problem_word1(pal_problem *new_problem) {
	return new_problem->word1;
}

char *get_problem_word2(pal_problem *new_problem) {
	return new_problem->word2;
}

int get_problem_typeof_exe(pal_problem *new_problem) {
	return new_problem->typeof_exe;
}

int get_problem_position1(pal_problem *new_problem) {
	return new_problem->position1;
}

int get_problem_position2(pal_problem *new_problem) {
	return new_problem->position2;
}

/******************* FREE INDEXING VECTOR *********************/
/*
void free_indexing_vector(vector *indexing_vector) {

	element *got_element = NULL;
	word_element *word_vector = NULL;
	int size = 0, i = 0;

	size = get_vector_size(indexing_vector);

	while(i < size) {
		got_element = get_vector_item(i, indexing_vector);
		if(got_element != NULL) {
			word_vector = get_element_word_vector(got_element);
			if(word_vector != NULL)
				free_vector(word_vector, free_word_element);		
		}
		i++;
	}

	free_vector(indexing_vector, free_element);
	return;
}

*/