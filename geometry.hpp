#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <SFML/Graphics.hpp>

struct LineSegment {
    sf::Vector2f p1;
    sf::Vector2f p2;
};

// Déclaration de la fonction
bool doLinesIntersect(const LineSegment& line1, const LineSegment& line2);

#endif // GEOMETRY_HPP
