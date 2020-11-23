#include "Settings.h"

//
// Created by brani on 03.08.2016.
//
// minor changes - clear code by hary 23.11.2020

#include "Settings.h"


Settings::Settings(float* extremes, int width, int height, lightType light) {
	this->light = light;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
	inicialise(extremes, width, height);
	windowSettings();

}


void Settings::onResize(float* extremes, int width, int height) {
	inicialise(extremes, width, height);
}


void Settings::inicialise(float* extremes, int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glLoadIdentity();


	glOrtho(extremes[0] - 1.0f * abs(extremes[0]), extremes[3] + 1.0f * abs(extremes[3]), extremes[1] -
		1.0f * abs(extremes[1]), extremes[4] + 1.0f * abs(extremes[4]), extremes[2] - 1.0f * abs(extremes[2]), extremes[5] + 1.0f * abs(extremes[5]));
	glScalef(1, 1, 1);
	

	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialShine);
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShineFactor);
	glLightfv(GL_LIGHT0, GL_POSITION, poziceSvetla);

	if (light) {
		turnOnLights();
	}

	cout << extremes[0] << "      " << extremes[3] << "     " << extremes[1] << "      " << extremes[4] << "      " << extremes[2] << "      " << extremes[5] << endl;
}

void Settings::turnOnLights() {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Settings::turnOffLights() {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

const sf::ContextSettings& Settings::getWindowSet() const {
	return windowSet;
}

void Settings::windowSettings() {
	windowSet.depthBits = 24;
	windowSet.stencilBits = 8;
	windowSet.antialiasingLevel = 2;
}




