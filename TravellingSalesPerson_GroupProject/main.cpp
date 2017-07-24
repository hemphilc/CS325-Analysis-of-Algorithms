/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 4
 * December 2, 2016
 * main.cpp
*/

#include "tsp.h"
void runTests();

int main(int argc, char *argv[]) {

    string inFilename;
    string outFilename;

    string runTestsStr = "runTests";

    // Ensure we are only getting one command line argument
    if((argc == 2) && (argv[1] != NULL)) {
        if(argv[1] == runTestsStr){
            runTests();
            return 0;
        }
        // Assign the file name
        inFilename = argv[1];
        outFilename = argv[1];
    }
    else {
        cout << "Error: Incorrect usage...\n" << endl;
        cout << "Usage: ./tsp [input filename]\n" << endl;
        exit(EXIT_FAILURE);
    }

    // Set up the input stream file name
    inFilename += ".txt";
    // Set up the output stream file name
    outFilename += ".txt.tour";

    ///////////////////     RUN TSP ON PASSED FILE HERE     ///////////////////
    ////////////////////////////////////////////////////////////////////////////

    // Setup clocks
    clock_t start, end, total;

    // Start the clock
    start = clock();

    // Traveling Sales Person Constructor call
    T_S_P SalesPerson(inFilename, outFilename);

    // Christofides Algorithm call
    SalesPerson.Christofides();

    // 2-Opt call
    //SalesPerson.twoOpt();

    // Print the results to an output file
    //SalesPerson.printToFile();
    SalesPerson.printToFileArr();

    // Stop the clock
    end = clock();

    // Calc runtime
    total = end - start;
    cout << "\nRuntime(can be unlim here): " << (((float)total)/CLOCKS_PER_SEC) << endl;

    return 0;
}

////////////////////////     RUN TSP ON ALL EXAMPLES     ///////////////////
////////////////////////////////////////////////////////////////////////////
void runTests() {
    string inFilename;
    string outFilename;
    // Variable for comparing our solutions to.
    float optimalAnswer = 0;

    cout << "******** SPEED/CORRECTNESS TESTS ********\n" << endl;
    /////////////////////////////////TSP EX1////////////////////////////////////
    cout << "TSP Example 1:" << endl;

    // Set up the input stream file name
    inFilename = "tsp_example_1.txt";
    // Set up the output stream file name
    outFilename = "tsp_example_1.txt.tour";

    // Setup clocks
    clock_t start, end, total;

    // Start the clock
    start = clock();

    // Traveling Sales Person Constructor call
    T_S_P SalesPerson1(inFilename, outFilename);

    // Christofides Algorithm call
    SalesPerson1.Christofides();

    // 2-Opt call
    //SalesPerson1.twoOpt();

    // Print the results to an output file
    SalesPerson1.printToFileArr();

    // Stop the clock
    end = clock();

    // Calc runtime
    total = end - start;
    cout << "Runtime(can be unlim here): " << (((float)total)/CLOCKS_PER_SEC) << endl;

    // Optimal Solutions provided by instructor
    //tsp_example 1: 108159
    optimalAnswer = 108159;

    cout << "Optimal Length: " << optimalAnswer << endl;
    cout << "Tour Length: " << SalesPerson1.minPathLength << endl;
    //SalesPerson.printPath();

    // Correctness gets calculated with (our length)/(optimal length)
    // for full credit we have to be below 1.25 in UNLIMITED time.
    float ratio = SalesPerson1.minPathLength / optimalAnswer;
    cout << "Ratio 1 < Rho < 1.25?: " << ratio << endl << endl;


    /////////////////////////////////TSP EX2////////////////////////////////////
    cout << "TSP Example 2:" << endl;

    // Set up the input stream file name
    inFilename = "tsp_example_2.txt";
    // Set up the output stream file name
    outFilename = "tsp_example_2.txt.tour";

    // Start the clock
    start = clock();

    // Traveling Sales Person Constructor call
    T_S_P SalesPerson2(inFilename, outFilename);

    // Christofides Algorithm call
    SalesPerson2.Christofides();

    // 2-Opt call
    //SalesPerson2.twoOpt();

    // Print the results to an output file
    SalesPerson2.printToFileArr();

    // Stop the clock
    end = clock();

    // Calc runtime
    total = end - start;
    cout << "Runtime(can be unlim here): " << (((float)total)/CLOCKS_PER_SEC) << endl;

    // Optimal Solutions provided by instructor
    //tsp_example 2: 2579
    optimalAnswer = 2579;

    cout << "Optimal Length: " << optimalAnswer << endl;
    cout << "Tour Length: " << SalesPerson2.minPathLength << endl;
    //SalesPerson.printPath();

    // Correctness gets calculated with (our length)/(optimal length)
    // for full credit we have to be below 1.25 in UNLIMITED time.
    ratio = SalesPerson2.minPathLength / optimalAnswer;
    cout << "Ratio 1 < Rho < 1.25?: " << ratio << endl << endl;
    /////////////////////////////////TSP EX3////////////////////////////////////

    cout << "TSP Example 3:" << endl;

    // Set up the input stream file name
    inFilename = "tsp_example_3.txt";
    // Set up the output stream file name
    outFilename = "tsp_example_3.txt.tour";

    // Start the clock
    start = clock();

    // Traveling Sales Person Constructor call
    T_S_P SalesPerson3(inFilename, outFilename);

    // Christofides Algorithm call
    SalesPerson3.Christofides();

    // 2-Opt call
    //SalesPerson3.twoOpt();

    // Print the results to an output file
    SalesPerson3.printToFileArr();

    // Stop the clock
    end = clock();

    // Calc runtime
    total = end - start;
    cout << "Runtime(can be unlim here): " << (((float)total)/CLOCKS_PER_SEC) << endl;

    // Optimal Solutions provided by instructor
    //tsp_example 3: 1573084
    optimalAnswer = 1573084;

    cout << "Optimal Length: " << optimalAnswer << endl;
    cout << "Tour Length: " << SalesPerson3.minPathLength << endl;
    //SalesPerson.printPath();

    // Correctness gets calculated with (our length)/(optimal length)
    // for full credit we have to be below 1.25 in UNLIMITED time.
    ratio = SalesPerson3.minPathLength / optimalAnswer;
    cout << "Ratio 1 < Rho < 1.25?: " << ratio << endl << endl;
}
