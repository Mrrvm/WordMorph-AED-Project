/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* main.c
* Main execution of the program
***************************************************************/

#include "file.h"

int main(int argc, char **argv) {

	FILE *pal_file, *outputfile;
	char first_word[100], second_word[100];
	char *nome;
	int typeof_exe;
	vector *indexing_vector = NULL;

	if(argc != 3 || strcmp(get_filename_ext(argv[1]), "dic") || strcmp(get_filename_ext(argv[2]), "pal"))
		file_error("Missing arguments or wrong extension specified on file input");

	/*Alloc vector with each index as the number 
		of letters of a word. The maximum number of letters is 100*/
	indexing_vector = create_vector(101);
	/*Read pal file once, to get the maximum number of comutations for
		each different number of letters, and to know which number of 
		letters	is a problem to solve*/
	manage_pal_file(argv[2], indexing_vector);
	/*Read dictionary file once to get the number of words 
		for each different number of letters*/
	manage_dic_file(argv[1], manage_dic_data1, indexing_vector);
	/*Create the rest of the vector with the number of word of each number
		of letters*/
	
	/*Read dictionary file again to put all the words in the dictionary*/
	manage_dic_file(argv[1], print_none, indexing_vector);

	/*Print the dicitonary already organized*/
	print_vector(indexing_vector, print_element);

	/*Read pal file again and leave it open till all the 
		problems are solved*/
	pal_file = fopen(argv[2], "r");
	if(pal_file == NULL)
		file_error("Unable to open specified file");

	while(read_pal_file(pal_file, first_word, second_word, &typeof_exe)) {
		/*decide which execution based on typeof_exe*/
		/*do the execution*/
		/*create output for that line*/
		spam(("%s %s %d\n", first_word, second_word, typeof_exe));
	}

	/*free data structures*/

	/*
	    nome=(char*)malloc(strlen(argv[2])+strlen(".stat")+1)*sizeof(char);
          
	strcpy ( nome, argv[2] );
    strcat ( nome, ".stat" );

	outputfile = fopen( nome , "w"); 
	fprintf(outputfile, 

	fclose(outputfile);
free(nome);
*/

	exit(0);

}
