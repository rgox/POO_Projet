#include "Tank.hpp"

//Définiion de la fonction virtuelle draw
void Tank::draw(sf::RenderWindow& window)  {

	sf::Texture texture1;
	 //Chargemnt de l'image
	if (!texture1.loadFromFile("truckcabin.png") ) {
		// Gestion de l'erreur si le chargement de la texture échoue
		printf("Problème chargement image Tank");
	}

	//Définitions des paramètres du personnage
	width=texture1.getSize().x*2;
	height=texture1.getSize().y*2;

	//Définition du sprite
	sf::Sprite sprite1;
	sprite1.setTexture(texture1);

	//On met à l'échelle
	sprite1.setScale(2, 2); 

	sprite1.setOrigin(width/4,height/4);
	sprite1.setPosition(position);
	sprite1.setRotation(orientation * 180 / M_PI);
	window.draw(sprite1);

	// Dessiner les points de débogage
	drawDebugPoints(window);
};