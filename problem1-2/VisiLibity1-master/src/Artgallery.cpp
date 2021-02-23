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


using namespace std;


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
	double epsilon = 0.000000001;
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



	//Check Environment is epsilon-valid
	/*std::cout << "Validating environment model . . . ";
	if (my_environment.is_valid(epsilon))
		std::cout << "OK" << std::endl;
	else {
		std::cout << std::endl << red << "Warning:  Environment model "
			<< "is invalid." << std::endl
			<< "A valid environment model must have" << std::endl
			<< "   1) outer boundary and holes pairwise "
			<< "epsilon -disjoint simple polygons" << std::endl
			<< "   (no two features should come "
			<< "within epsilon of each other)," << std::endl
			<< "   2) outer boundary is oriented ccw, and"
			<< std::endl
			<< "   3) holes are oriented cw."
			<< std::endl
			<< normal;
		exit(1);
	}*/
    
	/*----------Print Data and Statistics to Screen----------*/


 //Environment data
	/*std::cout << "The environment model is:" << std::endl;
	std::cout << magenta << my_environment << normal;


	//Environment stats
	std::cout << "This environment has " << cyan
		<< my_environment.n() << " vertices, "
		<< my_environment.r() << " reflex vertices, "
		<< my_environment.h() << " holes, "
		<< "area " << my_environment.area() << ", "
		<< "boundary length "
		<< my_environment.boundary_length() << ", "
		<< "diameter "
		<< my_environment.diameter() << "."
		<< normal << std::endl;
	*/
	VisiLibity::Visibility_Graph my_vis_graph((my_environment),
		epsilon);
		int n = my_environment.n();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cout << my_vis_graph(i, j);
			cout << my_environment(i) <<" "<< '\n';
		}
}