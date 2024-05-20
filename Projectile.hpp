#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdio>

class Projectile {
public:
	// Constructeur
    Projectile(float x, float y, float speed, float orientation);
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
	float x, y, angle, speed;
	//Forme et texture du projectile
    sf::Texture texture;
    sf::Sprite sprite;
	//Vitesse
    sf::Vector2f velocity;
};

#endif // PROJECTILE_HPP
