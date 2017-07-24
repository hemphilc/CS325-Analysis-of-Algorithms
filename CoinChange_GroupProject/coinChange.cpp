/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 2
 * October 26, 2016
 * coinChange.cpp
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "coinChange.h"

using namespace std;


int changeSlow(int* V, int length, int A, int* C) {
    //BASE CASE, we have 0 money to switch into coins
    //return 0, because we add the coins on the way up
    //(A < 0) should never happen because we check A >= V[i] before recursing
    if (A == 0) return 0;

    //creating an array that we will use to save best combination.
    int* save = new int[length];
    for(int i = 0; i < length; i++) save[i] = 0;

    //tracking vars
    int tempMin = 0;

    //not kosher, but helps find mins in the loop below
    //min needs to start out higher than the lowest value
    //that the recursed functions can return so that when we return
    //it min signifies the lowest value and not the value it was initialized with
    //more kosher would be to init it with MAX_INT.
    int min = 999999;
    int minIdx = 0; //index that we will use to track who returned the lowest sum

    //RECURSIVE CASE: FIND MIN VALUE OUT OF THE POSSIBLE BRANCHES
    //scroll through all coin denominations and recurse if A >= to the coin denomination
    //this means that we will break down A into all combinations of coins possible
    //we'll keep track of the smallest one and return that to the next level up
    //along with min we use C[] to store the best combination of coins found so far
    //and before returning we add the coin that returned the smallest number of coins to it
    for(int i = length - 1; i >= 0; i--) {
        if(A >= V[i]) {
            tempMin = changeSlow(V, length, A - V[i], C);
            if(tempMin < min){
                min = tempMin;
                //keep track of who returned the smallest coin num
                minIdx = i;
                //save min answer array
                for(int i = 0; i < length; i++) {
                    save[i] = C[i];
                }
            }
        }
        if(A < V[i]) {
            for(int i = 0; i < length; i++) {
                C[i] = 0;
            }
        }
    }

    //so, now that we are out of looping through all the branches
    //below us, with the smallest one saved in save[], we restore it into C[]
    //so that is can be read and used to track progress by the level above.
    for(int i = 0; i < length; i++){
        C[i] = save[i];
    }

    //finally, we update the smallest communication array that was returned with the 1 coin
    //that brought us this smallest array.
    C[minIdx]++;

    //free up temp array
    delete[] save;

    //up the minimum number of coins and return
    //min tracking and min C[] tracking are independant
    //and don't influence each other so we have to ++ both separately
    return min + 1;
}


int changeGreedy(int* V, int length, int A, int* C) {
    int totalLeft = A;
    int coinsUsed = 0;
    // Starting at the largest coin in a sorted array
    for(int i = length - 1; i >= 0; i--){
        // Delete denomination from the total until the total remaining is smaller than
        // the remaining change to be made
        while(totalLeft >= V[i]) {
            totalLeft -= V[i];
            C[i]++;
            coinsUsed ++;
        }
    }
    return coinsUsed;
}


int changeDP(int* V, int length, int A, int* C) {
    // Table to store values from bottom up
    int table[length][A + 1];
    // True/False table to track a coins usage
    bool* usedCoins[length];
    for (int i = 0; i < length; i++) {
        usedCoins[i] = new bool[A + 1];
    }

    // Set up the two tables for use, establishing the bottom first
    for(int i = 0; i < length; i++) {
        // Set the first column of each row to 0/false
        table[i][0] = 0;
        usedCoins[i][0] = false;
    }
    for(int i = 0; i <= A; i++) {
        // Set the first row's columns to i/true for the 1's denomination
        table[0][i] = i;
        usedCoins[0][i] = true;
    }

    // Build the table of values from the bottom up. The first row for the 1's
    // denomination has been set. Now fill in the table for denominations greater
    // than 1.
    for(int i = 1; i < length; i++) {
        for(int j = 1; j <= A; j++) {
            // If the current denomination is greater than the value we are searching
            // for, or if the coin count from the prior row is less than that of the
            // current table entry + 1, take that value and enter it as the current
            // table entry's value.
            if(V[i - 1] > j || table[i - 1][j] < (1 + table[i][j - V[i]])) {
                table[i][j] = table[i - 1][j];
                usedCoins[i][j] = false;
            }
            // Otherwise, count the current coin denomination towards finding the
            // total amount and count that coins usage in the table.
            else {
                table[i][j] = 1 + table[i][j - V[i]];
                usedCoins[i][j] = true;
            }
        }
    }

    // Call minCoinSet helper function to count how many times each denomination
    // was used in finding the total. (O(n + A))
    minCoinSet(length - 1, A, V, usedCoins, C);

    // Destroy the usedCoins array
    for(int i = 0; i < length; i++) {
        delete[] usedCoins[i];
    }

    // Return the last value from the table, which should be the minimum coins used
    return table[length - 1][A - 1];
}


void minCoinSet(int row, int A, int* V, bool* usedCoins[], int* C) {
    // If the current column index is zero, do nothing and return
    if(A <= 0) {return;}
    // If the current table entry is true, then add 1 to the current denomination's
    // count, reduce the current column index by the value of the current denomination,
    // and recurse.
    if(usedCoins[row][A] == true) {
        C[row]++;
        minCoinSet(row, A - V[row], V, usedCoins, C);
    }
    // Otherwise, reduce the row index and check the next row by recursing
    else {
        minCoinSet(row - 1, A, V, usedCoins, C);
    }
}


int* convertToArray(string line, int &length) {
    int size = 0;
    unsigned int i;
    string curr;
    for(i = 0; i < line.length(); i++) {
        if(line[i] == ',')
            size++;
    }
    length = size + 1;
    int* arr = new int[length];
    int j = 0;
    for(i = 1; i < line.length(); i++) {
        if(line[i] != ',' && line[i] != ']')
            curr += line[i];
        else {
            arr[j] = atoi(curr.c_str());
            curr.clear();
            j++;
        }
    }
    return arr;
}


void printToFile(ofstream& out, int* C, int length, int coinCount) {
    out << "[";
    for(int i = 0; i < length; i++) {
        out << C[i];
        if(i != length - 1)
            out << ", ";
    }
    out << "]\n";
    out << coinCount << endl;
}
