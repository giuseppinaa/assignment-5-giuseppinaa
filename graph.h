// Name:Giuseppina Pullara
// Assignment-5
// Professor: Ioannis Stamos#include <iostream>
#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
// This file is for your graph implementation.
// Add everything you need in between the "ifndef and "endif" statements.
// Do not put anything outside those statements	
#include <utility>		
#include <cfloat>	
#include <list>	
#include <queue>
#include <unordered_map> 

using namespace std; 
template<typename point>
 class Graph;
// class representing a vertex node in the graph
template <typename point>
class PointVertexNode{
public:
	friend class Graph<point>;
	// constructor with a storeKey parameter
	PointVertexNode()= default;
PointVertexNode(point storeKey) : storeIt(storeKey), 
        areaDist(DBL_MAX), previousPath(nullptr) {
 checkPoint = false;
 startingPointVertex = false;
        }

   

	double AreaDistance() const {
		double dummy = areaDist;
        return dummy; // return distance from node to node
	}
private:
	list<pair< PointVertexNode<point>*, double>> AdjacentNodes; //set variables and objects to private
	point storeIt;//the point stored in the vertex node
	double areaDist;//area distance of the graph
	bool checkPoint, startingPointVertex;
	PointVertexNode<point> * previousPath; //pointer to previous path
};

template <typename point>
class VerticesCheck{
 public:
 	bool operator()(const PointVertexNode<point> *lefths, const PointVertexNode<point> * righths) const{
 		
		auto checkleft = lefths->AreaDistance() > righths->AreaDistance();

 		return checkleft; 
 	}
};

template <typename point>
class Graph{
public:

	unordered_map<point, PointVertexNode<point>> NodeMapping;	//unorder_map

	void ResetNodeOfVertex(PointVertexNode<point> vert){//reseting properties of a vertex node
		vert.previousPath = NULL; //reset previous path of the vertex
		vert.checkPoint = false; 
		vert.areaDist = DBL_MAX;  //the distance of the graph
		vert.startingPointVertex = false;//reset starting point false
		
		
	}

	void vertex(point vertexA){
		auto find=NodeMapping.find(vertexA);
		auto end=NodeMapping.end();
		if(find ==end){ //check from point a to the end for vertex node in the graph map
			NodeMapping[vertexA] = PointVertexNode<point>(vertexA); //assign it to
		}
	}//connect two vertices in the graph with an edge and weight
	void connect(point vA, point vB, double VertexWeight){
    auto nds=NodeMapping.find(vA);
    auto nB=NodeMapping.find(vB);
    auto end=NodeMapping.end();

    if(nds == end){ //find for vertex a until end of graph map
        NodeMapping[vA] = PointVertexNode<point>(vA);//connects them
    }
    if(nB == end){//find for vertex b until end of graph map //connects them
        NodeMapping[vB] = PointVertexNode<point>(vB);
    }
    PointVertexNode<point>* nodeA = &NodeMapping[vA]; //getting pointer to node A
    PointVertexNode<point>* nodeB = &NodeMapping[vB]; //getting pointer to node B
    
    //check if the connection already exists and update the weight if so
    for (auto it = nodeA->AdjacentNodes.begin(); it != nodeA->AdjacentNodes.end(); ++it) {
        if (it->first == nodeB) {
            // Update the weight of the existing connection
            it->second = VertexWeight;
            return;
        }
    }

     //if no connection exists, create a new one
    pair<PointVertexNode<point>*, double> CreatingNewConnection = make_pair(nodeB, VertexWeight);
    nodeA->AdjacentNodes.push_back(CreatingNewConnection);
}

	//checking the weight (distance) between two nodes in the graph
	double CheckWeight(point nodeA, point nodeB) {
    auto search = NodeMapping.find(nodeA);
    auto end_at = NodeMapping.end();
    if (search != end_at) {
        for (const auto& [neighbour, weight] : search->second.AdjacentNodes) {
            if (neighbour->storeIt == nodeB) {
                return weight;
            }
        }
    }
    return DBL_MAX;
}

	//checking if the graph contains a vertex
	bool Contains(point VertexPointNode){
		auto contained=NodeMapping.find(VertexPointNode); //check if the vertex nds are contained from start of map to end in the graph
		auto checkuntilend=NodeMapping.end();
		return contained != checkuntilend;
	}
	//implement Dijkstra's algorithm to find the shortest path in the graph
	void DijkstraAlgo(point start) {
    priority_queue<PointVertexNode<point> *, vector<PointVertexNode<point> *>, VerticesCheck<point>> areaDistqueue; // important to use to go thru priority queue
    
    //reset all PointVertexNodes in the map
    for (auto& kvp : NodeMapping) {
        ResetNodeOfVertex(kvp.second);
    }
    
    PointVertexNode<point>* vert = &NodeMapping[start];
    vert->areaDist = 0.0;
    vert->startingPointVertex = true;
    areaDistqueue.push(vert);
    
    while (!areaDistqueue.empty()) {
        vert = areaDistqueue.top();
        areaDistqueue.pop();
        
        if (vert->checkPoint) {
            continue;
        }
        
        vert->checkPoint = true;
        
        for (auto& neighbor : vert->AdjacentNodes) {
            double dist = vert->areaDist + neighbor.second;
            if (dist < neighbor.first->areaDist) {
                neighbor.first->areaDist = dist;
                neighbor.first->previousPath = vert;
                areaDistqueue.push(neighbor.first);
            }
        }
    }
}

	
	//print the shortest path from a given node
	void path(const point & node_vert) {
		double max=DBL_MAX; //max val
		cout << node_vert << ": ";
		PointVertexNode<point> * fillin = & NodeMapping[node_vert];
		if(fillin->startingPointVertex){
			cout << fillin->storeIt << " cost: 0.0" << endl;//default 0.0 starting point
			return;
		}
		
		if(fillin->areaDist==max){
			cout << "not_possible" << endl; //print not possible if cant be connected
		}else{
			shortest_path(fillin);
			cout << "cost: " << fillin->areaDist  << endl;} //print the cost of the edge from vertex to vertex
	}

	void shortest_path(PointVertexNode<point>*& node_vert) {
    if (node_vert->previousPath == nullptr) { // if null print the current node
        cout << node_vert->storeIt << " ";
    }
    else {
        shortest_path(node_vert->previousPath); // call shortest_path recursively for previous path
        cout << node_vert->storeIt << " ";
    }
}
};

#endif
