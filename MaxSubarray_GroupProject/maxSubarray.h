/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 1
 * October 16, 2016
 * maxSubarray.h
*/

#ifndef MAXSUBARRAY
#define MAXSUBARRAY

////////////////////Functions////////////////////

/**
 * @brief randArray generates an array of 100 random integers
 * @param min the minimum integer value
 * @param max the maximum integer value
 * @param length the length of the array
 * @return an array of 100 random integers
 */
int* randArray(int min, int max, int length);


/**
 * @brief convertToArray generates an integer array from a string of chars
 * @param line a string of chars to be converted
 * @return a pointer to an array of integers
 */
int* convertToArray(std::string line, int* length);


/**
 * @brief printToFile prints test results to a file
 * @param out a pointer reference to a file
 * @param line the full array string
 * @param arr a pointer to an array of integers
 * @param maxSum maximum subarray sum from test
 * @param start the starting subarray index
 * @param end the ending subarray index
 */
void printToFile(std::ofstream &out, std::string line, int* arr, int maxSum, int start, int end);


/**
 * @brief enumeration iterative implementation of Max Subarray
 * @param starting index of maxSubArray
 * @param ending index of maxSubArray
 * @param length the lenght of the array
 * @param arr a pointer reference to the address of an array
 * @return the maximum sum from a subarray
 */
int enumeration(int* array, int length, int &startIndex, int &endIndex);


/**
 * @brief betterEnumeration iterative implementation of Max Subarray
 * @param starting index of maxSubArray
 * @param ending index of maxSubArray
 * @param length the lenght of the array
 * @param arr a pointer reference to the address of an array
 * @return the maximum sum from a subarray
 */
int betterEnumeration(int* array, int length, int &startIndex, int &endIndex);


/**
 * @brief linearMaxSubarray linear implementation of Max Subarray
 * @param arr a pointer reference to the address of an array
 * @param length the lenght of the array
 * @param startIndex the starting subarray index
 * @param endIndex the ending subarray index
 * @return the maximum sum from a subarray
 */
int linearMaxSubarray(int* arr, int length, int &startIndex, int &endIndex);


/**
 * @brief maxPrefix is a helper function for divMaxSubarray
 * that finds the maximum prefix of a subarray
 * @param arr a pointer to the array
 * @param length the length of the array
 * @param arrStart the starting index within the array
 * @param maxFirstIdx is the index of the start of the largest subarray
 * @return the maximum sum from a prefix of a subarray
 */
int maxPrefix(int* arr, int length, int arrStart, int* maxFirstIdx);


/**
 * @brief maxSuffix is a helper function for divMaxSubarray
 * that finds the maximum suffix of a subarray
 * @param arr a pointer to the array
 * @param length the length of the array
 * @param arrStart the starting index within the array
 * @param maxFirstIdx is the index of the start of the largest subarray
 * @return the maximum sum from a suffix of a subarray
 */
int maxSuffix(int* arr, int length, int arrStart, int* maxFirstIdx);


/**
 * @brief divMaxSubarray is a divide and conquer implementation
 * of Max Subarray that returns the sum of the maximum subarray
 * @param arr a pointer to the array
 * @param length the length of the array
 * @param arrStart the starting index within the array
 * @param maxFirstIdx is the index of the start of the largest subarray
 * @return the maximum sum from a subarray
 */
int divMaxSubarray(int* arr, int length, int arrStart, int* maxFirstIdx);


/**
 * @brief divMaxSubarrayPrint prints the subarray from divMaxSubarray
 * given a starting index and a total sum
 * @param arr a pointer to the array
 * @param maxFirstIdx is the index of the start of the largest subarray
 * @param maxSum is the maximum sum that divMaxSubarray returns
 */
int divMaxSubarrayPrint(int* arr, int* maxFirstIdx, int maxSum);


/**
* @brief getDivEndIdx calculates the end index for divMaxSubarray
* given a starting index and a total
* @param arr a pointer to the array
* @param maxFirstIdx is the index of the start of the largest subarray
* @param maxSum is the maximum sum that divMaxSubarray returns
*/
int getDivEndIdx(int* arr, int* maxFirstIdx, int maxSum);

#endif // MAXSUBARRAY
