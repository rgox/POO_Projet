#ifndef SNIPER_HPP
#define SNIPER_HPP

#include "Robot.hpp"

class Sniper : public Robot {
public:
    Sniper(Arene& hex, float x, float y, char controlScheme, sf::Color color) :
        Robot(hex, x, y, controlScheme, color) {

			// Nouveaux attributs

            health = 100;
            speed = 5;
			attackPower=50;
			defense=10;
        }


	//Définition de la fonction virtuelle draw

	void draw(sf::RenderWindow& window)override;

private:
    
};

#endif // SNIPER_HPP
