#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string>
#include <cfloat> 

#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv) {
    
    // Begin your code here. Feel free to add any helper functions or classes you need,
    // as long as we only have to call this function to run the specified assignment.
      Graph MyGraph = Graph :: buildGraph(argv[1]);
       
      MyGraph.showOutPut(argv[2]);
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
