/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 1
 * October 16, 2016
 * maxSubarray.cc
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "maxSubarray.h"

using namespace std;


int* randArray(int min, int max, int length) {
    int* arr = new int[length];
    for(int i = 0; i < length; i++) {
        arr[i] = (rand() % (max)) - (rand() % abs(min));
    }
    cout << endl;
    return arr;
}


int* convertToArray(string line, int* length) {
    int size = 0;
    unsigned int i;
    string curr;
    // Count commas to figure out array length
    for(i = 0; i < line.length(); i++) {
        if(line[i] == ',')
            size++;
    }
    *length = size + 1;
    int* arr = new int[*length];
    int j = 0;
    for(i = 1; i < line.length(); i++) {
        if(line[i] != ',' && line[i] != ']')
            curr += line[i];
        else {
            arr[j] = atoi(curr.c_str());
            //cout << arr[j] << " ";
            curr.clear();
            j++;
        }
    }
    //cout << endl;
    return arr;
}


void printToFile(ofstream& out, string line, int* arr, int maxSum, int start, int end) {
    out << line << "\n";
    out << "[";
    for(int i = start; i < end; i++) {
        out << arr[i];
        if(i != end - 1)
            out << ", ";
    }
    out << "]\n";
    out << maxSum << "\n\n";
}


int enumeration(int* arr, int length, int &startIndex, int &endIndex) {
    int k;
    int sum = 0;
    int maxSum = 0;
    for(int i = 0; i < length; i++) {
        for(int j = i; j < length; j++) {
            for(k = i; k <= j; k++) {
                sum += arr[k];
            }
            if(sum > maxSum) {
                startIndex = i;
                endIndex = k;
                maxSum = sum;
                //cout << "\nNew maxSum " << maxSum << " startIndex " << startIndex << " endIndex" << endIndex << "\n";
            }
            sum = 0;
        }
    }
    return maxSum;
}


int betterEnumeration(int* arr, int length, int &startIndex, int &endIndex) {
    int sum = 0;
    int maxSum = 0;
    for(int i = 0; i < length; i++) {
        for(int j = i; j < length; j++) {
            sum += arr[j];
            if(sum > maxSum) {
                startIndex = i;
                endIndex = j + 1;
                maxSum = sum;
            }
        }
        sum = 0;
    }
    return maxSum;
}


int linearMaxSubarray(int* arr, int length, int &startIndex, int &endIndex) {
    int lowEnd, highEnd;
    int endSum = 0;
    int maxSum = 0;
    for(int i = 0; i < length; i++) {
        highEnd = i;
        if(endSum > 0) {
            endSum = endSum + arr[i];
        }
        else {
            lowEnd = i;
            endSum = arr[i];
        }
        if(endSum > maxSum) {
            maxSum = endSum;
            startIndex = lowEnd;
            endIndex = highEnd + 1;
        }
    }
    return maxSum;
}


int maxPrefix(int* arr, int length, int arrStart,int* maxFirstIdx) {
   int maxSum = 0;
   int sum = 0;

   //since we are looking for a prefix, we scan up from the
   //left and return the highest val.
   for(int i = 0; i < length; i++){
      sum = sum + arr[arrStart + i];
      if(sum > maxSum) {
          maxSum = sum;
         *maxFirstIdx = arrStart + i;
      }
   }

   return maxSum;
}


int maxSuffix(int* arr, int length, int arrStart,int* maxFirstIdx){
   int maxSum = 0;
   int sum = 0;

   //since we are looking for suffix, we scan sown from the
   //right and return the biggest val.
   for(int i = length - 1; i >= 0; i--){
      sum = sum + arr[arrStart + i];
      if(sum > maxSum) {
         maxSum = sum;
         *maxFirstIdx = arrStart + i;
      }

   }

   return maxSum;
}


int divMaxSubarray(int* arr, int length, int arrStart, int* maxFirstIdx) {
   //base case
   if(length == 1){
      return arr[arrStart];
   }

   //resursive case
   //we get the max subarray sum from either left subarray, right, or
   //spanning the two.
   else {
      //Case 1: the max sum in left sub
      //length/2 is integer division, so equivalent of floor()
      int leftMax = divMaxSubarray(arr, length/2, arrStart, maxFirstIdx);

      //if array is odd, we set a special length
      //for the right array because left side was floored.
      int rightLength = length/2;
      if((length % 2) != 0){
         rightLength += 1;
      }

      //Case 2: the max sum in the right sub
      int rightMax = divMaxSubarray(arr, rightLength, arrStart + (length/2), maxFirstIdx);

      //save max first idx
      int curMax = *maxFirstIdx;

      //Case 3: max sum spanning the two
      int suffixMax =  maxPrefix(arr, rightLength, arrStart + (length/2), maxFirstIdx) +
                        maxSuffix(arr, length/2, arrStart, maxFirstIdx);

      //Pick the best case and return it. Update the maxFirstIdx.
      int max = suffixMax;

      if(rightMax >= max) {
         max = rightMax;
         *maxFirstIdx = curMax; //arrStart + (length/2);
      }

      if(leftMax >= max) {
         max = leftMax;
         *maxFirstIdx = arrStart;
      }

      return max;
   }
}


int divMaxSubarrayPrint(int* arr, int* maxFirstIdx, int maxSum){
   int sum = 0;
   int i = 0;
   cout << "[";
   while(sum < maxSum){
      cout << arr[*maxFirstIdx + i];
      sum += arr[*maxFirstIdx + i];
      if(sum >= maxSum) break;
      cout << ",";
      i++;
   }
   cout << "]" << endl;

   return 0;
}

int getDivEndIdx(int* arr, int* maxFirstIdx, int maxSum) {
    int sum = 0;
    int i = 0;
    //cout << "maxFirtsIdx: " << *maxFirstIdx << " maxSum: " << maxSum << endl;
    while (sum < maxSum) {
        sum += arr[*maxFirstIdx + i];
        i++;
        if (sum >= maxSum) break;
    }

    return (i + *maxFirstIdx);
}
