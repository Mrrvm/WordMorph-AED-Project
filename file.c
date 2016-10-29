/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* file.c
* All functions related to reading/creating/managing files.
***************************************************************/

#include "file.h"

void manage_dic_file(FILE *dic_file/*, void* store_dic_data */) {
	
	char word[100]; 

	/*reads word and stores it in data structure*/
	while(fscanf(dic_file, "%99s", word) == 1) {
		spam(("%s\n", word));
		/*store_dic_data()*/
	}
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

