

#include<string>
#include<iostream>
#include "GraphLoader.hpp"
#include<set>
#include<sstream>
#include <fstream>
#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
//#include "DominatingSet.hpp"

using namespace std;
//using namespace NGraph;
static void GraphLoader::loadGraph(Graph g, string filename) {
	
	set<int> seen;
	//Scanner sc;
	ifstream newfile; 
	newfile.open(filename); 
	if(newfile.is_open())
	{
		string tp;
		while(getline(newfile, tp)){ //read data from file object and put it into string.
			stringstream ss;    
			ss << tp;
			string temp;
			int v1,v2;
			ss >> temp;
			if (stringstream(temp) >> v1)
			{
				if (seen.find(v1)==seen.end())
				{
					g.addNode(v1);
					seen.insert(v1);
				}
					
			}
			temp="";
			ss>>temp;
			if(stringstream(temp)>>v2)
			{
				if (seen.find(v2)==seen.end())
				{
					g.addNode(v2);
					seen.insert(v2);
				}
			}
			g.addEdge(v1, v2);	
		}		
	}
	newfile.close();
}

