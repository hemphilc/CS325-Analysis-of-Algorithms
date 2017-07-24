/*
 * Corey Hemphill - hemphilc@oregonstate.edu
 * Sarah Cawley - cawleys@oregonstate.edu
 * Konstantin Yakovenko - yakovenk@oregonstate.edu
 * CS325 - Project 4
 * December 2, 2016
 * tsp.cpp
*/

#include "tsp.h"

/////////////////////CLASS FUNCTIONS////////////////////

City::City() {/*Do Nothing*/}

City::City(int id, int xVal, int yVal) {
    identifier = id;
    x = xVal;
    y = yVal;
}

City::~City() {
    if(DEBUG) cout << "--Destroying city " << identifier << endl;
}

int City::getDistanceTo(const City &other) const {
    double d = sqrt(pow((float)(this->x - other.x), 2) + pow((float)(this->y - other.y), 2));
    // Determine if need to round distance up or down
    // If the distance d minus the floor of itself is 0.5 or greater,
    // then we should round up. Otherwise, we will round down.
    if((d - floor(d)) >= 0.5){
        return ceil(d); // Round up
    }
    else {
        return floor(d); // Round down
    }
}

T_S_P::T_S_P() {/*Do Nothing*/}

T_S_P::T_S_P(string inFile, string outFile) {
    // Store the file names
    inFilename = inFile;
    outFilename = outFile;
    // Count the number of City objects we plan on taking in for our graph G
    numCities = cityCount(inFilename);
    // Allocate space for our Cities
    Cities = new City[numCities];
    // Read in the cities from the input file and store to array Cities
    readCityFile(inFilename, Cities);
    // Initialize a matrix which will store the distances between each City
    Graph = new int*[numCities];
    for(int i = 0; i < numCities; i++) {
        Graph[i] = new int[numCities];
    }
    // Generate the graph using distances calculated from input
    generateGraph();
    if(DEBUG) printGraph();
    // Initialize the adjacency matrix
    AdjMatrix = new vector<int> [numCities];
    // Initialize min path length to zero
    minPathLength = 0;
    // Init HamPathArr a integer array for storing a path
    HamPathArr = new int[numCities];
}

T_S_P::~T_S_P() {
    if(DEBUG) cout << "--Destroying T_S_P " << endl;
    // Clean everything up
    for (int i = 0; i < numCities; i++) {
        delete [] Graph[i];
    }
    delete [] Graph;
    delete [] Cities;
    delete [] AdjMatrix;
    delete [] HamPathArr;
}

void T_S_P::generateGraph() {
    // Fill the Graph with distances from city to city
    if(DEBUG) cout << "NumCities : " << numCities << endl;
    for (int i = 0; i < numCities; i++)
        for (int j = 0; j < numCities; j++){
            Graph[i][j] = Cities[i].getDistanceTo(Cities[j]);
        }
}

void T_S_P::printGraph() {
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            cout << Graph[i][j] << " ";
        }
        cout << endl;
    }
}

