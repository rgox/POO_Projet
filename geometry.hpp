#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <SFML/Graphics.hpp>

struct LineSegment {
    sf::Vector2f p1;
    sf::Vector2f p2;
};

// Déclaration des fonctions
bool doLinesIntersect(const LineSegment& line1, const LineSegment& line2);
float crossProduct(const sf::Vector2f& a, const sf::Vector2f& b);
sf::Vector2f subtract(const sf::Vector2f& a, const sf::Vector2f& b);

#endif // GEOMETRY_HPP
