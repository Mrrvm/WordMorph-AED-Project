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

	FILE *dic_file, *pal_file, *output_file;
	char first_word[1000], second_word[1000];
	int typeof_exe;

	if(argc != 3 || strcmp(get_filename_ext(argv[1]), "dic") || strcmp(get_filename_ext(argv[2]), "pal"))
		file_error("Missing arguments or wrong extension specified on file input");

	/*create vector or list???????????*/

	dic_file = fopen(argv[1], "r");
	if(dic_file == NULL)
		file_error("Unable to open specified file");

	/*read and store dictionary data*/
	manage_dic_file(dic_file);

	pal_file = fopen(argv[2], "r");
	if(pal_file == NULL)
		file_error("Unable to open specified file");

	while(read_pal_file(pal_file, first_word, second_word, &typeof_exe)) {
		/*decide which execution based on line_data[2]
		do the execution
		create output for that line*/
		printf("%s %s %d\n", first_word, second_word, typeof_exe);
	}

	/*free data structures*/

	exit(0);

}