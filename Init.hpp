#ifndef INIT_HPP
#define INIT_HPP

#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Robot.hpp"
#include "arene.hpp"
#include "bonus.hpp"
#include "InputBox.hpp"

class Init {
	public:
	
		Init() {
			this->texture.loadFromFile("background.jpg");
			if (!texture.loadFromFile("background.jpg")) {
				// Gestion de l'erreur si le chargement de la texture échoue
				std::cout << "Erreur de chargement de l'image" << std::endl;
			}
			this->sprite.setTexture(texture);
		};

		
		bool menu(sf::RenderWindow& window,int* i);
		bool choose(sf::RenderWindow& window,int* res);
		bool name(sf:: RenderWindow& window, char*& player1Name, char*& player2Name);
		bool fin= false;

	
		int getNbPlayers() const { return nbPlayers; }

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		int nbPlayers=0;
		
};

#endif // INIT_HPP