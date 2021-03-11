#include <GL/glut.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// void myInit (void)
// {
//     // making background color black as first 
//     // 3 arguments all are 0.0
//     glClearColor(0.0, 0.0, 0.0, 1.0);
     
//     // making picture color green (in RGB mode), as middle argument is 1.0
//     if(check == 0){
//         glColor3f(1.0,0.0,0.0);
//     }
//     else{
//         glColor3f(0.0, 1.0, 0.0);
//     }     
//     // setting window dimension in X- and Y- direction
//     gluOrtho2D(0, 10, -10, 10);
// }

void display()
{
    ifstream fin;
    fin.open("points.txt");
	  glClear(GL_COLOR_BUFFER_BIT);
    int n;
    while(fin>>n){
        glColor3f(0.0,1.0,0.0);
	      glBegin(GL_LINE_LOOP);  
        int i=0;
        //reading input
        float a,b;
        vector < pair<float,float> > points;
        for(i=0;i<n;i++){
        fin >> a >> b;
        points.push_back(make_pair(a,b));
    }
  	for(i=0;i<points.size();i++){
        glVertex2f(points[i].first,points[i].second);
  	}
	  glEnd();
    }
	  glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
	  glutCreateWindow("art gallery");
    //myInit();
    gluOrtho2D(0, 10, -10, 10);
	  glutDisplayFunc(display);
	  glutMainLoop();
}
