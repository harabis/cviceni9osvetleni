//
// Created by brani on 31.07.2016.
//

#include "PLYformatreader.h"

// Constructor, opening file, reading header and calling vertex listing function
PLYformatreader::PLYformatreader(string filename, lightType light) : light(light) {

	// if true, also vertex normals are computed	
	if (light) {
		cout << "Vertex normals will be computed" << endl;
	}


	if (filename.empty()) {
		cout << "Error, no file to open!" << endl;
		exit(-1);
	}

	file.open(filename.c_str(), fstream::in);
	if (!file.is_open()) {
		cerr << "Error file cannot be opened" << endl;
		exit(-2);
	}
	cout << "File: " << filename << " has been opened!" << endl;
	string line;
	while (getline(file, line)) {
		if (line.find("element vertex") != string::npos) {
			vertexNumber = getNumber(line);
		}
		if (line.find("element face") != string::npos) {
			faceNumber = getNumber(line);
		}
		if (line.find("end_header") != string::npos) {
			if (vertexNumber && faceNumber) {
				cout << "File has " << vertexNumber << " vertices" << " and " << faceNumber << " faces" << endl;
				findVertices();
			}
			else {
				cerr << "I don't have all informations needed, exiting..." << endl;
				exit(-2);
			}
		}
	}


}


int PLYformatreader::getNumber(string line) {
	istringstream iss(line);
	string parsed;
	int result = 0;
	while (getline(iss, parsed, ' ')) {
		try {
			result = stoi(parsed);
			break;
		}
		catch (std::invalid_argument & e) {
			continue;
		}
	}
	if (result == 0) {
		cerr << "Number haven't been obtained" << endl;
		exit(-3);
	}

	return result;
}




void PLYformatreader::findVertices() {
	int i, j;
	string line;
	string parsed;
	float number;
	vertex.resize((unsigned int)vertexNumber);
	if (light == NormalVertex) {
		vertexInFaceList.resize((unsigned int)vertexNumber);
	}
	for (i = 0; i < vertexNumber; i++) {
		vertex[i].resize(3);
		getline(file, line);
		if (line.empty()) {
			i--;
			continue;
		}
		istringstream iss(line);
		for (j = 0; j < 3; j++) {
			getline(iss, parsed, ' ');
			try {
				vertex[i][j] = stof(parsed);
				if (vertex[i][j] < extremes[j]) {
					extremes[j] = vertex[i][j];
				}
				else if (vertex[i][j] > extremes[j + 3]) {
					extremes[j + 3] = vertex[i][j];
				}

			}
			catch (std::invalid_argument & e) {
				cerr << "Hups number not converted: " << parsed << endl;
				cout << e.what();
				exit(-4);
			}
		}
	}
	findFaces();
}

// add vertexInFace calcul. for each found vertex, add the number of face to it.

void PLYformatreader::findFaces() {
	int i, j;
	int vx;
	string line;
	string parsed;
	int number;
	face.resize((unsigned int)faceNumber);
	for (i = 0; i < faceNumber; i++) {
		getline(file, line);

		if (line.empty()) {
			i--;
			continue;
		}

		istringstream iss(line);
		getline(iss, parsed, ' ');
		try {
			number = stoi(parsed);
			switch (number) {
			case 3: {
				triangleNumber++;
				break;
			}
			case 4: {
				quadsNumber++;
				break;
			}
			default: {
				polygonNumber++;
				break;
			}
			}
			face[i].resize((unsigned int)number);
		}
		catch (std::invalid_argument & e) {
			cerr << "Some error occured when converting parsed string to int: " << parsed << endl;
			exit(-5);
		}

		for (j = 0; j < number; j++) {
			getline(iss, parsed, ' ');
			try {
				vx = stoi(parsed);
				face[i][j] = vx;
				if (light == NormalVertex) {
					vertexInFaceList[vx].push_back(i);
				}
			}
			catch (std::invalid_argument & e) {
				cerr << "Some error occured when converting parsed string to int: " << parsed << endl;
				exit(-6);
			}

		}

	}

}


float* PLYformatreader::getExtremes() {
	return extremes;
}

const vector<vector<int>>& PLYformatreader::getVertexInFaceList() const {
	return vertexInFaceList;
}


