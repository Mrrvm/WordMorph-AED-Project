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
	
	char word[1000]; /*check if this is right!!!!*/

	/*reads word and stores it in data structure*/
	while(fscanf(dic_file, "%999s", word) == 1) {
		printf("%s\n", word);
		/*store_dic_data()*/
	}
	return;
}

int read_pal_file(FILE* pal_file, char *first_word, char *second_word, int *typeof_exe) {
	
	/*check SECURITY!!*/
	if(fscanf(pal_file, "%999s", first_word) == 1) {
		fscanf(pal_file, "%999s", second_word);
		fscanf(pal_file, "%d", typeof_exe);
		return 1;
	}
	else {
		/*File ended*/
		return 0;
	}
}