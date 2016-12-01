#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *my_file, *sol_file;
	char *my_string = NULL, *sol_string = NULL;
	int i = 1;

	my_file = fopen(argv[1], "r");
	if(my_file == NULL)
		printf("First arg is null\n");
	sol_file = fopen(argv[2], "r");
	if(sol_file == NULL)
		printf("Second arg is null\n");

	while(fscanf(sol_file, "%s", sol_string) == 1) {
		fscanf(my_file, "%s", my_string); 
		if(strcmp(my_string, sol_string) != 0) {
			printf("\nDIFFERENT IN LINE: %d\n", i);
			printf("SOL: %s\n", sol_string);
			printf("MINE: %s\n", my_string);
			exit(0);
		}
		i++;
	}
	printf("PERFECT!\n");
	exit(1);
}