#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cfloat>
#include <iostream>

using namespace std;

struct Node {
    int number = -1;
    double edgeWeight= -0.0;
};

class Vertex {
public:
    int number;
    list<Node> Edge;
    bool visited = false;
    double dist = DBL_MAX;
};

class Graph {
public:
    int NumberOfVertices;
    vector<Vertex> graphing;

    Graph() : NumberOfVertices(0) {}

    Graph(int numberOfVertices) {
        NumberOfVertices = numberOfVertices;
        graphing.resize(NumberOfVertices);
        for(int i=0; i< numberOfVertices; i++)
        {
            graphing[i].number = i+1;
        }
    }

    void addEdge(int from, int to, double weight) {
       
        Node newNode {to, weight};
        graphing[from-1].Edge.push_back(newNode);
        
       
    }

    static Graph buildGraph(string fileName) {
        ifstream readFile(fileName);
        if (!readFile.good()) {
            cerr << "Error reading file" << endl;
            exit(1);
        }

        string line;
        getline(readFile, line);
        int num = stoi(line);

        Graph newGraph(num);

        string str;
        while (getline(readFile, line)) {
            stringstream ss(line);
            ss >> str;
            int vertex = stoi(str);
        
            while (ss >> str) {
                int connected = stoi(str);
       
                ss >> str;
                double weight = stod(str);
        
                newGraph.addEdge(vertex, connected, weight);
            }
        }

        readFile.close();
        newGraph.printGraph();
        return newGraph;
    }

    void showOutPut(string queryFile) {
        ifstream readFile(queryFile);
        if (!readFile.good()) {
            cerr << "Error reading file" << endl;
            exit(1);
        }

        string line;
        while (getline(readFile, line)) {
            stringstream ss(line);
            ss >> line;
            int vertex = stoi(line);

            ss >> line;
            int connected = stoi(line);

            cout << vertex << " " << connected << ": ";
            cout << out(vertex, connected) << endl;
        }

        readFile.close();
    }

    string out(int vertex, int connected) {
        for (auto& node : graphing[vertex-1].Edge) {
            if (node.number == connected) {
                string weightStr = to_string(node.edgeWeight);
                size_t lastNonZero = weightStr.find_last_not_of('0');
                return "connected " + weightStr.substr(0, lastNonZero + 1);
            }
        }
        return "not_connected";
    }
};

#endif