void T_S_P::getMST() {
    if(DEBUG) cout << "Getting MST" << endl;
    // Keep track of the vertices used in the minimum spanning tree
    bool isInMST[numCities];
    // Store the distance values we use for our minimum spanning tree
    int keyVals[numCities];
    // Used to keep track of parent nodes
    int parentNodes[numCities];
    if(DEBUG) cout << "Initializing arrays" << endl;
    for(int i = 0; i < numCities; i++) {
        isInMST[i] = false; // Init all to false
        keyVals[i] = numeric_limits<int>::max(); // Init all to infinity
    }
    // First node is the root, thus its total distance is zero
    keyVals[0] = 0;
    // This is the root of the minimum spanning tree
    parentNodes[0] = -1;
    for(int i = 0; i < numCities; i++) {
        // Find our next minimum edge and vertex index
        int u = getMinKey(keyVals, isInMST);
        if(DEBUG) cout << i << ". Min Key = " << u << endl;
        // Keep track that we're adding this vertex to our minimum spanning tree
        isInMST[u] = true;
        if(DEBUG) cout << "index u = " << u << " is now in MST\n" << endl;
        for(int v = 0; v < numCities; v++) {
            // Check to see if there are vertices adjacent to u that are not
            // currently in the minimum spanning tree
            if(Graph[u][v] && isInMST[v] == false && Graph[u][v] < keyVals[v]) {
                // Mark v as u's parent
                parentNodes[v] = u;
                // Insert this distance into our key
                keyVals[v] = Graph[u][v];
            }
        }
    }
    // Print out the minimum spanning tree
    if(DEBUG) printMST(parentNodes);
    // Here is where we map vertices in our adjacency matrix if there is an edge
    // between two given vertices
    for(int v = 0; v < numCities; v++) {
        int p = parentNodes[v];
        if(DEBUG) cout << endl << v <<  ". v = " << v << endl;
        if(DEBUG) cout << "p = " << p << endl;
        // If our parent node is not the root of our mimimum spanning tree,
        // then we add these vertices to our adjacency matrix
        if(p != -1) {
            AdjMatrix[v].push_back(p);
            if(DEBUG) cout << "pushed p to v" << endl;
            AdjMatrix[p].push_back(v);
            if(DEBUG) cout << "pushed v to p" << endl;
        }
    }
}

int T_S_P::getMinKey(int keyVals[], bool isInMST[]) {
    int min = numeric_limits<int>::max();
    int minIdx;
    for(int i = 0; i < numCities; i++) {
        // If the current index is not being used in the MST,
        // and if the current key value is smaller than the
        // current minimum, we will set the minVal and store
        // the index of that vertex. What we've found is our
        // next shortest edge we can take and the index value
        // of the vertex that edge connects to
        if((isInMST[i] == false) && (keyVals[i] < min)) {
            if(DEBUG) cout << "\nNew min index = " << i << endl << endl;
            min = keyVals[i];
            minIdx = i;
        }
    }
    if(DEBUG) cout << "Returning ind = " << minIdx << endl;
    return minIdx;
}

void T_S_P::printMST(int parentNodes[]) {
    if(DEBUG) cout << "\nPrinting minimum spanning tree..." << endl;
    int total = 0;
    cout << "Edge   Weight\n" << endl;
    for(int i = 1; i < numCities; i++) {
        cout << i << ". " << parentNodes[i] << " - " << i << "   " << Graph[i][parentNodes[i]] << endl;
        total += Graph[i][parentNodes[i]];
    }
    cout << "Total distance: " << total << endl;
}

void T_S_P::getOddDegNodes() {
    if(DEBUG) cout << "\nGetting odd degree nodes..." << endl;
    for(int i = 0; i < numCities; i++)
        // Check each vertex to see if it has an odd number of adjacent
        // vertices, and if so, store the index of the vertex in a vector
        if((AdjMatrix[i].size() % 2) != 0) {
            if(DEBUG) cout << "Adding odd vertex " << i << endl;
            oddDegNodes.push_back(i);
        }
}

void T_S_P::getPerfectMatching() {
    if(DEBUG) cout << "\nGetting perfect matching..." << endl;
    int c; // Store the next closest vertex index
    int distance; // Store the distance to the next closest vertex
    vector<int>::iterator temp, start, end, it;
    // Get the subgraph O of odd degree vertices
    getOddDegNodes();
    // Match all vertices until oddDegNodes vector is emptied
    while(!oddDegNodes.empty()) {
        distance = numeric_limits<int>::max();
        it = oddDegNodes.begin() + 1;
        start = oddDegNodes.begin();
        end = oddDegNodes.end();
        // Check each vertex to see if it happens to be closer than the
        // current closest vertex and if so, keep track of it and update
        // c and length
        for(; it != end; ++it) {
            if(Graph[*start][*it] < distance) {
                distance = Graph[*start][*it];
                c = *it;
                temp = it;
            }
        }
        // We've found a match, relate these vertices in the adjacency matrix
        AdjMatrix[*start].push_back(c);
        AdjMatrix[c].push_back(*start);
        // Clean up so we dont use these vertices again
        oddDegNodes.erase(temp);
        oddDegNodes.erase(start);
    }
}

