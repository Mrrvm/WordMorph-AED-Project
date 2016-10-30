/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* structures.c
* All functions that create/append/add/free/get/set structures.
***************************************************************/

#include "storing.h"

struct _element
{
	int next_index;
	int n_words;
	int max_comut;
	vector *word_vector;
};

struct _word_element
{
	char *word;
};

struct _pal_problem
{
	char word1[100];
	char word2[100];
	int position1;
	int position2;
	int typeof_exe;
};

/********************* ELEMENT OF INDEXING VECTOR ***********************/

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

vector *get_element_word_vector(element *got_element) {
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

void set_element_word_vector(element *got_element, vector *got_vector) {
	got_element->word_vector = got_vector;
	return;
}

void print_element(item got_item) {

	element *got_element = (element *)got_item;
	vector* got_word_vector = NULL;
	int i = 0, size;

	if(got_element != NULL) {
		spam((KRED"n_words:"RESET"%d\n"
				KRED"max_comut:"RESET"%d\n", 
				got_element->n_words, got_element->max_comut));

		got_word_vector = got_element->word_vector;
		if(got_word_vector != NULL) {
			size = got_element->n_words;
			while(i < size) {
				spam((KCYN"[word_vector = %d]: "RESET, i));
				spam(("%s ", get_word_element_word(get_vector_item(i, got_word_vector))));
				i++;
			}
			spam(("\n"));
		}
	}
	return;
}

/********************* ELEMENT OF WORD VECTOR ***********************/

word_element *create_word_element(char *el_word) {

	word_element *new_element = NULL;

	new_element = (word_element *)malloc(sizeof(word_element));
    if(new_element == NULL) {
        memory_error("Unable to reserve word_element memory");
    }

   	new_element->word = (char*)malloc((strlen(el_word)+1)*sizeof(char));
    if(new_element->word == NULL) {
        memory_error("Unable to reserve word memory");
    }

    strcpy(new_element->word, el_word);
    return new_element;
}

char *get_word_element_word(word_element *got_element) {
	return got_element->word;
}

/********************* CREATE WORD VECTORS ***********************/

void create_word_vectors(vector *indexing_vector) {

	int size = 0, i = 0;
	vector *word_vector = NULL;
	element *got_element = NULL;

	size = get_vector_size(indexing_vector);

	while(i < size) {
		got_element = get_vector_item(i, indexing_vector);
		if(got_element != NULL) {
			word_vector = create_vector(get_element_n_words(got_element));
			set_element_word_vector(got_element, word_vector);
		}
		i++;
	}
	return;
}


/********************* PROBLEM STRUCTURE ***********************/

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

void addto_problem_position1(pal_problem *new_problem) {
	new_problem->position1 ++;
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

