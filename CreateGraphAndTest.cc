//Name: Giuseppina Pullara
//Assignment-5
//Professor: Ioannis Stamos#include <iostream>

#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cfloat>

#include "graph.h"

using namespace std;
// Function to read the graph from text file
template <typename point>
void ReadGraph(string const &readfile, Graph<point> &graphpoint)
{ // read lines of the graph text file
  string linetxt;
  point CurrentVertex, NextVertex; // vertices
  double WeightVertex;             // weights of the edges
  // open file
  ifstream file(readfile);
  if (!file)
  {
    cerr << "error!\n"; // show error if you cant read file
    abort();
  }

  string line;
  while (getline(file, line))
  {
    if (line.empty())
    {
      continue; // skip empty lines
    }
    stringstream ss(line);
    ss >> CurrentVertex;              // read current vertex
    graphpoint.vertex(CurrentVertex); // add current vertex to the graph
    while (ss >> NextVertex && ss >> WeightVertex)
    {
      graphpoint.connect(CurrentVertex, NextVertex, WeightVertex); // connect vertices to weight
    }
  }
  file.close(); // close file
}

// function to check weight of edges between vertices
template <typename point>
void CheckGraph(string const &read_file, Graph<point> &graphP)
{
  string linetxt;
  point vertexA, vB;        // vertices
  ifstream file(read_file); // open graph file
  if (!file)
  {
    cerr << "error!\n"; // error if unable to read
    abort();
  }

  double distance;
  double max = DBL_MAX;
  while (getline(file, linetxt))
  { // read file line by line using while loop
    if (!linetxt.empty())
    { // if it isn't empty
      stringstream ss(linetxt);
      ss >> vertexA >> vB;
      distance = graphP.CheckWeight(vertexA, vB); // check weight of edge thru connected points
      if (distance == max)
      {                                                            // if reached DBLMAX then its not connected
        cout << vertexA << " " << vB << ": not_connected" << endl; // print if not connected
      }
      else
      {
        cout << vertexA << " " << vB << ": connected " << distance << endl; // print connected with its weight
      }
    }
  }
  file.close();
}

int graphTestDriver(int argc, char **argv)
{

  Graph<int> graphpoint;                // graph object to store the graph
  ReadGraph<int>(argv[1], graphpoint);  // read graph from the specified file
  CheckGraph<int>(argv[2], graphpoint); // check weight of edges between vertices

  // Begin your code here. Feel free to add any helper functions or classes you need,
  // as long as we only have to call this function to run the specified assignment.

  return 0;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_File>"
         << "<ADJACENCY_QUERYFILE>" << endl;
    return 0;
  }
  // call driver function for graph testing
  graphTestDriver(argc, argv);

  return 0;
}
