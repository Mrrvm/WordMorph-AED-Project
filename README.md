# WordMorph - AED Project

<h2>Feel free to use any code bits according to GPL3.</h2>

This project was done within the subject of Algorithms and Data Structures. The final objective is to find the shortest path between two words, the cost being equal to the number of letters that change to the square. 

For example finding the shortest path between this 2 words (the number represents the maximum number of letters that can change - number of mutations):

	bola roxo 2

in this dictionary:

	sopa
	roxo
	roxa
	bata nao
	tal
	rola
	bola aio
	sequencia

The solution is:

	bola 3
	rola
	roxa
	roxo
	
(the number 3 is the total cost)

The mid objective was to get the total number of words of a size in the dictionary (variant 1) or finding the position of a word in the dictionary of words with its size (variant 2).

The project was evaluated through mooshak, passing 19 out of 20 tests. 

<hr>
Some commands to use this program:

* To download simply do:

        $ git clone https://github.com/Mrrvm/WordMorph---AED-Project/

* To compile: 
   
        $ make
    
* To execute:

    
        $ ./wordmorph /path/to/it/test_file.dic /path/to/it/test_file.pal
        
use time flag to check memory and execution time:

         $ /usr/bin/time -v ./wordmorph /path/to/it/test_file.dic r/path/to/it/test_file.pal     
                   
* Execute with valgrind:

    
        $ valgrind --leak-check=full -v ./wordmorph /path/to/it/test_file.dic /path/to/it/test_file.pal

* To clear out printfs change 

    
        #define DEBUG_ON 
to

        #define DEBUG_OFF

in defs.h, and use spam((a)) instead of printf(a).

* To run the script for testing all test files with time and memory flags, in /res/pal/ directory do

		$ sh run_all.sh > ../results.txt 2>&1


