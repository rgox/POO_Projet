#ifndef TANK_HPP
#define TANK_HPP

#include "Robot.hpp"

class Tank : public Robot {
public:
	Tank()
		:Robot(){
			health = 200;
            speed = 2;
			attackPower=25;
			defense=40;
	};
	Tank& operator=( Tank* other) ;
    Tank(Hexagone& hex, float x, float y, char controlScheme, sf::Color color) :
        Robot(hex, x, y, controlScheme, color) {
            // Ajustez les attributs existants ici si nécessaire
            health = 200;
            speed = 2;
			attackPower=25;
			defense=40;
            // Initialisez d'autres nouveaux attributs ici si nécessaire
        }

	void draw(sf::RenderWindow& window)override;
	
private:
};

#endif // TANK_HPP