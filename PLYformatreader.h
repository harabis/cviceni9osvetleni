//
// Created by brani on 31.07.2016.
//

#ifndef FVIZ_OBJ_PLYFORMATREADER_H
#define FVIZ_OBJ_PLYFORMATREADER_H

#include <iostream>
#include "cmath"
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;
#include "calculateNormals.h"


class PLYformatreader {
public:
	PLYformatreader(string filename, lightType light);
private:
	lightType light;
	fstream file;
	int vertexNumber = 0;
	int quadsNumber = 0;
	int polygonNumber = 0;
	int faceNumber = 0;
	int triangleNumber = 0;
	int getNumber(string line);
	void findVertices();
	void findFaces();
	float extremes[6] = { numeric_limits<float>::max(), numeric_limits<float>::max(),
			numeric_limits<float>::max(), numeric_limits<float>::min(),
			numeric_limits<float>::min(), numeric_limits<float>::min() };
	vector< vector <float> > vertex;
	vector< vector <int> > face;
	vector< vector <float> > normal;
	vector< vector <int> > vertexInFaceList;
public:
	const vector<vector<int>>& getVertexInFaceList() const;

private:
	bool vertexNormalsCalcul;


public:
	float* getExtremes();

	int getVertexNumber() const {
		return vertexNumber;
	}

	int getQuadsNumber() const {
		return quadsNumber;
	}

	int getPolygonNumber() const {
		return polygonNumber;
	}

	int getFaceNumber() const {
		return faceNumber;
	}

	int getTriangleNumber() const {
		return triangleNumber;
	}

	const vector<vector<float>>& getVertex() const {
		return vertex;
	}

	const vector<vector<int>>& getFace() const {
		return face;
	}
};


#endif //FVIZ_OBJ_PLYFORMATREADER_H
