/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* file.c
* All functions related to reading/creating/managing files and its data
************************************************************************/

#include "file.h"

/************************* PAL FILE FUNCTIONS **************************/

/*Receives a problem from the pal file, allocates space in the indexing
	vector for the element with its number of letters or if the memory 
	is already existant, just sets the number of comutations to the 
	number of comutations of the problem if this last one is higher.*/
void manage_pal_data(pal_problem *new_problem, vector *indexing_vector) {
	
	int word_len;
	element *got_element = NULL;
	list *problem_list = NULL;
	int typeof_exe = 0;

	/*Gets the element with the word length*/
	word_len = strlen(get_problem_word1(new_problem));
	got_element = get_vector_item(word_len, indexing_vector);

	if(got_element == NULL) {
		/*Creates the element with 0 words and the number of comutations
			of the current problem*/
		typeof_exe = get_problem_typeof_exe(new_problem);
		got_element = create_element(0, typeof_exe); 
		set_item_to_vector(word_len, indexing_vector, (element *)got_element);
	}
	else {
		if(typeof_exe > get_element_max_comut(got_element))
			set_element_max_comut(got_element, typeof_exe);
	}
	add_element_n_problems(got_element); /*useless - correct it later*/
	problem_list = get_element_problem_list(got_element);
	push_item_to_list(problem_list, (pal_problem *)new_problem);

	return;
}

/*Reads the whole pal file once and sends each problem to
	manage_pal_data() function.*/
void manage_pal_file(char *file, vector *indexing_vector, list *solution_list) {

	char first_word[100];
	char second_word[100];
	int typeof_exe = 0;
	pal_problem *new_problem =  NULL;
	FILE *pal_file;

	pal_file = fopen(file, "r");
	if(pal_file == NULL)
		file_error("Unable to open specified file");

	while(fscanf(pal_file, "%99s", first_word) == 1) {
		if(fscanf(pal_file, "%99s", second_word) == 1) {
			if(fscanf(pal_file, "%d", &typeof_exe) == 1) {
				new_problem = create_pal_problem(first_word, second_word, typeof_exe);
				manage_pal_data(new_problem, indexing_vector);
				push_item_to_list(solution_list, (pal_problem *)new_problem);
			}
		}
	}
	fclose(pal_file);
	return;
}

/************************* DIC FILE FUNCTIONS **************************/

/*First function to manage the dic file data. Receives each word of the
	dictionary, analyzes its length and adds up the number of words in 
	the element of the indexing vector with its length.*/
void manage_dic_data1(item got_char, item got_vector) {
	
	char *word = (char *)got_char;
	vector *indexing_vector = (vector *)got_vector;
	int word_len;
	element *got_element = NULL;
	
	/*Gets the element with the word length*/
	word_len = strlen(word);
	got_element = get_vector_item(word_len, indexing_vector);

	/*If its a problem to solve*/
	if(got_element != NULL) {
		add_element_n_words(got_element);
	}
	return;
}

/*Second function to manage the dic file data. Receives each word of 
	the dictionary, and adds it to the word vector pointed by the
	element of the indexing vector with the word length, if the  
	is a problem solver.*/
void manage_dic_data2(item got_char, item got_vector) {

	char *word = (char *)got_char;
	vector *indexing_vector = (vector *)got_vector;
	int word_len, next_index;
	element *got_element = NULL;
	vector *got_word_vector = NULL;
	word_vector_element *new_word_element =  NULL;
	
	/*Gets the element with the word length*/
	word_len = strlen(word);
	got_element = get_vector_item(word_len, indexing_vector);

	/*If this element is a problem solver aka not NULL*/
	if(got_element != NULL) {
		got_word_vector = get_element_word_vector(got_element);
		if(got_word_vector == NULL) {
			got_word_vector = create_vector(get_element_n_words(got_element));
			set_element_word_vector(got_element, got_word_vector);
		}
		next_index = get_element_next_index(got_element);
		new_word_element = create_word_vector_element(word);
		set_item_to_vector(next_index, got_word_vector, (word_vector_element *)new_word_element);
		add_element_next_index(got_element);
	}
	return;
}

/*Opens the dic file and send each word to a specified function.*/
void manage_dic_file(char *file, void (*manage_dic_data)(item, item), vector *indexing_vector) {
	
	char word[100]; 
	FILE *dic_file;

	dic_file = fopen(file, "r");
	if(dic_file == NULL)
		file_error("Unable to open specified file");

	while(fscanf(dic_file, "%s", word) == 1) {
		manage_dic_data(word, indexing_vector);
	}

	fclose(dic_file);
	return;
}

/*********************** OUTPUT FILE FUNCTIONS *************************/

/*Creates the name of the output file by using the name of the pal file
	and changing its extension.*/
char *create_output_filename(char *pal_filename) {

	char *output_filename;
	int len = 0;

    len = strlen(pal_filename);
	output_filename = (char*)malloc((len-4+strlen(".path")+1)*sizeof(char));
	strcpy(output_filename, pal_filename);
    
    while(len) {
        if(output_filename[len] == '.') {
            output_filename[len] = '\0';
            break;
        }
        len --;
    }
    strcat(output_filename, ".path");
    return output_filename;
}

/*Writes to output file for the execution of type 1. Gets the number 
	of words in the dictionary for the problem word length and writes 
	it in the output file.*/
void write_to_file1(vector *indexing_vector, pal_problem *new_problem, FILE *output_file) {

	element *got_element = NULL;
	int n_words = 0;
	int word_len = 0;
	char *word;

	word = get_problem_word1(new_problem);
	word_len = strlen(word);
	got_element = get_vector_item(word_len, indexing_vector);
	n_words = get_element_n_words(got_element);

	fprintf(output_file, "%s %d\n\n", word, n_words);
	return;
}

/*Writes to output file for the execution of type 2. Using the 
	problem structure, writes the information of the problem
	words and positions in the output file.*/
void write_to_file2(pal_problem *new_problem, FILE *output_file) {

	fprintf(output_file, "%s %d\n", 
		get_problem_word1(new_problem), 
		get_problem_position1(new_problem));
	fprintf(output_file, "%s %d\n\n", 
		get_problem_word2(new_problem),
		get_problem_position2(new_problem));
	return;
}