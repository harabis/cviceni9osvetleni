//
// Created by brani on 03.08.2016.

#include "DrawObject.h"


void DrawObject::drawPLYobject(const vector<vector<float> >& vertex, const vector<vector<int> >& face) {

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -2.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	int i, j, k;
	float var;
	for (i = 0; i < face.size(); i++) {
		if (face[i].size() == 3) {
			glBegin(GL_TRIANGLES);
		}
		else if (face[i].size() == 4) {
			glBegin(GL_QUADS);
		}
		else {
			glBegin(GL_POLYGON);
		}
		for (j = 0; j < face[i].size(); j++) {
			glVertex3f(vertex[face[i][j]][0], vertex[face[i][j]][1], vertex[face[i][j]][2]);
		}
		glEnd();
	}

	glFlush();
}

void DrawObject::drawPLYobject(const vector<vector<float> >& vertex, const vector<vector<int> >& face,
	const vector<vector<float> >& normal, lightType light) {
	//glTranslatef(0,0.0874782,0);
	if (light == NormalFace) {
		int i, j, k;
		float var;
		for (i = 0; i < face.size(); i++) {
			glNormal3f(normal[i][0], normal[i][1], normal[i][2]);
			if (face[i].size() == 3) {
				glBegin(GL_TRIANGLES);
			}
			else if (face[i].size() == 4) {
				glBegin(GL_QUADS);
			}
			else {
				glBegin(GL_POLYGON);
			}
			for (j = 0; j < face[i].size(); j++) {
				glVertex3f(vertex[face[i][j]][0], vertex[face[i][j]][1], vertex[face[i][j]][2]);
			}
			glEnd();
		}

	}
	else if (light == NormalVertex) {
		int i, j, k;
		float var;
		for (i = 0; i < face.size(); i++) {
			if (face[i].size() == 3) {
				glBegin(GL_TRIANGLES);
			}
			else if (face[i].size() == 4) {
				glBegin(GL_QUADS);
			}
			else {
				glBegin(GL_POLYGON);
			}
			for (j = 0; j < face[i].size(); j++) {
				glNormal3f(normal[face[i][j]][0], normal[face[i][j]][1], normal[face[i][j]][2]);
				glVertex3f(vertex[face[i][j]][0], vertex[face[i][j]][1], vertex[face[i][j]][2]);
			}
			glEnd();
		}

	}
	else {
		drawPLYobject(vertex, face);
	}

}

void DrawObject::transformObject(int xnew, int ynew, int znew) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0, 0.0, -50.0f);
	glTranslatef(0.0, 0.0, znew);
	glRotatef(ynew, 1.0, 0.0, 0.0);
	glRotatef(xnew, 0.0, 1.0, 0.0);
}










