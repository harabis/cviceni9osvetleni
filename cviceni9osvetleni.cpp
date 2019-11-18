
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <sstream>

#include "PLYformatreader.h"
using namespace std;


#include "Settings.h"
#include "DrawObject.h"
#include "Mouse.h"
#include "calculateNormals.h"
//#include "windows.h"




int main(int argc, char* argv[]) {
	cout << argv[0] << endl;
	lightType light = NormalVertex;
	PLYformatreader ply("ply/footbones.ply", light);
	Mouse m;
	// PO IMPLEMENTACII NORMALOVYCH VEKTOROV ODKOMENTOVAT!!
	calculateNormals norm(ply.getVertex(), ply.getFace(), ply.getVertexInFaceList());
	cout << "Vertex: " << ply.getVertexInFaceList().size() << endl;


	Settings s(ply.getExtremes(), 800, 800, light);

	sf::Window App(sf::VideoMode(800, 800), "OpenGLTriangle", sf::Style::Resize | sf::Style::Close, s.getWindowSet());
	s.onResize(ply.getExtremes(), 800, 800);
	DrawObject object;

	while (App.isOpen()) {
		sf::Event Event;
		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();
			if (Event.type == sf::Event::Resized) {
				s.onResize(ply.getExtremes(), Event.size.width, Event.size.height);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				App.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				sf::VideoMode v(sf::VideoMode::getFullscreenModes()[0]);
				App.create(sf::VideoMode(v), "OpenGLTriangle", sf::Style::Fullscreen);
				s.onResize(ply.getExtremes(), v.width, v.height);
				cout << v.height << "     " << v.width << endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if (light == None) {
					s.turnOnLights();
					light = NormalVertex;
				}
				else if (light == NormalFace) {
					s.turnOffLights();
					light = None;
				}
				else if (light == NormalVertex) {
					s.turnOnLights();
					light = NormalFace;

				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (Event.type == sf::Event::MouseButtonPressed) {
					m.setState(Mouse::State::Left);
					m.setXx(sf::Mouse::getPosition(App).x);
					m.setYy(sf::Mouse::getPosition(App).y);
				}
				m.onLeftButton(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (Event.type == sf::Event::MouseButtonPressed) {
					m.setState(Mouse::State::Right);
					m.setZz(sf::Mouse::getPosition(App).y);
				}
				m.onRightButton(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
			}

			if (Event.type == sf::Event::MouseButtonReleased) {
				if (m.getState() == Mouse::State::Left) {
					m.setXold(m.getXnew());
					m.setYold(m.getYnew());
				}
				else if (m.getState() == Mouse::State::Right) {
					m.setZold(m.getZnew());
				}
				m.setState(Mouse::State::None);
			}


		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		object.transformObject(m.getXnew(), m.getYnew(), m.getZnew());

		// PO IMPLEMENTACII OSVETLENIA ZAKOMENTOVAT NIZSIE DVA RIADKY!!
		//s.turnOffLights();
		//object.drawPLYobject(ply.getVertex(), ply.getFace());
		// PO IMLEMENTACII OSVETLENIA ODKOMENTOVAT!!!
		if (light == NormalFace) {
			object.drawPLYobject(ply.getVertex(), ply.getFace(), norm.getNormals(), light);
		}
		else if (light == NormalVertex) {
			//cout << "VerteNormal: " << norm.getVertexNormals().size() <<endl;
			object.drawPLYobject(ply.getVertex(), ply.getFace(), norm.getVertexNormals(), light);
		}
		else {
			object.drawPLYobject(ply.getVertex(), ply.getFace());
		}
		App.display();
	}






	cout << "Success" << endl;
	return 1;
}