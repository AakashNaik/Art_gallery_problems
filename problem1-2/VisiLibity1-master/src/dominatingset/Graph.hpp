#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include<map>
#include<vector>
#include<unordered_set>
#include<iostream>
using namespace std;

class MyHashFunction {
public:
    size_t operator()(const Edge *t) const 
    {
        //cout<<"d";
        return hash<string>()(to_string((*t).getNodev1()->getName())+to_string((*t).getNodev1()->getName()));
    }
};

class Graph
{
    private:
    map<int,Node*>nodes;
    unordered_set<Edge*,MyHashFunction>edges;
    
    public:
    Graph();
    void addNode(int key);
    void removeNode(int nodeToRemove);
	void removeNode(Node *nodeToRemove);
	void removeNodeEdges(int nodeToRemove);
	void removeNodesEdges(Node *nodeToRemove);
	int addEdge(int v1, int v2);
    void addEdge(Edge *newEdge);
    vector<Node* > getNodes();
    int getNumNodes();
    vector<Edge*> getEdges();
    int getNumEdges();
    string exportGraphString();
    void resetGraph();
};

#endif