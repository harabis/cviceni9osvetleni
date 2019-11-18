//
// Created by brani on 03.08.2016.
//

#ifndef FVIZ_OBJ_SETTINGS_H
#define FVIZ_OBJ_SETTINGS_H

#include <iostream>
#include <string>
#include <sstream>
#include "PLYformatreader.h"
using namespace std;

//#include "windows.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Settings {
public:
	Settings(float* extremes, int width, int height, lightType light);
	void onResize(float* extremes, int width, int height);
	void turnOnLights();
	void windowSettings();
	void turnOffLights();

	const sf::ContextSettings& getWindowSet() const;


private:
	void inicialise(float* extremes, int width, int height);
	GLfloat materialAmbient[4] = { 0.5f, 0.5f, 0.5f, 0.0f };
	GLfloat materialDiffuse[4] = { 0.8f, 0.4f, 0.4f, 0.0f };
	GLfloat materialShine[4] = { 0.8f, 0.4f, 0.4f, 0.0f };
	GLfloat materialShineFactor[1] = { 30.0f };
	GLfloat poziceSvetla[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	sf::ContextSettings windowSet;
	lightType light;
};


#endif //FVIZ_OBJ_SETTINGS_H