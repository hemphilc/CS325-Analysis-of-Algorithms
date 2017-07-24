## These are compilation and run instructions for Coin Change program by
## Corey Hemphill - hemphilc@oregonstate.edu
## Sarah Cawley - cawleys@oregonstate.edu
## Konstantin Yakovenko - yakovenk@oregonstate.edu
## CS325 - Project 2
## October 25, 2016

To compile the program:

    $ make

To run:

    $ ./coinChange [input filename].txt
    
    Note: This program only accepts .txt files. When running the program, pass only the actual
    input file's name as the argument. Do not add the .txt extension to the filename.

To cleanup *.o files:

    $ make clean 


## IMPLEMENTATION DETAILS:

ChangeSlow is too slow of an algorithm to run with larger problems. However, there was no exact 
limit to the size of A because all three factors--the size of the denomination array, value of 
the sum, and the exact denominations in the denomination array--have very significant impact in 
terms of changeSlow's runtime. A good place to start is a denomination array of size 4-5 and A 
around 30. This should produce a running time of less than 2 minutes, most likely quite a bit
less.  


## OUTPUT FORMAT:

The output file is printed in the following format:
 
    Algorithm name:
 
  For each input array, print the following:
  
    Array of denomination counts for the minimum set of coins using the current input
    The minimum number of coins used to make amount A using the current input

Example:
    Algorithm changeSlow:
    [0, 0, 2]
    2
    [1, 0, 3, 0]
    4
    [1, 1, 1, 1]
    4
    [0, 1, 2, 1]
    4
    [0, 0, 1, 2]
    3
