# WordMorph - AED Project

Feel free to use any code bits according to GPL3.

* Simply do:


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
