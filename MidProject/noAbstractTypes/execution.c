/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* execution.c
* All functions that directly allow the wordmorphism to happen
***************************************************************/

#include "execution.h"

int binary_search(char **arr, int l, int r, char *word) {
  while (l <= r) {
    int m;
    m = l + (r-l)/2;

    if(strcmp(arr[m], word) == 0) 
        return m;  

    if (strcmp(arr[m], word) < 0) 
        l = m + 1; 
    else
    	r = m - 1; 
  }
  return -1; 
}


void merge(char **array, int left, int mid, int right)
{
    char **temp_array  = NULL;
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
        if(strcmp(array[lpos], array[rpos]) < 0) {
            strcpy(temp_array[pos], array[lpos]);
            pos++;
            lpos++;
        }
        else {
        	strcpy(temp_array[pos], array[rpos]);
        	pos++;
        	rpos++;
        }
    }
    /*Merge the leftover part*/
    while(lpos <= mid) {
    	strcpy(temp_array[pos], array[lpos]);
         pos++;
         lpos++;
    }
    while(rpos <= right) {
    	strcpy(temp_array[pos], array[rpos]);
        pos++;
        rpos++;
    }
    
    /*Copy the temporary array to the real array*/
    for(iter = 0;iter < pos; iter++) {
    	strcpy(array[iter+left], temp_array[iter]);
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

void merge_sort(char **array, int left, int right)
{
    int mid = (left+right)/2;
    /*When left=right it is already sorted*/
    if(left<right) {
            /*Sort the left part */
            merge_sort(array,left,mid);
            /*Sort the right part */
            merge_sort(array,mid+1,right);
            /*Merge the two sorted parts */
           	merge(array,left,mid,right);
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
void simple_search_for_words(pal_problem *new_problem, char **got_word_vector, int size) {

	char *word1, *word2, *curr_word;
	int i = 0;
	int found_word1 = 0, found_word2 = 0;
	int result1 = 0, result2 = 0;
	int add1 = 0, add2 = 0;
	
	word1 = get_problem_word1(new_problem);
	word2 = get_problem_word2(new_problem);

	while(i < size) {
		curr_word = got_word_vector[i];
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
	char **got_word_vector = NULL;
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
					print_word_vector(got_word_vector, n_words);
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