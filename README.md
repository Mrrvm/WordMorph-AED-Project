# WordMorph - AED Project

To compile: 

    $ make
    
To execute:

    $ ./wordmorph res/test_file.dic res/test_file.pal
    
Execute with valgrind:

    $ valgrind --leak-check=full -v ./wordmorph res/test_file.dic res/test_file.pal
