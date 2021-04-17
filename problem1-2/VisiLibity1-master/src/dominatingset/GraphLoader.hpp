
#ifndef GRAPHLOADER_H
#define GRAPHLOADER_H


#include<iostream>
//#include "GraphLoader.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "GraphLoader.hpp"

#include "Graph.hpp"
//#include "DominatingSet.hpp"
using namespace std;

class GraphLoader 
{
  public:
  static void loadGraph(Graph g, string filename);
};
#endif