//
// Created by brani on 03.08.2016.
//

#ifndef FVIZ_OBJ_CALCULATENORMALS_H
#define FVIZ_OBJ_CALCULATENORMALS_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

enum lightType { None, NormalFace, NormalVertex };

class calculateNormals {
public:

	calculateNormals(const vector< vector <float>>& vertex, const vector<vector <int>>& face);
	void calculateNormalFace(const vector< vector <float>>& vertex, const vector<vector <int>>& face);
	calculateNormals(const vector<vector<float>>& vertex, const vector<vector<int>>& face, const vector<vector<int>>& vertexInFaceList);

private:
	vector< vector <float>> normals;
	void resizeVectorNormals(unsigned int length);
	vector< vector <float>> vertexNormals;
	void resizeVertexNormals(unsigned int length);
	void calculateVertexNormal(const vector< vector<int>>& vertexInFaceList);

public:
	const vector<vector<float>>& getVertexNormals() const;

	const vector<vector<float>>& getNormals() const {
		return normals;
	}
};



#endif //FVIZ_OBJ_CALCULATENORMALS_H
