#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "Robot.hpp"

class Projectile { 
public:
	// Constructeur
    Projectile(float x, float y, float angle, float speed);

	//Getters
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;

	//Verifiers
	bool isOffScreen(const sf::RenderWindow& window) const;
	bool isTouchingBorder(const sf::RenderWindow& window) const;
	
	//Met à jour la position
    void update();

	//Dessine le projectile
    void draw(sf::RenderWindow& window);
    
    

private:

	//Forme du projectile
    sf::CircleShape shape;

	//Vitesse
    sf::Vector2f velocity;
};

#endif // PROJECTILE_HPP
