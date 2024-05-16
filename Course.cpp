#include <algorithm>
#include <cmath>
#include "Course.hpp"
#include <cmath>

void Course::draw(sf::RenderWindow& window) {

	sf::Texture texture1;
    if (!texture1.loadFromFile("formula.png") ) {
        // Gestion de l'erreur si le chargement de la texture échoue
        printf("Problème chargement image Course");
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
}