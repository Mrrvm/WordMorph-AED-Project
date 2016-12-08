/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* execution.c
* All functions that directly allow the wordmorphism to happen
***************************************************************/

#include "execution.h"

/*************ORDERING AND SEARCHING ALGORITHMS****************/

/*Binary search algorithm*/
int binary_search(word_vector_element *got_word_vector, int left, int right, char *word) {
  
  char *temp_word;
  int mid;

  while (left <= right) {  
    mid = left + (right-left)/2;
    temp_word = get_word_vector_word(mid, got_word_vector);
    if(strcmp(temp_word, word) == 0) 
        return mid;  

    if (strcmp(temp_word, word) < 0) 
        left = mid + 1; 
    else
    	right = mid - 1; 
  }
  return -1; 
}


void merge(word_vector_element *got_word_vector, int left, int mid, int right) {
    char **temp_array  = NULL;
    char *wordl, *wordr;
    int pos=0,lpos = left,rpos = mid + 1;
    int iter = 0;

    /*Alloc a temporary array of strings*/
    temp_array = (char **)calloc((right-left+1),sizeof(char*));
    while(iter < right-left+1) {
    	temp_array[iter] = (char *)calloc(100, sizeof(char));
    	iter++;
    }

    /*Merge the 2 parts*/
    while(lpos <= mid && rpos <= right)
    {
    	wordl = get_word_vector_word(lpos, got_word_vector);
    	wordr = get_word_vector_word(rpos, got_word_vector);
        if(strcmp(wordl, wordr) < 0) {
            strcpy(temp_array[pos], wordl);
            pos++;
            lpos++;
        }
        else {
        	strcpy(temp_array[pos], wordr);
        	pos++;
        	rpos++;
        }
    }
    /*Merge the leftover part*/
    while(lpos <= mid) {
    	wordl = get_word_vector_word(lpos, got_word_vector);
    	strcpy(temp_array[pos], wordl);
         pos++;
         lpos++;
    }
    while(rpos <= right) {
    	wordr = get_word_vector_word(rpos, got_word_vector);
    	strcpy(temp_array[pos], wordr);
        pos++;
        rpos++;
    }
    
    /*Copy the temporary array to the real array*/
    for(iter = 0;iter < pos; iter++) {
    	copy_word_to_vector(temp_array[iter], got_word_vector, iter+left);
    }

    /*Free the temporary array*/
    iter = 0;
    while(iter < right-left+1) {
    	free(temp_array[iter]);
    	iter++;
    }
    free(temp_array);
    return;
}


void merge_sort(word_vector_element *got_word_vector, int left, int right) {
    int mid = (left+right)/2;
    /*When left=right it is already sorted*/
    if(left<right) {
            /*Sort the left part */
            merge_sort(got_word_vector, left, mid);
            /*Sort the right part */
            merge_sort(got_word_vector, mid+1, right);
            /*Merge the two sorted parts */
           	merge(got_word_vector, left, mid, right);
    }
}

/*********************GRAPH FUNCTIONS***************************/

/*Checks the number of mutations between 2 words.
    If the number becomes higher than the maximum number of mutations
    allowed for this word lenght, returns 0. Else returns 1. */
int check_number_of_mutations(char *word1, char *word2, int max_mut, int *n_mut) {
	int diff = 0, i=0, len = 0;

	len = strlen(word1);
	for(i=0; i < len; i++) {
    	if(word1[i] != word2[i])
    	   diff++;
    	if(IS_BIGGER(diff, max_mut))
    		return 0;
    }
    /*Saves the number of different letters between the 2 words (diff)
        in n_mut*/
    *n_mut = diff;
	return 1;
}

/*Function resposible for creating the graph.*/
void create_graph(element *got_element) {

	int size = 0, max_mut = 0, n_mut = 0;
	int i = 0, j = 0;
	word_vector_element *got_word_vector = NULL;
	char *curr_word, *temp_word;

    /*Gets the maximum number of mutations for this word length*/
	max_mut = get_element_max_mut(got_element);
    /*Gets the word vector for this word length*/
	got_word_vector = get_element_word_vector(got_element);
     /*Gets the number of words present in the dictionary of 
        of this word length*/
	size = get_element_n_words(got_element);

    /*For each word in the word vector*/
	for(i=0; i<size; i++) {
		curr_word = get_word_vector_word(i, got_word_vector);
        /*For each one of the other words in the word vector*/
		for(j=i+1; j<size; j++) {
			temp_word = get_word_vector_word(j, got_word_vector);
            /*Get the number of mutations beteween the words.
                If is less than the maximum, push the words to each 
                others adj lists*/
			if(check_number_of_mutations(curr_word, temp_word, max_mut, &n_mut)) {
				push_adj_el_to_word_vector_el(i, got_word_vector, create_adj_element(j, n_mut));
				push_adj_el_to_word_vector_el(j, got_word_vector, create_adj_element(i, n_mut));
			}
		}
	}
    /*Let the program know that the graph for this word length is created*/
	set_element_got_graph(got_element);
	return;
}

