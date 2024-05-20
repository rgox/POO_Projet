#include "Tank.hpp"

//Définiion de la fonction virtuelle draw
void Tank::draw(sf::RenderWindow& window) {
        sprite1.setPosition(position);
        sprite1.setRotation(orientation * 180 / M_PI);
        window.draw(sprite1);
    }