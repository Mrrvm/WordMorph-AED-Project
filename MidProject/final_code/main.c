/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* main.c
* Main execution of the program
***************************************************************/

#include "execution.h"

int main(int argc, char **argv) {

	FILE *pal_file, *output_file;
	vector *indexing_vector = NULL;
	pal_problem *new_problem = NULL;
	char *output_filename;
	int typeof_exe = 0;

	/*Checks if the invocation is right*/
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
	/*Read dictionary file again to put all the words in the dictionary*/
	manage_dic_file(argv[1], manage_dic_data2, indexing_vector);
	/*Open pal file again and leave it open till all the 
		problems are solved*/
	pal_file = fopen(argv[2], "r");
	if(pal_file == NULL)
		file_error("Unable to open specified file");
	/*Alloc space for a structure to hold the problems of pal file,
		temporarily*/
	new_problem = create_pal_problem();
	/*Create the output filename - pal filename with .stat extension.
		Generate the output file*/
	output_filename = create_output_filename(argv[2]);
	output_file = fopen(output_filename, "w");
	if(output_file == NULL)
		file_error("Unable to create specified file");
	/*Start reading problem by problem until EOF*/
	while(read_pal_file(pal_file, new_problem)) {
		typeof_exe = get_problem_typeof_exe(new_problem);
		if(typeof_exe == 1) {
			write_to_file1(indexing_vector, new_problem, output_file);
		}
		else if(typeof_exe == 2) {
			run_position_search(new_problem, indexing_vector);
			write_to_file2(new_problem, output_file);
		}
 	}
 	/*Bring freedom upon this data structures!*/
 	free(output_filename);
 	free(new_problem);
 	free_indexing_vector(indexing_vector);
 	/*Bring death upon this files!*/
 	fclose(output_file);
	fclose(pal_file);
	exit(0);
}
