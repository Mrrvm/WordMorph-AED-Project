# WordMorph - AED Project

* Simply do:


        $ git clone https://github.com/Mrrvm/WordMorph---AED-Project/

* To compile: 

   
        $ make
    
* To execute:

    
        $ ./wordmorph res/test_file.dic res/test_file.pal
    
* Execute with valgrind:

    
        $ valgrind --leak-check=full -v ./wordmorph res/test_file.dic res/test_file.pal

* To clear out printfs change 

    
        #define DEBUG_ON 
to

        #define DEBUG_OFF
    
And use spam((a)) instead of printf(a).
