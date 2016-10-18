/**************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* main.c
***************************************/

#include "file.h"

int main(int argc, char **argv) {

	FILE *dic_file, *pal_file, *output_file;
	char *line_data[3];

	if(argc != 3 || strcmp(get_filename_ext(argv[1]), "dic") || strcmp(get_filename_ext(argv[2]), "pal"))
		file_error("Missing arguments or wrong extension specified on file input");

	//create vector or list???????????

	dic_file = fopen(argv[1], "r");
	if(dic_file == NULL)
		file_error("Unable to open specified file");

	//read and store dictionary data

	pal_file = fopen(argv[2], "r");
	if(pal_file == NULL)
		file_error("Unable to open specified file");

	//while(read_pal_file(pal_file, line_data) != 0) {
		//decide which execution based on line_data[2]
		//do the execution
		//create output for that line
	//}

	//free data structures

	//exit

}