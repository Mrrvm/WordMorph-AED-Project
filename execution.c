/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* execution.c
* All functions that directly allow the wordmorphism to happen
***************************************************************/

#include "execution.h"

void search_for_words(pal_problem *new_problem, vector *got_word_vector) {

	char *word1, *word2, *curr_word;
	int size, i = 0;
	word_element *got_word_element = NULL;
	
	word1 = get_problem_word1(new_problem);
	word2 = get_problem_word2(new_problem);
	size = get_vector_size(got_word_vector);

	while(i < size) {
		got_word_element = get_vector_item(i, got_word_vector);
		curr_word = get_word_element_word(got_word_element);
		if(strcmp(word1, curr_word) > 0) {
			addto_problem_position1(new_problem);
		}
		if(strcmp(word2, curr_word) > 0) {
			addto_problem_position2(new_problem);
		}
		i++;
	}
}

void run_type2(pal_problem *new_problem, vector *indexing_vector) {

	int word_len = 0;
	element *got_element = NULL;
	vector *got_word_vector = NULL;

	word_len = strlen(get_problem_word1(new_problem));
	got_element = get_vector_item(word_len, indexing_vector);
	/*Just to be sure*/
	if(got_element != NULL) {
		got_word_vector = get_element_word_vector(got_element);
		/*For little Ns, simple search*/
		search_for_words(new_problem, got_word_vector);
		/*For big Ns, order and search - TO IMPLEMENT*/
	}
	return;
}