#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "Robot.hpp"

class Projectile {
public:
    Projectile(float x, float y, float angle, float speed);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isOffScreen(const sf::RenderWindow& window) const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

#endif // PROJECTILE_HPP
