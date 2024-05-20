#ifndef TANK_HPP
#define TANK_HPP

#include "Robot.hpp"

class Tank : public Robot {
public:
    Tank(Arene& hex, float x, float y, char controlScheme, sf::Color color) :
        Robot(hex, x, y, controlScheme, color) {
            
			// Nouveaux attributs

            health = 200;
            speed = 2;
			attackPower=25;
			defense=40;
            
        }

	//Définition de la fonction virtuelle draw

	void draw(sf::RenderWindow& window)override  ;
	
private:
    
};

#endif // TANK_HPP