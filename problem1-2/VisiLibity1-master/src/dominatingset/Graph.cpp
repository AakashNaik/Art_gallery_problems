#include<string>
#include<set>
#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include<map>
#include <iostream>
#include<unordered_set>
#include<vector>
using namespace std; 

Graph::Graph()
{

}

void Graph::addNode(int key)
{
    if ( nodes.find(key) == nodes.end())
    {
        Node *newNode=new Node();
        newNode->setName(key);
        newNode->setAssignment(-1);
        nodes[key]= newNode;
    }
    return;
}

void Graph::removeNode(int nodeToRemove)
{
    Node  *node = nodes[nodeToRemove];
    removeNodesEdges(node);
    //nodes.put(nodeToRemove, NULL);
}



void Graph::removeNode(Node *nodeToRemove)
{
    removeNodesEdges(nodeToRemove);
}

void Graph::removeNodeEdges(int nodeToRemove)
{
    Node  *node = nodes[nodeToRemove];
    removeNodesEdges(node);
}



void Graph::removeNodesEdges(Node  *nodeToRemove)
{
    for (Node  *node : (nodeToRemove)->getNeighbors())
    {
        Edge* e1= new Edge(nodeToRemove,node);
        Edge* e2= new Edge(node,nodeToRemove);
        if(edges.find(e1)!=edges.end())
         edges.erase(e1);
        if(edges.find(e2)!=edges.end())
         edges.erase(e2);
        
    }   
}


int Graph::addEdge(int v1, int v2)
{	
    if (nodes.find(v1)==nodes.end())	
        return 0;    
    if (nodes.find(v2)==nodes.end())
        return 0;
    Node  *node1 = nodes[v1];
    Node  *node2 = nodes[v2];
    Edge *newEdge=new Edge(nodes[v1],nodes[v2]);
    //cout<<"c";
    //cout<<newEdge->toString()<<'\n';
    if ( (nodes[v1]->getNeighbors()).find(nodes[v2])!=(nodes[v1]->getNeighbors()).end() )
    {
        //cout<<"c";
       return 1; 
    }
    //cout<<"d";
    if(edges.find(newEdge)==edges.end())
        edges.insert(newEdge);
    nodes[v1]->addNode(nodes[v2]);
    nodes[v2]->addNode(nodes[v1]);
    //cout<<"e";
    return 1;   
}


    void Graph::addEdge(Edge *newEdge)
{
    //if(edges.find())
    if(edges.find(newEdge)==edges.end())
    edges.insert(newEdge);
    Node  *v1 = newEdge->getNodev1();
    Node  *v2 = newEdge->getNodev2();
    v1->addNode(v2);
    v2->addNode(v1);
}


vector<Node*> Graph::getNodes()
{	
    vector<Node*>t;
    for(auto &i:nodes)
    {
        t.push_back(i.second);
    }
    return t;        
}

int Graph::getNumNodes()
{   return nodes.size(); }

vector<Edge*> Graph::getEdges()
{	
    vector<Edge*>d;
    for(auto &i:edges)
        d.push_back(i);
    return d; 
}


int Graph::getNumEdges()
{	return edges.size(); }

/*
string Graph::exportGraphString()
{
    string s = "";
    for (int key : nodes.keySet() )
    {
        s += "\n" + key + "--> [";
        Node  node = nodes[key];
        
        for (Node  node : node->getNeighbors())
        {
            s += " " + to_string( node);
        }
        s += " ]";
    }
    return s;
}*/


/**
 * Resets all Nodes and Edges in graph to uncovered.
 * Runs in O(|V| + |E|).
 */
/*
void Graph::resetGraph()
{
    for (auto node= nodes.begin();node!=nodes.end();node++ )
        (node->second).setAssignment(-1);

    for (Edge edge : edges)
        edge.setIsCovered(-1);
    
    return;
}
*/

