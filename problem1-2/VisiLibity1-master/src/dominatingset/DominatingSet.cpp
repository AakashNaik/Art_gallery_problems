#include<set>
#include<string>
#include<vector>
#include<math.h>
#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include "DominatingSet.hpp"
using namespace std;
	
vector<Node*> DominatingSet::findMinimumDominatingSet(Graph* graph)
{   
    vector<Node*> mds = recursiveSearchTree(graph);
    return mds;
}

vector<Node*> DominatingSet::recursiveSearchTree(Graph *graph)
{   
    Node  *w1=NULL;
    Node  *u1=NULL;
    Node  *u2=NULL;
    Node  *v=NULL;
    
    vector<Node* > wResult ;
    vector<Node* > u1Result ;
    vector<Node* > u2Result ;
    vector<Node* > vResult  ;

    // set the size of the result sets to the max integer value
    int wSize  = INT_MAX;
    int u1Size = INT_MAX;
    int u2Size = INT_MAX;
    int vSize  = INT_MAX;

    for (Node  *n:graph->getNodes() )
    {
        if (n->isAssigned() == -1)
        {
            vector<Node*> unassigned = getNumUnassignedNeighbors(n);
            if (unassigned.size() == 1)
            {   
                w1 = unassigned[0];
                v = n;
            }
            else if (unassigned.size() == 2)
            {
                u1 = unassigned[0];
                u2 = unassigned[1];
                v = n;
            }
        }
    }

    if (w1==NULL && u1==NULL  && u2==NULL  && v==NULL )
    {   
        int numNodesAssigned = 0;
        for (Node  *node : graph->getNodes())
            if (node->isAssigned() == 1)  { numNodesAssigned++; }
        int x=graph->getNumNodes() - numNodesAssigned;
        return bruteForce(graph, x, numNodesAssigned);
    }
        

    if (w1!=NULL )
    {
        w1->setAssignment(1);
        v->setAssignment(0);
        for(Node *i:graph->getNodes())
        {
            if(w1->getName()==i->getName())
                i->setAssignment(1);
            if(v->getName()==i->getName())
                i->setAssignment(0);        
        }

        wResult = recursiveSearchTree(graph);
        wSize = wResult.size();
        w1->setAssignment(-1);
        v->setAssignment(-1);
        for(Node* i:graph->getNodes())
        {
            if(w1->getName()==i->getName())
                i->setAssignment(-1);
            if(v->getName()==i->getName())
                i->setAssignment(-1);
                
        }
    }

    if (u1!=NULL )
    {   
        // case 2a
        u1->setAssignment(1);
        u2->setAssignment(-1);
        v->setAssignment(0);
        for(Node *i:graph->getNodes())
        {
            if(u1->getName()==i->getName())
                i->setAssignment(1);
            if(u2->getName()==i->getName())
                i->setAssignment(-1);
            
            if(v->getName()==i->getName())
                i->setAssignment(0);        
        }
     
        u1Result = recursiveSearchTree(graph);
        u1Size = u1Result.size();

        // case 2b
        u1->setAssignment(0);
        u2->setAssignment(0);
        v->setAssignment(1);
        
        for(Node *i:graph->getNodes())
        {
            if(u1->getName()==i->getName())
                i->setAssignment(0);
            if(u2->getName()==i->getName())
                i->setAssignment(0);
            
            if(v->getName()==i->getName())
                i->setAssignment(1);
                
        }
    
        vResult = recursiveSearchTree(graph);
        vSize = vResult.size();

        // case 2c
        u1->setAssignment(0);
        u2->setAssignment(1);
        v->setAssignment(0);
        
        for(Node *i:graph->getNodes())
        {
            if(u1->getName()==i->getName())
                i->setAssignment(0);
            if(u2->getName()==i->getName())
                i->setAssignment(1);
            if(v->getName()==i->getName())
                i->setAssignment(0);       
        }
        //cout<<"Call6\n";
        u2Result = recursiveSearchTree(graph);
        u2Size = u2Result.size();

        // reset assignments
        u1->setAssignment(-1);
        u2->setAssignment(-1);
        v->setAssignment(-1);
        
        for(Node* i:graph->getNodes())
        {
            if(u1->getName()==i->getName())
                i->setAssignment(-1);
            if(u2->getName()==i->getName())
                i->setAssignment(-1);
            if(v->getName()==i->getName())
                i->setAssignment(-1);    
        }
    }

    // return smallest result
    int minNum = min( wSize, min(u1Size, min(u2Size, vSize)));
    //cout<<minNum<<" min\n";
    if      (minNum == wSize ) { return wResult;  }
    else if (minNum == u1Size) { return u1Result; }
    else if (minNum == u2Size) { return u2Result; }
    else                       { return vResult;  }
}


