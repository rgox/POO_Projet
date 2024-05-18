#ifndef TANK_HPP
#define TANK_HPP

#include "Robot.hpp"

class Tank : public Robot {
public:
    Tank(Hexagone& hex, float x, float y, char controlScheme, sf::Color color) :
        Robot(hex, x, y, controlScheme, color) {
            // Ajustez les attributs existants ici si nécessaire
            health = 200;
            speed = 2;
			attackPower=25;
			defense=40;
            // Initialisez d'autres nouveaux attributs ici si nécessaire
        }

	void draw(sf::RenderWindow& window)override  {

	sf::Texture texture1;
    if (!texture1.loadFromFile("truckcabin.png") ) {
        // Gestion de l'erreur si le chargement de la texture échoue
        printf("Problème chargement image Tank");
    }
	width=texture1.getSize().x*2;
	height=texture1.getSize().y*2;
	sf::Sprite sprite1;
	sprite1.setTexture(texture1);
	sprite1.setScale(2, 2);
	
	sprite1.setOrigin(width/4,height/4);
	sprite1.setPosition(position);
    sprite1.setRotation(orientation * 180 / M_PI);
    window.draw(sprite1);

	// Dessiner les points de débogage
    drawDebugPoints(window);
};
	
private:
    
};

#endif // TANK_HPP