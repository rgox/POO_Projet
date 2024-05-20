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

			this->texture.loadFromFile("background.png");
			if (!texture.loadFromFile("background.png")) {
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
		sf::Font font;
		sf::Texture texture, texture3, texture4, texture5, texture6;
		sf::Sprite sprite, sprite3, sprite4, sprite5, sprite6;
		sf::Text VieP1, SpeedP1, DefenseP1, AttackP1;
		sf::Text VieP2, SpeedP2, DefenseP2, AttackP2;
		int nbPlayers;
		std::vector<Bonus> bonuses;
		int initialHealth1, initialHealth2;
		//Au cas où on décide de faire un jeu en 3 manches
		int P1Wins = 0;
    	int P2Wins = 0;
		
};

#endif // AFFICHE_HPP