vector<Node*> DominatingSet::bruteForce(Graph *graph, int &sizeOfSubgraph, int &numAlreadyAssigned)
{   
    
    Node  *u=NULL ;
    //u.setAssignment(-2); 
    int totalNumAssignedToOne = 0;
     
    // check if dominating set is possible, if not return full graph as dominating set
    for (Node  *node : graph->getNodes() )
    {   
        if (node->isAssigned() == 0)
        {
            bool allNeighborsSetToZero = true;
            
            for (Node  *neighbor : node->getNeighbors() ) 
            {   
                if (neighbor->isAssigned() != 0)
                    allNeighborsSetToZero = false;
            }

            
            if (allNeighborsSetToZero)
            {
                return (vector<Node*>) graph->getNodes();
            }  
        }
        else if (node->isAssigned() == 1)
            totalNumAssignedToOne++;
        else
            u = node;
    }

    // if all nodes have been assigned and set is valid, return dominating set
    if (u==NULL)
    {   
        vector<Node*> ds;
        for (Node * node : graph->getNodes())
        {
            if (node->isAssigned() == 1)
                ds.push_back(node);
        }
        return ds;
    }

    // stop searching if number of assigned nodes is greater than or equal
    // to 3n/8
    if (totalNumAssignedToOne - numAlreadyAssigned >= 3*sizeOfSubgraph/8)
        return (vector<Node*>) graph->getNodes();

    // recursively iterate through all assignments of u
    u->setAssignment(0);
    vector<Node*> u0 = bruteForce(graph, sizeOfSubgraph, numAlreadyAssigned);
    u->setAssignment(1);
    vector<Node*> u1 = bruteForce(graph, sizeOfSubgraph, numAlreadyAssigned);
    u->setAssignment(-1);

    //return the smallest set
    if ( u0.size() < u1.size() )   { return u0; }
    else                           { return u1; }
}


vector<Node*> DominatingSet::getNumUnassignedNeighbors(Node  *node)
{
    vector<Node*> unAssigned;
    for (Node *neighbor : node->getNeighbors())
        if (neighbor->isAssigned() == -1)
        {
            unAssigned.push_back(neighbor);
        }
    return unAssigned;
}


vector<Node*> DominatingSet::findGreedyDominatingSet(Graph *graph)
{
    bool allNodesAreCovered = false;
    Node*  maxCoverNode;
    vector<Node*> visited ;

    while (!allNodesAreCovered)
    {	
        allNodesAreCovered = false;
        int maxCoverNum = 0;
        
        for (Node  *node : graph->getNodes())
        {	
            if (node->isAssigned() != 1 )
            {
                int uncoveredNeighbors = getNumberUncoveredNeighbors(node);
                if (uncoveredNeighbors > maxCoverNum)
                {
                    maxCoverNum = uncoveredNeighbors;
                    maxCoverNode = node;
                }
            }
        }

        updateCover(maxCoverNode);
        visited.push_back(maxCoverNode);

        // check that all nodes are covered
        allNodesAreCovered = true;
        for (Node  *node : graph->getNodes())
        {
            if (node->isAssigned() == -1)
            {
                allNodesAreCovered = false;
                break;
            }
        }
    }
    //graph.resetGraph();
    return visited;
}


int DominatingSet::getNumberUncoveredNeighbors(Node  *candidate)
{
    int numUncovered = 0;

    if (candidate->isAssigned() != 1) { numUncovered++; }

    for (Node  *neighbor : candidate->getNeighbors() )
        if ( neighbor->isAssigned() == -1 ) {	numUncovered++; }

    return numUncovered;
}

void DominatingSet::updateCover(Node *node)
{   
    node->setAssignment(1);    
    for (Node  *neighbor : node->getNeighbors() )
        if ( neighbor->isAssigned() == -1 ) 
            neighbor->setAssignment(0);
}
