#ifndef SNIPER_HPP
#define SNIPER_HPP

#include "Robot.hpp"

class Sniper : public Robot {
public:
	Sniper()
		:Robot(){
			health = 100;
            speed = 5;
			attackPower=50;
			defense=10;
	}
	Sniper& operator=( Sniper* other) ;
    Sniper(Hexagone& hex, float x, float y, char controlScheme, sf::Color color) :
        Robot(hex, x, y, controlScheme, color) {
            // Ajustez les attributs existants ici si nécessaire
            health = 100;
            speed = 5;
			attackPower=50;
			defense=10;
            // Initialisez d'autres nouveaux attributs ici si nécessaire
        }

	void draw(sf::RenderWindow& window)override;
	
private:
    
};

#endif // SNIPER_HPP
