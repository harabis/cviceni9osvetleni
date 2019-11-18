//
// Created by brani on 03.08.2016.
//

#ifndef FVIZ_OBJ_DRAWOBJECT_H
#define FVIZ_OBJ_DRAWOBJECT_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

//#include "windows.h"
#include "calculateNormals.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>



class DrawObject {
public:
	void drawPLYobject(const vector< vector <float> >& vertex, const vector< vector <int> >& face);
	void drawPLYobject(const vector< vector <float> >& vertex, const vector< vector <int> >& face, const vector< vector <float> >& normal, lightType light);

	void transformObject(int xnew, int ynew, int znew);
private:

};


#endif //FVIZ_OBJ_DRAWOBJECT_H
