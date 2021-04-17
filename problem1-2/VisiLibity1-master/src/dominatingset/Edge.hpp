#ifndef EDGE_H
#define EDGE_H



//#include <bits/stdc++.h> 
//#include "GraphLoader.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include<string>
#include<vector>
#include<map>
/*#include "Graph.hpp"
#include "DominatingSet.hpp"*/
using namespace std; 



class Edge
{
	private:
    Node *v1;
	Node  *v2;
	int iscovered; 

	public:
    Edge (Node  *node1, Node  *node2);
	bool operator==(const Edge *t) const 
	{
		return ((this->getNodev1())->getName() == (t->getNodev1())->getName())&&((this->getNodev2())->getName() == (t->getNodev2())->getName());
	}

	string toString(); 
	Node*  getOtherNode(Node *node) ;
	Node*  getNodev1() const;
    Node*  getNodev2() const;
    bool isEqualTo(Edge *edge);
	int isCovered();
    void setIsCovered(int newState);
};
#endif