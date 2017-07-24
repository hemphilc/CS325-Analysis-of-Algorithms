/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 2
 * October 26, 2016
 * coinChange.h
*/

#ifndef COINCHANGE
#define COINCHANGE

////////////////////Functions////////////////////

/**
 * @brief changeSlow uses divide and conquer to determine the minimum number of coins to make A
 * @param V a pointer to an array of integer denominations
 * @param length the length of V
 * @param A the amount of change to find minimum coins
 * @param C a pointer to an array containing a coint of each denomination used
 * @return the minimum number of coins to make A
 */
int changeSlow(int* V, int length, int A, int* C);


/**
 * @brief changeGreedy uses greedy method to determine the minimum number of coins to make A
 * @param V a pointer to an array of integer denominations
 * @param length the length of V
 * @param A the amount of change to find minimum coins
 * @param C a pointer to an array containing a coint of each denomination used
 * @return the minimum number of coins to make A
 */
int changeGreedy(int* V, int length, int A, int* C);


/**
 * @brief changeDP uses dynamic programming to determine the minimum number of coins to make A
 * @param V a pointer to an array of integer denominations
 * @param length the length of V
 * @param A the amount of change to find minimum coins
 * @param C a pointer to an array containing a coint of each denomination used
 * @return the minimum number of coins to make A
 */
int changeDP(int* V, int length, int A, int* C);



/**
 * @brief minCoinSet helper function that determines the minimum coin set to make A
 * @param i the current row
 * @param A the current column
 * @param V an array of denominations
 * @param usedCoins a two dimensional true/false table
 * @param C the array to store the denomination counts
 * @return C array is altered by reference
 */
void minCoinSet(int row, int A, int* V, bool* usedCoins[], int *C);


/**
 * @brief convertToArray generates an integer array from a string of chars
 * @param line a string of chars to be converted
 * @param length the length of the integer array returned
 * @return a pointer to an array of integers
 */
int* convertToArray(std::string line, int &length);


/**
 * @brief printToFile prints test results to a file
 * @param out a pointer reference to a file
 * @param C a pointer to an array of integers
 * @param length the length of the array
 * @param coinCount the number of coins used
 */
void printToFile(std::ofstream &out, int* C, int length, int coinCount);

/////////////////////////////////////////////////

 #endif // COINCHANGE
