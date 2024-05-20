#ifndef AFFICHE_HPP
#define AFFICHE_HPP

#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Robot.hpp"
#include "arene.hpp"
#include "bonus.hpp"

class Affiche {
	public:
		//Constructeur
		Affiche(Arene& hexagone, Robot& rob1, Robot& rob2)
    : hexagon(hexagone), P1(rob1), P2(rob2) {

			this->texture.loadFromFile("background.jpg");
			if (!texture.loadFromFile("background.jpg")) {
				// Gestion de l'erreur si le chargement de la texture échoue
				std::cout << "Erreur de chargement de l'image" << std::endl;
			}
			this->sprite.setTexture(texture);
		};

		//Méthode refresh
		bool refresh(sf::RenderWindow& window, sf::Time timePerMove, sf::Clock& clock, sf::Event& event);
		
		//Getter du nombre de joueurs
		int getNbPlayers() const { return nbPlayers; }

		//Setter du nombre de joueurs
		void set_nbPlayers(int i){nbPlayers=i;}

		//Met à jour la position des robots
    	void updateControls(Robot& robot);

		//Permet d'afficher un message de fin lorsqu'un joueur meurt
		void showEndMessage(sf::RenderWindow& window, const std::string& winner);
		

	private:
		Arene& hexagon;
		
    	Robot& P1;
    	Robot& P2;

		sf::Texture texture;
		sf::Sprite sprite;
		int nbPlayers=0;
		std::vector<Bonus> bonuses;
		
		//Au cas où on décide de faire un jeu en 3 manches
		int P1Wins = 0;
    	int P2Wins = 0;
		
};

#endif // AFFICHE_HPP