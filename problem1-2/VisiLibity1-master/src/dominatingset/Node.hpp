

#ifndef NODE_H
#define NODE_H

//#include<bits/stdc++.h>
#include<unordered_set>
//#include "GraphLoader.hpp"
//#include "Edge.hpp"
//#include "Graph.hpp"
#include"Node.hpp"
#include<string>
#include<vector>
#include<map>
/*#include "DominatingSet.hpp"*/
using namespace std;
class Node
{
  private:
	  int name;
    unordered_set<Node*> nodesEdges;
	  int assignment;
  public:
    Node();
    Node(int name);
    int getName() const;
    void setName(int key);
    unordered_set<Node*> getNeighbors() ;
    int numNeighbors();
    int isAssigned();
    void setAssignment(int newAssignment) ;
    int getAssignment();
    void addNode(Node *newEdge) ;
    string toString() ;
    
};


#endif //VISILIBITY_H
