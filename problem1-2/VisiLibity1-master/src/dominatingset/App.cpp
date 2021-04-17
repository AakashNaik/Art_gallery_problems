#include<iostream>
#include<set>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include "DominatingSet.hpp"
using namespace std;



int  main()
{
  string filename = "C:/Users/aakas/Desktop/Art_gallery/Art_gallery_problems/problem1-2/VisiLibity1-master/src/data.txt";
  //cout<<"a";
  Graph *g=new Graph();
  //cout<<"a";
  set<int> seen;
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
          //cout<<v1<<'\n';
					g->addNode(v1);
					seen.insert(v1);
				}
					
			}
			temp="";
			ss>>temp;
			if(stringstream(temp)>>v2)
			{
				if (seen.find(v2)==seen.end())
				{
          //cout<<v2<<'\n';
					g->addNode(v2);
					seen.insert(v2);
				}
			}
      //cout<<((to_string(v1)))+((to_string(v2)))<<'\n';
      //cout<<"b";
   
			g->addEdge(v1, v2);	
      //cout<<"b";
   
		}		
	}
	newfile.close();
   
	cout<<"\nAnalyzing "<<filename<<" ...";
  cout<<"The undirected graph has "<<g->getNumNodes()<< " nodes.";
	cout<<"Undirected  graph has "<<g->getNumEdges()<<" edges.";

		
	vector<Node*> mds = DominatingSet::findMinimumDominatingSet(g);
  
  for(Node *i:mds)
  {
    cout<<i->getName()<<'\n';

  }
  
  cout<<mds.size()<<'\n';
		
		
}
	
	

