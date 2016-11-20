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
	int sorted;
	int n_problems;
	vector *word_vector;
};

struct _word_vector_element {
	char *word;
	list *adj_list;
};

struct _pal_problem {
	char word1[100];
	char word2[100];
	int position1;
	int position2;
	int typeof_exe;
};

struct _adj_element {
	int word_position;
	int n_comut; 
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
    new_element->sorted = 0;
    new_element->n_problems = 0;
    
    return new_element;
}

int get_element_next_index(element *got_element) {
	return got_element->next_index;
}

int get_element_n_problems(element *got_element) {
	return got_element->n_problems;
}

int get_element_n_words(element *got_element) {
	return got_element->n_words;
}

int get_element_max_comut(element *got_element) {
	return got_element->max_comut;
}

vector *get_element_word_vector(element *got_element) {
	return got_element->word_vector;
}

int get_element_sorted(element *got_element) {
	return got_element->sorted;
}

void add_element_n_words(element *got_element) {
	got_element->n_words ++;
	return;
}

void add_element_next_index(element *got_element) {
	got_element->next_index ++;
	return;
}

void add_element_n_problems(element *got_element) {
	got_element->n_problems++;
}

void set_element_max_comut(element *got_element, int el_max_comut) {
	got_element->max_comut = el_max_comut;
	return;
}

void set_element_word_vector(element *got_element, vector *_word_vector) {
	got_element->word_vector = _word_vector;
	return;
}

void set_element_sorted(element *got_element) {
	got_element->sorted = 1;
	return;
}

void free_element(item got_item) {

	element *got_element = (element *)got_item;
	free(got_element);
}

/**************** ELEMENT OF WORD VECTOR *****************/

word_vector_element *create_word_vector_element(char *_word) {

	word_vector_element *new_element = NULL;

	new_element = (word_vector_element *)malloc(sizeof(word_vector_element));
    if(new_element == NULL) {
        memory_error("Unable to reserve word_vector_element memory");
    }

   	new_element->word = (char*)malloc((strlen(_word)+1)*sizeof(char));
    if(new_element->word == NULL) {
        memory_error("Unable to reserve word memory");
    }

    new_element->adj_list = create_list();

    strcpy(new_element->word, _word);
    return new_element;
}

char *get_word_vector_element_word(word_vector_element *got_element) {
	return got_element->word;
}

void set_word_vector_element_word(word_vector_element *got_element, char *_word) {
	strcpy(got_element->word, _word);
	return;
}

list *get_word_vector_element_list(word_vector_element *got_element) {
	return got_element->adj_list;
}

void free_word_vector_element(item got_item) {

	word_vector_element *got_element = (word_vector_element *)got_item;
	free_list(got_element->adj_list, free_adj_element);
	free(got_element->word);
	free(got_element);
}

void print_word_vector_element(item got_item) {
	word_vector_element *got_word_element = (word_vector_element *)got_item;
	if(got_word_element != NULL)
		spam((KMAG"\n Word: %s, \n List: "RESET, got_word_element->word));
	/*print_list(got_word_element->adj_list)*/
	return;
}

/******************** WORD VECTOR ******************/
void print_word_vector(item got_item) {
	element *got_element = (element *)got_item;
	char *vector_name = " of word_vector";
	if(got_element != NULL)
		if(got_element->word_vector != NULL) {
			print_vector(got_element->word_vector, print_word_vector_element, vector_name);
		}
	return;
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

/******************* GRAPH ELEMENT *********************/

adj_element *create_adj_element(int _word_position, int _n_comut) {

	adj_element *new_element = NULL;

	new_element = (adj_element *)malloc(sizeof(adj_element));
	if(new_element == NULL) {
		memory_error("Unable to reserve adj_element memory");
	}

	new_element->word_position = _word_position;
	new_element->n_comut = _n_comut;

	return new_element;
}

void free_adj_element(item got_item) {

	adj_element *got_adj_element = (adj_element *)got_item;
	free(got_adj_element);
}

/******************* FREE INDEXING VECTOR *********************/
/*
void free_indexing_vector(vector *indexing_vector) {

	element *got_element = NULL;
	char **got_word_vector = NULL;
	int size = 0, i = 0;

	size = get_vector_size(indexing_vector);

	while(i < size) {
		got_element = get_vector_item(i, indexing_vector);
		if(got_element != NULL) {
			got_word_vector = get_element_word_vector(got_element);
			if(got_word_vector != NULL)
				free_word_vector(got_word_vector, get_element_n_words(got_element));		
		}
		i++;
	}

	free_vector(indexing_vector, free_element);
	return;
}
*/