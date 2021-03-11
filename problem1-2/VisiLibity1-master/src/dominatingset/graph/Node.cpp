

#include<bits/stdc++.h>
using namespace std;

class Node:
{
    private:
	int name;
    set<Edge> nodesEdges;
	int assignment;

    public:
	Node(int name)
	{
		this.name = name;
		this.assignment = -1;
	}

	int getName() { return this.name; }

	set<Node> getNeighbors() 
	{
		set<Node> neighbors;
		for (Edge edge : nodesEdges) {
			neighbors.insert(edge.getOtherNode(this));
		}
		return neighbors;
	}


	int numNeighbors() { return nodesEdges.size(); }


	set<Edge> getEdges() { return this.nodesEdges; }
	

	int isAssigned() { return this.assignment; }


	void setAssignment(int newAssignment) 
	{ 
		if (newAssignment == -1 || newAssignment == 0 || newAssignment == 1)
			this.assignment = newAssignment;
		
			
	}


	void addEdge(Edge newEdge) 
	{ 
		if (nodesEdges.find(newEdge)==nodesEdges.end() )
			nodesEdges.add(newEdge); 
	}


	string toString() { return str(this.name); }
	
}