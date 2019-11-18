//
// Created by brani on 03.08.2016.
//

#include <cmath>
#include "calculateNormals.h"


calculateNormals::calculateNormals(const vector<vector<float>>& vertex, const vector<vector<int>>& face) {
	resizeVectorNormals((unsigned int)face.size());
	calculateNormalFace(vertex, face);
}


calculateNormals::calculateNormals(const vector<vector<float>>& vertex, const vector<vector<int>>& face,
	const vector<vector<int>>& vertexInFaceList) {
	resizeVectorNormals((unsigned int)face.size());
	calculateNormalFace(vertex, face);
	vertexNormals.resize(vertex.size());
	calculateVertexNormal(vertexInFaceList);

}


void calculateNormals::resizeVectorNormals(unsigned int length) {
	normals.resize(length);
	for (int i = 0; i < length; i++) {
		normals[i].resize(3);
	}
}




void calculateNormals::calculateVertexNormal(const vector<vector<int>>& vertexInFaceList) {
	int i, j;
	float varx, vary, varz;

	for (i = 0; i < vertexNormals.size(); i++) {
		vertexNormals[i].resize(3);
		varx = 0;
		vary = 0;
		varz = 0;
		for (j = 0; j < vertexInFaceList[i].size(); j++) {
			varx += normals[vertexInFaceList[i][j]][0];
			vary += normals[vertexInFaceList[i][j]][1];
			varz += normals[vertexInFaceList[i][j]][2];
		}
		vertexNormals[i][0] = varx / (float)vertexInFaceList[i].size();
		vertexNormals[i][1] = vary / (float)vertexInFaceList[i].size();
		vertexNormals[i][2] = varz / (float)vertexInFaceList[i].size();
	}
}


void calculateNormals::calculateNormalFace(const vector< vector <float>>& vertex, const vector<vector <int>>& face) {
	int i, j, k;
	float x1, y1, y2, x2, z1, z2;
	float nx, ny, nz, nn;
	for (i = 0; i < face.size(); i++) {
		x1 = vertex[face[i][1]][0] - vertex[face[i][0]][0];
		y1 = vertex[face[i][1]][1] - vertex[face[i][0]][1];
		z1 = vertex[face[i][1]][2] - vertex[face[i][0]][2];
		x2 = vertex[face[i][2]][0] - vertex[face[i][0]][0];
		y2 = vertex[face[i][2]][1] - vertex[face[i][0]][1];
		z2 = vertex[face[i][2]][2] - vertex[face[i][0]][2];
		nx = y1 * z2 - y2 * z1;
		ny = z1 * x2 - x1 * z2;
		nz = x1 * y2 - y1 * x2;
		nn = sqrt(nx * nx + ny * ny + nz * nz);
		normals[i][0] = nx / nn;
		normals[i][1] = ny / nn;
		normals[i][2] = nz / nn;
		//cout << nx/nn << "  " << ny / nn << "   " << nz / nn <<endl;
	}
}

const vector<vector<float>>& calculateNormals::getVertexNormals() const {
	return vertexNormals;
}