void T_S_P::eulerianPath(int idx) {
    if(DEBUG) cout << "\nGetting Eulerian path..." << endl;
    // Copy the original adjacency matrix
    vector<int> *temp = new vector<int> [numCities];
    int p = idx;
    for(int i = 0; i < numCities; i++) {
        temp[i].resize(AdjMatrix[i].size());
        temp[i] = AdjMatrix[i];
    }
    // Clear the EulerPath vector
    EulerPath.clear();
    // Initialize a stack for storing vertex indices
    stack<int> s;
    while(temp[p].size() > 0 || !s.empty()) {
        // Check to see if the current vertex has any adjacent vertices
        if(temp[p].size() == 0) {
            if(DEBUG) cout << "\n" << p << " does not have adjacent vertices" << endl;
            if(DEBUG) cout << "Pushing " << p << " into the Euler path" << endl;
            // If not, add the vertex to the Euler path
            EulerPath.push_back(p);
            // Set our new position to the index of the vertex at the top of the stack
            p = s.top();
            if(DEBUG) cout << "p = "<< p << endl;
            // Pop that index off of the stack
            if(DEBUG) cout << "Popping 1 off of s..." << endl;
            s.pop();
        }
        // The current vertex must have adjacent vertices
        else {
            if(DEBUG) cout << "\n" << p << " has adjacent vertices" << endl;
            // Add the current vertex index to the top of the stack
            if(DEBUG) cout << "Pushing 1 onto s..." << endl;
            s.push(p);
            // Get the adjacent vertices
            int adjV = temp[p].back();
            if(DEBUG) cout << "adjV = "<< adjV << endl;
            // Destroy the edge connecting these vertices
            temp[p].pop_back();
            for(unsigned int i = 0; i < temp[adjV].size(); i++) {
                // Check all vertices, find the position of the adjacent
                // vertex in the list, and delete it
                if(temp[adjV][i] == p) {
                    if(DEBUG) cout << "Grabbing adjacent vertex and destroying edge" << endl;
                    temp[adjV].erase(temp[adjV].begin() + i);
                    break; // Once we find the vertex, break the for loop
                }
            }
            // The new current vertex is the
            p = adjV;
            if(DEBUG) cout << "p = "<< p << endl;
        }
    }
    // Add the current vertex to the Euler path
    if(DEBUG) cout << "Pushing " << p << " into the Euler path" << endl;
    EulerPath.push_back(p);
    if(DEBUG) cout << "\nEuler path complete..." << endl;
}

