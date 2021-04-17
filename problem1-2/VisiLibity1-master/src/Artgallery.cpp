#include "visilibity.hpp"  //VisiLibity header file
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
#include"clipper.hpp"
#include<math.h>
#include "polypartition.h"
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

	ofstream myfile, myfile1;
	myfile.open("data.txt");
	myfile1.open("map.txt");
	
	TPPLPolyList polylist{},outlist{};
	TPPLPoly  poly;

	
	poly.Init(my_environment[0].n());
	poly.SetHole(false);
	
	for(int i=0;i<my_environment[0].n();i++)
	{   
		(poly.GetPoints())[i].x=my_environment[0][i].x();
		(poly.GetPoints())[i].y=my_environment[0][i].y();
    }
	polylist.push_back(poly);

	for(int j=1;j<=my_environment.h();j++)
	{
		TPPLPoly  poly;
		poly.Init(my_environment[j].n());
		poly.SetHole(true);
		for(int i=0;i<my_environment[j].n();i++)
		{   
			(poly.GetPoints())[i].x=my_environment[j][i].x();
			(poly.GetPoints())[i].y=my_environment[j][i].y();
    	}
		polylist.push_back(poly);
	}
	
	TPPLPartition z;
	int y= z.ConvexPartition_HM(&polylist,&outlist);
    v_comp components[outlist.size()];
	int i=0;
	vector<set<VisiLibity::Point>>vert_poly;
	vector<bool>flag;
	for (auto it = (outlist).begin(); it != (outlist).end(); ++it)
	{ 
	    components[i].flag=true;
		double a=0.0,b=0.0;
		set<VisiLibity::Point>temp;
		for(int j=0;j<it->GetNumPoints();j++)
		{
			VisiLibity::Point re(it->GetPoints()[j].x,it->GetPoints()[j].y);
			temp.insert(re);
			a+=(it->GetPoints())[j].x;
			b+= (it->GetPoints())[j].y;
		}
		vert_poly.push_back(temp);
		flag.push_back(false);
		a=a/it->GetNumPoints();
		b=b/it->GetNumPoints();
		components[i].x=a;
		components[i].y=b;
		i++;	
	}
	
	map<VisiLibity::Point,set<int>>d;
    for(int i=0;i<my_environment.n();i++)
	{
		VisiLibity::Polygon polygon_temp = VisiLibity::Visibility_Polygon(my_environment(i), my_environment, epsilon);
		for(int j=0;j<outlist.size();j++)
		{
			VisiLibity::Point p(components[j].x,components[j].y);
			if(p.in(polygon_temp, epsilon))
			{
				if(d.find(my_environment(i))==d.end())
				{
					set<int>f;
					f.insert(j);
					
					d[my_environment(i)]=f;
				}
				else
				{
					d[my_environment(i)].insert(j);
				}	
			}
		}
	}
	while(!d.empty())
	{
		VisiLibity::Point dum;
		int max1=-1;
		for(auto t:d)
		{
			if((int)t.second.size()>max1)
			{
				max1=t.second.size();
				dum.set_x(t.first.x());
				dum.set_y(t.first.y());
			}

		}
		set<int>g=d[dum];
		for(auto t=d.begin();t!=d.end();t++)
		{
			for(auto k:g)
			{
				if(t->second.find(k)!=t->second.end())
				    t->second.erase(k);
			}
		}
		for(auto t:d)
		{
			if((t.second.empty()))
			  d.erase(t.first);
		}
		
	}
	int tr=vert_poly.size();
	string filename1 = "C:/Users/aakas/Desktop/Art_gallery/Art_gallery_problems/problem1-2/VisiLibity1-master/src/guards.txt";
  
    ofstream newfile1; 
	newfile1.open(filename1);

	while(tr>0)
	{
		map<VisiLibity::Point,int>count;
		
		for(int i=0;i<my_environment.n();i++)
		{
			int yt=0;
			for(int j=0;j<vert_poly.size();j++)
			{
				if(!flag[j] &&vert_poly[j].find(my_environment(i))!=vert_poly[j].end())
				   yt++;
			}
			count[my_environment(i)]=yt;
		}

		int max=-1;
		VisiLibity::Point p;
		for(auto itr:count)
		{
			if(itr.second>max)
			 {
				 p.set_x(itr.first.x());
				 p.set_y(itr.first.y());
				 max=itr.second;
			 }
		}
		for(int j=0;j<vert_poly.size();j++)
		{
			if(vert_poly[j].find(p)!=vert_poly[j].end())
			{	
				flag[j]=true;
				tr--;
			}
		}
		string d= to_string(p.x())+','+to_string(p.y());
        cout<<d<<'\n';
        newfile1<<d<<endl;
        
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

		//map<int,VisiLibity::Point>rt;
	/*int j=0;
	for(int i=0;i<my_environment.n();i++)
	{
		rt[j++]=my_environment[i];
	}*/



	/*VisiLibity::Visibility_Graph my_vis_graph((my_environment),
		epsilon);
		int n = my_environment.n();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if(my_vis_graph(i, j)&&i!=j)
				myfile << i<<" "<<j<<'\n';
			myfile1 << my_environment(i)<<'\n';
		}
		myfile.close();
		myfile1.close();*/
	/*VisiLibity::Polygon outer_boundary = my_environment[0];
	vis vis_poly[my_environment.n()];
	int k = 0;
	for (int i = 0; i <= my_environment.h(); i++)
	{
		for (int j = 0; j < my_environment[i].n(); j++)
		{
			VisiLibity::Point observer = my_environment[i][j];
			//cout<<observer<<'\n';
			VisiLibity::Visibility_Polygon my_vis_poly(observer,
				(my_environment),
				epsilon);
			Path x;
			for (int l = 0; l < my_vis_poly.n(); l++) {
				IntPoint a;
				a.X = my_vis_poly[l].x();
				a.Y = my_vis_poly[l].y();
				x << a;
			}
			vis_poly[k].path<<x;
			vis_poly[k].area = abs(my_vis_poly.area());
			IntPoint v(observer.x(), observer.y());
			vis_poly[k].pt = v;
			k++;
		}
		

	}*/
	
	/*for (int i = 0; i < my_environment.n(); i++)
		cout << vis_poly[i].pt << '\n' << vis_poly[i].area << " \n//////////\n";*/
    //cout<<"d";
	
/*	double poly_area = my_environment[0].area();
	
	for (int i = 1; i <= my_environment.h(); i++)
		poly_area -= abs(my_environment[i].area());
	//cout << "area is " << poly_area << '\n';
	int y = 3;
	while (poly_area > 0.0001)
	{

		int ind=0;
		double max_area = 0;
		for (int i = 0; i < my_environment.n(); i++)
		{
			if (vis_poly[i].area > max_area)
			{
				ind = i;
				max_area = vis_poly[i].area;
			}
			//cout << "i: " << i << " " << vis_poly[i].area << '\n';
		}
		if (max_area < 0.0001)
			break;
		poly_area -= max_area;
		//cout <<"new index"<< ind <<" a: "<<vis_poly[ind].area<< '\n';
		//cout << "Area " << poly_area << '\n';
		for (int i = 0; i < my_environment.n(); i++)
		{
			if (vis_poly[i].area > 0.000001&&ind!=i)
			{
				//cout << i << '\n';
				Paths q, w;
				q = vis_poly[i].path;
				w = vis_poly[ind].path;
				Clipper clpr;
				clpr.AddPaths(q, ptSubject, true);
				clpr.AddPaths(w, ptClip, true);
				Paths solution;
				clpr.Execute(ctDifference, solution, pftEvenOdd, pftEvenOdd);
				vis_poly[i].path = solution;
				//cout<<solution.size()<<'\n';
				//cout << "Solution area is " << solution[0] << " " << Area(solution[0]) << '\n';
				vis_poly[i].area=0;
				for(int j=0;j<solution.size();j++)
				vis_poly[i].area += abs(Area(solution[j]));
			}
			
		}
		vis_poly[ind].area = 0;
		for(int i=0;i<my_environment.n();i++)
		{
			cout<<vis_poly[i].pt<<" a "<<'\n';
			cout<<vis_poly[i].path<<" b "<<'\n';
			cout<<vis_poly[i].area<<" c "<<'\n';
			
		}
		cout << vis_poly[ind].pt<<'\n';
		cout << "old area " << poly_area <<" AA "<<max_area<< '\n';

		y--;
		//break;
	}*/
	/*Path a, b;
	IntPoint x;
	x.X = 0;
	x.Y = 0;
	a << x;
	x.X = 3;
	x.Y = 0;
	a << x;
	x.X = 3;
	x.Y = 3;
	a << x;
	x.X = 0;
	x.Y = 3;
	a << x;
	

	x.X = 0;
	x.Y = 0;
	b << x;
	x.X = 3;
	x.Y = 0;
	b << x;
	x.X = 3;
	x.Y = 3;
	b << x;
	x.X = 0;
	x.Y = 3;
	b << x;
	Paths q, w;
	q << a;
	w << b;
	Clipper clpr;
	clpr.AddPaths(q, ptSubject, true);
	clpr.AddPaths(w, ptClip, true);
	Paths solution;
	clpr.Execute(ctDifference, solution, pftEvenOdd, pftEvenOdd);
	cout << "\n" << solution << Area(solution[0]);*/
	//for(int i=0;i<)
	/*for (int i = 0; i < outer_boundary.n(); i++)
	{
		cout << vis_poly[i].path << '\n';
		cout << vis_poly[i].area << '\n';
		cout << vis_poly[i].pt << '\n';
		cout << "//////////////////\n";
	}*/

	
		
		//display the subject and clip polygons ...
		//cout << sub;
		//<< sub1;
		
		//get the intersection of the subject and clip polygons ...
		/*Clipper clpr;
		clpr.AddPaths(q, ptSubject, true);
		clpr.AddPaths(q1, ptClip, true);
		Paths solution;
		clpr.Execute(ctDifference, solution, pftEvenOdd, pftEvenOdd);
		cout << solution;*/
		//finally draw the intersection polygons ...
		//DrawPolygons(solution, 0x40808080);*/
}
