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
	
	sprite1.setOrigin(width/4,height/4);
	sprite1.setPosition(position);
    sprite1.setRotation(orientation * 180 / M_PI);
    window.draw(sprite1);

	// Dessiner les points de débogage
    drawDebugPoints(window);
}

Tank& Tank::operator=( Tank* other) {
    if (this != other) {
        //On copie chaque attribut de l'objet passé en argument
		hexagon=other->hexagon;
    	position=other->position;
    	health=other->health;       // Santé actuelle du robot
    	speed=other->speed;      // Vitesse de déplacement du robot
    	attackPower=other->attackPower;  // Puissance d'attaque
    	defense=other->defense;      // Capacité de défense
		lastPosX=other->lastPosX;
		lastPosY=other->lastPosY;
		rectangleShape=other->rectangleShape;
		controlScheme=other->controlScheme;  // 'A' pour les flèches, 'B' pour ZQSD
		color=other->color;
		width = other->width;   // Largeur du robot, à adapter selon votre setup
    	height = other->height;  // Hauteur du robot, à adapter selon votre setup
		lastValidPosition=other->lastValidPosition;
		orientation=other->orientation; // Angle en radians
        
    }
    return *this;
}


