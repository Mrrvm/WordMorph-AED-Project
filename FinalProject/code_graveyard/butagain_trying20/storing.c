/***************************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* storing.c
* All functions that create/append/add/free/get/set NOT abstract structures.
****************************************************************************/

#include "storing.h"

struct _adj_element {
	unsigned int word_position;
	unsigned int n_mut;
	unsigned int weight;
	adj_element *next; 
};

struct _word_vector_element {
	char *word;
	adj_element *head;
};

struct _element {
	unsigned int next_index;
	unsigned int n_words;
	unsigned int max_mut;
	unsigned int sorted;
	unsigned int n_problems;
	unsigned int got_graph;
	word_vector_element *word_vector;
};

struct _pal_problem {
	char word1[100];
	char word2[100];
	unsigned int position1;
	unsigned int position2;
	int typeof_exe;
};


/*********************** ELEMENT OF INDEXING VECTOR *************************/

element *create_element(int el_n_words, int el_max_mut) {

	element *new_element = NULL;

	new_element = (element *)malloc(sizeof(element));
    if (new_element == NULL) {
        memory_error("Unable to reserve index_element memory");
    }

    new_element->next_index = 0;
    new_element->n_words = el_n_words;
    new_element->max_mut = el_max_mut;
    new_element->word_vector = NULL;
    new_element->sorted = 0;
    new_element->n_problems = 0;
    new_element->got_graph = 0;
    
    return new_element;
}

int get_element_got_graph(element *got_element) {
	return got_element->got_graph;
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

int get_element_max_mut(element *got_element) {
	return got_element->max_mut;
}

word_vector_element *get_element_word_vector(element *got_element) {
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

void sub_element_n_problems(element *got_element) {
	got_element->n_problems--;
}

void set_element_got_graph(element *got_element) {
	got_element->got_graph = 1;
	return;
}

void set_element_max_mut(element *got_element, int el_max_mut) {
	got_element->max_mut = el_max_mut;
	return;
}

void set_element_word_vector(element *got_element, word_vector_element *_word_vector) {
	got_element->word_vector = _word_vector;
	return;
}

void set_element_sorted(element *got_element) {
	got_element->sorted = 1;
	return;
}

void free_element(item got_item) {

	element *got_element = (element *)got_item;
	if(got_element != NULL)
	free(got_element);
}


/******************************* WORD VECTOR ********************************/

word_vector_element *create_word_vector(int n_words) {

	word_vector_element *word_vector = NULL;

	word_vector = (word_vector_element *)calloc(n_words, sizeof(word_vector_element ));
	if(word_vector == NULL) {
		memory_error("Unable to reserve word_element memory");
	}
	return word_vector; 
}

word_vector_element get_word_vector_element(int i, word_vector_element *got_word_vector) {
	return got_word_vector[i];
}

char *get_word_vector_word(int i, word_vector_element *got_word_vector) {
	return got_word_vector[i].word;
}

adj_element *get_word_vector_head(int i, word_vector_element *got_word_vector) {
	return got_word_vector[i].head;
}

void copy_word_to_vector(char *_word, word_vector_element *got_word_vector, int i) {

	if(got_word_vector[i].word != NULL)
		free(got_word_vector[i].word);
	got_word_vector[i].word = (char *)calloc(strlen(_word)+1, sizeof(char));
	strcpy(got_word_vector[i].word, _word);
	return;
}

void set_word_vector_element_head(word_vector_element *got_word_vector, int i, adj_element *_head) {
	got_word_vector[i].head = _head;
}

void print_word_vector(word_vector_element *got_word_vector, int n_words) {
	int i = 0;
	adj_element *node;

	while(i<n_words) {
		spam(("Word %d: %s \n", i, got_word_vector[i].word));
		spam(("List:"));
		if(got_word_vector[i].head != NULL) {
			node = got_word_vector[i].head;
			while(node != NULL) {
				spam((" -> "));
				spam(("Word pos : %d , n_mut: %d\n", 
					node->word_position,
					node->n_mut));
				node = node->next;
			}
		}
		spam(("\n"));
		i++;
	}
	return;
}

void free_word_vector(word_vector_element *got_word_vector, int n_words) {
	int i = 0;
	adj_element *node = NULL;

	while(i<n_words) {
		free(got_word_vector[i].word);
		node = got_word_vector[i].head;
		while(node != NULL) {
			node = got_word_vector[i].head->next;
			free(got_word_vector[i].head);
			got_word_vector[i].head = node;
		}	
		i++;
	}
	free(got_word_vector);
	return;

}

/********************************* ADJ LIST *********************************/

adj_element *create_adj_element(int _word_position, int _n_mut) {
	adj_element *new_element;
	new_element = (adj_element *)malloc(sizeof(adj_element));
	if(new_element == NULL)
        memory_error("Unable to reserve list memory");

    new_element->next = NULL;
    new_element->word_position = _word_position;
    new_element->n_mut = _n_mut;
    new_element->weight = SQUARE(_n_mut);

    return new_element;
}

void push_adj_el_to_word_vector_el(int i, word_vector_element *got_word_vector, adj_element *new_element) {
	new_element->next = got_word_vector[i].head;
	got_word_vector[i].head = new_element;
	return;
}

adj_element *get_next_adj_element(adj_element *curr_node) {
	return curr_node->next;
}

int get_adj_element_n_mut(adj_element *curr_node) {
	return curr_node->n_mut;
}

int get_adj_element_weight(adj_element *curr_node) {
	return curr_node->weight;
}

int get_adj_element_dic_index(adj_element *curr_node) {
	return curr_node->word_position;
}

/**************************** PROBLEM STRUCTURE *****************************/

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
	new_problem->position1 = -1;
	new_problem->position2 = -1;
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

void set_problem_typeof_exe(pal_problem *new_problem, int _typeof_exe) {
	new_problem->typeof_exe = _typeof_exe;
}

void set_problem_position1(int _position, pal_problem *new_problem) {
	new_problem->position1 = _position;
}

void set_problem_position2(int _position, pal_problem *new_problem) {
	new_problem->position2 = _position;
}