void T_S_P::hamiltonianPath() {
    if(DEBUG) cout << "\nGetting Hamiltonian path..." << endl;
    bool HamiltonPath[numCities];
    int hamPathIt = 0;
    for(int i = 0; i < numCities; i++)
        HamiltonPath[i] = false; // Init all to false
    // Init mimPathLength to zero
    minPathLength = 0;
    // Set the root value
    int root = EulerPath.front();
    // Init vectors for comparing EulerPath distances
    vector<int>::iterator it_curr = EulerPath.begin();
    vector<int>::iterator it_next = EulerPath.begin() + 1;
    HamPathArr[hamPathIt] = *it_curr;
    // Set the root to true
    HamiltonPath[root] = true;
    // Visit every single vertex in the Euler path
    if(DEBUG) cout << "Checking each vertex in the Euler path..." << endl;
    while(it_next != EulerPath.end()) {
        // If we haven't visited the next city, visit it
        if(HamiltonPath[*it_next] == false) {
            if(DEBUG) cout << "\nVisiting next " << *it_next << endl;
            // Add the distance to the next vertex to minPathLength
            minPathLength += Graph[*it_curr][*it_next];
            if(DEBUG) cout << "Min Path Length = " << minPathLength << endl;
            // Set the current to be the next
            it_curr = it_next;
            // Mark this vertex as visited
            HamiltonPath[*it_curr] = true;
            if(DEBUG) cout << "Marked " << *it_curr << " as visited" << endl;
            // Move next forward to the next
            it_next = it_curr + 1;
            hamPathIt++;
            HamPathArr[hamPathIt] = *it_curr;
        }
        // Otherwise, get rid of the "next" vertex
        else {
            if(DEBUG) cout << "\nAlready visited " << *it_next << "... Removing..." << endl;
            it_next = EulerPath.erase(it_next);
        }
    }
    // Add the total distance travelled to the root distance
    minPathLength += Graph[*it_curr][*it_next];
    if(DEBUG) cout << "Total distance: " << minPathLength << endl;
    if(DEBUG) cout << "\nHamilton path complete..." << endl;
    if(DEBUG) { cout << "hamPathArr:" << endl;
        for(int i=0; i < numCities; i++){
            cout << i << ". " << HamPathArr[i] << endl;
        }
    }
}

void T_S_P::Christofides() {
    // Use Prim's algorithm to get a minimum spanning tree
    getMST();
    // Get a perfect matching M in the induced subgraph given by O
    // Calls getOddDegNodes within to get subgraph O of odd degree vertices
    getPerfectMatching();
    // Form a Eulerian circuit
    eulerianPath(0);
    // Make the Eulerian circuit into a Hamiltonian path
    hamiltonianPath();
}

void T_S_P::printPath() {
    int i = 1;
    for(vector<int>::iterator it = EulerPath.begin(); it != EulerPath.end(); ++it) {
        cout << i << ". " << EulerPath[*it] << endl;
        i++;
    }
    cout << endl;
}

void T_S_P::twoOpt() {
    if(DEBUG) cout << "Entering 2-Opt..." << endl;
    //if(DEBUG) cout << "MinPathLenght 2OPT: " << minPathLength << endl;
    int prevMinLength = minPathLength;
    int conditionVal = 5;
    int count = 0;
    int u1, u2, v1, v2;
    // Check each edge in the current known shortest path
    for(int i = 0; i < numCities; i++) {
        if(DEBUG) cout << "i = " << i << endl;
        // Starting edge
        v1 = i;
        // If this vertex is the last, jump back to the start
        u1 = (i + 1) % numCities;
        // Check nonadjacent vertices by jumping over current adjacent edges
        for(int j = i + 2; ((j + 1) % numCities) != i; j++) {
            if(DEBUG) cout << "j = " << j << endl;
            v2 = j % numCities;
            u2 = (j + 1) % numCities;
            // Check to see if the new path is shorter than the current
            if(pathIsShorter(HamPathArr[v1], HamPathArr[u1], HamPathArr[v2], HamPathArr[u2])) {
                // If the new path is shorter, swap it in
                swapNodes(i + 1, j);
                // Don't stop until we've swapped at least 5 vertices
                if(((minPathLength - prevMinLength) < 5) && (count == conditionVal)) {
                    break;
                }
                // If we've swapped less than 5 vertices, reset i and start again
                if(minPathLength - prevMinLength > conditionVal) {
                    i = 0;
                }
                prevMinLength = minPathLength;
                count++;
            }
        }
    }
    if(DEBUG) cout << "Exiting 2-Opt..." << endl;
}

