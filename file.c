/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* file.c
* All functions related to reading/creating/managing files and its data
************************************************************************/

#include "file.h"

/********************* PAL FILE FUNCTIONS ***********************/

void manage_pal_data(char *word, vector *indexing_vector, int typeof_exe) {
	
	int word_len;
	element *got_element = NULL;
	
	word_len = strlen(word);
	got_element = get_vector_item(word_len, indexing_vector);

	if(got_element == NULL) {
		got_element = create_element(0, typeof_exe); 
		set_item_to_vector(word_len, indexing_vector, (element *)got_element);
	}
	else {
		if(typeof_exe > get_element_max_comut(got_element))
			set_element_max_comut(got_element, typeof_exe);
	}

	return;
}

void manage_pal_file(char *file, vector *indexing_vector) {

	char first_word[100];
	char second_word[100];
	int typeof_exe = 0;
	FILE *pal_file;

	pal_file = fopen(file, "r");
	if(pal_file == NULL)
		file_error("Unable to open specified file");

	while(fscanf(pal_file, "%99s", first_word) == 1) {
		fscanf(pal_file, "%99s", second_word);
		fscanf(pal_file, "%d", &typeof_exe);
		manage_pal_data(second_word, indexing_vector, typeof_exe);
	}

	fclose(pal_file);
	return;
}

int read_pal_file(FILE* pal_file, char *first_word, char *second_word, int *typeof_exe) {
	
	/*check SECURITY!!*/
	if(fscanf(pal_file, "%99s", first_word) == 1) {
		fscanf(pal_file, "%99s", second_word);
		fscanf(pal_file, "%d", typeof_exe);
		return 1;
	}
	else {
		/*File ended*/
		return 0;
	}
}

/********************* DIC FILE FUNCTIONS ***********************/

void manage_dic_data1(item got_char, item got_vector) {
	
	char *word = (char *)got_char;
	vector *indexing_vector = (vector *)got_vector;
	int word_len;
	element *got_element = NULL;
	
	word_len = strlen(word);
	got_element = get_vector_item(word_len, indexing_vector);

	if(got_element != NULL) {
		add_element_n_words(got_element);
	}
	return;
}

void manage_dic_data2(item got_char, item got_vector) {


	char *word = (char *)got_char;
	vector *indexing_vector = (vector *)got_vector;
	int word_len, next_index;
	element *got_element = NULL;
	vector *word_vector = NULL;
	word_element *new_word_element = NULL;
	
	word_len = strlen(word);
	got_element = get_vector_item(word_len, indexing_vector);

	if(got_element != NULL) {
		word_vector = get_element_word_vector(got_element);
		next_index = get_element_next_index(got_element);
		new_word_element = create_word_element(word);
		set_item_to_vector(next_index, word_vector, new_word_element);
		add_element_next_index(got_element);
	}
	return;
}

void manage_dic_file(char *file, void (*manage_dic_data)(item, item), vector *indexing_vector) {
	
	char word[100]; 
	FILE *dic_file;

	dic_file = fopen(file, "r");
	if(dic_file == NULL)
		file_error("Unable to open specified file");

	while(fscanf(dic_file, "%99s", word) == 1) {
		spam(("%s\n", word));
		manage_dic_data(word, indexing_vector);
	}

	fclose(dic_file);
	return;
}


