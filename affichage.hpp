#ifndef AFFICHE_HPP
#define AFFICHE_HPP

#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Robot.hpp"
#include "sniper.hpp"
#include "Tank.hpp"
#include "Course.hpp"
#include "arene.hpp"
#include "bonus.hpp"

class Affiche {
	public:
	
		Affiche(Hexagone& hexagone)
		: hexagon(hexagone) {
			this->texture.loadFromFile("background.jpg");
			if (!texture.loadFromFile("background.jpg")) {
				// Gestion de l'erreur si le chargement de la texture échoue
				std::cout << "Erreur de chargement de l'image" << std::endl;
			}
			this->sprite.setTexture(texture);
			
		};

		
		bool refresh(sf::RenderWindow& window, sf::Time timePerMove, sf::Clock& clock, sf::Event& event,Robot& P1, Robot& P2);
		bool menu(sf::RenderWindow& window);
		int choose(sf::RenderWindow& window);
		bool fin= false;

	
    	void updateControls(Robot& P1,Robot& P2);
		int getNbPlayers() const { return nbPlayers; }

	private:
		Hexagone& hexagon;
		sf::Texture texture;
		sf::Sprite sprite;
		int nbPlayers=0;
		
};

#endif // AFFICHE_HPP