bool T_S_P::pathIsShorter(int v1, int v2, int v3, int v4) {
    if(DEBUG) cout << "Entering pathIsShorter..." << endl;
    // If the new path distance is shorter than the current, then we can use it
    if((Graph[v1][v3] + Graph[v2][v4]) < (Graph[v1][v2] + Graph[v3][v4])) {
        // Adjust the minimum path length and then return true because the path is shorter
        minPathLength -= (Graph[v1][v2] + Graph[v3][v4] - Graph[v1][v3] - Graph[v2][v4]);
        if(DEBUG) cout << "Exiting pathIsShorter..." << endl;
        //if(DEBUG) cout << "MinPathLenght pre: " << minPathLength << endl;
        minPathLength = minPathLength;
        if(DEBUG) cout << "MinPathLenght post: " << minPathLength << endl;
        return true;
    }
    // The new path is not shorter, return false
    if(DEBUG) cout << "Exiting pathIsShorter..." << endl;
    return false;
}

void T_S_P::swapNodes(int startV, int endV) {
    if(DEBUG) cout << "Entering swapNodes..." << endl;
    // Start on the ends and work inward
    while((endV - startV) > 0) {
        int tmp = EulerPath[startV % numCities];
        // Swap the nodes to get a different edge
        EulerPath[startV % numCities] = EulerPath[endV % numCities];
        EulerPath[endV % numCities] = tmp;
        startV++;
        endV--;
    }
    if(DEBUG) cout << "Exiting swapNodes..." << endl;
}

void T_S_P::printToFile() {
    ofstream out;
    out.open(outFilename.c_str());
    if(out.fail()) {
        cout << "Could not open " << outFilename << endl;
        exit(EXIT_FAILURE);
    }
    out << minPathLength << endl;
    for(vector<int>::iterator it = EulerPath.begin(); it != EulerPath.end(); ++it)
        out << EulerPath[*it] << endl;
    out << endl;
    out.close();
}

void T_S_P::printToFileArr() {
    ofstream out;
    out.open(outFilename.c_str());
    if(out.fail()) {
        cout << "Could not open " << outFilename << endl;
        exit(EXIT_FAILURE);
    }
    out << minPathLength << endl;

    for(int i=0; i < numCities; i++){
        out << HamPathArr[i] << endl;
        }
    out << endl;
    out.close();
}

void T_S_P::printAdjMatrix() {
    for (int i = 0; i < numCities; i++) {
        cout << i << ": "; //print which vertex's edge list follows
        for (int j = 0; j < (int)AdjMatrix[i].size(); j++) {
            cout << AdjMatrix[i][j] << " "; //print each item in edge list
        }
        cout << endl;
    }
}

////////////////////////////////////////////////////////

////////////////////NORMAL FUNCTIONS////////////////////

int cityCount(const string inFile) {
    ifstream in;
    int count = 0;
    string line;
    in.open(inFile.c_str());
    if(in.fail()) {
        cout << "Could not open " << inFile << endl;
        exit(EXIT_FAILURE);
    }
    // Count each line in the input file
    while(getline(in, line))
        count++;
    in.close();
    return count;
}

void readCityFile(const string fileName, City *Cities) {
    ifstream in;
    in.open(fileName.c_str());
    if(in.fail()) {
        cout << "Could not open " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    // Read in lines and parse them
    while(!in.eof()) {
        // City is city number, X and Y are coordinates on the grid
        int city, cityX, cityY;
        while(in >> city >> cityX >> cityY) {
            // WE CONSTRUCT CITY OBJECTS HERE
            //if(DEBUG) cout << "city: " << city << " X: " << cityX << " Y: " << cityY << endl;
            // Construct a city object
            City currCity(city, cityX, cityY);
            //if(DEBUG) cout << currCity.identifier << " " << currCity.x << " " << currCity.y << endl;
            // Place the city into an array G
            Cities[currCity.identifier] = currCity;
            //if(DEBUG) cout << Cities[currCity.identifier].identifier << " " << Cities[currCity.identifier].x << " " << Cities[currCity.identifier].y << endl;
        }
    }
    in.close();
}

template <typename T>
void printArray(T arr[], int length) {
    if(length <= 0) return;
    else {
        for(int i = 0; i < length; i++)
            cout << arr[i] << " ";
    }
}

////////////////////////////////////////////////////////
