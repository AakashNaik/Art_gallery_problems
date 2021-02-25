#include <bits/stdc++.h>
#include "visilibity.hpp"  //VisiLibity header file
//#include <cmath>         //Puts math functions in std namespace
#include <cstdlib>       //rand, srand, exit
#include <ctime>         //Unix time
#include <fstream>       //File I/O
#include <iostream>      //std I/O
#include <cstring>       //C-string manipulation
#include <string>        //string cla ss
#include <sstream>       //string streams
#include <vector>        //std vectors
//#define NDEBUG           //Turns off assert.
#include <cassert>
#include"clipper.hpp"
#include<math.h>

using namespace std;
using namespace ClipperLib;

struct vis
{
	Path path;
	IntPoint pt;
	double area;

};

int main(int argc, char* argv[])
{
	//Check input validity
	if (argc > 2) {
		std::cerr << "Error: too many input arguments" << std::endl;
		exit(1);
	}


	//Set iostream floating-point display format
	const int IOS_PRECISION = 10;
	std::cout.setf(std::ios::fixed);
	std::cout.setf(std::ios::showpoint);
	std::cout.precision(IOS_PRECISION);


	//Seed the rand() fnc w/Unix time
	//(only necessary once at the beginning of the program)
	std::srand(std::time(NULL)); rand();


	//Set geometric robustness constant
	//:WARNING: 
	//may need to modify epsilon for Environments with greatly varying
	//scale of features
	double epsilon = 0.01;
	//std::cout << green << "The robustness constant epsilon is set to "
		//<< epsilon << normal << std::endl;


	/*----------Load Geometry from Files----------*/
	//Load geometric environment model from file
	std::cout << "Loading environment file ";
	std::string environment_file(argv[1]);
	//Print environment filename to screen
	std::cout << environment_file << " . . . ";
	//Construct Environment object from file
	VisiLibity::Environment my_environment(environment_file);
	std::cout << "OK" << std::endl;

	

	ofstream myfile, myfile1;
	myfile.open("data.txt");
	myfile1.open("map.txt");
	VisiLibity::Visibility_Graph my_vis_graph((my_environment),
		epsilon);
		int n = my_environment.n();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if(my_vis_graph(i, j)&&i!=j)
				myfile << i<<" "<<j<<'\n';
			
			//myfile << '\n';
			myfile1 << my_environment(i)<<'\n';
		}
		myfile.close();
		myfile1.close();
	//VisiLibity::Point observer(0.5000000000 , 0.0000000000);
	// find all visible polygon of all vertices
	// find their area as well and store them in struct
	VisiLibity::Polygon outer_boundary = my_environment[0];
	vis vis_poly[my_environment.n()];
	int k = 0;
	for (int i = 0; i <= my_environment.h(); i++)
	{
		for (int j = 0; j < my_environment[i].n(); j++)
		{
			VisiLibity::Point observer = my_environment[i][j];
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
			vis_poly[k].path = x;
			vis_poly[k].area = abs(my_vis_poly.area());
			IntPoint v(observer.x(), observer.y());
			vis_poly[k].pt = v;
			k++;

		}
		

	}
	
	/*for (int i = 0; i < my_environment.n(); i++)
		cout << vis_poly[i].pt << '\n' << vis_poly[i].area << " \n//////////\n";*/
	double poly_area = my_environment[0].area();
	//cout << "old area " << poly_area << '\n';

	for (int i = 1; i <= my_environment.h(); i++)
		poly_area -= abs(my_environment[i].area());
	cout << "area is " << poly_area << '\n';
	int y = 3;
	while (poly_area > 0.1)
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
		if (max_area < 0.1)
			break;
		poly_area -= max_area;
		//cout <<"new index"<< ind <<" a: "<<vis_poly[ind].area<< '\n';
		//cout << "Area " << poly_area << '\n';
		for (int i = 0; i < outer_boundary.n(); i++)
		{
			if (vis_poly[i].area > 0.0001&&ind!=i)
			{
				//cout << i << '\n';
				Paths q, w;
				q << vis_poly[i].path;
				w << vis_poly[ind].path;
				Clipper clpr;
				clpr.AddPaths(q, ptSubject, true);
				clpr.AddPaths(w, ptClip, true);
				Paths solution;
				clpr.Execute(ctDifference, solution, pftEvenOdd, pftEvenOdd);
				vis_poly[i].path = solution[0];
				//cout << "Solution area is " << solution[0] << " " << Area(solution[0]) << '\n';
				vis_poly[i].area = abs(Area(solution[0]));
			}
			
		}
		vis_poly[ind].area = 0;
		cout << vis_poly[ind].pt<<'\n';
		y--;
		//break;
	}
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
		//DrawPolygons(solution, 0x40808080);
}