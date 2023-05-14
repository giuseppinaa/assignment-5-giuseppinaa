//Name:Giuseppina Pullara
//Assignment-5
//Professor: Ioannis Stamos

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <cstdlib>
#include "graph.h"

using namespace std;
template <typename point>
void MakeGraph(string const & readfile, Graph<point> & graphpoint){
    string linetxt; //used to read text lines of graph txt
    point CurrentVertex,NextVertex;//given two point objects to use for vertex
    double WeightVertex;//variable for weight of the node

    ifstream file(readfile);//checkfile error
    if(!file){
       cerr << "error!\n";
        abort();
    }

    getline(file, linetxt); //getline once to skip start of text
    while(getline(file, linetxt)){
        auto checkline = linetxt.empty();
        if(!checkline){//loop until empty
            stringstream ss(linetxt);
            ss >> CurrentVertex; //inp for current vertex
            graphpoint.vertex(CurrentVertex);
            while(ss >> NextVertex && ss >> WeightVertex){
                graphpoint.connect(CurrentVertex, NextVertex, WeightVertex); //connect ndoe to next vertex and its given weight
            }
        } 
    }
    file.close();
}


int pathfindDriver(int argc, char **argv) {
    int source = stoi(argv[2]);
    
    Graph<int> checkingGraph;
    MakeGraph<int>(argv[1], checkingGraph);
    checkingGraph.DijkstraAlgo(source);
    
    int check = 1;
    while (checkingGraph.Contains(check)) {
        checkingGraph.path(check);
        check++;
    }
    
    return 0;
}


int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
