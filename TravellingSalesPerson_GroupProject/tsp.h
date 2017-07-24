/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 4
 * December 2, 2016
 * tsp.h
*/

#ifndef TSP
#define TSP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath> //math.h
#include <limits>
#include <vector>
#include <stack>
#include <iomanip>

#define DEBUG 0

using namespace std;

/////////////////////CLASSES/////////////////////

class City
{
public:
    int identifier;
    int x;
    int y;

    /**
     * @brief Default Constructor
     */
    City();

    /**
     * @brief Parameterized Constructor initializes all members
     */
    City(int id, int xVal, int yVal);

    /**
     * @brief Default Destructor
     */
    ~City();

    /**
     * @brief getDistance determines the distance between two cities
     * @param other a city object for which we want to find the distance to
     * @return the distance between the two cities
     */
    int getDistanceTo(const City& other) const;
};

class T_S_P
{
public:
    string inFilename; // Input file name
    string outFilename; // Output file name
    int numCities; // Number of cities
    City *Cities; // A pointer to an array of City objects
    int **Graph; // A graph storing distances between Cities
    vector<int> *AdjMatrix; // An adjacency matrix for related Cities
    vector<int> oddDegNodes; // A vector storing indicies for odd degree vertices
    vector<int> EulerPath; // A vector storing a Euler path
    int *HamPathArr; // An array for storing a Hamilton path
    int minPathLength; // The shortest path length found

    /**
     * @brief Default Constructor
     */
    T_S_P();

    /**
     * @brief Parameterized Constructor initializes all members
     */
    T_S_P(string inFile, string outFile);

    /**
     * @brief Default Destructor
     */
    ~T_S_P();

    /**
     * @brief generateGraph fills Graph with the distances between each city
     * @return a filled matrix by reference
     */
    void generateGraph();

    /**
     * @brief printGraph prints values from a filled matrix Graph
     * @return values from a matrix Graph are printed to console
     */
    void printGraph();

    /**
     * @brief getMST uses Prim's algorithm to find a minimal spanning tree in a Graph
     * @return a minimum spanning tree graph
     */
    void getMST();

    /**
     * @brief getMinKey helper function to getMST, finds next smallest edge to traverse
     * @param keyVals an array storing the edge distances for used edges
     * @param isInMST an array storing T/F values indicating a vertex's use in the MST
     * @return an index of the next vertex with the smallest edge distance
     */
    int getMinKey(int keyVals[], bool isInMST[]);

    /**
     * @brief printMST prints a minimum spanning tree to console
     * @param parentsNodes an array of parent tree nodes
     * @return a minimum spanning tree is printed to console
     */
    void printMST(int parentNodes[]);

    /**
     * @brief getOddDegNodes fills a vector with indicies of odd degree vertices
     * @return a subgraph O filled with odd degree vertices
     */
    void getOddDegNodes();

    /**
     * @brief getPerfectMatching finds a min cost perfect matching subgraph M for O
     * @return a perfect matching subgraph M filled with odd degree vertices
     */
    void getPerfectMatching();

    /**
     * @brief eulerianPath finds a Euler path
     * @param p starting position for iterating through a vector
     * @return a Euler path stored in a vector by reference
     */
    void eulerianPath(int idx);

    /**
     * @brief hamiltonianPath finds a Hamilton path
     * @return a Hamilton path stored in a vector by reference
     */
    void hamiltonianPath();

    /**
     * @brief Christofides finds an approximate solution to the TSP problem
     * @param p starting position for iterating through a vector
     * @return the shortest path for a given graph G = (V, w)
     */
    void Christofides();

    /**
     * @brief twoOpt takes a route that crosses over itself and reorders it
     * @return the length of a more optimized shortest path
     */
    void twoOpt();

    /**
     * @brief pathIsShorter helper for finding a shorter minimum path
     * @return the length of a more optimized shortest path
     */
    bool pathIsShorter(int v1, int v2, int v3, int v4);

    /**
     * @brief swapNodes swaps two nodes
     * @param startV starting vertex index
     * @param endV ending vertex index
     * @return two nodes have been swapped
     */
    void swapNodes(int startV, int endV);

    /**
     * @brief printPath prints the mimimum path to console
     * @return a list of indicies representing a path is printed to the console
     */
    void printPath();

    /**
     * @brief printToFile prints the mimimum path and tour length to an outfile
     */
    void printToFile();

    /**
     * @brief printToFileArr prints the mimimum path ARRAY and tour length to an outfile
     */
    void printToFileArr();

    /**
     * @brief printAdjMatrix prints the adjacency matrix to console
     * @return a list of indicies representing a matrix and adj vertices is printed
     */
    void printAdjMatrix();
};

/////////////////////////////////////////////////

////////////////////FUNCTIONS////////////////////

/**
 * @brief readCityFile reads in city data from file and stores to an array
 * @param fileName the name of the file to be read from
 * @param Cities a pointer to an array of City objects
 * @return an array of City objects by reference
 */
void readCityFile(const string fileName, City *Cities);

/**
 * @brief cityCount determines number of nodes by counting lines in the in-file
 * @param inFile a string containing the name of an input file
 * @return the number of nodes found
 */
int cityCount(const string inFile);

/**
 * @brief printArray prints a given array to console
 * @param arr an array of a given type to be printed
 * @param length the length of the array
 * @param a given array is printed to console
 */
template <typename T>
void printArray(T arr[], int length);

/////////////////////////////////////////////////

 #endif // TSP
