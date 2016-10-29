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
	int n_words;
	int max_comut;
	vector *word_vector;
};

element *create_element(int el_n_words, int el_max_comut) {

	element *new_element = NULL;

	new_element = (element *)malloc(sizeof(element));
    if (new_element == NULL)
        memory_error("Unable to reserve index_element memory");

    new_element->n_words = el_n_words;
    new_element->max_comut = el_max_comut;
    new_element->word_vector = NULL;
    
    return new_element;
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
}

void set_element_max_comut(element *got_element, int el_max_comut) {
	got_element->max_comut = el_max_comut;
}

void print_element(item got_item) {

	element *got_element = (element *)got_item;

	if(got_element != NULL) {
		spam((KRED"n_words:"RESET"%d\n"
				KRED"max_comut:"RESET"%d\n", 
				got_element->n_words, got_element->max_comut));
	}
	return;
}