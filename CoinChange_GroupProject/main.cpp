/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 2
 * October 25, 2016
 * main.cpp
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


int main(int argc, char *argv[]) {

    cout << "*********** Input and Output **********\n" << endl;

    string inFilename;
    string outFilename;

    // Ensure we are only getting one command line argument
    if((argc == 2) && (argv[1] != NULL)) {
        // Assign the file name
        inFilename = argv[1];
        outFilename = argv[1];
    }
    else {
        cout << "Error: Incorrect usage...\n" << endl;
        cout << "Usage: ./coinChange [input filename].txt\n" << endl;
        return 1;
    }

    ifstream in;
    ofstream out;

    // Set up the input stream file
    inFilename += ".txt";
    in.open(inFilename.c_str());
    if(in.fail()) {
        cout << "Could not open " << inFilename << endl;
        return 1;
    }

    // Set up the output stream file
    outFilename += "change.txt";
    out.open(outFilename.c_str());
    if(out.fail()) {
        cout << "Could not open " << outFilename << endl;
        return 1;
    }

    // String to store the line of text containing the integer array (getline)
    string line;
    // String to store the amount value that we want to find (getline)
    string val;
    // Total we are making change from
    int A;
    // The minimum number of coins used to make A
    int minCoins;
    // The length of the array of denominations V
    int length;

    cout << "Testing for correctness...\n" << endl;

    //////////////////////     CORRECTNESS TESTS HERE     //////////////////////
    ////////////////////////////////////////////////////////////////////////////

     out << "Algorithm changeSlow:" << endl;
     while(!in.eof()) {
         // Grab the line containing the array from the file and parse it
         while(getline(in, line)) {
             // Grab the amount A
             getline(in, val);
             // Convert val to an integer and store it as the amount A
             A = atoi(val.c_str());
             // Array of denominations
             int* V = convertToArray(line, length);
             // Array to store the number of times each denomination is used
             int* C = new int[length];
             // Zero all of C out
             for(int i = 0; i < length; i++)
                 C[i] = 0;
                
             // Brute Force or Divide and Conquer Algorithm
             // minCoins = changeSlow(V, length, A, C);
             // printToFile(out, C, length, minCoins);

             delete[] C;
             delete[] V;
         }
     }

     out << endl;
     in.clear();
     in.seekg(0, in.beg);

    out << "Algorithm changeGreedy:" << endl;
    while(!in.eof()) {
        // Grab the line containing the array from the file and parse it
        while(getline(in, line)) {
            // Grab the amount A
            getline(in, val);
            // Convert val to an integer and store it as the amount A
            A = atoi(val.c_str());
            // Array of denominations
            int* V = convertToArray(line, length);
            // Array to store the number of times each denomination is used
            int* C = new int[length];
            // Zero all of C out
            for(int i = 0; i < length; i++)
                C[i] = 0;

            // Greedy Algorithm
            minCoins = changeGreedy(V, length, A, C);
            printToFile(out, C, length, minCoins);

            delete[] C;
            delete[] V;
        }
    }

    out << endl;
    in.clear();
    in.seekg(0, in.beg);

    int count = 0;
    out << "Algorithm changeDP:" << endl;
    while(!in.eof()) {
        // Grab the line containing the array from the file and parse it
        while(getline(in, line)) {
            // Grab the amount A
            getline(in, val);
            // Convert val to an integer and store it as the amount A
            A = atoi(val.c_str());
            // Array of denominations
            int* V = convertToArray(line, length);
            // Array to store the number of times each denomination is used
            int* C = new int[length];
            // Zero all of C out
            for(int i = 0; i < length; i++)
                C[i] = 0;

            // Dynamic Programming
            minCoins = changeDP(V, length, A, C);
            printToFile(out, C, length, minCoins);

            delete[] C;
            delete[] V;
            count++;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    in.close();
    out.close();

    cout << "Output successfully printed to " << outFilename << "\n\n" << endl;

     cout << "******** Experimental Analysis ********\n" << endl;

     // /////////////////     EXPERIMENTAL ANALYSIS TESTS HERE     /////////////////

     // Set up the output stream file
     outFilename = "analysis.txt";
     out.open(outFilename.c_str());
     if(out.fail())
         cout << "Could not open " << outFilename << endl;

     clock_t start, end, total;

     // Sum of the runtimes
     double sum;
     // Average of the runtimes
     double avg;

     ///////     SET THESE VALUES     ///////
     ////////////////////////////////////////
     // The starting A value
     int startA = 1;
     // The end A value
     int endA = 50;
     // The value by which A increments
     int inc = 5;
     // An array of denominations
     int V[] = {1, 5, 10, 25, 50};
     // The length of V
     length = 5;
     ////////////////////////////////////////
     ////////////////////////////////////////
    
     // Array for storing denomination counts
     int *C = new int[length];
     // The number of values from startA to endA
     int n = (endA - startA) / inc;

     //Calculate runtimes for changeSlow()
     cout << "Calculating changeSlow Runtimes..." << endl;
     out << "Calculating changeSlow Runtimes..." << endl;
     cout << "n = " << n << endl;
     out << "n = " << n << endl;

     sum = 0;
     // Collect the sum of n runtimes
     for(int i = startA; i <= endA; i += inc) {
         start = clock();
         minCoins = changeSlow(V, length, i, C);
         end = clock();
         total = end - start;
         sum += total;
         cout << i << " Execution Time: " << (((float)total)/CLOCKS_PER_SEC) << endl;
         out << i << ": " << minCoins << " Execution Time: " << (((float)total)/(CLOCKS_PER_SEC)) << endl;
     }

     // Take the average of the runtimes
     avg = sum / n;
     cout << "\nAverage Runtime: " << avg << " ms";
     out << "\n\nAverage Runtime: " << avg << " ms" << endl;

     cout << "\n\n" << endl;
     out << "\n" << endl;


     // Calculate runtimes for changeGreedy()
     cout << "Calculating changeGreedy Runtimes..." << endl;
     out << "Calculating changeGreedy Runtimes..." << endl;
     cout << "n = " << n << endl;
     out << "n = " << n << endl;

     sum = 0;
     // Collect the sum of n runtimes
     for(int i = startA; i <= endA; i += inc) {
         start = clock();
         minCoins = changeGreedy(V, length, i, C);
         end = clock();
         total = end - start;
         sum += total;
         cout << i << " Execution Time: " << (((float)total)/(CLOCKS_PER_SEC)) << endl;
         out << i << ": " << minCoins << " Execution Time: " << (((float)total)/(CLOCKS_PER_SEC)) << endl;
     }

     // Take the average of the runtimes
     avg = sum / n;
     cout << "\nAverage Runtime: " << avg << " ms";
     out << "\n\nAverage Runtime: " << avg << " ms" << endl;

     cout << "\n\n" << endl;
     out << "\n" << endl;


     // Calculate runtimes for changeDP()
     cout << "Calculating changeDP Runtimes..." << endl;
     out << "Calculating changeDP Runtimes..." << endl;
     cout << "n = " << n << endl;
     out << "n = " << n << endl;

     sum = 0;
     // Collect the sum of n runtimes
     for(int i = startA; i <= endA; i += inc) {
         start = clock();
         minCoins = changeDP(V, length, i, C);
         end = clock();
         total = end - start;
         sum += total;
         cout << i << " Execution Time: " << (((float)total)/(CLOCKS_PER_SEC)) << endl;
         out << i << ": " << minCoins << " Execution Time: " << (((float)total)/(CLOCKS_PER_SEC)) << endl;
     }

     // Take the average of the runtimes
     avg = sum / n;
     cout << "\nAverage Runtime: " << avg << " ms";
     out << "Average Runtime: " << avg << " ms" << endl;

     cout << "\n\n" << endl;
     out << "\n" << endl;

     out.close();

     ////////////////////////////////////////////////////////////////////////////

    return 0;
}
