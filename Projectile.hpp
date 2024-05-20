#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdio>

class Projectile {
public:
    Projectile(float x, float y, float speed, float orientation);

    void update();
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    bool isOffScreen(const sf::RenderWindow& window) const;
    bool isTouchingBorder(const sf::RenderWindow& window) const;

private:
	float x, y, angle, speed;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
};

#endif // PROJECTILE_HPP
