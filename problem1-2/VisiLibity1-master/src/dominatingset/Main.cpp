#include "../visilibity.hpp"  //VisiLibity header file
#include <cstdlib>       //rand, srand, exit
#include <ctime>         //Unix time
#include <fstream>       //File I/O
#include <iostream>      //std I/O
#include <cstring>       //C-string manipulation
#include <string>        //string cla ss
#include <sstream>       //string streams
#include <vector>        //std vectors
//#define NDEBUG           //Turns off assert.
#include<map>
#include<set>
#include <cassert>
#include"../clipper.hpp"
#include<math.h>
#include "../polypartition.h"
#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include "DominatingSet.hpp"
using namespace std;
using namespace ClipperLib;
struct vis
{
	Paths path;
	TPPLPoint pt;
};

struct v_comp
{
	bool flag;
	double x,y;
};

int main(int argc, char* argv[])
{
	if (argc > 2) {
		std::cerr << "Error: too many input arguments" << std::endl;
		exit(1);
	}


	//Set iostream floating-point display format
	const int IOS_PRECISION = 10;
	std::cout.setf(std::ios::fixed);
	std::cout.setf(std::ios::showpoint);
	std::cout.precision(IOS_PRECISION);

	std::srand(std::time(NULL)); rand();
    double epsilon = 0.00001;
	std::cout << "Loading environment file ";
	std::string environment_file(argv[1]);
	std::cout << environment_file << " . . . ";
	VisiLibity::Environment my_environment(environment_file);
	std::cout << "OK" << std::endl;

	//ofstream myfile, myfile1;
	//myfile.open("data.txt");
	//myfile1.open("map.txt");

    map<int,VisiLibity::Point>rt;
	int j=0;
	for(int i=0;i<my_environment.n();i++)
	{
		rt[j++]=my_environment(i);
	}


    vector<vector<int>>pt;
	VisiLibity::Visibility_Graph my_vis_graph((my_environment),
		epsilon);
		int n = my_environment.n();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if(my_vis_graph(i, j)&&i!=j)
			{	
                vector<int>f={i,j};
                pt.push_back(f);
                //cout<< i<<" "<<j<<'\n';

            }
			//cout>> my_environment(i)>>'\n';
		}
    
    Graph *g=new Graph();
    for(int i=0;i<pt.size();i++)
    {
        int x=pt[i][0];
        int y=pt[i][1];
        g->addNode(x);
        g->addNode(y);
        g->addEdge(x,y);
    }
	//cout<<"\nAnalyzing "<<filename<<" ...";
    cout<<"The undirected graph has "<<g->getNumNodes()<< " nodes.";
	cout<<"Undirected  graph has "<<g->getNumEdges()<<" edges.";

		
	vector<Node*> mds = DominatingSet::findMinimumDominatingSet(g);
     cout<<'\n';
    string filename1 = "C:/Users/aakas/Desktop/Art_gallery/Art_gallery_problems/problem1-2/VisiLibity1-master/src/guards.txt";
  
    ofstream newfile1; 
	newfile1.open(filename1);
    if(newfile1.is_open())
    {
        for(Node *i:mds)
        {
            cout<<rt[i->getName()]<<'\n';
            string d= to_string(rt[i->getName()].x())+','+to_string(rt[i->getName()].y());
            cout<<d<<'\n';
            newfile1<<d<<endl;

        }
        newfile1.close();    
    }
    string filename = "C:/Users/aakas/Desktop/Art_gallery/Art_gallery_problems/problem1-2/VisiLibity1-master/src/vis.txt";
  
    ofstream newfile; 
	newfile.open(filename);

    if(newfile.is_open())
    {
        for(int i=0;i<=my_environment.h();i++)
        {
            string d= to_string(my_environment[i].n());
            newfile<<d<<endl;
            for(int j=0;j<my_environment[i].n();j++)
            {

                string d= to_string(my_environment[i][j].x())+','+to_string(my_environment[i][j].y());
                cout<<d<<'\n';
                newfile<<d<<endl;
            }
        }
        newfile.close();
    }
    else cerr<<"Unable to open file";
    //cout<<mds.size()<<'\n';

    

		

}