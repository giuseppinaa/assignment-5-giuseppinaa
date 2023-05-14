// Name: Giuseppina Pullara
// Assignment-5
// Professor: Ioannis Stamos

#include <iostream>
#include <sstream> 
#include <vector>
#include <string>
#include <fstream>
#include "graph.h"
#include <cfloat> 

using namespace std;
//function to create a graph from a text file
template <typename point>
void ReadGraph(string const & readfile, Graph<point> & graphpoint){
    string linetxt;//used to read text lines of graph txt
    point CurrentVertex,NextVertex;//given two point objects to use for vertices
    double WeightVertex; //aariable for weight of node

    ifstream file(readfile); //open file
    if(!file){
       cerr << "error!\n"; //show error if cant read
        abort();
    }
    
    string line;
    while(getline(file, line)) {//getting the first line 
        if(line.empty()) {
            continue;
        }
        stringstream ss(line);
        ss >> CurrentVertex;//read current vertex
        graphpoint.vertex(CurrentVertex);//add current vertex to the graph
        while(ss >> NextVertex && ss >> WeightVertex){//read the next vertex and its weight and connect to current vertex
            graphpoint.connect(CurrentVertex, NextVertex, WeightVertex);//connect vertex
        }
    }
    file.close();//close file
 }


template <typename point>
void CheckGraph(string const& read_file, Graph<point>& graphP) {
    string linetxt;
    point vertexA, vB; //both points used for vertex
    ifstream file(read_file); //read graph file
    if (!file) {
        cerr << "error!\n"; //check for error
        abort();
    }

    double distance;
    double max = DBL_MAX; //check if max
    while (getline(file, linetxt)) { // read file line by line using while loop
        if (!linetxt.empty()) { //if it isn't empty
            stringstream ss(linetxt);
            ss >> vertexA >> vB; //ss to insert point verta,vertb to check for integer
            distance = graphP.CheckWeight(vertexA, vB); //check the weight of the edge through the connected points
            if (distance == max) { // if reached DBLMAX then not connected
                cout << vertexA << " " << vB << ": not_connected" << endl; //print if not connected
            }
            else {
                cout << vertexA << " " << vB << ": connected " << distance << endl; //print connected along with its weight
            }
        }
    }
    file.close();
}
 

int graphTestDriver(int argc, char **argv) {
  
    
    Graph<int> graphpoint;
    ReadGraph<int>(argv[1], graphpoint);//read graph
    CheckGraph<int>(argv[2], graphpoint);//check graph
    
    // Begin your code here. Feel free to add any helper functions or classes you need,
    // as long as we only have to call this function to run the specified assignment.

   return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
