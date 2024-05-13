#include <SFML/Graphics.hpp>
#include <cstdlib> // Pour rand et srand
#include <ctime>   // Pour time
#include "bonus.hpp"
void Bonus::drawBonus(sf::RenderWindow& window) const{
        if (circleShape.getRadius() != 0) {
            window.draw(circleShape);
        } else if (rectangleShape.getSize() != sf::Vector2f(0, 0)) {
            window.draw(rectangleShape);
        } else {
            window.draw(triangleShape);
        }
    }