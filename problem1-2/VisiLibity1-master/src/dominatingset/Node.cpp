#include<unordered_set>
#include "Node.hpp"
#include<string>
#include<iostream>
#include<vector>
#include<map>
using namespace std;


Node::Node( )
{
	name =0;
	assignment = -1;
}   

Node::Node(int name)
{
	name = name;
	assignment = -1;
}

void Node::setName(int key)
{
	name=key;
}

int Node::getName() const { return name;}

int Node::getAssignment()
{
	return assignment;
}

unordered_set<Node*> Node::getNeighbors() 
{
	
	return nodesEdges;
}


int Node::numNeighbors() { return nodesEdges.size(); }

int Node::isAssigned() { return assignment; }

void Node::setAssignment(int newAssignment) 
{ 
	if (newAssignment == -1 || newAssignment == 0 || newAssignment == 1)
		assignment = newAssignment;		
}


void Node::addNode(Node *node) 
{ 
	if(nodesEdges.find(node)==nodesEdges.end())
	nodesEdges.insert(node);
}


string Node::toString() 
{ 
	string f="a" ;
	return f; 
}
	
