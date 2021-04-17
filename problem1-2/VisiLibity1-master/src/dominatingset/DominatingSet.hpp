#ifndef DOMINATINGSET_H
#define DOMINATINGSET_H


#include<set>
#include<string>
#include "GraphLoader.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include "DominatingSet.hpp"
using namespace std;


class DominatingSet
{   
    private:
    /**
     * This method implements the core of the algorithm developed by Fomin, et. al. 
     * 
     * The recursive search tree works finding all nodes with degree 1 and 2 (that is,
     * nodes with only 1 or 2 neighbors). 
     *      Case 1: If node v is of degree 1, then this algorithm assigns its neighbor, w,
     *      to be in the dominating set.
     *      Case 2: If the node v is of degree 2, then this algorithm splits into three
     *      subcases. Let the two neighbors be denoted as u1 and u2
     *          Case 2a: Mark u1 as in D, and v as not in D. Recurse on resulting graph.
     *          Case 2b: Mark v as in D, and u1 and u2 as not in D. Recurse on resulting graph.
     *          Case 2c: Mark u2 as in D, and u1 and v as not in D. Recurse on resulting graph.
     * After the search tree has dealt with all nodes of degree one and two, it calls the brute force
     * search to find the minimum dominating set on the "reduced" graph.
     * 
     * @param graph The graph object for which a minimum dominating set is to be found.
     * @return A List of Nodes representing the nodes included in the dominating set.
     */
    static vector<Node*> recursiveSearchTree(Graph *graph);
    /**
     * Finds the minimum dominant set of a graph.
     *
     * This uses brute force, that is, it tries every possible combination of assignments,
     * to find a minimum dominant set of a graph. Given that there are 2 possible states for
     * each of the n nodes, this method runs in O(2^n).
     *
     * @param graph The graph object for which a minimum dominating set is to be found.
     * @return A List of Nodes representing the nodes included in the dominating set.
     */
    static vector<Node*> bruteForce(Graph *graph, int &sizeOfSubgraph, int &numAlreadyAssigned);
   
    /** 
     * Returns a list of unassigned neighbors of a given node.
     *
     * @param node The node for which to get the neighbors that have
     *                  have not been assigned to in or out of the dominating set.
     * @return A List of the unassigned neighbor nodes
     */
    static vector<Node*> getNumUnassignedNeighbors(Node *node);
    
    /**
     * Returns the number of neighbors of a given node that are uncovered.
     * @param name An integer representing the name of a node
     * @return An integer representing the number of uncovered neighbors
     */
    static int getNumberUncoveredNeighbors(Node *candidate);

    /**
     * Updates the neighborhood of a node that has been assigned to 
     * the dominating set by marking all of its neighbors as out of the
     * dominating set.
     *
     * @param node The Node whose neighborhood needs to be updated.
     */
    static void updateCover(Node *node);

    public:
    static vector<Node*> findMinimumDominatingSet(Graph *graph);
    
     /**
     * Returns a list of the Nodes that are included in the Dominating Set.
     * This implementation uses a Greedy Algorithm to find the dominating set 
     * of the graph. The Dominating Set, D, is a subset of nodes such that every
     * not in D is adjacent to at least one node in D.
     *
     * Note. This implementation on returns a Dominating Set. It is not guaranteed to
     * return the minimum dominating set.
     *
     * @param graph The graph object for which a dominating set is to be found.
     * 
     * @return A List of Nodes representing the nodes included in the dominating set.
     */
    static vector<Node*> findGreedyDominatingSet(Graph *graph);
  
    
    
  
};
#endif