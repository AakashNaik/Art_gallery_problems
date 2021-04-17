//#include <bits/stdc++.h> 
#include<unordered_set>
//#include "GraphLoader.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include<string>
#include<iostream>
#include<vector>
#include<map>
/* #include "Graph.hpp"
#include "DominatingSet.hpp" */
using namespace std; 




	
Edge::Edge (Node  *node1, Node  *node2)
{	
	Node  *val1;
	Node  *val2;

	if      ( node1->getName() < node2->getName() )  { val1 = node1; val2 = node2; }
	else if ( node1->getName() > node2->getName() )  { val2 = node1; val1 = node2; }
	//cout<<'e'<<'\n';
	v1 = val1;
	v2 = val2;
	iscovered = -1;
}



string Edge::toString() 
{ 	
	return to_string(v1->getName()) + "---" + to_string(v2->getName());
}



Node*  Edge::getOtherNode(Node  *node) 
{
	if (node->getName()==v1->getName()) 
		return v2;
	else if (node->getName()==v2->getName())
		return v1;
	return v1;

}


Node*  Edge::getNodev1() const{ return v1; }


Node*  Edge::getNodev2() const{ return v2; }


bool Edge::isEqualTo(Edge *edge)
{
	if ( v1->getName()==edge->getNodev1()->getName()&& v1->getName()==edge->getNodev2()->getName() )
		return true;
	return false;
}


int Edge::isCovered() { return iscovered; }


void Edge::setIsCovered(int newState) 
{ 
	if (newState == -1 || newState == 0 || newState == 1)
		iscovered = newState;
}

