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

	FILE *output_file;
	vector *indexing_vector = NULL;
	char *output_filename;
	list *solution_list;
	/*TEMPORARY*/
	FILE *pal_file;
	int typeof_exe = 0;
	int i = 0;
	element *got_element = NULL;
	char *vector_name = " of indexing_vector";
	pal_problem *new_problem = NULL;

	/*Checks if the invocation is right*/
	if(argc != 3 || strcmp(get_filename_ext(argv[1]), "dic") || strcmp(get_filename_ext(argv[2]), "pal"))
		file_error("Missing arguments or wrong extension specified on file input");
	/*Alloc vector with each index as the number 
		of letters of a word. The maximum number of letters is 100*/
	indexing_vector = create_vector(101);
	/*Read pal file once, to get the maximum number of comutations for
		each different number of letters,  to know which number of 
		letters	is a problem to solve and save each problem in a list*/
	solution_list = create_list();
	manage_pal_file(argv[2], indexing_vector, solution_list);

	/*Printer*/
	for(i=0; i<101; i++) {
		got_element = get_vector_item(i, indexing_vector);
		spam((KGRN"Indexing vector element: %d\n"RESET,i));
		if(got_element != NULL)
			print_list(get_element_problem_list(got_element),
				print_pal_problem);
		spam(("\n"));
	}
	print_list(solution_list,
				print_pal_problem);
	spam(("\n"));
	/********/

	/*Read dictionary file once to get the number of words 
		for each different number of letters*/
	manage_dic_file(argv[1], manage_dic_data1, indexing_vector);
	/*Read dictionary file again to put all the words in the dictionary*/
	manage_dic_file(argv[1], manage_dic_data2, indexing_vector);

	print_vector(indexing_vector, print_word_vector, vector_name);


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

	/*SOLVE THE PROBLEMS*/
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

	/*WRITE OUTPUT FILE*/

 	/*Bring freedom upon this data structures!*/
 	free(output_filename);
 	/*free_indexing_vector(indexing_vector);*/
 	/*Bring death upon this files!*/
 	fclose(output_file);
	exit(0);
}
