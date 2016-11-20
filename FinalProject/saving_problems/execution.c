/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* execution.c
* All functions that directly allow the wordmorphism to happen
***************************************************************/

#include "execution.h"

int binary_search(vector *got_word_vector, int l, int r, char *word) {
  
  char *temp_word;
  int m;

  while (l <= r) {  
    m = l + (r-l)/2;
    temp_word = get_word_vector_element_word(get_vector_item(m, got_word_vector));
    if(strcmp(temp_word, word) == 0) 
        return m;  

    if (strcmp(temp_word, word) < 0) 
        l = m + 1; 
    else
    	r = m - 1; 
  }
  return -1; 
}


void merge(vector *got_word_vector, int left, int mid, int right)
{
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
    	wordl = get_word_vector_element_word(get_vector_item(lpos, got_word_vector));
    	wordr = get_word_vector_element_word(get_vector_item(rpos, got_word_vector));
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
    	wordl = get_word_vector_element_word(get_vector_item(lpos, got_word_vector));
    	strcpy(temp_array[pos], wordl);
         pos++;
         lpos++;
    }
    while(rpos <= right) {
    	wordr = get_word_vector_element_word(get_vector_item(rpos, got_word_vector));
    	strcpy(temp_array[pos], wordr);
        pos++;
        rpos++;
    }
    
    /*Copy the temporary array to the real array*/
    for(iter = 0;iter < pos; iter++) {
    	set_word_vector_element_word(get_vector_item(iter+left, got_word_vector), 
    		temp_array[iter]);
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

void merge_sort(vector *got_word_vector, int left, int right)
{
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


/*Searches the position of the 2 words of the problem in the word 
	vector of its number of letters. 
	The search is made by comparing the problem strings with each vector
	string. If the vector string is less than the problem string, the 
	problem string position adds up. 
	Example:
		VECTOR: roxa boca rola bola roda 
		A PROBLEM STRING: rola 
		COMPARISSONS:
			rola > roxa - discarded
			rola < boca - adds up (+1)
			rola = rola - discarded
			rola < bola - adds up (+1)
			rola < roda - adds up (+1)
		POSITION: rola 3 
*/
void simple_search_for_words(pal_problem *new_problem, vector *got_word_vector, int size) {

	char *word1, *word2, *curr_word;
	int i = 0;
	int found_word1 = 0, found_word2 = 0;
	int result1 = 0, result2 = 0;
	int add1 = 0, add2 = 0;
	
	word1 = get_problem_word1(new_problem);
	word2 = get_problem_word2(new_problem);

	while(i < size) {
		curr_word = get_word_vector_element_word(get_vector_item(i, got_word_vector));
		result1 = strcmp(word1, curr_word);
		result2 = strcmp(word2, curr_word);
		if(result1 > 0) 
			add1++;
		else if(result1 == 0)
			found_word1 = 1;	
		if(result2 > 0) 
			add2++;
		else if(result2 == 0) 
			found_word2 = 1;
		i++;
	}

	if(found_word1 != 1)
		set_problem_position1(new_problem, -1);
	else
		set_problem_position1(new_problem, add1);

	if(found_word2 != 1) 
		set_problem_position2(new_problem, -1);
	else 
		set_problem_position2(new_problem, add2);

	return;
}


/*Gets the correct vector to search the words position into and decides which
	function to execute depending on the number of problems of each number of 
	letters.*/
void run_position_search(pal_problem *new_problem, vector *indexing_vector) {

	int word_len = 0;
	element *got_element = NULL;
	vector *got_word_vector = NULL;
	int n_words = 0;

	word_len = strlen(get_problem_word1(new_problem));
	got_element = get_vector_item(word_len, indexing_vector);
	n_words = get_element_n_words(got_element);
	/*Just to be sure*/
	if(got_element != NULL) {
		got_word_vector = get_element_word_vector(got_element);
		/*If there words of this size in the dictionary, then...*/
		if(got_word_vector != NULL) {
			/*If there are less problems then HYBRID_DEF of a determined
				number of letters, do a simple search 0(N) - not so bad*/
			if(get_element_n_problems(got_element) < HYBRID_DEF)
				simple_search_for_words(new_problem, got_word_vector, n_words);
			/*If there many problems using the same dictionary, then sort
				the dictionary once - O(NlogN) - and use binary search 
				after - O(logN) - pretty good right? */
			else {
				if(!get_element_sorted(got_element)) {
					merge_sort(got_word_vector, 0, n_words-1);
					set_element_sorted(got_element);
				}
				/*Set the position of the words in the problem structure after the search*/
				set_problem_position1(new_problem, binary_search(got_word_vector, 0, n_words, get_problem_word1(new_problem)));
				set_problem_position2(new_problem, binary_search(got_word_vector, 0, n_words, get_problem_word2(new_problem)));	
			}
		}
		/*If the element has no words in the word vector, the result
			of the search will be -1*/
		else {
			set_problem_position1(new_problem, -1);
			set_problem_position2(new_problem, -1);
		}
	}
	return;
}

/*******************************************************************/

int get_number_of_comutations(item got_item1, item got_item2) {
	char *word1 = (char *)got_item1;
	char *word2 = (char *)got_item2;
	int diff = 0, i=0, len = 0;

	len = strlen(word1);
	for(i=0; i < len; i++) {
    	if(word1[i] != word2[i])
    		diff ++;
    }
	return diff;
}

void create_graph(element *got_element) {

	int size = 0, max_comut = 0, n_comut = 0;
	int i = 0, j = 0;
	vector *got_word_vector = NULL;
	char *curr_word, *temp_word;
	adj_element *new_adj_element = NULL;
	list *curr_adj_list = NULL, *temp_adj_list = NULL;
	word_vector_element *curr_element, *temp_element;

	max_comut = get_element_max_comut(got_element);
	got_word_vector = get_element_word_vector(got_element);
	size = get_element_n_words(got_element);

	if(get_element_n_problems(got_element) >= HYBRID_DEF) {
		if(!get_element_sorted(got_element)) {
			merge_sort(got_word_vector, 0, size-1);
			set_element_sorted(got_element);
		}
	}

	for(i=0; i<size; i++) {
		curr_element = get_vector_item(i, got_word_vector);
		curr_word = get_word_vector_element_word(curr_element);
		curr_adj_list = get_word_vector_element_list(curr_element);
		for(j=i+1; j<size; j++) {
			temp_element = get_vector_item(j, got_word_vector);
			temp_word = get_word_vector_element_word(temp_element);
			temp_adj_list = get_word_vector_element_list(temp_element);
			n_comut = get_number_of_comutations(curr_word, temp_word);
			if(n_comut < max_comut) {
				new_adj_element = create_adj_element(j, n_comut);
				push_item_to_list(curr_adj_list, (adj_element *)new_adj_element);
				new_adj_element = create_adj_element(i, n_comut);
				push_item_to_list(temp_adj_list, (adj_element *)new_adj_element);
			}
		}
	}
	return;
}

void do_dijkstra() {
	return;
}

void run_element_problems_solver(element *got_element) {

	list *problem_list = NULL;
	node *list_element = NULL;

	create_graph(got_element);
	problem_list = get_element_problem_list(got_element);
	list_element = get_head(problem_list);
	/*While there are still problems to solve in this element*/
	while(list_element != NULL) {
		do_dijkstra();
		save_problem_solution();
		list_element = get_next_node(list_element);
	}
	free_vector(get_element_word_vector(got_element), free_word_vector_element);
	return;
}

void run_all_problems_solver(vector *indexing_vector) {

	int i = 0;
	int size = 0;
	element *got_element = NULL;

	size = get_vector_size(indexing_vector);
	while(i < size) {
		got_element = get_vector_item(i, indexing_vector);
		if(got_element != NULL) {
			if(get_element_n_words(got_element) != 0)
				run_element_problems_solver(got_element);
		}
		i++;
	}
	return;
}