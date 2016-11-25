/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* structures.c
* All functions that create/append/add/free/get/set structures.
***************************************************************/

#include "storing.h"

struct _adj_element {
	int word_position;
	int n_comut;
	adj_element *next; 
};

struct _word_vector_element {
	char *word;
	adj_element *head;
};

struct _element {
	int next_index;
	int n_words;
	int max_comut;
	int sorted;
	int n_problems;
	int got_graph;
	word_vector_element *word_vector;
};

struct _pal_problem {
	char word1[100];
	char word2[100];
	int position1;
	int position2;
	int typeof_exe;
	/*solution array*/
};

struct _heap_element {
	int dic_index;
	int weight;
};

struct _path_element {
	int total_weight;
	int parent;
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

int get_element_max_comut(element *got_element) {
	return got_element->max_comut;
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

void set_element_max_comut(element *got_element, int el_max_comut) {
	got_element->max_comut = el_max_comut;
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

/*********************** WORD VECTOR *********************/

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
		spam(("Word: %s \n", got_word_vector[i].word));
		spam(("List:"));
		if(got_word_vector[i].head != NULL) {
			node = got_word_vector[i].head;
			while(node != NULL) {
				spam((" -> "));
				spam(("Word pos: %d , n_comut: %d\n", 
					node->word_position,
					node->n_comut));
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

/********************* ADJ LIST **********************/

adj_element *create_adj_element(int _word_position, int _n_comut) {
	adj_element *new_element;
	new_element = (adj_element *)malloc(sizeof(adj_element));
	if(new_element == NULL)
        memory_error("Unable to reserve list memory");

    new_element->next = NULL;
    new_element->word_position = _word_position;
    new_element->n_comut = _n_comut;

    return new_element;
}

void push_adj_el_to_word_vector_el(int i, word_vector_element *got_word_vector, adj_element *new_element) {
	new_element->next = got_word_vector[i].head;
	got_word_vector[i].head = new_element;
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

void save_problem_solution() {
	return;
}

/*************** HASH TABLE *******************/

int *create_hash_table(int n_elements) {

	int *hash_table = NULL;

	hash_table = (int *)malloc(n_elements*sizeof(int));
	if(hash_table == NULL)
		memory_error("Unable to reserve hash table memory");

	return hash_table;
}

int get_hash_table_value(int i, int *hash_table) {
	return hash_table[i];
}

void set_hash_table_value(int _value, int i, int *hash_table) {
	hash_table[i] = _value;
}

/*************** HEAP VECTOR *******************/

heap_element *create_heap_vector(int n_elements) {

	heap_element *heap_vector = NULL;

	heap_vector = (heap_element *)malloc(n_elements*sizeof(heap_element));
    if (heap_vector == NULL) {
        memory_error("Unable to reserve heap_vector memory");
    }
    return heap_vector;
}

heap_element get_heap_vector_element(int i, heap_element *heap_vector) {
	return heap_vector[i];
}

/*************** HEAP VECTOR ELEMENT *******************/

int get_heap_element_dic_index(int i, heap_element *heap_vector) {
	return heap_vector[i].dic_index;
}

int get_heap_element_weight(int i, heap_element *heap_vector) {
	return heap_vector[i].weight;
}

void set_heap_element_dic_index(int _dic_index, int i, heap_element *heap_vector) {
	heap_vector[i].dic_index =_dic_index;
}

void set_heap_element_weight(int _weight, int i, heap_element *heap_vector) {
	heap_vector[i].weight =_weight;
}

/*************** PATH VECTOR *******************/

path_element *create_path_vector(int n_elements) {

	path_element *path_vector = NULL;

	path_vector = (path_element *)malloc(n_elements*sizeof(path_element));
    if (path_vector == NULL) {
        memory_error("Unable to reserve heap_vector memory");
    }
    return path_vector;
}

path_element get_path_vector_element(int i, path_element *path_vector) {
	return path_vector[i];
}

/*************** PATH VECTOR ELEMENT *******************/

int get_path_element_total_weight(int i, path_element *path_vector) {
	return path_vector[i].total_weight;
}

int get_path_element_parent(int i, path_element *path_vector) {
	return path_vector[i].parent;
}

void set_path_element_total_weight(int _total_weight, int i, path_element *path_vector) {
	path_vector[i].total_weight = _total_weight;
}

void set_path_element_parent(int _parent, int i, path_element *path_vector) {
	path_vector[i].parent =_parent;
}