/*Prints the graph created - for debug purposes*/
void print_graph(item got_item) {

    element *got_element = (element *)got_item;

    if(got_element != NULL)
        print_word_vector(get_element_word_vector(got_element), get_element_n_words(got_element));

}

/*********************PROBLEM SOLVERS***************************/

/*This function is responsible for getting dijkstra running.
    Initializes the heap (aka putting all the words in INF distance and ORFAN),
    sets the source to distance 0 and itself as its parent,
    runs heapify to convert a non-heap (aka a disordered thing) into a heap,
    runs dijkstra algorithm in each member of the queue (heap_vector).
*/
path_element *run_dijkstra(element *got_element, int src_index, int max_mut) {

    heap_element *heap_vector = NULL;
    int *hash_table = NULL;
    path_element *path_vector = NULL;
    int i = 0, n_words = 0;
    int curr_heap_dic_index;
    adj_element *node = NULL;

    n_words = get_element_n_words(got_element);
    heap_vector = create_heap_vector(n_words+1);
    hash_table = create_hash_table(n_words);
    path_vector = create_path_vector(n_words);

    /*Set initial dijkstra variables*/
    initialize_heap(n_words, hash_table, path_vector, heap_vector);
    /*Set source variables*/
    set_path_element_parent(src_index, src_index, path_vector);
    set_path_element_total_weight(0, src_index, path_vector);
    set_heap_element_weight(0, src_index+1, heap_vector);

    /*Start by ordering the "heap"*/
    for (i = n_words/2; i >= 1; i--) {
        heapify(i, n_words, hash_table, heap_vector);
    }
    i = n_words;
    /*While queue is not empty */
    while(i > 0) { 
        /*Get the first element of the queue*/
        curr_heap_dic_index = get_first_heap_dic_index(hash_table, i, heap_vector);
        /*Get each adj element to that first element of the queue*/
        node = get_word_vector_head(curr_heap_dic_index, 
            get_element_word_vector(got_element));
        while(node != NULL) {
            /*If the number of mutations of the adj element is less or equal
            to the maximum of mutations asked*/
            if(get_adj_element_n_mut(node) <= max_mut) {
                /*Find a better path between the element and its adj element*/
                find_better_path(path_vector, curr_heap_dic_index, node, hash_table, heap_vector);
            }
            node = get_next_adj_element(node);
        }

        i--;
    }
    /*Get this vectors into the USA*/
    free(heap_vector);
    free(hash_table);
	return path_vector;
}

/*This function is responsible for solving problems.
    It receives a problem, 
        sorts the dictionary,
        finds the positions of the words in the problem in the dictionary,
        creates a graph for the word length if not the yet created, 
        runs dijkstra to get the path vector with the solution, 
        and reduces the number of problems in the element of the word length. */
path_element *run_problem_solver(pal_problem *new_problem, vector *indexing_vector) {

	int len = 0, size = 0, i = 0, diff = 0;
	element *got_element = NULL;
    int src_index = 0, dest_index = 0;
    path_element *path_vector = NULL;
    word_vector_element *got_word_vector = NULL;
    int max_mut = 0;
    char *word1 = NULL, *word2 = NULL;

	len = strlen(get_problem_word1(new_problem));
	got_element = get_vector_item(len, indexing_vector);
	max_mut = get_problem_typeof_exe(new_problem);
    got_word_vector = get_element_word_vector(got_element);
    size = get_element_n_words(got_element);
    
    /*Sorts the dictionary by alpabetical order if not yet sorted*/
    if(!get_element_sorted(got_element)) {
        merge_sort(got_word_vector, 0, size-1);
        set_element_sorted(got_element);
    }

    src_index = binary_search(
        get_element_word_vector(got_element),
        0,
        get_element_n_words(got_element),
        get_problem_word1(new_problem));
    set_problem_position1(src_index, new_problem);
    dest_index = binary_search(
        get_element_word_vector(got_element),
        0,
        get_element_n_words(got_element),
        get_problem_word2(new_problem));
    set_problem_position2(dest_index, new_problem);

    word1 = get_word_vector_word(src_index, got_word_vector);
    word2 = get_word_vector_word(dest_index, got_word_vector);
    for(i=0; i < len; i++) {
        if(word1[i] != word2[i])
           diff++;
    }

    /*If the source and destiny word is the same, 
        no more work is done here*/
    if(src_index == dest_index || diff == 1) {
        return NULL;
    }

	if(!get_element_got_graph(got_element)) {
		create_graph(got_element);
    }

    path_vector = run_dijkstra(got_element, src_index, max_mut);
    sub_element_n_problems(got_element);
	return path_vector;
}
