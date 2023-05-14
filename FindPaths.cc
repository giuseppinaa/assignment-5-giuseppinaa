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

//function to create a graph from a text file
template <typename point>
void MakeGraph(string const &readfile, Graph<point> &graphpoint) {
    string linetxt; //used to read text lines of graph txt
    point CurrentVertex, NextVertex; //given two point objects to use for vertices
    double WeightVertex; //aariable for weight of node

    ifstream file(readfile); //open the file
    if (!file) {
        cerr << "Error opening file!\n";
        abort();
    }

    getline(file, linetxt); //getting the first line 
    while (getline(file, linetxt)) {
        auto checkline = linetxt.empty();
        if (!checkline) { // loops until empty lines
            stringstream ss(linetxt);
            ss >> CurrentVertex; //read current vertex

            graphpoint.vertex(CurrentVertex); //add current vertex to the graph

            //read the next vertex and its weight and connect to current vertex
            while (ss >> NextVertex && ss >> WeightVertex) {
                graphpoint.connect(CurrentVertex, NextVertex, WeightVertex);
            }
        }
    }
    file.close(); //close file
}

//driver function for finding the shortest path in graph
int pathfindDriver(int argc, char **argv) {
    int source = stoi(argv[2]); //starting vertex as command line argument
    
    Graph<int> checkingGraph;
    MakeGraph<int>(argv[1], checkingGraph); //create graph from the specified file
    checkingGraph.DijkstraAlgo(source); //apply Dijkstra's algo to find the shortest path

    int check = 1;
    while (checkingGraph.Contains(check)) {
        checkingGraph.path(check); //pint shortest path for each vertex in the graph
        check++;
    }
    
    return 0;
}


int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << " <STARTING_VERTEX>" << endl;
        return 0;
    }

    pathfindDriver(argc, argv); //call driver function to find the shortest path

    return 0;
}
