#include <algorithm>
#include <cmath>
#include "Tank.hpp"
#include <cmath>

void Tank::draw(sf::RenderWindow& window) {

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
	

	sprite1.setPosition(position);
    sprite1.setRotation(orientation * 180 / M_PI);
    window.draw(sprite1);

	// Dessiner les points de débogage
    drawDebugPoints(window);
}