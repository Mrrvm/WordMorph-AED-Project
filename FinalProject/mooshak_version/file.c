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
	is already existant, just sets the number of mutations to the 
	number of mutations of the problem if this last one is higher.*/
void manage_pal_data(char *word, vector *indexing_vector, int typeof_exe) {
	
	int word_len;
	element *got_element = NULL;
	
	/*Gets the element with the word length from the indexing_vector*/
	word_len = strlen(word);
	got_element = get_vector_item(word_len, indexing_vector);

	if(got_element == NULL) {
		/*Creates the element with 0 words and the number of mutations
			of the current problem*/
		got_element = create_element(0, typeof_exe); 
		set_item_to_vector(word_len, indexing_vector, (element *)got_element);
	}
	else {
		if(typeof_exe > get_element_max_mut(got_element))
			set_element_max_mut(got_element, typeof_exe);
	}
	/*Add up the number of problems in the element with
		the current number of letter*/
	add_element_n_problems(got_element);
	return;
}

/*Reads the whole pal file once and sends each problem to
	manage_pal_data() function.*/
void manage_pal_file(char *file, vector *indexing_vector) {

	char first_word[100];
	char second_word[100];
	int typeof_exe = 0;
	FILE *pal_file;

	pal_file = fopen(file, "r");
	if(pal_file == NULL)
		file_error("Unable to open pal_file file");

	while(fscanf(pal_file, "%99s", first_word) == 1) {
		/*This conditions are just to avoid mooshak warnings...*/
		if(fscanf(pal_file, "%99s", second_word) == 1) {
			if(fscanf(pal_file, "%d", &typeof_exe) == 1) {
				manage_pal_data(second_word, indexing_vector, typeof_exe);
			}
		}
	}
	fclose(pal_file);
	return;
}

/*Reads one problem of the pal file and sets the problem variables
	to its structure in set_problem_variables() function*/
int read_pal_file(FILE* pal_file, pal_problem *new_problem) {
	
	char first_word[100];
	char second_word[100];
	int typeof_exe = 0;

	if(fscanf(pal_file, "%99s", first_word) == 1) {
		if(fscanf(pal_file, "%99s", second_word) == 1)
			if(fscanf(pal_file, "%d", &typeof_exe) == 1)
				set_problem_variables(new_problem, first_word, second_word, typeof_exe);
		return 1;
	}
	else
		return 0;
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

	if(got_element != NULL) {
		add_element_n_words(got_element);
	}
	return;
}

/*Second function to manage the dic file data. Receives each word of 
	the dictionary, and saves it to the word vector pointed by the
	element of the indexing vector with the word length, if this 
	word lenght	is a problem solver.*/
void manage_dic_data2(item got_char, item got_vector) {

	char *word = (char *)got_char;
	vector *indexing_vector = (vector *)got_vector;
	int word_len, next_index;
	element *got_element = NULL;
	word_vector_element *got_word_vector = NULL;
	
	/*Gets the element with the word length*/
	word_len = strlen(word);
	got_element = get_vector_item(word_len, indexing_vector);

	/*If this element is a problem solver aka not NULL*/
	if(got_element != NULL) {
		got_word_vector = get_element_word_vector(got_element);
		if(got_word_vector == NULL) {
			got_word_vector = create_word_vector(get_element_n_words(got_element));
			set_element_word_vector(got_element, got_word_vector);
		}
		/*Save it to the next available spot in the word vector*/
		next_index = get_element_next_index(got_element);
		copy_word_to_vector(word, got_word_vector, next_index);
		/*Set the future adj list of this word to null*/
		set_word_vector_element_head(got_word_vector, next_index, NULL);
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
	and changing its extension to path.*/
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

/*Prints the asked path for the problem being solved to the output file, 
	recursively*/
void print_path(word_vector_element *word_vector, FILE *aux_file, int src_index, path_element *path_vector, int i) {

	int parent = get_path_element_parent(i, path_vector);
	if(parent == src_index) {
		fprintf(aux_file, "%s\n", get_word_vector_word(i, word_vector));
		return;
	}
	print_path(word_vector, aux_file, src_index, path_vector, parent);
	
	fprintf(aux_file, "%s\n", get_word_vector_word(i, word_vector));
}

/*Writes everything needed to the output file. 
	The source word, the total weight and the path*/
void write_to_file(vector *indexing_vector, pal_problem *new_problem, FILE *output_file, path_element *path_vector) {

	int word_len = 0;
	element *got_element = NULL;
	word_vector_element *word_vector = NULL;
	int src_index = 0, dest_index = 0;

	/*Get the element with the word length from the indexing_vector*/
	word_len =  strlen(get_problem_word1(new_problem));
	got_element = get_vector_item(word_len, indexing_vector);
	/*Get the word vector of that element*/
	word_vector = get_element_word_vector(got_element);
	/*Get the position of the source and destiny word in the dictionary*/
	src_index = get_problem_position1(new_problem);
	dest_index = get_problem_position2(new_problem);

	/*Print the source word*/
	fprintf(output_file, "%s ", get_problem_word1(new_problem));
	/*If there is no path (aka if the parent of the destiny is ORFAN)*/
	if(get_path_element_parent(dest_index, path_vector) == ORFAN) {
		fprintf(output_file, "%d\n", -1);
		fprintf(output_file, "%s\n", get_problem_word2(new_problem));
	}
	else {
		/*Print the total weight from source to destiny*/
		fprintf(output_file, "%d\n", get_path_element_total_weight(dest_index, path_vector));
		/*Print the path recusively*/
		print_path(word_vector, output_file, src_index, path_vector, dest_index);
	}
	fprintf(output_file, "\n");
	/*Free dicionary of word size if there are no more problems to solve*/
	if(get_element_n_problems(got_element) == 0)
		free_word_vector(get_element_word_vector(got_element), get_element_n_words(got_element));
	return;
}
