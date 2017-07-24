/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 1
 * October 16, 2016
 * main.cpp
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "maxSubarray.h"

using namespace std;

int main() {
    srand((unsigned)time(0));

    cout << "*********** Input and Output **********\n" << endl;

    ifstream in;
    ofstream out;

    string inFilename = "MSS_Problems.txt";
    in.open(inFilename.c_str());
    if(in.fail())
        cout << "Could not open " << inFilename << endl;

    string outFilename = "MSS_Results.txt";
    out.open(outFilename.c_str());
    if(out.fail())
        cout << "Could not open " << outFilename << endl;

    string line;
    int maxSum = 0;
    int startIndex = 0;
    int endIndex = 0;
    int* length = new int;

    cout << "Testing for correctness..." << endl;

    // Read until we reach the end of the file
    while(!in.eof()) {
        // Get a line from the file and parse it
        while(getline(in, line)) {
            int* arr = convertToArray(line, length);

        //////////////////////     CORRECTNESS TESTS HERE     //////////////////////

            // Enumeration
            maxSum = enumeration(arr, *length, startIndex, endIndex);
            printToFile(out, line, arr, maxSum, startIndex, endIndex);

            // Better Enumeration
            maxSum = betterEnumeration(arr, *length, startIndex, endIndex);
            printToFile(out, line, arr, maxSum, startIndex, endIndex);

            // Divide and Conquer
            int maxFirstIdx = 0;
            int staticLength = *length;
            startIndex = 0;
            maxSum =  divMaxSubarray(arr, staticLength, startIndex, &maxFirstIdx);
            int divEndIdx = getDivEndIdx(arr, &maxFirstIdx, maxSum);
            printToFile(out, line, arr, maxSum, maxFirstIdx, divEndIdx);

            // Linear
            maxSum = linearMaxSubarray(arr, *length, startIndex, endIndex);
            printToFile(out, line, arr, maxSum, startIndex, endIndex);

        ////////////////////////////////////////////////////////////////////////////

            //cout << endl;
            delete[] arr;
        }
    }
    in.close();
    out.close();
    free(length);

    cout << "Output successfully printed to " << outFilename << "\n\n" << endl;

    cout << "******** Experimental Analysis ********\n" << endl;

    /////////////////     EXPERIMENTAL ANALYSIS TESTS HERE     /////////////////

    outFilename = "analysis.txt";
    out.open(outFilename.c_str());
    if(out.fail())
        cout << "Could not open " << outFilename << endl;

    int* arr;
    int numTests = 10;
    int n = 100;
    int min = -100;
    int max = 100;
    double sum;
    double avg;

    clock_t start, end, total;

    // Calculate runtimes for enumeration()

    cout << "Calculating Enumeration Max Sum Subarray Runtimes..." << endl;
    out << "Calculating Enumeration Max Sum Subarray Runtimes..." << endl;
    cout << "n = " << n;
    out << "n = " << n << endl;
    sum = 0;
    for(int i = 0; i < numTests; i++) {
        arr = randArray(min, max, n);
        start = clock();
        maxSum = enumeration(arr, n, startIndex, endIndex);
        end = clock();
        total = end - start;
        sum += total;
        cout << (i + 1) << ". " << "Execution Time: " << (((float)total)/CLOCKS_PER_SEC);
        out << (i + 1) << ". " << "Execution Time: " << (((float)total)/CLOCKS_PER_SEC) << endl;
        delete[] arr;
    }

    avg = sum / numTests;
    cout << "\nAverage Runtime: " << avg << " ms";
    out << "Average Runtime: " << avg << " ms" << endl;

    cout << "\n\n" << endl;
    out << "\n" << endl;


    // Calculate runtimes for betterEnumeration()
    cout << "Calculating Better Enumeration Max Sum Subarray Runtimes..." << endl;
    out << "Calculating Better Enumeration Max Sum Subarray Runtimes..." << endl;
    cout << "n = " << n;
    out << "n = " << n << endl;

    sum = 0;
    for(int i = 0; i < numTests; i++) {
        arr = randArray(min, max, n);
        start = clock();
        maxSum = betterEnumeration(arr, n, startIndex, endIndex);
        end = clock();
        total = end - start;
        sum += total;
        cout << (i + 1) << ". " << "Execution Time: " << (((float)total)/CLOCKS_PER_SEC);
        out << (i + 1) << ". " << "Execution Time: " << (((float)total)/CLOCKS_PER_SEC) << endl;
        delete[] arr;
    }

    avg = sum / numTests;
    cout << "\nAverage Runtime: " << avg << " ms";
    out << "Average Runtime: " << avg << " ms" << endl;

    cout << "\n\n" << endl;
    out << "\n" << endl;


    // Calculate runtimes for divMaxSubarray()
    cout << "Calculating Divide and Conquer Max Sum Subarray Runtimes..." << endl;
    out << "Calculating Divide and Conquer Max Sum Subarray Runtimes..." << endl;
    cout << "n = " << n;
    out << "n = " << n << endl;

    sum = 0;
    int maxFirstIdx = 0;
    for(int i = 0; i < numTests; i++) {
        arr = randArray(min, max, n);
        start = clock();
        maxSum = divMaxSubarray(arr, n, 0, &maxFirstIdx); //*length -> n
        end = clock();
        total = end - start;
        sum += total;
        cout << (i + 1) << ". " << "Execution Time: " << (((float)total)/(CLOCKS_PER_SEC));
        out << (i + 1) << ". " << "Execution Time: " << (((float)total)/(CLOCKS_PER_SEC)) << endl;
        delete[] arr;
    }

    avg = sum / numTests;
    cout << "\nAverage Runtime: " << avg << " ms";
    out << "Average Runtime: " << avg << " ms" << endl;

    cout << "\n\n" << endl;
    out << "\n" << endl;


    // Calculate runtimes for linearMaxSub()
    cout << "Calculating Linear Max Sum Subarray Runtimes..." << endl;
    out << "Calculating Linear Max Sum Subarray Runtimes..." << endl;
    cout << "n = " << n;
    out << "n = " << n << endl;

    sum = 0;
    for(int i = 0; i < numTests; i++) {
        arr = randArray(min, max, n);
        start = clock();
        maxSum = linearMaxSubarray(arr, n, startIndex, endIndex);
        end = clock();
        total = end - start;
        sum += total;
        cout << (i + 1) << ". " << "Execution Time: " << (((float)total)/(CLOCKS_PER_SEC));
        out << (i + 1) << ". " << "Execution Time: " << (((float)total)/(CLOCKS_PER_SEC)) << endl;
        delete[] arr;
    }

    avg = sum / numTests;
    cout << "\nAverage Runtime: " << avg << " ms";
    out << "Average Runtime: " << avg << " ms" << endl;

    cout << "\n\n" << endl;
    out << "\n" << endl;

    out.close();

    ////////////////////////////////////////////////////////////////////////////

    return 0;
}
